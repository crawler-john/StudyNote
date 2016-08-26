#ifndef __SINGLEINST_H__
#define __SINGLEINST_H__
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
/*  2011-10-14 * Ricky Gong      * Creation of the file                      */
/*  2012-02-11 * Ricky Gong      * Moved the initialization and deletion code*/
/*             *                 *  of mutex from constructor or destructor  */
/*             *                 * to createInst() and deleteInst()          */
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


/*****************************************************************************/
/* Class Description:                                                        */
/*****************************************************************************/
/*   Single instance template class                                          */
/*                                                                           */
/*   The single instance will allow to create the class instance only once in*/
/*   global                                                                  */
/*                                                                           */
/*****************************************************************************/
template <class T> 
class CSingleInstT
{
    public:

        /*********************************************************************/
        /*                     Constructor & Destructor                      */
        /*********************************************************************/
        CSingleInstT()
        {
        }

        ~CSingleInstT()
        {
        }

        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/


        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/
        static void createInst()
        {
        #if defined(_WIN32)
            InitializeCriticalSection(&threadSafeMutex);
        #elif defined(__linux)
            // here we don't invoke mutex initialisation (pthread_mutex_init) 
            // because the static mutex has already initialised in instance 
            // decleration field (global or static mutex can be initialised 
            // like this) and to avoid initialize twice time
        #endif

            // Using double checked locking pattern
            if (pInst == 0)
            {
            #if defined(_WIN32)
                EnterCriticalSection(&threadSafeMutex);
            #elif defined(__linux)
                pthread_mutex_lock(&threadSafeMutex);
            #endif

                if (pInst == 0)
                {
                    pInst = new T;
                }

            #if defined(_WIN32)
                LeaveCriticalSection(&threadSafeMutex);
            #elif defined(__linux)
                pthread_mutex_unlock(&threadSafeMutex);
            #endif
            }
        }

        static void deleteInst()
        {
        #if defined(_WIN32)
            EnterCriticalSection(&threadSafeMutex);
        #elif defined(__linux)
            pthread_mutex_lock(&threadSafeMutex);
        #endif

            delete pInst;
            pInst = 0;

        #if defined(_WIN32)
            LeaveCriticalSection(&threadSafeMutex);
        #elif defined(__linux)
            pthread_mutex_unlock(&threadSafeMutex);
        #endif

        #if defined(_WIN32)
            DeleteCriticalSection(&threadSafeMutex);
        #elif defined(__linux)
            pthread_mutex_destroy(&threadSafeMutex);
        #endif
        }

        static T& instance()
        {
            if (pInst == 0)
            {
            #if defined(_WIN32)
                EnterCriticalSection(&threadSafeMutex);
            #elif defined(__linux)
                pthread_mutex_lock(&threadSafeMutex);
            #endif

                ASSERT(pInst != 0);

            #if defined(_WIN32)
                LeaveCriticalSection(&threadSafeMutex);
            #elif defined(__linux)
                pthread_mutex_unlock(&threadSafeMutex);
            #endif
            }

            return *pInst;
        }

        static bool isCreated()
        {
            return ((pInst) ? true : false);
        }


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
        static T* volatile pInst;
        static const char* pClassName;
    #if defined(_WIN32)
        static CRITICAL_SECTION threadSafeMutex;
    #elif defined(__linux)
        static pthread_mutex_t threadSafeMutex;
    #endif


        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/

};

#define CSingleInst CSingleInstT

#if defined(_WIN32)
#if !defined(UNDER_CE)
#define DECLARE_SINGLE_INST(class) \
template<> class* volatile CSingleInstT<class>::pInst = 0; \
template<> const char* CSingleInstT<class>::pClassName = #class; \
template<> CRITICAL_SECTION CSingleInstT<class>::threadSafeMutex = {NULL, 0, 0, NULL, NULL, 0};
#else // #if !defined(UNDER_CE)
#define DECLARE_SINGLE_INST(class) \
template<> class* volatile CSingleInstT<class>::pInst = 0; \
template<> const char* CSingleInstT<class>::pClassName = #class; \
template<> CRITICAL_SECTION CSingleInstT<class>::threadSafeMutex = {0, NULL, NULL, 0, 0};
#endif // #if !defined(UNDER_CE)

#elif defined(__linux) // #if defined(_WIN32)

#define DECLARE_SINGLE_INST(class) \
template<> class* volatile CSingleInstT<class>::pInst = 0; \
template<> const char* CSingleInstT<class>::pClassName = #class; \
template<> pthread_mutex_t CSingleInstT<class>::threadSafeMutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
#endif // #if defined(_WIN32)

#define CREATE_SINGLE_INST(class) CSingleInstT<class>::createInst()

#define DELETE_SINGLE_INST(class) CSingleInstT<class>::deleteInst()

#define SINGLE_INST_CREATED(class) CSingleInstT<class>::isCreated()


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


#endif //__SINGLEINST_H__

