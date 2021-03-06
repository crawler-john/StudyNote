#ifndef __SYNC_H__
#define __SYNC_H__
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
#include <pthread.h>
#include <semaphore.h>
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

#if defined(_WIN32)
#define WAIT_INFINITE    INFINITE
#define SEM_ID           HANDLE
#elif defined(__linux)
#define WAIT_INFINITE    (-1)
#define SEM_ID           sem_t *
#endif
#define OS_SEM_EMPTY     0
#define OS_SEM_FULL      1


/*****************************************************************************/
/* Class Description:                                                        */
/*****************************************************************************/
/*   Semaphore class                                                         */
/*                                                                           */
/*****************************************************************************/
class CSem		//旗语基类
{
    public:

        /*********************************************************************/
        /*                     Constructor & Destructor                      */
        /*********************************************************************/
        virtual ~CSem();


        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/


        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/
        virtual bool take(int timeout = WAIT_INFINITE);
        virtual void release();


    private:

        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/


        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/


    protected:	//构造函数写在保护区，只有子类可以使用

        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/


        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/
    #if defined(__linux)
        CSem();
    #endif
        CSem(SEM_ID id);

        SEM_ID m_id;
};

/*****************************************************************************/
/* Class Description:                                                        */
/*****************************************************************************/
/*   Binary semaphore class                                                  */
/*                                                                           */
/*****************************************************************************/
class CBinarySem: public CSem		//二进制旗语类
{
    public:

        enum EInitialState
        {
            EMPTY = OS_SEM_EMPTY,		
            FULL = OS_SEM_FULL
        };

        /*********************************************************************/
        /*                     Constructor & Destructor                      */
        /*********************************************************************/
        CBinarySem(EInitialState initialState = EMPTY);
        ~CBinarySem();


        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/


        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/
        using CSem::take;
    #if defined(_WIN32)
        using CSem::release;
    #elif defined(__linux)
        void release();
    #endif


    private:

        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/
    #if defined(__linux)
        pthread_mutex_t m_cs;
        bool bMutexInitialised;
    #endif

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


};

/*****************************************************************************/
/* Class Description:                                                        */
/*****************************************************************************/
/*   Counting semaphore class                                                */
/*                                                                           */
/*****************************************************************************/
class CCountingSem: private CSem		//计数旗语类
{
    public:

        /*********************************************************************/
        /*                     Constructor & Destructor                      */
        /*********************************************************************/
        CCountingSem(int initialCount = 0, int maxCount = 0x7FFFFFFF);
        CCountingSem(const char* pInstanceName, int initialCount = 0, 
                     int maxCount = 0x7FFFFFFF);
        ~CCountingSem();


        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/


        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/
        using CSem::take;
        bool release(int count = 1);


    private:

        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/
        int m_maxCount;

    #if defined(__linux)
        pthread_mutex_t m_cs;
        bool bMutexInitialised;
    #endif


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


};

/*****************************************************************************/
/* Class Description:                                                        */
/*****************************************************************************/
/*   Synchronous  class                                                      */
/*                                                                           */
/*****************************************************************************/
class CSync			//同步信息类
{
    public:

        /*********************************************************************/
        /*                     Constructor & Destructor                      */
        /*********************************************************************/
        CSync();
        ~CSync();


        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/


        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/
        bool wait(int timeout = WAIT_INFINITE);
        void signal();
        void broadcast();


    private:

        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/
    #if defined(_WIN32)
        HANDLE m_eventHandles[2];
    #elif defined(__linux)
        pthread_mutex_t m_mutex;
        pthread_cond_t m_cond;
        bool bInitialised;
        bool bSignalExists;
    #endif


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


};

/*****************************************************************************/
/* Class Description:                                                        */
/*****************************************************************************/
/*   Mutex class for accessing critical sections                             */
/*                                                                           */
/*****************************************************************************/
class CMutex			//互斥量
{
    public:

        /*********************************************************************/
        /*                     Constructor & Destructor                      */
        /*********************************************************************/
        CMutex();
       ~CMutex();


        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/


        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/
        bool take(int timeout = WAIT_INFINITE);
        void release();

    private:

        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/
    #if defined(_WIN32)
        CRITICAL_SECTION m_cs;
    #elif defined(__linux)
        pthread_mutex_t m_cs;
    #endif
        bool bInitialised;


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


};

/*****************************************************************************/
/* Class Description:                                                        */
/*****************************************************************************/
/*   Auto lock class for accessing mutex                                     */
/*                                                                           */
/*****************************************************************************/
class CLock				//自动互斥量锁类
{
    public:

        /*********************************************************************/
        /*                     Constructor & Destructor                      */
        /*********************************************************************/
        CLock(CMutex& rMutex);

        ~CLock();


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
        CMutex& m_rMutex;


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


};

#define AUTO_LOCK(mutex)    CLock lock(const_cast<CMutex&>(mutex));

#define DECLARE_THREAD_SAFE CMutex m_threadSafeMutex;

#define THREAD_SAFE         AUTO_LOCK(m_threadSafeMutex);

/*****************************************************************************/
/* Class Description:                                                        */
/*****************************************************************************/
/*   Condition class                                                         */
/*                                                                           */
/*****************************************************************************/
class CCondition			//条件类
{
    public:

        /*********************************************************************/
        /*                     Constructor & Destructor                      */
        /*********************************************************************/
        CCondition(CMutex& rMutex);
        ~CCondition();


        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/
        unsigned int getWaiters() const;


        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/
        CMutex& getMutex() const;
        bool enter(int timeout = WAIT_INFINITE);
        void leave();
        bool wait(int timeout = WAIT_INFINITE);
        bool signal();
        bool broadcast();


    private:

        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/
        CMutex& m_rMutex; // Associated mutex
        CMutex m_waitersMutex;
        unsigned int m_nbWaiters; // Number of waiting threads.
        CCountingSem m_waitSem;
        CBinarySem m_broadcastSem;
        bool m_broadcastInProgress;


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


};


/*****************************************************************************/
/*                                                                           */
/*  Variable Declarations                                                    */
/*                                                                           */
/*****************************************************************************/
//CSem:: CSem()

/*****************************************************************************/
/*                                                                           */
/*  Function Declarations                                                    */
/*                                                                           */
/*****************************************************************************/


#endif //__SYNC_H__

