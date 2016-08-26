#ifndef __MSG_QUEUE_H__
#define __MSG_QUEUE_H__
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
#ifdef _MSC_VER // ignore 4786 warning in MS VC
#pragma warning(disable:4786)
#endif
#endif

#if defined(_WIN32)
#if !defined(UNDER_CE)
    #ifdef _WIN32_WINNT
        #undef _WIN32_WINNT
    #endif
    #define _WIN32_WINNT 0x500
#endif
#endif

#if defined(_WIN32)
#include "windows.h"
#elif defined(__linux)
#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <assert.h>
#endif


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
#elif defined(__linux)
#define ASSERT(x) assert(x)
#endif

#define WAIT_ZERO               0
#if defined(_WIN32)
#define WAIT_INFINITE           INFINITE
#elif defined(__linux)
#define WAIT_INFINITE           (-1)
#endif

/*****************************************************************************/
/* Class Description:                                                        */
/*****************************************************************************/
/*   Message queue class                                                     */
/*                                                                           */
/*****************************************************************************/
class CMsgQueue
{
    public:

        /*********************************************************************/
        /*                     Constructor & Destructor                      */
        /*********************************************************************/
        virtual ~CMsgQueue();


        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/


        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/


    private:

        /*********************************************************************/
        /*                     Constructor & Destructor                      */
        /*********************************************************************/
        CMsgQueue(const CMsgQueue&);


        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/


        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/


    protected:

        /*********************************************************************/
        /*                     Constructor & Destructor                      */
        /*********************************************************************/
        CMsgQueue();


        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/
    #if defined(_WIN32)
        HANDLE m_id;
        HANDLE m_wid;
        size_t m_size;
    #elif defined(__linux)
        mqd_t mqd;
        std::string mqname;
    #endif
    #if defined(_WIN32)
    #if !defined(UNDER_CE)
        size_t m_nbMsgs;
    #endif
    #endif

        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/
        void initInstance(size_t itemSize, size_t size);
        bool enqueue(const char* pItem, size_t itemSize, 
                     bool urgent = false, int timeout = WAIT_INFINITE);
        bool dequeue(char* pItem, size_t itemSize, 
                     int timeout = WAIT_INFINITE);


};

/*****************************************************************************/
/* Class Description:                                                        */
/*****************************************************************************/
/*   Message queue template                                                  */
/*                                                                           */
/*****************************************************************************/


template <class SMsg>
class CMsgQueueT: public CMsgQueue
{
    public:

        /*********************************************************************/
        /*                     Constructor & Destructor                      */
        /*********************************************************************/
        CMsgQueueT(size_t size)
        {
            initInstance(size);
        }

        ~CMsgQueueT()
        {
        }


        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/


        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/
        bool enqueue(const SMsg& rMsg, bool urgent = false, 
                     int timeout = WAIT_INFINITE)
        {
            return CMsgQueue::enqueue((char *)&rMsg, sizeof(SMsg), 
                                      urgent, timeout);
        }

        bool dequeue(SMsg& rMsg, int timeout = WAIT_INFINITE)
        {
            return CMsgQueue::dequeue((char *)&rMsg, sizeof(SMsg), timeout);
        }


    private:

        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/


        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/
        void initInstance(size_t size)
        {
            CMsgQueue::initInstance(sizeof(SMsg), size);
        }


};

#endif //__MSG_QUEUE_H__
