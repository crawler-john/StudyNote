// !!--
// P. Soulard	Dec 2004	(Thanks to J. Martens who found the MAX_NUM_TIMERS limitation)
//		In original mmtimer.c (and thefore mmtimer.dll), MAX_NUM_TIMERS is defined to 16 which is too small
//		==> include this file (from WinCE Shared Source Distribution) in osBase
//		==> Redefined TDD_MAXPERIOD
//		==> Redefined MAX_NUM_TIMERS
//		==> Defined USE_GLOBAL_THREAD
//		==> Added field 'uFlags' in struct 'TIMER_DB' : was missing ????
//		==> Commented out DllMain() ; init is done in static object at load time (see osTime.cpp)
//
// P. Soulard & J. Martens	Feb 2005
//		==> Commented out code in timeSetEvent() which makes the id unique since this code leads to an interger overflow
//		when MAX_NUM_TIMERS is not a power of 2, and hence to a bug when timeKillEvent() tries to retrieve the timer slot
//		from the id with "% MAX_NUM_TIMERS" -> an other timer is deleted


#define USE_GLOBAL_THREAD

// --!!


//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this source code is subject to the terms of the Microsoft end-user
// license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
// If you did not accept the terms of the EULA, you are not authorized to use
// this source code. For a copy of the EULA, please see the LICENSE.RTF on your
// install media.
//

#define _WINMM_
#include <windows.h>
// !!--
#undef WINMMAPI
#define WINMMAPI
#pragma warning(push)
#pragma warning(disable:4273)
// --!!
#include <dbgapi.h>

#ifdef DEBUG
#define ZONE_ERROR			DEBUGZONE(0)	/* 0x0001 */
#define ZONE_WARNING		DEBUGZONE(1)	/* 0x0002 */
#define ZONE_DEBUG			DEBUGZONE(2)	/* 0x0004 */
#define ZONE_GETINFO		DEBUGZONE(3)	/* 0x0008 */
#define ZONE_ENTRY			DEBUGZONE(4)	/* 0x0010 */
#endif

#define TDD_MINRESOLUTION			55					// in milliseconds
#define TDD_MAXRESOLUTION			1					// in milliseconds

// !!--
//#define TDD_MAXPERIOD				1000000				// 1000 seconds
#define TDD_MAXPERIOD				1000000000			// 1000000 seconds
// --!!
#define TDD_MINPERIOD				TDD_MAXRESOLUTION
// !!--
//#define MAX_NUM_TIMERS				16
#define MAX_NUM_TIMERS				1000
// --!!

// !!--
#define DEFAULT_MMTIMER_PRIORITY	40
// --!!
#define DEFAULT_PRIORITY_TRUST		248
#define DEFAULT_PRIORITY			THREAD_PRIORITY_TIME_CRITICAL

#define LOCK_TIMERLIST()			EnterCriticalSection(&g_TimerCS)
#define UNLOCK_TIMERLIST()			LeaveCriticalSection(&g_TimerCS)

#define SET_THREAD_PRIORITY(h, p)	(*g_pfnSetThreadPriority)((h), (p))
#define GET_THREAD_PRIORITY(h)		(*g_pfnGetThreadPriority)((h))

#define MAX_PRIORITY_LEVELS   256
#define MAX_WIN32_PRIORITY_LEVELS   8
#define PRIORITY256_TO_8(p)         ((p) > (MAX_PRIORITY_LEVELS - MAX_WIN32_PRIORITY_LEVELS) ?  \
                                            (p) - (MAX_PRIORITY_LEVELS - MAX_WIN32_PRIORITY_LEVELS) : 0)


#define THREAD_PRIORITY_KEY         TEXT("SYSTEM\\MMTIMER")
#define THREAD_VALUE_NAME           TEXT("Priority256")

typedef struct TIMER_DB TIMER_DB, *LPTIMER_DB;
struct TIMER_DB {
	UINT uDelay;									// requested delay (ms)
	UINT uResolution;								// requested resolution (ms)
	LPTIMECALLBACK lpCallback;						// callback when timer due
	DWORD dwUser;									// user data passed to callback	UINT uFlags;									// timer option flags
	// !!--
	UINT  uFlags;
	// --!!
	UINT uId;										// time ID

	LARGE_INTEGER liFireTime;						// time it should fire
	BOOL bActive;									// timer is free or not

#ifdef USE_GLOBAL_THREAD
	LPTIMER_DB pNext;								// linked to next timer
	LPTIMER_DB pPrev;								// linked to previous timer
#else
	HANDLE hTimerThread;							// timer thread handle
#endif
};

// MMTimer globals
WORD g_PeriodSlots[TDD_MINRESOLUTION];				// count of what periods are set
TIMER_DB g_Timers[MAX_NUM_TIMERS];					//
HANDLE g_hTimerEvent = NULL;						// event for signal timer thread
DWORD g_dwThreadPriority = DEFAULT_PRIORITY;
DWORD g_dwMinResolution = TDD_MINRESOLUTION;
DWORD g_uCurrentPeriod = TDD_MINRESOLUTION;

// P. Soulard & J. Martens	Feb 2005
//DWORD g_dwTimerCount = 0;
DWORD g_dwTimerCount = MAX_NUM_TIMERS;

CRITICAL_SECTION g_ResCS;
CRITICAL_SECTION g_TimerCS;
int (*g_pfnGetThreadPriority)(HANDLE hThread);
BOOL (*g_pfnSetThreadPriority)(HANDLE hThread, int nPriority);


#ifdef USE_GLOBAL_THREAD
HANDLE g_hTimerThread = NULL;						// timer thread handle
LPTIMER_DB g_lpTimerList = NULL;
DWORD g_dwWaitTime = INFINITE;
BOOL g_bContinue = TRUE;
#endif


#ifdef DEBUG
DBGPARAM dpCurSettings = {
    TEXT("MMTIMER"), {
    TEXT("Error"),TEXT("Warning"),TEXT("Debug"),TEXT("GetInfo"),
    TEXT("Entry"),TEXT("UnDefined"),TEXT("UnDefined"),TEXT("UnDefined"),
    TEXT("UnDefined"),TEXT("UnDefined"),TEXT("UnDefined"),TEXT("UnDefined"),
    TEXT("UnDefined"),TEXT("UnDefined"),TEXT("UnDefined"),TEXT("UnDefined") },
    0x0003
};
#endif

UINT AllocateTimerDB(VOID)
{
	UINT i;
	LOCK_TIMERLIST();
	for (i=0; i< MAX_NUM_TIMERS; i++) {
		if (!g_Timers[i].uId && !g_Timers[i].bActive) {
			// set the slot to active to prevent re-allocate by other process
			g_Timers[i].bActive = TRUE;
			break;
		}
	}
	UNLOCK_TIMERLIST();
	return i;
}



VOID DeAllocTimerDB(LPTIMER_DB lpTimer)
{
	DEBUGCHK(lpTimer);
	DEBUGCHK(!lpTimer->bActive);
	DEBUGCHK(lpTimer->uId);
	lpTimer->uId = 0;
}



#ifdef USE_GLOBAL_THREAD
BOOL AddTimerDB(LPTIMER_DB lpTimer)
{
	LPTIMER_DB lpCurrent;
	BOOL bSignalEvent = FALSE;

	DEBUGCHK(lpTimer);

    LOCK_TIMERLIST();
    lpCurrent = g_lpTimerList;
	if (!lpCurrent) {
		// empty list, insert data block into list
		lpTimer->pNext = NULL;
		lpTimer->pPrev = NULL;
		g_lpTimerList = lpTimer;
		bSignalEvent = TRUE;
	} else {
		// non-empty list
        do {
            if (lpCurrent->liFireTime.QuadPart > lpTimer->liFireTime.QuadPart) {
                lpTimer->pNext = lpCurrent;
                lpTimer->pPrev = lpCurrent->pPrev;
                lpCurrent->pPrev = lpTimer;
                if (lpTimer->pPrev) {
                    lpTimer->pPrev->pNext = lpTimer;
                } else {
                    g_lpTimerList = lpTimer;
                    bSignalEvent = TRUE;
                }
                break;

            } else if (!lpCurrent->pNext) {
                // add into the end of list
                lpCurrent->pNext = lpTimer;
                lpTimer->pPrev = lpCurrent;
                lpTimer->pNext = NULL;
                break;
            }
        } while (lpCurrent = lpCurrent->pNext);
	}
    UNLOCK_TIMERLIST();
    return bSignalEvent;
}



BOOL RemoveTimerDB(LPTIMER_DB lpTimer)
{
	BOOL bResult = FALSE;

    LOCK_TIMERLIST();

	if (lpTimer->pNext)			// not last block in list
		lpTimer->pNext->pPrev = lpTimer->pPrev;
	if (lpTimer->pPrev)
		lpTimer->pPrev->pNext = lpTimer->pNext;
	else {
		g_lpTimerList = lpTimer->pNext;	// first block in list
		bResult = TRUE;
	}
    UNLOCK_TIMERLIST();
    return bResult;
}



//
// check whether we need to fire timer or update waiting time
//
// return TRUE if there is timer due
//
BOOL UpdateTimeOut()
{
    LPTIMER_DB lpTimer;
    LARGE_INTEGER liCurrTick;
    LONGLONG llDiff;
    BOOL bResult = FALSE;

    LOCK_TIMERLIST();
    while (g_lpTimerList) {
        lpTimer = g_lpTimerList;
        if (!lpTimer->bActive) {
        	RemoveTimerDB(lpTimer);
        	DeAllocTimerDB(lpTimer);
        	continue;
        }
        liCurrTick.QuadPart = (LONGLONG)GetTickCount();
        llDiff = lpTimer->liFireTime.QuadPart - liCurrTick.QuadPart;
        if ((lpTimer->liFireTime.QuadPart <= liCurrTick.QuadPart) ||
            llDiff < (LONGLONG)g_uCurrentPeriod) {
            bResult = TRUE;     // timer due
        }
        break;
    }
    if (g_lpTimerList)
    	g_dwWaitTime = (DWORD)llDiff;
    else
    	g_dwWaitTime = INFINITE;
    UNLOCK_TIMERLIST();
    return bResult;
}



//
// get first timer-node from list and fire it
//
static void ProcessTimer(void)
{
    LPTIMER_DB lpTimer;

    LOCK_TIMERLIST();
    lpTimer = g_lpTimerList;

    if (lpTimer) {
        switch (lpTimer->uFlags & TIME_CALLBACK_TYPEMASK) {
            case TIME_CALLBACK_FUNCTION:
                (*lpTimer->lpCallback)(lpTimer->uId, 0, lpTimer->dwUser, 0, 0);
                break;

            case TIME_CALLBACK_EVENT_SET:
                SetEvent((HANDLE)lpTimer->lpCallback);
                break;

            case TIME_CALLBACK_EVENT_PULSE:
                PulseEvent((HANDLE)lpTimer->lpCallback);
                break;

            default:
                // shouldn't reach here
                DEBUGMSG(TRUE, (TEXT("ProcessTimer: Invalid timer flag\r\n")));
                DEBUGCHK(FALSE);
                break;
        }
        // timer done, remove it from list
        RemoveTimerDB(lpTimer);

        // check whether timer had been killed or not
        if (lpTimer->bActive) {
        	// still alive
	        if (!(lpTimer->uFlags & TIME_PERIODIC)) {
    	        // one-shot timer, free it
    	        lpTimer->bActive = FALSE;
	            timeEndPeriod((DWORD)lpTimer->uResolution);	// clear resolution
    	        DeAllocTimerDB(lpTimer);                      // free the timer
        	} else {
            	// periodic timer, add it back to the right position
	            lpTimer->liFireTime.QuadPart += (LONGLONG)lpTimer->uDelay;
    	        // add it back to list
        	    AddTimerDB(lpTimer);
        	}
        } else {
        	// timer killed by others, we just need to free the timer node
        	DeAllocTimerDB(lpTimer);
        }
    }
    UNLOCK_TIMERLIST();
}



static DWORD WINAPI TimerThread(LPVOID lpParam)
{
	DWORD dwWait;

	while (g_bContinue) {
		dwWait = WaitForSingleObject(g_hTimerEvent, g_dwWaitTime);
		if (dwWait == WAIT_OBJECT_0) {
			// timer list status changed, maybe new timer is inserted at the head of list
			while (UpdateTimeOut())
				ProcessTimer();
		} else if (dwWait == WAIT_TIMEOUT) {
			// timer due, process it
			//ProcessTimer();
			while (UpdateTimeOut())
				ProcessTimer();
		}
	}
	return 0;
}
#else
static DWORD WINAPI TimerThread(LPVOID lpParam)
{
	UINT uTimerId = (UINT)lpParam;
	LPTIMER_DB lpTimer;
	LARGE_INTEGER liCurrTick;
	LONGLONG llDiff;

	DEBUGCHK(uTimerId);
	lpTimer = &g_Timers[uTimerId % MAX_NUM_TIMERS];
	while (lpTimer->uId == uTimerId && lpTimer->bActive) {
        liCurrTick.QuadPart = (LONGLONG)GetTickCount();
        llDiff = lpTimer->liFireTime.QuadPart - liCurrTick.QuadPart;
        if ((lpTimer->liFireTime.QuadPart <= liCurrTick.QuadPart) ||
            llDiff < (LONGLONG)g_uCurrentPeriod) {
            // timer due
	        switch (lpTimer->uFlags & TIME_CALLBACK_TYPEMASK) {
	            case TIME_CALLBACK_FUNCTION:
	                (*lpTimer->lpCallback)(lpTimer->uId, 0, lpTimer->dwUser, 0, 0);
	                break;

    	        case TIME_CALLBACK_EVENT_SET:
        	        SetEvent((HANDLE)lpTimer->lpCallback);
            	    break;

	            case TIME_CALLBACK_EVENT_PULSE:
    	            PulseEvent((HANDLE)lpTimer->lpCallback);
        	        break;

            	default:
                	// shouldn't reach here
	                DEBUGCHK(FALSE);
    	            break;
        	}

	        // check whether timer had been killed or not
	        if (lpTimer->bActive) {
    	    	// still alive
	    	    if (!(lpTimer->uFlags & TIME_PERIODIC)) {
    	    	    // one-shot timer, free it
    	        	lpTimer->bActive = FALSE;
		            timeEndPeriod((DWORD)lpTimer->uResolution);	// clear resolution
    		 	} else {
            		// periodic timer, update fire time
	            	lpTimer->liFireTime.QuadPart += (LONGLONG)lpTimer->uDelay;
        		}
	        }
        } else {
        	Sleep((DWORD)llDiff);
        }
	}
	DeAllocTimerDB(lpTimer);
	return 0;
}
#endif


BOOL InitializeTimerEngine(VOID)
{
	BOOL bResult = FALSE;
// !!--
//	LONG lStatus;
//	DWORD dwSize, dwValue, dwType;
//	HKEY hKey;
// --!!
	int i;

	if (!(g_hTimerEvent = CreateEvent(NULL, FALSE, FALSE, NULL)))
		goto exit;

// !!--
#if 0
	// check trust level, if it is trusted, we can set thread more higher
	if (CeGetCurrentTrust() == OEM_CERTIFY_TRUST) {
		g_pfnSetThreadPriority = CeSetThreadPriority;
		g_pfnGetThreadPriority = CeGetThreadPriority;
		g_dwThreadPriority = DEFAULT_PRIORITY_TRUST;
	} else {
		g_pfnSetThreadPriority = SetThreadPriority;
		g_pfnGetThreadPriority = GetThreadPriority;
		g_dwThreadPriority = DEFAULT_PRIORITY;
	}

	// look for thread priority in the registry
	lStatus = RegOpenKeyEx(HKEY_LOCAL_MACHINE, THREAD_PRIORITY_KEY, 0, 0, &hKey);
	if (lStatus == ERROR_SUCCESS) {
	    // get thread priority
	    dwSize = sizeof(dwValue);
	    lStatus = RegQueryValueEx(hKey, THREAD_VALUE_NAME, NULL, &dwType, (LPBYTE) &dwValue, &dwSize);
	    if (lStatus == ERROR_SUCCESS && dwType == REG_DWORD) {
	        if (g_pfnSetThreadPriority == SetThreadPriority) {
	            // non-trusted, convert priority256 to 8 level priority
    	        DEBUGMSG(ZONE_DEBUG, (TEXT("Non-Trusted Process, convert priority %d to %d-level \n"), dwValue, MAX_WIN32_PRIORITY_LEVELS));
	            dwValue = PRIORITY256_TO_8(dwValue);
	        }
	        DEBUGMSG(ZONE_DEBUG, (TEXT("Overwrite thread priority to %d\n"), dwValue));
	        g_dwThreadPriority = dwValue;
	    }
	    RegCloseKey(hKey);
	}
#endif
		g_pfnSetThreadPriority = CeSetThreadPriority;
		g_pfnGetThreadPriority = CeGetThreadPriority;
		g_dwThreadPriority = DEFAULT_MMTIMER_PRIORITY;
// --!!

#ifdef USE_GLOBAL_THREAD
	if (!(g_hTimerThread = CreateThread(NULL, 0, TimerThread, NULL, 0, NULL))) {
		CloseHandle(g_hTimerEvent);
		goto exit;
	}
	if (!SET_THREAD_PRIORITY(g_hTimerThread, g_dwThreadPriority))
		DEBUGCHK(FALSE);
#endif

	InitializeCriticalSection(&g_TimerCS);
	InitializeCriticalSection(&g_ResCS);
	for (i=0; i<TDD_MINRESOLUTION; i++)
		g_PeriodSlots[i] = 0;
	for (i=0; i< MAX_NUM_TIMERS; i++) {
		g_Timers[i].uId = 0;
		g_Timers[i].bActive = FALSE;
	}
	bResult = TRUE;

exit:
	return bResult;
}


#ifdef USE_GLOBAL_THREAD
VOID DeinitializeTimerEngine(VOID)
{
	LPTIMER_DB lpTimer, lpNextTimer;

	if (g_hTimerThread) {
		if (g_hTimerEvent) {
			// remove all timers in list
			LOCK_TIMERLIST();
			lpTimer = g_lpTimerList;
			while (lpTimer) {
				lpNextTimer = lpTimer->pNext;
				DeAllocTimerDB(lpTimer);
				lpTimer = lpNextTimer;
			}
			g_lpTimerList = NULL;
			g_dwWaitTime = INFINITE;
			UNLOCK_TIMERLIST();

			g_bContinue = FALSE;
			SetEvent(g_hTimerEvent);
			WaitForSingleObject(g_hTimerThread, INFINITE);

			CloseHandle(g_hTimerEvent);
			g_hTimerEvent = NULL;
		}
		CloseHandle(g_hTimerThread);
		g_hTimerThread = NULL;
		DeleteCriticalSection(&g_TimerCS);
		DeleteCriticalSection(&g_ResCS);
	}
}
#else
VOID DeinitializeTimerEngine(VOID)
{
	INT i;

	if (g_hTimerEvent) {
		// remove all timers in list
		LOCK_TIMERLIST();
		for (i=0; i<MAX_NUM_TIMERS; i++) {
			if (g_Timers[i].uId) {
				g_Timers[i].bActive = FALSE;
				DeAllocTimerDB(&g_Timers[i]);
			}
		}
		UNLOCK_TIMERLIST();
		CloseHandle(g_hTimerEvent);
		g_hTimerEvent = NULL;

		DeleteCriticalSection(&g_TimerCS);
		DeleteCriticalSection(&g_ResCS);
	}
}
#endif



WINMMAPI MMRESULT WINAPI timeSetEvent(UINT uDelay, UINT uResolution,
    LPTIMECALLBACK fptc, DWORD dwUser, UINT fuEvent)
{
	LPTIMER_DB lpTimer;
	UINT uIdx;
	DWORD dwTimerId;
	INT nCurrPrio256;


	// check input flags
	if ((fuEvent & ~TIME_CALLBACK_TYPEMASK) & ~(TIME_ONESHOT | TIME_PERIODIC))
	{
		return 0L;
	}

	// verify period parameter
	if (uDelay > TDD_MAXPERIOD || uDelay < TDD_MINPERIOD)
	{
		return 0L;
	}

	// this API will try to insert timer into timer list, we need to set it's priority
	// the same as timer thread, otherwise it may have no chance to set new timer
//_inline HANDLE GetCurrentThread(void) {
//	return ((HANDLE)(SH_CURTHREAD+SYS_HANDLE_BASE));

//	nCurrPrio256 = GET_THREAD_PRIORITY(GetCurrentThread());
	nCurrPrio256 = GET_THREAD_PRIORITY((HANDLE)(SH_CURTHREAD+SYS_HANDLE_BASE));

	SET_THREAD_PRIORITY(GetCurrentThread(), g_dwThreadPriority);

	// if resolution is 0, set it to default, otherwise make sure it is in range
	if (uResolution > g_dwMinResolution)
		uResolution = g_dwMinResolution;
	else if (uResolution < TDD_MAXRESOLUTION)
		uResolution = TDD_MAXRESOLUTION;

	if (uResolution > uDelay)
		uResolution = g_dwMinResolution;

	// set up period to be used
	if (timeBeginPeriod(uResolution) == MMSYSERR_NOERROR) {

		LOCK_TIMERLIST();
		uIdx = AllocateTimerDB();
		if (uIdx != MAX_NUM_TIMERS) {
			lpTimer = &g_Timers[uIdx];
			lpTimer->uDelay = uDelay;
			lpTimer->uResolution = uResolution;
			lpTimer->lpCallback = fptc;
			lpTimer->dwUser = dwUser;
			lpTimer->uFlags = fuEvent;
			lpTimer->bActive = TRUE;

			/**
			P. Soulard & J. Martens	Feb 2005
			These instructions make the id unique but after some long time the id (int => 2^32) overflows
			=> Pb with timeKillEvent() which cancels a bad id due to '% MAX_NUM_TIMERS' :
				lpTimer = &g_Timers[uTimerId % MAX_NUM_TIMERS];
			=> comment out these instructions

			do {
				g_dwTimerCount += MAX_NUM_TIMERS;
			} while (g_dwTimerCount == 0);
			**/
			dwTimerId = lpTimer->uId = g_dwTimerCount + uIdx;

			lpTimer->liFireTime.QuadPart = (LONGLONG)(GetTickCount() + uDelay);
#ifdef USE_GLOBAL_THREAD
			if (AddTimerDB(lpTimer)) {
				SetEvent(g_hTimerEvent);			// we are the first timer in list
			}
#else
			if (!(lpTimer->hTimerThread = CreateThread(NULL, 0, TimerThread, (LPVOID)dwTimerId, 0, NULL))) {
				lpTimer->bActive = FALSE;
				DeAllocTimerDB(lpTimer);
				dwTimerId = 0;
			}
			if (!SET_THREAD_PRIORITY(lpTimer->hTimerThread, g_dwThreadPriority))
				DEBUGCHK(FALSE);
			// TODO: Wait for thread begin here
#endif
		} else {
			dwTimerId = 0;							// no free slot right now
		}
		UNLOCK_TIMERLIST();

		// if we don't get a good id, give up
		if (dwTimerId == 0)
			timeEndPeriod(uResolution);
	} else {
		dwTimerId = 0L;
	}

	// restore thread priority back to its original value
	SET_THREAD_PRIORITY(GetCurrentThread(), nCurrPrio256);
	return dwTimerId;

}



WINMMAPI MMRESULT WINAPI timeKillEvent(UINT uTimerId)
{
	MMRESULT dwResult = MMSYSERR_INVALPARAM;
	UINT uResolution;
	LPTIMER_DB lpTimer;
	INT nCurrPrio256;
#ifdef USE_GLOBAL_THREAD
	BOOL bReschedule = FALSE;
#else
	HANDLE hTimerThread;
#endif

	if (!uTimerId)
		return MMSYSERR_INVALPARAM;

	// this API will try to access timer in timer list, we need to set it's priority
	// the same as timer thread, otherwise it may have no chance to access the timer
	nCurrPrio256 = GET_THREAD_PRIORITY(GetCurrentThread());
	SET_THREAD_PRIORITY(GetCurrentThread(), g_dwThreadPriority);

	lpTimer = &g_Timers[uTimerId % MAX_NUM_TIMERS];
	LOCK_TIMERLIST();
	if (lpTimer->uId == uTimerId && lpTimer->bActive) {
#ifdef USE_GLOBAL_THREAD
		// if the timer is at the head oflist, we need to adjust our waiting habits
		if (lpTimer == g_lpTimerList)
			bReschedule = TRUE;
#else
		DEBUGCHK(lpTimer->hTimerThread);
		hTimerThread = lpTimer->hTimerThread;
#endif
		lpTimer->bActive = FALSE;
		uResolution = lpTimer->uResolution;
		dwResult = TIMERR_NOERROR;
	}
	UNLOCK_TIMERLIST();

	if (dwResult == TIMERR_NOERROR) {
		timeEndPeriod(uResolution);
#ifdef USE_GLOBAL_THREAD
		if (bReschedule)
			SetEvent(g_hTimerEvent);
#else
		CloseHandle(hTimerThread);
#endif
	}

	// restore thread priority back to its original value
	SET_THREAD_PRIORITY(GetCurrentThread(), nCurrPrio256);
	return dwResult;
}



WINMMAPI MMRESULT WINAPI timeBeginPeriod(UINT uPeriod)
{
	// check period range
	if (uPeriod < TDD_MAXRESOLUTION)
		return TIMERR_NOCANDO;

	if( uPeriod >= g_dwMinResolution)
		return TIMERR_NOERROR;				// we can do it with min-resolution

	//
	// period fall into the range of min- and max-resolution, do the bookkeeping
	//
	EnterCriticalSection(&g_ResCS);
	// see what happen in our slots
	if (g_PeriodSlots[uPeriod - TDD_MAXRESOLUTION]== 0xffff) {
		// overflow
		LeaveCriticalSection(&g_ResCS);
		return TIMERR_NOCANDO;
	}

	g_PeriodSlots[uPeriod - TDD_MAXRESOLUTION]++;

	if (g_PeriodSlots[uPeriod - TDD_MAXRESOLUTION] == 1 && uPeriod < g_uCurrentPeriod) {
		// min resolution changed
		g_uCurrentPeriod = uPeriod;
	}
	LeaveCriticalSection(&g_ResCS);
	return MMSYSERR_NOERROR;
}



WINMMAPI MMRESULT WINAPI timeEndPeriod(UINT uPeriod)
{
	UINT uNewPeriod;

	// check period range
	if (uPeriod < TDD_MAXRESOLUTION)
		return TIMERR_NOCANDO;

	if( uPeriod >= g_dwMinResolution)
		return TIMERR_NOERROR;				// we can do it with min-resolution

	//
	// period fall into the range of min- and max-resolution, do the bookkeeping
	//
	EnterCriticalSection(&g_ResCS);

	if (g_PeriodSlots[uPeriod - TDD_MAXRESOLUTION] == 0) {
		// overflow
		LeaveCriticalSection(&g_ResCS);
		return TIMERR_NOCANDO;
	}

	g_PeriodSlots[uPeriod - TDD_MAXRESOLUTION]--;

	if (g_PeriodSlots[uPeriod - TDD_MAXRESOLUTION] == 0 && uPeriod == g_uCurrentPeriod) {
		// the slot is just finished and was the fastest, so find the next fastest one
		for (uNewPeriod = uPeriod; uNewPeriod < g_dwMinResolution; uNewPeriod++) {
			if(g_PeriodSlots[uNewPeriod - TDD_MAXRESOLUTION] != 0)
				break;
		}

		// set the new resolution
		g_uCurrentPeriod = uNewPeriod;
	}

	LeaveCriticalSection(&g_ResCS);
	return TIMERR_NOERROR;
}



WINMMAPI MMRESULT WINAPI timeGetDevCaps(LPTIMECAPS ptc, UINT cbtc)
{
	if (!ptc || cbtc < sizeof(TIMECAPS))
		return TIMERR_STRUCT;
	ptc->wPeriodMin = TDD_MINPERIOD;
	ptc->wPeriodMax = TDD_MAXPERIOD;
	return MMSYSERR_NOERROR;
}



WINMMAPI DWORD WINAPI timeGetTime(void)
{
    return GetTickCount();			// wrap to GetTickCount
}



WINMMAPI DWORD WINAPI timeGetTimeSinceInterrupt(void)
{
	return 0xFFFFFFFF;
}



WINMMAPI DWORD WINAPI timeGetHardwareFrequency(void)
{
	LARGE_INTEGER liFreq;
	if (QueryPerformanceFrequency(&liFreq))
		return liFreq.LowPart;
	return 0;
}


// !!--
#if 0
BOOL WINAPI DllMain(HANDLE hinstDLL, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason) {
		case DLL_PROCESS_ATTACH:
			DEBUGREGISTER(hinstDLL);
			DisableThreadLibraryCalls((HMODULE) hinstDLL);
			return InitializeTimerEngine();

		case DLL_PROCESS_DETACH:
            // don't call DeinitializeTimerEngine(), let OS do the clean up for us.
			//DeinitializeTimerEngine();
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
	}
	return TRUE;
}
#endif
// --!!

// !!--
#pragma warning(pop)
// --!!

