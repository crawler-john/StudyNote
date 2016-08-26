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
/*  2011-10-17 * Ricky Gong      * Creation of the file                      */
/*  2012-12-18 * Ricky Gong      * Added Linux implementations               */
/*             *                 *                                           */
/*****************************************************************************/


/*****************************************************************************/
/*                                                                           */
/*  Include Files                                                            */
/*                                                                           */
/*****************************************************************************/
#if defined(__linux)
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "timemath.h"
#endif
#include "sync.h"


/*****************************************************************************/
/*                                                                           */
/*  Definitions                                                              */
/*                                                                           */
/*****************************************************************************/
#if defined(__linux)
// mutex recursive attribute for linux
// PTHREAD_MUTEX_NORMAL: this type of mutex does not detect deadlock
// PTHREAD_MUTEX_ERRORCHECK: this type of mutex provides error checking
// PTHREAD_MUTEX_RECURSIVE: a thread attempting to relock this mutex without 
//                          first unlocking it shall succeed in locking the mutex
// PTHREAD_MUTEX_DEFAULT: attempting to recursively lock a mutex of this type 
//                        results in undefined behavior
#define MUTEX_RECURSIVE_ATTRIBUTE    PTHREAD_MUTEX_RECURSIVE
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
#if defined(__linux)
CSem::CSem()
    : m_id (NULL)
{
}
#endif

CSem::CSem(SEM_ID id)
    : m_id (id)
{
#if defined(_WIN32)
    ASSERT(m_id);
#elif defined(__linux)
    ASSERT(m_id != NULL);
#endif
}

CSem::~CSem()
{
    if(m_id == NULL)
        return;

#if defined(_WIN32)
    ASSERT(CloseHandle(m_id) != 0);
#elif defined(__linux)
    if(sem_destroy(m_id) != 0)
    {
        printf("sem_destroy: %s\n", strerror(errno));
        ASSERT(false);
    }
    if(m_id != NULL)
    {
        delete m_id;
        m_id = NULL;
    }
#endif
}

bool CSem::take(int timeout)
{
    if(m_id == NULL)
        return false;

#if defined(_WIN32)
    DWORD status = WaitForSingleObject(m_id, timeout);
    if(status == WAIT_FAILED)
    {
        ASSERT(false);
    }
    return (status == WAIT_OBJECT_0) ? true : false;
#elif defined(__linux)
    int status = -1;

    if(timeout < 0)
    {
        // wait until semaphore available
        while(((status = sem_wait(m_id)) == -1) && (errno == EINTR))
        {
            continue; // ignore system interrupt
        }
        if(status != 0)
        {
            printf("sem_wait: %s\n", strerror(errno));
            ASSERT(false);
        }
        return (status == 0) ? true : false;
    }
    else
    {
        timespec ts;
        if(clock_gettime(CLOCK_REALTIME, &ts) == 0)
        {
            ts = timespec_add_sec_nsec(ts, timeout / MSEC_PER_SEC, (timeout % MSEC_PER_SEC) * NSEC_PER_MSEC);
            while(((status = sem_timedwait(m_id, &ts)) == -1) && (errno == EINTR))
            {
                continue; // ignore system interrupt
            }
            if((status != 0) && (errno != ETIMEDOUT))
            {
                printf("sem_timedwait: %s\n", strerror(errno));
                ASSERT(false);
            }
        }
        else
        {
            printf("clock_gettime: %s\n", strerror(errno));
            ASSERT(false);
        }
        return (status == 0) ? true : false;
    }
#endif
}

void CSem::release()
{
    if(m_id == NULL)
        return;

#if defined(_WIN32)
    BOOL status = ReleaseSemaphore(m_id, 1, 0);
    if(!status)
    {
        ASSERT(false);
    }
#elif defined(__linux)
    if(sem_post(m_id) != 0)
    {
        printf("sem_post: %s\n", strerror(errno));
        ASSERT(false);
    }
#endif
}

CCountingSem::CCountingSem(int initialCount, int maxCount)
#if defined(_WIN32)
    : CSem(CreateSemaphore(0, initialCount, maxCount, 0)),
      m_maxCount(maxCount)
#elif defined(__linux)
    : CSem(),
      m_maxCount(maxCount),
      bMutexInitialised(false)
#endif
{
#if defined(__linux)
    m_id = new sem_t;
    if(m_id == NULL) {
        ASSERT(false);
        return;
    }

    if(sem_init(m_id, 0, (initialCount <= maxCount) ? initialCount : maxCount) != 0)
    {
        printf("sem_init: %s\n", strerror(errno));
        ASSERT(false);
        return;
    }

    pthread_mutexattr_t mta;
    int status = pthread_mutexattr_init(&mta);
    if(status != 0)
    {
        printf("pthread_mutexattr_init: %s\n", strerror(status));
        ASSERT(false);
        return;
    }
    status = pthread_mutexattr_settype(&mta, MUTEX_RECURSIVE_ATTRIBUTE);
    if(status != 0)
    {
        printf("pthread_mutexattr_settype: %s\n", strerror(status));
        ASSERT(false);
        return;
    }
    status = pthread_mutex_init(&m_cs, &mta);
    if(status != 0)
    {
        printf("pthread_mutex_init: %s\n", strerror(status));
        ASSERT(false);
        return;
    }
    status = pthread_mutexattr_destroy(&mta);
    if(status != 0)
    {
        printf("pthread_mutexattr_destroy: %s\n", strerror(status));
        ASSERT(false);
        return;
    }
    bMutexInitialised = true;
#endif
}

CCountingSem::~CCountingSem()
{
#if defined(__linux)
    if(!bMutexInitialised)
        return;

    int status = -1;
    while((status = pthread_mutex_destroy(&m_cs)) == EBUSY)
    {
        // maybe the mutex is recursively taken, so release mutex before being 
        // destroyed
        status = pthread_mutex_unlock(&m_cs);
        if(status != 0)
        {
            printf("pthread_mutex_unlock: %s\n", strerror(status));
            ASSERT(false);
        }
    }

    if(status != 0)
    {
        printf("pthread_mutex_destroy: %s\n", strerror(status));
        ASSERT(false);
    }
    bMutexInitialised = false;
#endif
}

bool CCountingSem::release(int count)
{
    if(m_id == NULL)
        return false;

#if defined(_WIN32)
    BOOL status = ReleaseSemaphore(m_id, LONG(count), 0);
    if(!status)
    {
        DWORD error = GetLastError();
    #if defined(_WIN32)
    #if !defined(UNDER_CE)
        if (error != 298 /* ERROR_TOO_MANY_POSTS */)
    #else
        // seems that WCE doesn't generate ERROR_TOO_MANY_POSTS but 
        // ERROR_INVALID_PARAMETER
        if(error != 87 /* ERROR_INVALID_PARAMETER */)
    #endif
    #endif
        {
        }
    }
    return (status != 0);
#elif defined(__linux)
    if(!bMutexInitialised)
        return false;

    int m_val = 0;
    int status = -1;
    int nret = pthread_mutex_lock(&m_cs);
    if(nret != 0)
    {
        printf("pthread_mutex_lock: %s\n", strerror(nret));
        ASSERT(false);
    }
    status = sem_getvalue(m_id, &m_val);
    if(status != 0)
    {
        printf("sem_getvalue: %s\n", strerror(errno));
        ASSERT(false);
    }
    if((status == 0) && (m_val < m_maxCount))
    {
        for(int i = 0; i < ((count <= (m_maxCount-m_val))? count : (m_maxCount-m_val)); i++)
        {
            status = sem_post(m_id);
            if(status != 0)
            {
                printf("sem_post: %s\n", strerror(errno));
                ASSERT(false);
                break;
            }
        }
    }
    else
    {
        status = -1; // set status to -1 to return false
    }
    nret = pthread_mutex_unlock(&m_cs);
    if(nret != 0)
    {
        printf("pthread_mutex_unlock: %s\n", strerror(nret));
        ASSERT(false);
    }
    return (status == 0);
#endif
}

CBinarySem::CBinarySem(EInitialState initialState)
#if defined(_WIN32)
    : CSem(CreateSemaphore(0, initialState, 1, 0))
#elif defined(__linux)
    : CSem(),
      bMutexInitialised(false)
#endif
{
#if defined(__linux)
    m_id = new sem_t;
    if(m_id == NULL) {
        ASSERT(false);
        return;
    }

    if(sem_init(m_id, 0, (initialState <= OS_SEM_FULL) ? initialState : OS_SEM_FULL) != 0)
    {
        printf("sem_init: %s\n", strerror(errno));
        ASSERT(false);
        return;
    }

    pthread_mutexattr_t mta;
    int status = pthread_mutexattr_init(&mta);
    if(status != 0)
    {
        printf("pthread_mutexattr_init: %s\n", strerror(status));
        ASSERT(false);
        return;
    }
    status = pthread_mutexattr_settype(&mta, MUTEX_RECURSIVE_ATTRIBUTE);
    if(status != 0)
    {
        printf("pthread_mutexattr_settype: %s\n", strerror(status));
        ASSERT(false);
        return;
    }
    status = pthread_mutex_init(&m_cs, &mta);
    if(status != 0)
    {
        printf("pthread_mutex_init: %s\n", strerror(status));
        ASSERT(false);
        return;
    }
    status = pthread_mutexattr_destroy(&mta);
    if(status != 0)
    {
        printf("pthread_mutexattr_destroy: %s\n", strerror(status));
        ASSERT(false);
        return;
    }
    bMutexInitialised = true;
#endif
}

CBinarySem::~CBinarySem()
{
#if defined(__linux)
    if(!bMutexInitialised)
        return;

    int status = -1;
    while((status = pthread_mutex_destroy(&m_cs)) == EBUSY)
    {
        // maybe the mutex is recursively taken, so release mutex before being 
        // destroyed
        status = pthread_mutex_unlock(&m_cs);
        if(status != 0)
        {
            printf("pthread_mutex_unlock: %s\n", strerror(status));
            ASSERT(false);
        }
    }

    if(status != 0)
    {
        printf("pthread_mutex_destroy: %s\n", strerror(status));
        ASSERT(false);
    }
    bMutexInitialised = false;
#endif
}

#if defined(__linux)
void CBinarySem::release()
{
    if(m_id == NULL)
        return;

    if(!bMutexInitialised)
        return;

    int m_val = 0;
    int status = 0;
    int nret = pthread_mutex_lock(&m_cs);
    if(nret != 0)
    {
        printf("pthread_mutex_lock: %s\n", strerror(nret));
        ASSERT(false);
    }
    status = sem_getvalue(m_id, &m_val);
    if(status != 0)
    {
        printf("sem_getvalue: %s\n", strerror(errno));
        ASSERT(false);
    }
    if(m_val < OS_SEM_FULL)
    {
        if(sem_post(m_id) != 0)
        {
            printf("sem_post: %s\n", strerror(errno));
            ASSERT(false);
        }
    }
    nret = pthread_mutex_unlock(&m_cs);
    if(nret != 0)
    {
        printf("pthread_mutex_unlock: %s\n", strerror(nret));
        ASSERT(false);
    }
}
#endif

CSync::CSync()
#if defined(__linux)
    : bInitialised(false),
      bSignalExists(false)
#endif
{
#if defined(_WIN32)
    m_eventHandles[0] = CreateEvent(0, FALSE, FALSE, 0);
    m_eventHandles[1] = CreateEvent(0, TRUE, FALSE, 0);
    ASSERT(m_eventHandles[0]);
    ASSERT(m_eventHandles[1]);
#elif defined(__linux)
    pthread_mutexattr_t mta;
    int status = pthread_mutexattr_init(&mta);
    if(status != 0)
    {
        printf("pthread_mutexattr_init: %s\n", strerror(status));
        ASSERT(false);
        return;
    }
    status = pthread_mutexattr_settype(&mta, MUTEX_RECURSIVE_ATTRIBUTE);
    if(status != 0)
    {
        printf("pthread_mutexattr_settype: %s\n", strerror(status));
        ASSERT(false);
        return;
    }
    status = pthread_mutex_init(&m_mutex, &mta);
    if(status != 0)
    {
        printf("pthread_mutex_init: %s\n", strerror(status));
        ASSERT(false);
        return;
    }
    status = pthread_mutexattr_destroy(&mta);
    if(status != 0)
    {
        printf("pthread_mutexattr_destroy: %s\n", strerror(status));
        ASSERT(false);
        return;
    }
    status = pthread_cond_init(&m_cond, NULL);
    if(status != 0)
    {
        printf("pthread_cond_init: %s\n", strerror(status));
        ASSERT(false);
        return;
    }
    bInitialised = true;
#endif
}

CSync::~CSync()
{
#if defined(_WIN32)
    if((m_eventHandles[0] == NULL) || (m_eventHandles[1] == NULL))
        return;

    CloseHandle(m_eventHandles[0]);
    CloseHandle(m_eventHandles[1]);
#elif defined(__linux)
    if(!bInitialised)
        return;

    // try to lock the mutex before destroy the condition
    int status = pthread_mutex_lock(&m_mutex);
    if(status != 0)
    {
        printf("pthread_mutex_lock: %s\n", strerror(status));
        ASSERT(false);
    }

    status = pthread_cond_destroy(&m_cond);
    if(status != 0)
    {
        printf("pthread_cond_destroy: %s\n", strerror(status));
        ASSERT(false);
    }

    do {
        // maybe the mutex is recursively taken, so release mutex before being 
        // destroyed
        status = pthread_mutex_unlock(&m_mutex);
        if(status != 0)
        {
            printf("pthread_mutex_unlock: %s\n", strerror(status));
            ASSERT(false);
        }
        status = pthread_mutex_destroy(&m_mutex);
    } while(status == EBUSY);

    if(status != 0)
    {
        printf("pthread_mutex_destroy: %s\n", strerror(status));
        ASSERT(false);
    }
    bInitialised = false;
    bSignalExists = false;
#endif
}

bool CSync::wait(int timeout)
{
#if defined(_WIN32)
    if((m_eventHandles[0] == NULL) || (m_eventHandles[1] == NULL))
        return false;

    DWORD status = WaitForMultipleObjects(2, m_eventHandles, FALSE, timeout);
    if(status == WAIT_FAILED)
    {
        ASSERT(false);
    }
    return ((status == WAIT_OBJECT_0) || (status == (WAIT_OBJECT_0 + 1))) ? true : false;
#elif defined(__linux)
    if(!bInitialised)
        return false;

    int status = -1;

    int nret = pthread_mutex_lock(&m_mutex);
    if(nret != 0)
    {
        printf("pthread_mutex_lock: %s\n", strerror(nret));
        ASSERT(false);
    }
    if(timeout < 0)
    {
        // wait until the correct condition being waited signaled
        do {
            // signal already exists, break to stop the waiting
            if(bSignalExists)
            {
                bSignalExists = false;
                break;
            }
            // wait until condition available
            status = pthread_cond_wait(&m_cond, &m_mutex);
            if(status != 0)
            {
                printf("pthread_cond_wait: %s\n", strerror(status));
                ASSERT(false);
            }
        } while(1);
    }
    else
    {
        timespec ts;
        if(clock_gettime(CLOCK_REALTIME, &ts) == 0)
        {
            ts = timespec_add_sec_nsec(ts, timeout / MSEC_PER_SEC, (timeout % MSEC_PER_SEC) * NSEC_PER_MSEC);
            // wait until the correct condition being waited signaled
            do {
                // signal already exists, break to stop the waiting
                if(bSignalExists)
                {
                    bSignalExists = false;
                    break;
                }
                status = pthread_cond_timedwait(&m_cond, &m_mutex, &ts);
                if((status != 0) && (status != ETIMEDOUT))
                {
                    printf("pthread_cond_timedwait: %s\n", strerror(status));
                    ASSERT(false);
                }
                else if(status == ETIMEDOUT)
                {
                    break;
                }
            } while(1);
        }
        else
        {
            printf("clock_gettime: %s\n", strerror(errno));
            ASSERT(false);
        }
    }
    nret = pthread_mutex_unlock(&m_mutex);
    if(nret != 0)
    {
        printf("pthread_mutex_unlock: %s\n", strerror(nret));
        ASSERT(false);
    }
    return (status == 0) ? true : false;
#endif
}

void CSync::signal()
{
#if defined(_WIN32)
    if(m_eventHandles[0] == NULL)
        return;

    BOOL status = SetEvent(m_eventHandles[0]);
    if(!status)
    {
        ASSERT(false);
    }
#elif defined(__linux)
    if(!bInitialised)
        return;

    int nret = pthread_mutex_lock(&m_mutex);
    if(nret != 0)
    {
        printf("pthread_mutex_lock: %s\n", strerror(nret));
        ASSERT(false);
    }
    if(!bSignalExists)
    {
        // signal one thread to wake up
        int status = pthread_cond_signal(&m_cond);
        if(status != 0)
        {
            printf("pthread_cond_signal: %s\n", strerror(status));
            ASSERT(false);
        }
        else
        {
            bSignalExists = true;
        }
    }
    nret = pthread_mutex_unlock(&m_mutex);
    if(nret != 0)
    {
        printf("pthread_mutex_unlock: %s\n", strerror(nret));
        ASSERT(false);
    }
#endif
}

void CSync::broadcast()
{
#if defined(_WIN32)
    if(m_eventHandles[1] == NULL)
        return;

    // All pending thread are awakened ; inner state not changed
    BOOL status = PulseEvent(m_eventHandles[1]);
    if(!status)
    {
        ASSERT(false);
    }
#elif defined(__linux)
    if(!bInitialised)
        return;

    int nret = pthread_mutex_lock(&m_mutex);
    if(nret != 0)
    {
        printf("pthread_mutex_lock: %s\n", strerror(nret));
        ASSERT(false);
    }
    if(!bSignalExists)
    {
        // broadcast to all the pending threads to wake up
        int status = pthread_cond_broadcast(&m_cond);
        if(status != 0)
        {
            printf("pthread_cond_broadcast: %s\n", strerror(status));
            ASSERT(false);
        }
        else
        {
            bSignalExists = true;
        }
    }
    nret = pthread_mutex_unlock(&m_mutex);
    if(nret != 0)
    {
        printf("pthread_mutex_unlock: %s\n", strerror(nret));
        ASSERT(false);
    }
#endif
}

CMutex::CMutex()
    : bInitialised(false)
{
#if defined(_WIN32)
    InitializeCriticalSection(&m_cs);
#elif defined(__linux)
    pthread_mutexattr_t mta;
    int status = pthread_mutexattr_init(&mta);
    if(status != 0)
    {
        printf("pthread_mutexattr_init: %s\n", strerror(status));
        ASSERT(false);
        return;
    }
    status = pthread_mutexattr_settype(&mta, MUTEX_RECURSIVE_ATTRIBUTE);
    if(status != 0)
    {
        printf("pthread_mutexattr_settype: %s\n", strerror(status));
        ASSERT(false);
        return;
    }
    status = pthread_mutex_init(&m_cs, &mta);
    if(status != 0)
    {
        printf("pthread_mutex_init: %s\n", strerror(status));
        ASSERT(false);
        return;
    }
    status = pthread_mutexattr_destroy(&mta);
    if(status != 0)
    {
        printf("pthread_mutexattr_destroy: %s\n", strerror(status));
        ASSERT(false);
        return;
    }
#endif
    bInitialised = true;
}

CMutex::~CMutex()
{
    if(!bInitialised)
        return;

    CMutex::take();

#if defined(_WIN32)
    DeleteCriticalSection(&m_cs);
#elif defined(__linux)
    int status = -1;
    do {
        // maybe the mutex is recursively taken, so release mutex before being 
        // destroyed
        CMutex::release();
        status = pthread_mutex_destroy(&m_cs);
    } while(status == EBUSY);

    if(status != 0)
    {
        printf("pthread_mutex_destroy: %s\n", strerror(status));
        ASSERT(false);
    }
#endif
    bInitialised = false;
}

bool CMutex::take(int timeout)
{
    if(!bInitialised)
        return false;

    bool status;

#if defined(_WIN32)
    if(timeout == (int)WAIT_INFINITE)
    {
        EnterCriticalSection(&m_cs);
        status = true;
    }
    else
    {
        do
        {
            if(TryEnterCriticalSection(&m_cs))
            {
                // Got it
                status = true;
                break;
            }
            if(timeout == 0)
            {
                status = false;
                break;
            }
            timeout -= 1;
            Sleep(1);
        } while(true);
    }
#elif defined(__linux)
    int nret = -1;

    if(timeout == WAIT_INFINITE)
    {
        nret = pthread_mutex_lock(&m_cs);
        if(nret != 0)
        {
            printf("pthread_mutex_lock: %s\n", strerror(nret));
            ASSERT(false);
        }
        status = ((nret == 0) ? true : false);
    }
    else
    {
        timespec ts;
        if(clock_gettime(CLOCK_REALTIME, &ts) == 0)
        {
            ts = timespec_add_sec_nsec(ts, timeout / MSEC_PER_SEC, (timeout % MSEC_PER_SEC) * NSEC_PER_MSEC);
            nret = pthread_mutex_timedlock(&m_cs, &ts);
            if((nret != 0) && (nret != ETIMEDOUT))
            {
                printf("pthread_cond_timedwait: %s\n", strerror(nret));
                ASSERT(false);
            }
        }
        else
        {
            printf("clock_gettime: %s\n", strerror(errno));
            ASSERT(false);
        }
        status = ((nret == 0) ? true : false);
    }
#endif

    return status;
}

void CMutex::release()
{
    if(!bInitialised)
        return;

#if defined(_WIN32)
    LeaveCriticalSection(&m_cs);
#elif defined(__linux)
    int nret = pthread_mutex_unlock(&m_cs);
    if(nret != 0)
    {
        printf("pthread_mutex_unlock: %s\n", strerror(nret));
        ASSERT(false);
    }
#endif
}

CLock::CLock(CMutex& rMutex)
    : m_rMutex(rMutex)
{
    m_rMutex.take(WAIT_INFINITE);
}

CLock::~CLock()
{
    m_rMutex.release();
}

CCondition::CCondition(CMutex& rMutex)
    : m_rMutex(rMutex),
      m_waitersMutex(),
      m_nbWaiters(0),
      m_waitSem(),
      m_broadcastSem(),
      m_broadcastInProgress(false)
{
}

CCondition::~CCondition()
{
}

CMutex& CCondition::getMutex() const
{
    return m_rMutex;
}

bool CCondition::enter(int timeout)
{
    return m_rMutex.take(timeout);
}

void CCondition::leave()
{
    m_rMutex.release();
}

bool CCondition::wait(int timeout)
{
    m_waitersMutex.take();
    m_nbWaiters++;
    m_waitersMutex.release();

    m_rMutex.release();
    // <--- could be scheduled at this point by a "client" which will call 
    // broadcast()
    // => m_waitSem is a CCountingSem not a CBinarySem
    bool gotSync = m_waitSem.take(timeout);

    bool isLastWaiter = false;
    m_waitersMutex.take();
    m_nbWaiters--;
    if((m_broadcastInProgress) && (m_nbWaiters == 0))
    {
        isLastWaiter = true;
    }
    m_waitersMutex.release();

    if(isLastWaiter)
    {
        // Broadcast && Last waiter => acknowledge the broadcast : all pended 
        // threads before broadcast() are now awakened
        m_broadcastSem.release();
    }

    m_rMutex.take();

    return gotSync;
}

// WARNING : Must be called with m_rMutex taken by "client" before 
// (if not it can lead to the "lost wakeup bug")
bool CCondition::signal()
{
    bool noWaitersPended;
    m_waitersMutex.take();
    noWaitersPended = (m_nbWaiters == 0);
    m_waitersMutex.release();

    if(noWaitersPended)
    {
        // Do nothing
        return false;
    }

    // ONE credit => only ONE waiter will wake up
    m_waitSem.release();
    return true;
}

// WARNING : Must be called with m_rMutex taken by "client" before 
// (if not it can lead to the "lost wakeup bug")
bool CCondition::broadcast()
{
    bool noWaitersPended;
    m_waitersMutex.take();
    if(m_nbWaiters)
    {
        noWaitersPended = false;
        m_broadcastInProgress = true;
    }
    else
    {
        noWaitersPended = true;
    }
    m_waitersMutex.release();

    if(noWaitersPended)
    {
        // Do nothing
        return false;
    }

    // Wake up ALL waiters
    // Each waiter will wake up in wait() and will pend on the 
    // "m_rMutex.take();" before exiting
    m_waitSem.release(m_nbWaiters);
    // Wait for all waiters awaken before exiting (and therefore releasing 
    // m_rMutex)
    m_broadcastSem.take();
    m_broadcastInProgress = false;

    return true;
}

