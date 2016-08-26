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
#include <process.h>
#endif
#elif defined(__linux)
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/resource.h>
#include <limits.h>
#endif
#include "thread.h"


/*****************************************************************************/
/*                                                                           */
/*  Definitions                                                              */
/*                                                                           */
/*****************************************************************************/
#if defined(__linux)
// linux don't define __stdcall, so just define it to use
#define   __stdcall

// Linux core schedule policy
// SCHED_RR - realtime with round-robin schedule policy
// SCHED_FIFO - realtime with first in first out schedule policy
// SCHED_OTHER - non-realtime round-robin schedule policy
#define THREADS_SCHED_POLICY    SCHED_RR
#endif


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


/*****************************************************************************/
/*                                                                           */
/*  Function Implementations                                                 */
/*                                                                           */
/*****************************************************************************/
IRunnable::~IRunnable()
{
}

CThread::CThread()
    : m_id(0),
#if defined(_WIN32)
      m_win32ThreadId(0),
#endif
      m_isStarted(false),
      m_pRunnable(0),
      m_stackSize(0),
      m_priority(0),
      m_attributes(0),
      m_exitCode(SUCCESS),
      m_startedSync(),
      m_joinSync(),
      m_stopRequest(true)
{
}

CThread::CThread(const char* pInstanceName, size_t stackSize,
                 int priority, int attributes)
    : m_id(0),
#if defined(_WIN32)
      m_win32ThreadId(0),
#endif
      m_isStarted(false),
      m_pRunnable(0),
      m_stackSize(stackSize),
      m_priority(priority),
      m_attributes(attributes),
      m_exitCode(SUCCESS),
      m_startedSync(),
      m_joinSync(),
      m_stopRequest(true)
{
    initInstance(pInstanceName, stackSize, priority, attributes);
}

CThread::CThread(IRunnable* pRunnable, const char* pInstanceName, 
                 size_t stackSize, int priority, int attributes)
    : m_id(0),
#if defined(_WIN32)
      m_win32ThreadId(0),
#endif
      m_isStarted(false),
      m_pRunnable(pRunnable),
      m_stackSize(stackSize),
      m_priority(priority),
      m_attributes(attributes),
      m_exitCode(SUCCESS),
      m_startedSync(),
      m_joinSync(),
      m_stopRequest(true)
{
    initInstance(pInstanceName, stackSize, priority, attributes);
}

CThread::~CThread()
{
    THREAD_SAFE

    if (m_exitCode == RUNNING)
    {
        // Deletion of the thread instance (memory location) => deletion of the 
        // corresponding OS thread (task)
        // WARNING : Since CThread::stop() is virtual and may be overloaded in 
        // a class derived from CThread, the overloaded stop() method MUST be 
        // called in the derived class destructor
        CThread::stop();

        // the running OS Thread must respond to stop otherwise it will be 
        // killed and memory leak could occur
        if (!join(THREAD_DEFAULT_STOP_TIMEOUT))
        {
            kill();
        }
    }
    #if defined(_WIN32)
    if (m_id)
    {
        if (GetCurrentThread() != m_id)
        {
            if (!CloseHandle(m_id))
            {
                ASSERT(false);
            }
        }
    }
    #elif defined(__linux)
    // pthread_self always succeeds, returning the calling thread's ID
    // check if the threads ids are the same
    if(pthread_equal(pthread_self(), m_id) != 0)
    {
        // try to cancel the m_id thread
        int status = pthread_cancel(m_id);
        if(status != 0)
        {
            printf("pthread_cancel(0x%lx): %s\n", m_id, strerror(status));
            ASSERT(false);
        }
    }
    #endif
}

void CThread::initInstance(const char* pInstanceName, size_t stackSize,
                           int priority, int attributes)
{
    m_stackSize = (stackSize == 0) ? THREAD_DEFAULT_STACK_SIZE : stackSize;
    m_priority = (priority == 0) ? THREAD_DEFAULT_PRIORITY : priority;
    m_attributes = (attributes == 0) ? THREAD_DEFAULT_ATTRIBUTES : attributes;

#if defined(__linux)
    int maxPrio = sched_get_priority_max(THREADS_SCHED_POLICY);
    if(maxPrio == -1)
    {
        printf("sched_get_priority_max: %s\n", strerror(errno));
        ASSERT(false);
        return;
    }
    int minPrio = sched_get_priority_min(THREADS_SCHED_POLICY);
    if(minPrio == -1)
    {
        printf("sched_get_priority_max: %s\n", strerror(errno));
        ASSERT(false);
        return;
    }

    if(m_priority > maxPrio)
    {
        m_priority = maxPrio;
    }

    if(m_priority < minPrio)
    {
        m_priority = minPrio;
    }

    // the stack size of linux thread must more than PTHREAD_STACK_MIN (16384) bytes.
    m_stackSize = (m_stackSize > PTHREAD_STACK_MIN) ? m_stackSize : PTHREAD_STACK_MIN;
#endif
}

void CThread::start()
{
    THREAD_SAFE

    if (m_stackSize == 0)
    {
        return;
    }

    // Only one OS thread is associated to one thread instance
    if (m_exitCode == RUNNING)
    {
        return;
    }

    m_exitCode = RUNNING;

    m_joinSync.wait(WAIT_ZERO);

    m_stopRequest = false;

#if defined(_WIN32)
    HANDLE id;
#if !defined(UNDER_CE)
	// using CRT function _beginthreadex() unstead of WIN32 native CreateThread() to have CRT data created for this thread
	if ((id = (HANDLE)_beginthreadex(0,
                                     m_stackSize,
                                     (unsigned (__stdcall*)(void*))(runWrapper_),
                                     (void*)this,
                                     m_attributes,
                                     (unsigned int*)&m_win32ThreadId)) == 0)
#else
    if ((id = CreateThread(0,              // No security attributes
                           m_stackSize,
                           (unsigned long (__stdcall*)(void*))(runWrapper_),
                           (void*)this,
                           m_attributes | STACK_SIZE_PARAM_IS_A_RESERVATION,   // 0 or CREATE_SUSPENDED
                           &m_win32ThreadId)) == 0)
#endif
    {
        return;
    }


    m_id = id;

#if !defined(UNDER_CE)
    // WARNING : m_priority MUST be WIN32_W2K native priority (use osBase pre-defined priorities)
    if (m_priority > THREAD_MAX_PRIORITY) m_priority = THREAD_MAX_PRIORITY;
    if (m_priority < THREAD_MIN_PRIORITY) m_priority = THREAD_MIN_PRIORITY;
    if (SetThreadPriority(id, m_priority) == 0)
#else
    if (CeSetThreadPriority(id, m_priority) == 0)
#endif
    {
        stop();
        return;
    }
#elif defined(__linux)
    pthread_attr_t attr;

    // Initialize thread creation attributes
    int status = pthread_attr_init(&attr);
    if(status != 0)
    {
        printf("pthread_attr_init: %s\n", strerror(status));
        ASSERT(false);
        return;
    }

    // set the thread schedule policy of the Linux core
    status = pthread_attr_setschedpolicy(&attr, THREADS_SCHED_POLICY);
    if(status != 0)
    {
        printf("pthread_attr_setschedpolicy: %s\n", strerror(status));
        ASSERT(false);
        return;
    }

    // set the priority of the thread
    struct sched_param sp;
    sp.sched_priority = m_priority;
    status = pthread_attr_setschedparam(&attr, &sp);
    if(status != 0)
    {
        printf("pthread_attr_setschedparam: %s\n", strerror(status));
        ASSERT(false);
        return;
    }

    // set the thread stack size
    if(m_stackSize > 0)
    {
        status = pthread_attr_setstacksize(&attr, m_stackSize);
        if(status != 0)
        {
            printf("pthread_attr_setstacksize: %s\n", strerror(status));
            ASSERT(false);
            return;
        }
    }
    else
    {
        printf("Stack size (%d) error\n", m_stackSize);
        ASSERT(false);
        return;
    }

    // create the thread
    status = pthread_create(&m_id, 
                            &attr, 
                            (void *(__stdcall*)(void*))(runWrapper_),
                            (void*)this);
    if(status != 0)
    {
        printf("pthread_create: %s\n", strerror(status));
        ASSERT(false);
        return;
    }

    status = pthread_attr_destroy(&attr);
    if(status != 0)
    {
        printf("pthread_attr_destroy: %s\n", strerror(status));
        ASSERT(false);
        return;
    }
#endif
}

bool CThread::waitStarted(int timeout)
{
    return (m_isStarted ? true : m_startedSync.wait(timeout));
}

int CThread::runWrapper_(CThread* _this_)
{
    return _this_->runWrapper();
}

int CThread::runWrapper()
{
    m_isStarted = true;
    m_startedSync.signal();

    m_exitCode = EExitCode(run());

    m_isStarted = false;

#if defined(_WIN32)
    m_win32ThreadId = 0;
#elif defined(__linux)
    m_id = 0;
#endif

    int exitCode = m_exitCode;

    m_joinSync.signal();

    return exitCode;
}

int CThread::run()
{
    if(m_pRunnable != 0)
    {
        return m_pRunnable->run();
    }

    return SUCCESS;
}

bool CThread::join(int timeout)
{
    switch(m_exitCode)
    {
        case RUNNING:
        {
            if(!m_joinSync.wait(timeout))
            {
                return false;
            }

            // Signal again for others
            m_joinSync.signal();
        }
        break;

        default:
        break;
    }

    return true;
}

void CThread::stop()
{
    THREAD_SAFE

    if ((m_exitCode == RUNNING) && !m_stopRequest)
    {
        m_stopRequest = true;
        if(m_pRunnable)
        {
            m_pRunnable->stop();
        }
    }
}

void CThread::kill()
{
    if (m_exitCode == RUNNING)
    {
    #if defined(_WIN32)
        // WARNING : memory leakage possibility exists here
        TerminateThread(m_id, KILLED);
    #elif defined(__linux)
        // try to cancel the m_id thread
        int status = pthread_cancel(m_id);
        if(status != 0)
        {
            printf("pthread_cancel(0x%lx): %s\n", m_id, strerror(status));
            ASSERT(false);
        }
    #endif

        m_exitCode = KILLED;
        m_joinSync.signal();
    }
}

