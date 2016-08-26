/*****************************************************************************/
/*                                                                           */
/*    Copyright (C) - LEGATE Intelligent Equipment - All rights reserved     */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*  Except if expressly provided in a dedicated License Agreement, you are   */
/*  not authorized to:                                                       */
/*                                                                           */
/*  1. Use, copy, modify or transfer this software component, module or      */
/*  product, including any accompanying electronic or paper documentation    */
/*  (together, the "Software").                                              */
/*                                                                           */
/*  2. Remove any product identification, copyright, proprietary notices or  */
/*  labels from the Software.                                                */
/*                                                                           */
/*  3. Modify, reverse engineer, decompile, disassemble or otherwise attempt */
/*  to reconstruct or discover the source code, or any parts of it, from the */
/*  binaries of the Software.                                                */
/*                                                                           */
/*  4. Create derivative works based on the Software (e.g. incorporating the */
/*  Software in another software or commercial product or service without a  */
/*  proper license).                                                         */
/*                                                                           */
/*  By installing or using the "Software", you confirm your acceptance of the*/
/*  hereabove terms and conditions.                                          */
/*                                                                           */
/*****************************************************************************/


/*****************************************************************************/
/*  History:                                                                 */
/*****************************************************************************/
/*  Date       * Author          * Changes                                   */
/*****************************************************************************/
/*  2011-10-18 * Ricky Gong      * Creation of the file                      */
/*  2012-12-18 * Ricky Gong      * Added Linux implementations               */
/*             *                 *                                           */
/*****************************************************************************/


/*****************************************************************************/
/*                                                                           */
/*  Include Files                                                            */
/*                                                                           */
/*****************************************************************************/
#include "timer.h"
#if defined(_WIN32)
#if defined(UNDER_CE)
#include "wcemmtimer.c"
#endif
#elif defined(__linux)
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "timemath.h"
#endif


/*****************************************************************************/
/*                                                                           */
/*  Definitions                                                              */
/*                                                                           */
/*****************************************************************************/
#if defined(_WIN32)
#if defined(UNDER_CE)
static class CInitWceTimers
{
    public:

        /*********************************************************************/
        /*                     Constructor & Destructor                      */
        /*********************************************************************/
        CInitWceTimers()
        {
            InitializeTimerEngine();

            TIMECAPS    tc;
            if (::timeGetDevCaps(&tc,sizeof(TIMECAPS)) != TIMERR_NOERROR)
            {
                ASSERT(false);
            }
            CTimer::s_resolution = min(max(tc.wPeriodMin, 1), tc.wPeriodMax);

            if (::timeBeginPeriod(CTimer::s_resolution) != TIMERR_NOERROR)
            {
                ASSERT(false);
            }
        }

        ~CInitWceTimers()
        {
            if (::timeEndPeriod(CTimer::s_resolution) != TIMERR_NOERROR)
            {
                ASSERT(false);
            }

            DeinitializeTimerEngine();
        }


        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/


        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/


    private:

        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/


        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/


    protected:

        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/


        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/


} _initWceTimersAtLoadTime;
#endif
#endif


/*****************************************************************************/
/*                                                                           */
/*  Variable Declarations                                                    */
/*                                                                           */
/*****************************************************************************/
// declare single instance of common thread
DECLARE_SINGLE_INST(CCommonThreadedTimersThread);

#if defined(_WIN32)
#if !defined(UNDER_CE)
DECLARE_SINGLE_INST(CTimersInterruptEmulationThread);

#else

unsigned long CTimer::s_resolution;
#endif

#elif defined(__linux)

DECLARE_SINGLE_INST(CTimersInterruptEmulationThread);

#endif


/*****************************************************************************/
/*                                                                           */
/*  Function Implementations                                                 */
/*                                                                           */
/*****************************************************************************/
CTimer::CEvtTimerHasExpired::CEvtTimerHasExpired()
{
}

CTimer::CEvtTimerHasExpired::~CEvtTimerHasExpired()
{
}

CTimer::CTimer(EMode mode,
               const char* pThreadName,
               size_t threadStackSize,
               int threadPriority,
               int threadAttributes)
    : 
#if defined(_WIN32)
#if !defined(UNDER_CE)
      m_id(CreateWaitableTimer(0, true, 0)),
#else
      m_id(0),
#endif
#endif
      m_mode(mode),
      m_isRunning(false),
      m_hasExpired(false),
      m_timeout(0),
      m_repetitive(false),
      m_pThread(NULL),
      m_expired(),
      m_stopRequest(false),
      m_pCondMutex(NULL),
      m_pCommonThreadedCond(NULL),
      m_commonThreadedTimeoutsInProgress(0)
{
#if !defined(_WIN32)
    if(clock_gettime(CLOCK_REALTIME, &l_tvStart) != 0)
    {
        printf("clock_gettime: %s\n", strerror(errno));
        ASSERT(false);
        return;
    }
#endif
    initInstance(mode, pThreadName, threadStackSize, 
                 threadPriority, threadAttributes);
}

void CTimer::initInstance(EMode mode,
                          const char* pThreadName,
                          size_t threadStackSize,
                          int threadPriority,
                          int threadAttributes)
{
    m_mode = mode;

    switch(mode)
    {
        case UNTHREADED:
        {
            // Nothing to do
        }
        break;

        case THREADED:
        {
            declare(CEvtTimerHasExpired());

            m_pThread = new CThread(this, 
                                    (pThreadName) ? pThreadName : "ThreadTimer",
                                    (threadStackSize) ? threadStackSize : 10000,
                                    (threadPriority) ? threadPriority : THREAD_VERY_HIGH_PRIORITY,
                                    (threadAttributes) ? threadAttributes : 0);

            m_pThread->start();
        }
        break;

        case COMMON_THREADED:
        {
            declare(CEvtTimerHasExpired());

            // Explicitly create condition for COMMON_THREADED timers
            m_pCondMutex = new CMutex;
            m_pCommonThreadedCond = new CCondition(*m_pCondMutex);

            m_pThread = &TheCommonThreadedTimersThread;
        }
        break;

        default:
        {
            ASSERT(false);
        }
        break;
    }
}

CTimer::~CTimer()
{
    cancel();

#if defined(_WIN32)
#if !defined(UNDER_CE)
	if (!CloseHandle(m_id))
	{
		ASSERT(false);
	}
#endif
#endif

    switch(m_mode)
    {
        case UNTHREADED:
        {
            // Nothing to do
        }
        break;

        case THREADED:
        {
            delete m_pThread;
        }
        break;

        case COMMON_THREADED:
        {
            // Note: the OS timer is deleted at this stage => no new 
            // timeout interrupt
            // just synchronize with TheCommonThreadedTimersThread (wait 
            // for all timeouts are executed)
            CLock condAccess(*m_pCondMutex);

            while(m_commonThreadedTimeoutsInProgress != 0)
            {
                bool status = m_pCommonThreadedCond->wait(5000);
                ASSERT(status == true);
                // Pacify the compiler if NDEBUG set
                status = status;
            }
        }
        delete m_pCommonThreadedCond;
        delete m_pCondMutex;
        break;

        default:
        {
            ASSERT(false);
        }
        break;
    }
}

bool CTimer::start(unsigned long timeout, bool repetitive)
{
#if defined(_WIN32)
#if defined(UNDER_CE)
    if (timeout == 0)
    {
        m_isRunning = false;
        m_hasExpired = true;
        this->timeout();
        return true;
    }
    else 
#endif
#endif
    if (timeout == TIME_INFINITE)
    {
        return true;
    }

    cancel();
    m_hasExpired = false;

    m_repetitive = repetitive;

    return start_(timeout);
}

bool CTimer::start_(unsigned long timeout)
{
    m_timeout = timeout;

    m_isRunning = true;

    // Note : can't use m_isRunning to check if the timer is started, since the 
    // timer may timeout
    // just after the OS call (=> m_isRunning reset to false) before the end if 
    // this method
    bool isStarted;

#if defined(_WIN32)
#if !defined(UNDER_CE)
    TheTimersInterruptEmulationThread.startTimer(this);
    isStarted = true;
#else
    m_id = ::timeSetEvent(timeout, s_resolution, timeoutWrapper_, (DWORD)this,
                          (m_repetitive ? TIME_PERIODIC : TIME_ONESHOT) 
                          | TIME_CALLBACK_FUNCTION);

    isStarted = (m_id != 0);
#endif

#elif defined(__linux)
    TheTimersInterruptEmulationThread.startTimer(this);
    isStarted = true;
#endif

    ASSERT(isStarted);

    if (!isStarted)
    {
        m_isRunning = false;
    }

    return isStarted;
}

bool CTimer::restart()
{
#if defined(_WIN32)
#if defined(UNDER_CE)
    if (m_timeout == 0)
    {
        m_isRunning = false;
        m_hasExpired = true;
        this->timeout();
        return true;
    }
#endif
#endif

    return start(m_timeout, m_repetitive);
}

void CTimer::cancel()
{
    // first to cancel the emulation thread related timer to avoid wrong timeout 
    // because of time out value changed to 0 in this function
#if defined(_WIN32)
#if !defined(UNDER_CE)
	CancelWaitableTimer(m_id);
#else
    if(m_id)
    {
        // <=== the timer may time out here ==>
        if (::timeKillEvent(m_id) != TIMERR_NOERROR)
        {
            if (m_id != 0)
            {
                ASSERT(false);
            }
            //else the timer has timed out before ::timeKillEvent() call
        }
        m_id = 0;
    }
#endif
#elif defined(__linux)
    TheTimersInterruptEmulationThread.cancelTimer(this);
#endif

    m_isRunning = false;
    m_timeout = 0;
    m_repetitive = false;
}

bool CTimer::isRunning() const
{
    return m_isRunning;
}

bool CTimer::hasExpired() const
{
    return m_hasExpired;
}

int CTimer::run()
{
    CEvtTimerHasExpired evt;
    while (true)
    {
        m_expired.take();
        if (m_stopRequest)
        {
            break;
        }

        notify(evt);
        timeout();
    }

    return CThread::SUCCESS;
}

void CTimer::stop()
{
    m_stopRequest = true;
    if (m_mode == THREADED)
    {
        m_expired.release();
    }
}

#if defined(_WIN32)
#if !defined(UNDER_CE)
void CALLBACK CTimer::timeoutWrapper_(LPVOID _this_, DWORD dwTimerLowValue,
                                      DWORD dwTimerHighValue)
{
    reinterpret_cast<CTimer*>(_this_)->timeoutWrapper();
}

#else

void CALLBACK CTimer::timeoutWrapper_(UINT uID, UINT uReservedMsg, DWORD _this_, 
                                      DWORD dwReserved1, DWORD dwReserved2)

{
    reinterpret_cast<CTimer*>(_this_)->timeoutWrapper();
}
#endif
#endif

void CTimer::timeoutWrapper()
{
    if(m_repetitive)
    {
    }
    else
    {
        m_isRunning = false;
        m_hasExpired = true;
    #if defined(_WIN32)
    #if defined(UNDER_CE)
        m_id = 0;
    #endif
    #endif
    }

    switch(m_mode)
    {
        case UNTHREADED:
        {
            timeout();
        }
        break;

        case THREADED:
        {
            m_expired.release();
        }
        break;

        case COMMON_THREADED:
        {
            if(static_cast<CCommonThreadedTimersThread*>(m_pThread)->timeout(this))
            {
                CLock   condAccess(*m_pCondMutex);

                m_commonThreadedTimeoutsInProgress++;
            }
        }
        break;

        default:
        {
            // Should not happen
            ASSERT(false);
        }
        break;
    }
}

void CTimer::commonThreadedTimeout()
{
    notify(CEvtTimerHasExpired());
    timeout();

    CLock condAccess(*m_pCondMutex);

    m_commonThreadedTimeoutsInProgress--;
    m_pCommonThreadedCond->signal();
}

void CTimer::timeout()
{
}

#if defined(_WIN32)
#if !defined(UNDER_CE)
CTimersInterruptEmulationThread::CTimersInterruptEmulationThread()
    : CThread(),
      m_pTimer(NULL),
      m_hStartTimerSem(CreateSemaphore(0, 0, 1, 0)),
      m_hTimerStartedSem(CreateSemaphore(0, 0, 1, 0)),
      m_stopRequest(false),
      m_startSync()
{
    CThread::initInstance("TimersIntptEmul", 10000, THREAD_VERY_HIGH_PRIORITY);

    start();
    m_startSync.wait();
}

CTimersInterruptEmulationThread::~CTimersInterruptEmulationThread()
{
    stop();
    join();
    CloseHandle(m_hStartTimerSem);
    CloseHandle(m_hTimerStartedSem);
}

void CTimersInterruptEmulationThread::startTimer(CTimer* pTimer)
{
    THREAD_SAFE

    m_pTimer = pTimer;
    ReleaseSemaphore(m_hStartTimerSem, 1, 0);
    WaitForSingleObject(m_hTimerStartedSem, INFINITE);
}

int CTimersInterruptEmulationThread::run()
{
    m_startSync.signal();

    while(!m_stopRequest)
    {
        // How it works ?
        //  0. thread waiting in WaitForSingleObjectEx()
        //
        //  1. thread exits from WaitForSingleObjectEx() because startTimer() signaled m_hStartTimerSem
        //          => continue and calls SetWaitableTimer() with timeoutWrapper_ APC
        //  2. thread calls WaitForSingleObjectEx() with bAlertable parameter set to true
        //          => can execute APC when timer is signaled (timeout has elapsed)
        //          => remains waiting in WaitForSingleObjectEx()
        //  goto step 1.

        // Note : if a timer elapsed when the thread is not in alertable mode (has exited from WaitForSingleObjectEx())
        //        the APC is enqueued so it will be executed the next time the thread enters in alertable mode

        if (WaitForSingleObjectEx(m_hStartTimerSem, INFINITE, true) 
            == WAIT_OBJECT_0)
        {
            if (!m_stopRequest)
            {
                __int64         tmp;
                LARGE_INTEGER   timeout;

                tmp = m_pTimer->m_timeout;
                tmp *= -10000;      // 100 nanoseconds unit ; negative value to be relative timeout from now
                timeout.LowPart = (DWORD)(tmp & 0xFFFFFFFF);
                timeout.HighPart = (LONG)(tmp >> 32);
                SetWaitableTimer(m_pTimer->m_id, &timeout,
                                 m_pTimer->m_repetitive ? m_pTimer->m_timeout : 0,
                                 CTimer::timeoutWrapper_,
                                 reinterpret_cast<LPVOID>(m_pTimer),
                                 false);
                ReleaseSemaphore(m_hTimerStartedSem, 1, 0);
            }
        }

    }

    return STOPPED;
}

void CTimersInterruptEmulationThread::stop()
{
    m_stopRequest = true;
    ReleaseSemaphore(m_hStartTimerSem, 1, 0);
}
#endif

#elif defined(__linux)

CTimersInterruptEmulationThread::CTimersInterruptEmulationThread()
    : CThread(),
      m_stopRequest(false),
      m_startSync(),
      m_waitSem(),
      m_checkSem(),
      m_threadSafeMutex(),
      m_cTimers()
{
    if(sem_init(&m_waitSem, 0, 0) != 0)
    {
        printf("sem_init: %s\n", strerror(errno));
        ASSERT(false);
    }

    CThread::initInstance("TimersIntptEmul", 10000, THREAD_VERY_HIGH_PRIORITY);

    start();
    m_startSync.wait();
}

CTimersInterruptEmulationThread::~CTimersInterruptEmulationThread()
{
    stop();
    join();

    if(sem_destroy(&m_waitSem) != 0)
    {
        printf("sem_destroy: %s\n", strerror(errno));
        ASSERT(false);
    }
}

void CTimersInterruptEmulationThread::startTimer(CTimer* pTimer)
{
    size_t timerCnt = 0;
    m_threadSafeMutex.take();

    timerCnt = m_cTimers.size();

    // initialise start time in us
    if(clock_gettime(CLOCK_REALTIME, &(pTimer->l_tvStart)) != 0)
    {
        printf("clock_gettime: %s\n", strerror(errno));
        ASSERT(false);
        return;
    }

    for(std::list<CTimer *>::iterator it = m_cTimers.begin(); it != m_cTimers.end(); ++it)
    {
        if(*it == pTimer)
        {
            m_threadSafeMutex.release();
            return;
        }
    }
    m_cTimers.push_back(pTimer);

    m_threadSafeMutex.release();

    // if it's the first timer in list, inform to start timeout process
    if(timerCnt <= 0)
        m_checkSem.release();
    if(sem_post(&m_waitSem) != 0)
    {
        printf("sem_post: %s\n", strerror(errno));
        ASSERT(false);
    }
}

void CTimersInterruptEmulationThread::cancelTimer(CTimer* pTimer)
{
    m_threadSafeMutex.take();

    for(std::list<CTimer *>::iterator it = m_cTimers.begin(); it != m_cTimers.end(); ++it)
    {
        if(*it == pTimer)
        {
            m_cTimers.remove(pTimer);
            m_threadSafeMutex.release();
            if(sem_post(&m_waitSem) != 0)
            {
                printf("sem_post: %s\n", strerror(errno));
                ASSERT(false);
            }
            return;
        }
    }
    m_threadSafeMutex.release();
}

int CTimersInterruptEmulationThread::run()
{
    timespec m_lMinSleep;
    timespec zeroTimeSt = sec_nsec_to_timespec(0L, 0L);

    m_startSync.signal();

    while(!m_stopRequest)
    {
        m_threadSafeMutex.take();
        if(m_cTimers.size() > 0)
        {
            m_threadSafeMutex.release();

            m_lMinSleep = sec_nsec_to_timespec(TIME_INFINITE, 0);
            timespec l_lMin = sec_nsec_to_timespec(TIME_INFINITE, 0);

            m_threadSafeMutex.take();

            for(std::list<CTimer *>::iterator it = m_cTimers.begin(); it != m_cTimers.end(); ++it)
            {
                CTimer *pt = *it;

                timespec l_tv;
                if(clock_gettime(CLOCK_REALTIME, &l_tv) != 0)
                {
                    printf("clock_gettime: %s\n", strerror(errno));
                    ASSERT(false);
                    return ASSERTION_FAILED;
                }

                timespec l_tvElapsed = timespec_sub(l_tv, (pt->l_tvStart));
                timespec l_tvTimeout = sec_nsec_to_timespec(pt->m_timeout / MSEC_PER_SEC, 
                                                            (pt->m_timeout % MSEC_PER_SEC) * NSEC_PER_MSEC);
                // If time passed is greater than or equal to timeout: THEN
                if(timespec_compare(&l_tvElapsed, &l_tvTimeout) >= 0)
                {
                    // continue with the next timeout
                    if(pt->m_repetitive)
                    {
                        // time before invoking timeout wrapper function is the 
                        // start time of next timeout
                        pt->l_tvStart = timespec_to_timespec(l_tv);
                    }

                    // timeout function
                    pt->timeoutWrapper();

                    // continue with the next timeout
                    if(pt->m_repetitive)
                    {
                        if(clock_gettime(CLOCK_REALTIME, &l_tv) != 0)
                        {
                            printf("clock_gettime: %s\n", strerror(errno));
                            ASSERT(false);
                            return ASSERTION_FAILED;
                        }
                        // The minimum for this timer = timeout value - time elasped invoking timeout wrapper
                        timespec tmp = timespec_sub(l_tv, pt->l_tvStart);
                        l_lMin = timespec_sub(l_tvTimeout, tmp);
                    }
                    else
                    {
                        l_lMin = sec_nsec_to_timespec(TIME_INFINITE, 0);

                        // move to the next item firstly to avoid list linkage lost
                        it++;
                        // remove the timer 
                        m_cTimers.remove(pt);
                    }
                }
                else
                {
                    l_lMin = timespec_sub(l_tvTimeout, l_tvElapsed);
                }
                // Find the actual minumum time you can sleep to not lock
                if((timespec_compare(&m_lMinSleep, &zeroTimeSt) > 0) 
                    && (timespec_compare(&l_lMin, &zeroTimeSt) > 0))
                {
                    m_lMinSleep = timespec_min(m_lMinSleep, l_lMin);
                }
                else if((timespec_compare(&l_lMin, &zeroTimeSt) > 0))
                {
                    m_lMinSleep = timespec_to_timespec(l_lMin);
                }
            }
            m_threadSafeMutex.release();
            // sleep for the minimun time that can sleep
            if((timespec_compare(&m_lMinSleep, &zeroTimeSt) > 0))
            {
                timespec l_tv;
                if(clock_gettime(CLOCK_REALTIME, &l_tv) != 0)
                {
                    printf("clock_gettime: %s\n", strerror(errno));
                    ASSERT(false);
                    return ASSERTION_FAILED;
                }

                l_tv = timespec_add(l_tv, m_lMinSleep);
                int status = -1;
                while(((status = sem_timedwait(&m_waitSem, &l_tv)) == -1) && (errno == EINTR))
                {
                    continue; // ignore system interrupt
                }
                if((status != 0) && (errno != ETIMEDOUT))
                {
                    printf("sem_timedwait: %s\n", strerror(errno));
                    ASSERT(false);
                    return ASSERTION_FAILED;
                }
            }
        }
        else
        {
            m_threadSafeMutex.release();

            // wait until a new timer added into list
            m_checkSem.take();
        }
    }

    return STOPPED;
}

void CTimersInterruptEmulationThread::stop()
{
    m_stopRequest = true;
    if(sem_post(&m_waitSem) != 0)
    {
        printf("sem_post: %s\n", strerror(errno));
        ASSERT(false);
    }
    m_checkSem.release();
}
#endif

CCommonThreadedTimersThread::CCommonThreadedTimersThread()
    : CThread(0, "CommonTimer",
              10000,
              THREAD_VERY_HIGH_PRIORITY),
      m_queue(1000)
{
    start();
}

CCommonThreadedTimersThread::~CCommonThreadedTimersThread()
{
    // call stop() in the destructor since stop() is overloaded
    // (CThread::~CThread() can't call the overloaded stop() in the 
    // derived class)
    CCommonThreadedTimersThread::stop();
}

bool CCommonThreadedTimersThread::timeout(CTimer* pTimer)
{
    if (m_queue.enqueue(pTimer, false, WAIT_ZERO))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int CCommonThreadedTimersThread::run()
{
    bool stopRequest = false;
    while(!stopRequest)
    {
        CTimer* pTimer;
        m_queue.dequeue(pTimer);
        if (pTimer)
        {
            pTimer->commonThreadedTimeout();
        }
        else
        {
            stopRequest = true;
        }
    }

    return SUCCESS;
}

void CCommonThreadedTimersThread::stop()
{
    m_queue.enqueue(0);
}

