#ifndef __TIMER_H__
#define __TIMER_H__
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
#if defined(_WIN32)
#if !defined(UNDER_CE)
    #ifdef _WIN32_WINNT
        #undef _WIN32_WINNT
    #endif
    #define _WIN32_WINNT 0x500
#endif
#endif

#if defined(_WIN32)
#include <windows.h>
#endif

#include "event.h"
#include "thread.h"
#include "msgQueue.h"


/*****************************************************************************/
/*                                                                           */
/*  Definitions                                                              */
/*                                                                           */
/*****************************************************************************/
#if defined(_WIN32)
#define TIME_INFINITE                   ((unsigned long)(INFINITE))
#elif defined(__linux)
#define TIME_INFINITE                   ((unsigned long)(-1))
#endif

class CCommonThreadedTimersThread;

/*****************************************************************************/
/* Class Description:                                                        */
/*****************************************************************************/
/*   Timer class                                                             */
/*                                                                           */
/*****************************************************************************/
class CTimer: public CEventProvider,
              public IRunnable
{
    public:

        class CEvtTimerHasExpired: public IEvent
        {
            public:
                CEvtTimerHasExpired();
                ~CEvtTimerHasExpired();
        };

        enum EMode
        {
            UNTHREADED,
            THREADED,
            COMMON_THREADED
        };

        /*********************************************************************/
        /*                     Constructor & Destructor                      */
        /*********************************************************************/
        CTimer(EMode mode,
               const char* pThreadName = 0,
               size_t threadStackSize = 0,
               int threadPriority  = 0,
               int threadAttributes = 0);
        virtual ~CTimer();


        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/
        static unsigned long s_resolution;


        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/
        bool start(unsigned long timeout, bool repetitive = false);
        bool startRepetitive(unsigned long timeout);
        bool restart();
        void cancel();
        bool isRunning() const;
        bool hasExpired() const;


    private:

        friend class CCommonThreadedTimersThread;

        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/
    #if defined(_WIN32)
    #if !defined(UNDER_CE)
        HANDLE m_id;
    #else
        MMRESULT m_id;
    #endif
    #endif
        EMode m_mode;
        bool m_isRunning;
        bool m_hasExpired;
        unsigned long m_timeout;
        bool m_repetitive;
        CThread* m_pThread;
        CCountingSem m_expired;
        bool m_stopRequest;
        CMutex* m_pCondMutex;
        CCondition* m_pCommonThreadedCond;
        int m_commonThreadedTimeoutsInProgress;
    #if defined(_WIN32)
    #if !defined(UNDER_CE)
        friend class CTimersInterruptEmulationThread;
    #endif
    #elif defined(__linux)
        timespec l_tvStart;
        friend class CTimersInterruptEmulationThread;
    #endif

        DECLARE_THREAD_SAFE


        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/
        #if defined(_WIN32)
        #if !defined(UNDER_CE)
        static void CALLBACK timeoutWrapper_(LPVOID _this_,
                                             DWORD dwTimerLowValue,
                                             DWORD dwTimerHighValue);
        #else
        static void CALLBACK timeoutWrapper_(UINT uID,
                                             UINT uReservedMsg,
                                             DWORD _this_,
                                             DWORD dwReserved1,
                                             DWORD dwReserved2);
        #endif
        #endif
        bool start_(unsigned long timeout);
        void timeoutWrapper();
        void commonThreadedTimeout();
        int run();
        void stop();


    protected:

        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/


        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/
        void initInstance(EMode mode,
                          const char* pThreadName,
                          size_t threadStackSize,
                          int threadPriority,
                          int threadAttributes = 0);
        virtual void timeout();


};

#if defined(_WIN32)
#if !defined(UNDER_CE)
class CTimersInterruptEmulationThread: public CThread
{
    public:

        ~CTimersInterruptEmulationThread();

        void startTimer(CTimer* pTimer);

    private:

        friend class CSingleInstT<CTimersInterruptEmulationThread>;

        CTimersInterruptEmulationThread();

        int run();
        void stop();;

        CTimer* m_pTimer;
        HANDLE m_hStartTimerSem;
        HANDLE m_hTimerStartedSem;
        bool m_stopRequest;
        CSync m_startSync;

        DECLARE_THREAD_SAFE
};

typedef CSingleInst<CTimersInterruptEmulationThread> TheTimersInterruptEmulationThread_;
#define TheTimersInterruptEmulationThread (TheTimersInterruptEmulationThread_::instance())
#endif

#elif defined(__linux)

// linux
class CTimersInterruptEmulationThread: public CThread
{
    public:

        ~CTimersInterruptEmulationThread();

        void startTimer(CTimer* pTimer);
        void cancelTimer(CTimer* pTimer);

    private:

        friend class CSingleInstT<CTimersInterruptEmulationThread>;

        CTimersInterruptEmulationThread();

        int run();
        void stop();

        bool m_stopRequest;
        CSync m_startSync;
        sem_t m_waitSem;
        CBinarySem m_checkSem;
        CMutex m_threadSafeMutex;

        std::list<CTimer *> m_cTimers;
};

typedef CSingleInst<CTimersInterruptEmulationThread> TheTimersInterruptEmulationThread_;
#define TheTimersInterruptEmulationThread (TheTimersInterruptEmulationThread_::instance())
#endif

/*****************************************************************************/
/* Class Description:                                                        */
/*****************************************************************************/
/*   Common threaded timer thread class                                      */
/*                                                                           */
/*****************************************************************************/
class CCommonThreadedTimersThread: public CThread
{
    public:

        /*********************************************************************/
        /*                     Constructor & Destructor                      */
        /*********************************************************************/
        CCommonThreadedTimersThread();
        ~CCommonThreadedTimersThread();


        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/


        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/
        bool timeout(CTimer* pTimer);


    private:

        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/
        CMsgQueueT<CTimer*> m_queue;


        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/
        int run();
        void stop();


    protected:

        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/


        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/


};

typedef CSingleInst<CCommonThreadedTimersThread> TheCommonThreadedTimersThread_;
#define TheCommonThreadedTimersThread (TheCommonThreadedTimersThread_::instance())


/*****************************************************************************/
/*                                                                           */
/*  Variable Declarations                                                    */
/*                                                                           */
/*****************************************************************************/


/*****************************************************************************/
/*                                                                           */
/*  Function Declarations                                                    */
/*                                                                           */
/*****************************************************************************/


#endif //__TIMER_H__

