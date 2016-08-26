#ifndef __GOODIES_H__
#define __GOODIES_H__
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
/*  2012-04-06 * Ricky Gong      * Creation of the file                      */
/*  2012-12-18 * Ricky Gong      * Added Linux implementations               */
/*             *                 *                                           */
/*****************************************************************************/


/*****************************************************************************/
/*                                                                           */
/*  Include Files                                                            */
/*                                                                           */
/*****************************************************************************/


/*****************************************************************************/
/*                                                                           */
/*  Definitions                                                              */
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
#include "windows.h"
#elif defined(__linux)
#include <assert.h>
#endif

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

#ifndef STR
#define _STR(x) #x
#define STR(x) _STR(x)
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
#if defined(_WIN32) && defined(UNDER_CE)
char* strdup(const char* pString);
#endif

#define strupr  strUpper
#define strlwr  strLower

#if defined(_WIN32) && defined(UNDER_CE)
int stricmp(const char* pDest, const char* pSrc);
#endif

char* strDuplicate(const char* pString);
bool strtoint(char const *pString, int& result);
char* strUpper(char* pString);
char* strLower(char* pString);
void strSplit(char* pStr, char separator, int* pArgc, char** pArgv);


/*****************************************************************************/
/* Class Description:                                                        */
/*****************************************************************************/
/*   Class packed with unicode pointer                                       */
/*                                                                           */
/*****************************************************************************/
#if defined (_UNICODE)
class CUnicodePtr
{
    public:
        CUnicodePtr(const char* p, size_t size);
        ~CUnicodePtr();
        operator wchar_t*() const;

    private:
        wchar_t* m_wp;
};

#define UNICODE_PTR(p, size) ((wchar_t*)(CUnicodePtr(p, size)))
#define TEXT_PTR(s) UNICODE_PTR(s, strlen(s))
#else
#define TEXT_PTR(s) (s)
#endif

/*****************************************************************************/
/* Class Description:                                                        */
/*****************************************************************************/
/*   Class packed with 64 bit data type                                      */
/*                                                                           */
/*****************************************************************************/
class CLong64
{
    public:
        CLong64(int hi, int lo);
        CLong64(int lo = 0);
        CLong64(double d);

        operator double() const;

        CLong64(const CLong64& rL);
        CLong64& operator=(const CLong64& rL);
        CLong64 operator-() const;

        friend CLong64 operator+(const CLong64& rL1, const CLong64& rL2);
        friend CLong64 operator-(const CLong64& rL1, const CLong64& rL2);
        friend CLong64& operator+=(CLong64& rL1, const CLong64& rL2);
        friend CLong64& operator-=(CLong64& rL1, const CLong64& rL2);
        friend bool operator==(const CLong64& rL1, const CLong64& rL2);
        friend bool operator!=(const CLong64& rL1, const CLong64& rL2);
        friend bool operator<(const CLong64& rL1, const CLong64& rL2);
        friend bool operator<=(const CLong64& rL1, const CLong64& rL2);
        friend bool operator>(const CLong64& rL1, const CLong64& rL2);
        friend bool operator>=(const CLong64& rL1, const CLong64& rL2);
        long getLo() const;
        long getHi() const;


    private:
        long    m_hi;
        long    m_lo;
};

/*****************************************************************************/
/* Class Description:                                                        */
/*****************************************************************************/
/*   Class packed with ring buffer                                           */
/*                                                                           */
/*****************************************************************************/
class CRingBuffer
{
    public:
        CRingBuffer(int size = 0);
        ~CRingBuffer();

        bool allocBuffer(int size);
        void flush();
        bool isEmpty();
        bool isFull();
        int get(char* pBuffer, int size);
        int put(char* pBuffer, int size);
        int getNbBytes();


    private:
        CRingBuffer(const CRingBuffer& rL);
        CRingBuffer& operator=(const CRingBuffer& rL);

        int     m_size;
        char*   m_pBuffer;
        char*   m_pGet;
        char*   m_pPut;
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


#endif // __GOODIES_H__

