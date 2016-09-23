#ifndef __THREAD_H__
#define __THREAD_H__
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
#include "Windows.h"
#elif defined(__linux)
#include <unistd.h>
#endif
#include "sync.h"


/*****************************************************************************/
/*                                                                           */
/*  Definitions                                                              */
/*                                                                           */
/*****************************************************************************/
#if defined(_WIN32)
#if !defined(UNDER_CE)
    #if !defined(ASSERT)
        #ifdef _DEBUG
            #define ASSERT(x) {if(!(x)) _asm{int 0x03}}
        #else
            #define ASSERT(x)
        #endif
    #endif
#endif
#endif

#define WAIT_ZERO                       0
#if defined(_WIN32)
#define WAIT_INFINITE                   INFINITE
#elif defined(__linux)
#define WAIT_INFINITE                   (-1)
#endif

#if defined(_WIN32)
#if !defined(UNDER_CE)		//	不是WINCE
#define THREAD_MAX_PRIORITY             THREAD_PRIORITY_TIME_CRITICAL
#define THREAD_VERY_HIGH_PRIORITY       THREAD_PRIORITY_HIGHEST
#define THREAD_HIGH_PRIORITY            THREAD_PRIORITY_ABOVE_NORMAL
#define THREAD_MEDIUM_PRIORITY          THREAD_PRIORITY_NORMAL
#define THREAD_LOW_PRIORITY             THREAD_PRIORITY_BELOW_NORMAL
#define THREAD_VERY_LOW_PRIORITY        THREAD_PRIORITY_LOWEST
#define THREAD_MIN_PRIORITY             THREAD_PRIORITY_IDLE
#else				//WinCE
#define THREAD_MAX_PRIORITY             153
#define THREAD_VERY_HIGH_PRIORITY       160
#define THREAD_HIGH_PRIORITY            180
#define THREAD_MEDIUM_PRIORITY          200
#define THREAD_LOW_PRIORITY             220
#define THREAD_VERY_LOW_PRIORITY        240
#define THREAD_MIN_PRIORITY             255
#endif
#elif defined(__linux)	//Linux
// here we use regular realtime thread priority setting
// if we want to use time critical realtime thread, it needs to use:
//     struct sched_param param;  // scheduling priority
//     int policy = SCHED_RR;     // scheduling policy
//     param.sched_priority = 90;
//     int pthread_setschedparam(pthread_t target_thread, 
//                               int policy, 
//                               const struct sched_param *param)
#define THREAD_MAX_PRIORITY             99L
#define THREAD_VERY_HIGH_PRIORITY       83L
#define THREAD_HIGH_PRIORITY            66L
#define THREAD_MEDIUM_PRIORITY          50L
#define THREAD_LOW_PRIORITY             34L
#define THREAD_VERY_LOW_PRIORITY        17L
#define THREAD_MIN_PRIORITY             1L
#endif

#define THREAD_DEFAULT_STACK_SIZE       20000
#define THREAD_DEFAULT_PRIORITY         THREAD_MEDIUM_PRIORITY
#define THREAD_DEFAULT_ATTRIBUTES       0
#define THREAD_DEFAULT_STOP_TIMEOUT     10000

#if defined(_WIN32)
typedef HANDLE ThreadID_t;
#else
typedef pthread_t ThreadID_t;
#endif

/*****************************************************************************/
/* Class Description:                                                        */
/*****************************************************************************/
/*   Runable class                                                           */
/*                                                                           */
/*****************************************************************************/
class IRunnable		//符合可运行属性的类的基本功能接口
{
    public:

        virtual ~IRunnable();
        virtual int run() = 0;
        virtual void stop() = 0;
};

/*****************************************************************************/
/* Class Description:                                                        */
/*****************************************************************************/
/*   Thread class                                                            */
/*                                                                           */
/*****************************************************************************/
class CThread
{
    public:

        enum EExitCode
        {
            RUNNING                             = 1,		//线程运行中
            SUCCESS                             = 0,		//线程退出成功
            STOPPED                             = -1,	//线程已正常停止
            ABORTED                             = -2,	//线程已异常中止
            EXITED_WITH_UNHANDLED_EXCEPTION     = -3,	//线程由于未处理异常退出
            ASSERTION_FAILED                    = -4,			//线程断言失败退出
            KILLED                              = -5,					//线程被杀死
            EXITED_WITH_UNEXPECTED_EXCEPTION    = -6	//线程由于未知异常退出
        };

        /*********************************************************************/
        /*                     Constructor & Destructor                      */
        /*********************************************************************/
        CThread();
        CThread(IRunnable* pRunnable,
                const char* pInstanceName,
                size_t stackSize,
                int priority,
                int attributes = 0);
        virtual ~CThread();


        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/


        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/
        void start();
        bool waitStarted(int timeout = WAIT_INFINITE);
        bool join(int timeout = WAIT_INFINITE);
        virtual void stop();
        void kill();

        inline static void sleep(int time)
        {
        #if defined(_WIN32)
            Sleep(time);
        #elif defined(__linux)
            usleep(time*1000);
        #endif
        }

        inline EExitCode getExitCode() const
        {
            return m_exitCode;
        }

        inline ThreadID_t getThreadId() const
        {
        	return m_id;
        }


    private:
        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/
    #if defined(_WIN32)
        DWORD           m_win32ThreadId;
    #endif
        ThreadID_t      m_id;
        bool            m_isStarted;
        IRunnable*      m_pRunnable;
        size_t          m_stackSize;
        int             m_priority;
        int             m_attributes;
        EExitCode       m_exitCode;
        CSync           m_startedSync;	//线程开始同步
        CSync           m_joinSync;	//线程结束同步
        DECLARE_THREAD_SAFE


        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/
        static int runWrapper_(CThread* _this_);
        int runWrapper();


    protected:

        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/
        bool m_stopRequest;


        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/
        CThread(const char* pInstanceName,
                size_t      stackSize,
                int         priority,
                int         attributes  = 0);
        void initInstance(const char* pInstanceName,
                          size_t      stackSize,
                          int         priority,
                          int         attributes  = 0);
        virtual int run();


};


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


#endif //__THREAD_H__

