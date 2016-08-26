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
#if defined(__linux)
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#include "timemath.h"
#endif
#include "msgQueue.h"


/*****************************************************************************/
/*                                                                           */
/*  Definitions                                                              */
/*                                                                           */
/*****************************************************************************/


/*****************************************************************************/
/*                                                                           */
/*  Variable Declarations                                                    */
/*                                                                           */
/*****************************************************************************/


/*****************************************************************************/
/*                                                                           */
/*  Function Implementations                                                 */
/*                                                                           */
/*****************************************************************************/
CMsgQueue::CMsgQueue()
#if defined(_WIN32)
    : m_id(NULL),
      m_wid(NULL),
      m_size(0)
#if !defined(UNDER_CE)
      , m_nbMsgs(0)
#endif
#elif defined(__linux)
    : mqd((mqd_t)-1),
      mqname()
#endif
{
}

CMsgQueue::~CMsgQueue()
{
#if defined(_WIN32)
#if!defined(UNDER_CE)
    DWORD   size;
    DWORD   completionKey;
    char*   pItem;
    while (GetQueuedCompletionStatus(
                                m_id,
                                &size,
                                &completionKey,
                                reinterpret_cast<LPOVERLAPPED*>(&pItem),
                                0) != 0)
    {
        delete[] pItem;
    }
    if (!CloseHandle(m_id))
    {
        ASSERT(false);
    }
#else
    if(!CloseMsgQueue(m_id))
    {
        ASSERT(false);
    }
    if(!CloseMsgQueue(m_wid))
    {
        ASSERT(false);
    }
#endif
#elif defined(__linux)
    // free memory allocated
    if(mqd != (mqd_t)-1)
    {
        if(mq_close(mqd) != 0)
        {
            printf("mq_close: %s\n", strerror(errno));
            ASSERT(false);
        }
    }
    if(mq_unlink(mqname.c_str()) != 0)
    {
        printf("mq_unlink: %s\n", strerror(errno));
        ASSERT(false);
    }
#endif
}

void CMsgQueue::initInstance(size_t itemSize, size_t size)
{
#if defined(_WIN32)
    m_size = size;

#if !defined(UNDER_CE)
    // size & itemSize ignored
    m_id = CreateIoCompletionPort(
                            INVALID_HANDLE_VALUE,
                            NULL,
                            0,
                            5);
    ASSERT(m_id);
#else
    MSGQUEUEOPTIONS qOptions;

    qOptions.dwSize = sizeof(MSGQUEUEOPTIONS);
    qOptions.dwFlags = MSGQUEUE_ALLOW_BROKEN;
    qOptions.dwMaxMessages = size;
    qOptions.cbMaxMessage = itemSize;
    qOptions.bReadAccess = true;

    m_id = CreateMsgQueue(0, &qOptions);
    ASSERT(m_id);

    qOptions.bReadAccess = false;
    m_wid = OpenMsgQueue(GetCurrentProcess(), m_id, &qOptions);

    ASSERT(m_wid);
#endif
#elif defined(__linux)
    char filename[64];
    // create a message queue name using the current time
    timespec ts;
    if(clock_gettime(CLOCK_REALTIME, &ts) == 0)
    {
        sprintf(filename, "/mq%lx.%lx", ts.tv_sec, ts.tv_nsec);
        mqname = filename;
    }
    else
    {
        printf("clock_gettime: %s\n", strerror(errno));
        ASSERT(false);
        return;
    }

    /* Create message queue */
    struct mq_attr attr;
    attr.mq_flags = 0; // Flags: 0 or O_NONBLOCK
    attr.mq_maxmsg = size; // Max. # of messages on queue
    attr.mq_msgsize = itemSize; // Max. message size (bytes)
    attr.mq_curmsgs = 0; // # of messages currently in queue

    mqd = mq_open(mqname.c_str(), 
                  O_CREAT | O_RDWR, 
                  S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH, 
                  &attr);
    if(mqd == (mqd_t)-1)
    {
        printf("mq_open: %s\n", strerror(errno));
        ASSERT(false);
    }
#endif
}

#if defined(_WIN32)
struct SItem
{
    size_t  size;
    char    data[1 /*size*/];
};
#endif

bool CMsgQueue::enqueue(const char* pItem, size_t itemSize, 
                        bool urgent, int timeout)
{
#if defined(_WIN32)
#if !defined(UNDER_CE)
    // urgent & timeout ignored
    if (m_nbMsgs == m_size)
    {
        return false;
    }

    char*   p = new char[sizeof(size_t)+itemSize];
    ((SItem*)p)->size = itemSize;
    memcpy(((SItem*)p)->data, pItem, itemSize);
    m_nbMsgs++;
    if (PostQueuedCompletionStatus(
                                m_id,
                                0, // ignore size ; implicit = sizeof(SMsg)
                                0, // completion key ignored,
                                reinterpret_cast<LPOVERLAPPED>(p)) == 0)
    {
        // Can't enqueue message
        m_nbMsgs--;

        ASSERT(false);

        return false;
    }

#else
    if(!WriteMsgQueue(m_wid, const_cast<char *>(pItem), itemSize, 
                       timeout, urgent ? MSGQUEUE_MSGALERT : 0))
    {
        ASSERT(false);

        // No message dequeued
        return false;
    }
#endif

    return true;
#elif defined(__linux)
    int status = -1;

    if(timeout < 0)
    {
        while(((status = mq_send(mqd, pItem, itemSize, (urgent ? 1 : 0))) == -1) && (errno == EINTR))
        {
            continue; // ignore system interrupt
        }
        if(status != 0)
        {
            printf("mq_send: %s\n", strerror(errno));
            ASSERT(false);
        }
    }
    else
    {
        timespec ts;
        if(clock_gettime(CLOCK_REALTIME, &ts) == 0)
        {
            ts = timespec_add_sec_nsec(ts, timeout / MSEC_PER_SEC, (timeout % MSEC_PER_SEC) * NSEC_PER_MSEC);
            while(((status = mq_timedsend(mqd, pItem, itemSize, (urgent ? 1 : 0), &ts)) == -1) && (errno == EINTR))
            {
                continue; // ignore system interrupt
            }
            if(status != 0)
            {
                if(errno != ETIMEDOUT)
                {
                    printf("mq_timedsend: %s\n", strerror(errno));
                    ASSERT(false);
                }
            }
        }
        else
        {
            printf("clock_gettime: %s\n", strerror(errno));
            ASSERT(false);
        }
    }

    return (status == 0) ? true : false;
#endif
}

bool CMsgQueue::dequeue(char* pItem, size_t itemSize, int timeout)
{
#if defined(_WIN32)
#if !defined(UNDER_CE)
    DWORD   size            = 0;
    DWORD   completionKey;
    char*   p               = 0;
    if (GetQueuedCompletionStatus(
                                m_id,
                                &size,
                                &completionKey,
                                reinterpret_cast<LPOVERLAPPED*>(&p),
                                timeout) == 0)
    {
        ASSERT(GetLastError() == 258 /* WAIT_TIMEOUT */);

        // No message dequeued
        return false;
    }
    // ignore size
    // ignore completionKey ; not used
    m_nbMsgs--;
    ASSERT(((SItem*)p)->size <= itemSize);
    memcpy(pItem, ((SItem*)p)->data, ((SItem*)p)->size);
    delete[] p;
#else
    DWORD   size;
    DWORD   flag;
    if(!ReadMsgQueue(m_id, pItem, itemSize, &size, timeout, &flag))
    {
        DWORD error = GetLastError();
        if((error != 258 /*WAIT_TIMEOUT*/) && (error != 1460 /* ERROR_TIMEOUT */))
        {
            ASSERT(false);
        }

        // No message dequeued
        return false;
    }
#endif

    return true;
#elif defined(__linux)
    ssize_t status = -1;

    if(timeout < 0)
    {
        while(((status = mq_receive(mqd, pItem, itemSize, NULL)) == -1) && (errno == EINTR))
        {
            continue; // ignore system interrupt
        }
        // received data size should be more than zero and less than assigned item size
        if((status < 0) || (status > (ssize_t)itemSize))
        {
            printf("mq_receive: %s\n", strerror(errno));
            ASSERT(false);
        }
    }
    else
    {
        timespec ts;
        if(clock_gettime(CLOCK_REALTIME, &ts) == 0)
        {
            ts = timespec_add_sec_nsec(ts, timeout / MSEC_PER_SEC, (timeout % MSEC_PER_SEC) * NSEC_PER_MSEC);
            while(((status = mq_timedreceive(mqd, pItem, itemSize, NULL, &ts)) == -1) && (errno == EINTR))
            {
                continue; // ignore system interrupt
            }
            if((status < 0) || (status > (ssize_t)itemSize))
            {
                if(errno != ETIMEDOUT)
                {
                    printf("mq_timedreceive: %s\n", strerror(errno));
                    ASSERT(false);
                }
            }
        }
        else
        {
            printf("clock_gettime: %s\n", strerror(errno));
            ASSERT(false);
        }
    }

    return (status >= 0) ? true : false;
#endif
}
