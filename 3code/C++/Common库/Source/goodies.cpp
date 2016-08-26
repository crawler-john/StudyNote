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
/*             *                 *                                           */
/*****************************************************************************/


/*****************************************************************************/
/*                                                                           */
/*  Include Files                                                            */
/*                                                                           */
/*****************************************************************************/
#include <string.h>
#include <ctype.h>

#include "goodies.h"



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
/*  Function Declarations                                                    */
/*                                                                           */
/*****************************************************************************/


/*****************************************************************************/
/*                                                                           */
/*  Function Implementations                                                 */
/*                                                                           */
/*****************************************************************************/
#if defined(_WIN32) && defined(UNDER_CE)
char* strdup(const char* pString)
{
    if (!pString)
    {
        return NULL;
    }

    size_t  size = strlen(pString);
    char* p = (char*)malloc(size + 1);  // +1 for '\0'
    strcpy(p, pString);
    p[size] = '\0';
    return p;
}
#endif

#if defined(_WIN32) && defined(UNDER_CE)
int stricmp(const char* pDest, const char* pSrc)
{
    int f,l;

    do
    {
        if(((f = (unsigned char)(*(pDest++))) >= 'A') && (f <= 'Z'))
        {
            f -= ('A' - 'a');
        }

        if(((l = (unsigned char)(*(pSrc++))) >= 'A') && (l <= 'Z'))
        {
            l -= ('A' - 'a');
        }
    } while (f && (f == l));

    return(f - l);
}
#endif

char* strDuplicate(const char* pString)
{
    if (!pString)
    {
        return NULL;
    }

    size_t  size = strlen(pString);
    char* p = new char[size + 1];   // +1 for '\0'
    strcpy(p, pString);
    p[size] = '\0';
    return p;
}

bool strtoint(char const  *pString, int& result)
{
    char const  *p;
    char        c;
    bool        negative = false;

    if (*pString == '-')
    {
        pString++;
        negative = true;
    }

    if ((strncmp(pString, "0x", 2) == 0) || (strncmp(pString, "0X", 2) == 0))
    {
        // Hexadecimal

        if (strlen(pString+2) > 8) // 8 xdigits max
        {
            return false;
        }

        p = pString+2;
        result = 0;
        while ((c = *p++) != '\0')
        {
            if (!isxdigit(c))
            {
                return false;
            }

            result = (result << 4) + (isdigit(c) ? (c - '0') : (islower(c) ? (c + 0xA - 'a') : (c + 0xA - 'A')));
        }
    }

    else
    {
        // Decimal

        p = pString;
        result = 0;
        while ((c = *p++) != '\0')
        {
            if (!isdigit(c))
            {
                return false;
            }

            result = (10 * result) + (c - '0');
            if (result < 0)
            {
                // number too big
                return false;
            }
        }
    }

    if (negative)
    {
        result = -result;
    }

    return true;
}

char* strUpper(char* pString)
{
    if (pString)
    {
        for (unsigned int i = strlen(pString) - 1; i > 0; i--)
        {
            char c = pString[i];
            if (islower(c))
            {
                pString[i] = toupper(c);
            }
        }
    }

    return pString;
}

char* strLower(char* pString)
{
    if (pString)
    {
        for (unsigned int i = strlen(pString) - 1; i > 0; i--)
        {
            char c = pString[i];
            if (isupper(c))
            {
                pString[i] = tolower(c);
            }
        }
    }

    return pString;
}

void strSplit(char* pStr, char separator, int* pArgc, char** pArgv)
{
    if (pArgc == 0)
    {
        return;
    }

    if (pStr == 0)
    {
        *pArgc = 0;
        return;
    }

    if (*pStr == '\0')
    {
        *pArgc = 0;
        return;
    }

    char*   p;

    // At least one arg !
    *pArgc = 1;
    for (p = pStr; *p != '\0'; p++)
    {
        if (*p == separator)
        {
            (*pArgc)++;
        }
    }

    int argvSize = *pArgc;
    if ((argvSize == 0) || (pArgv == 0))
    {
        // We've just computed argc
        return;
    }

    int i = 0;
    pArgv[i++] = pStr;
    for (p = pStr; (*p != '\0') && (i < argvSize); p++)
    {
        if (*p == separator)
        {
            *p = '\0';
            pArgv[i++] = p+1;
        }
    }
}

#if defined (_UNICODE) || defined (UNICODE)
CUnicodePtr::CUnicodePtr(const char* p, size_t size)
{
    if (p == 0)
    {
        m_wp = 0;
    }
    else
    {
        m_wp = new wchar_t[size + 1];
        MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, p, -1, m_wp, size);
        m_wp[size] = 0;
    }
}

CUnicodePtr::~CUnicodePtr()
{
    delete[] m_wp;
}

CUnicodePtr::operator wchar_t*() const
{
    return m_wp;
}
#endif


const double    __2E32 = 4294967296.0;              // 2^32
const double    __2E64 = 18446744073709551616.0;    // 2^64

CLong64::CLong64(int hi, int lo)
    : m_hi(hi),
      m_lo(lo)
{
}

CLong64::CLong64(int lo)
    : m_lo(lo)
{
    if (lo >= 0)
    {
        m_hi = 0;
    }
    else
    {
        m_hi = -1;
    }
}

CLong64::CLong64(double d)
    : m_hi((d >= 0) ? long(d / __2E32) : (unsigned long)((d + __2E64) / __2E32)),
      m_lo(long(d - (m_hi*__2E32)))
{
}

CLong64::operator double() const
{
    return (m_hi*__2E32 + (unsigned long)m_lo);
}

CLong64::CLong64(const CLong64& rL)
    : m_hi(rL.m_hi),
      m_lo(rL.m_lo)
{
}

CLong64& CLong64::operator=(const CLong64& rL)
{
    if (&rL != this)
    {
        m_lo = rL.m_lo;
        m_hi = rL.m_hi;
    }

    return *this;
}

CLong64 CLong64::operator-() const
{
    return CLong64(-m_hi - 1, -m_lo);
}

CLong64 operator+(const CLong64& rL1, const CLong64& rL2)
{
    int hi = rL1.m_hi + rL2.m_hi;
    int lo = rL1.m_lo + rL2.m_lo;

    if ((unsigned)lo < (unsigned)rL1.m_lo)
    {
        hi++;
    }

    return CLong64(hi, lo);
}

CLong64 operator-(const CLong64& rL1, const CLong64& rL2)
{
    int hi = rL1.m_hi - rL2.m_hi;
    int lo = rL1.m_lo - rL2.m_lo;

    if ((unsigned)lo > (unsigned)rL1.m_lo)
    {
        hi--;
    }

    return CLong64(hi, lo);
}

CLong64& operator+=(CLong64& rL1, const CLong64& rL2)
{
    int lo = rL1.m_lo + rL2.m_lo;
    int hi = rL1.m_hi + rL2.m_hi;

    if ((unsigned)lo < (unsigned)rL1.m_lo)
    {
        hi++;
    }

    rL1.m_hi = hi;
    rL1.m_lo = lo;

    return rL1;
}

CLong64& operator-=(CLong64& rL1, const CLong64& rL2)
{
    int lo = rL1.m_lo - rL2.m_lo;
    int hi = rL1.m_hi - rL2.m_hi;

    if ((unsigned)lo > (unsigned)rL1.m_lo)
    {
        hi--;
    }

    rL1.m_hi = hi;
    rL1.m_lo = lo;

    return rL1;
}

bool operator==(const CLong64& rL1, const CLong64& rL2)
{
    return (rL1.m_lo == rL2.m_lo) && (rL1.m_hi == rL2.m_hi);
}

bool operator!=(const CLong64& rL1, const CLong64& rL2)
{
    return !((rL1.m_lo == rL2.m_lo) && (rL1.m_hi == rL2.m_hi));
}

bool operator<(const CLong64& rL1, const CLong64& rL2)
{
    return ((rL1.m_hi < rL2.m_hi) || ((rL1.m_hi == rL2.m_hi) && (rL1.m_lo < rL2.m_lo)));
}

bool operator<=(const CLong64& rL1, const CLong64& rL2)
{
    return ((rL1.m_hi < rL2.m_hi) || ((rL1.m_hi == rL2.m_hi) && (rL1.m_lo <= rL2.m_lo)));
}

bool operator>(const CLong64& rL1, const CLong64& rL2)
{
    return ((rL1.m_hi > rL2.m_hi) || ((rL1.m_hi == rL2.m_hi) && (rL1.m_lo > rL2.m_lo)));
}

bool operator>=(const CLong64& rL1, const CLong64& rL2)
{
    return ((rL1.m_hi > rL2.m_hi) || ((rL1.m_hi == rL2.m_hi) && (rL1.m_lo >= rL2.m_lo)));
}

long CLong64::getLo() const
{
    return m_lo;
}

long CLong64::getHi() const
{
    return m_hi;
}

// ----------------------------------------------------------------------------

// WARNING :
//  - implicit thread safe for ONE reader and ONE writer
//  - need explicit protection (mutex) if more than one reader and one writer

CRingBuffer::CRingBuffer(int size)
    : m_size(size),
      m_pBuffer(NULL),
      m_pGet(NULL),
      m_pPut(NULL)
{
    if (size == 0)
    {
        m_size = 0;
        m_pGet = 0;
        m_pPut = 0;
    }
    else
    {
        bool status = allocBuffer(size);
        ASSERT(status);
        // Pacify the compiler if NDEBUG set
        status = status;
    }
}

CRingBuffer::~CRingBuffer()
{
    if (m_pBuffer)
    {
        delete[] m_pBuffer;
    }
}

bool CRingBuffer::allocBuffer(int size)
{
    if (size == 0)
    {
        return false;
    }

    size += 1;  // At least 1 char difference between m_pGet & m_pPut
    char* pBuffer = new char[size];

    if (pBuffer == 0)
    {
        return false;
    }

    if (m_pBuffer)
    {
        delete[] m_pBuffer;
    }

    m_size = size;
    m_pBuffer = pBuffer;
    m_pGet = m_pBuffer;
    m_pPut = m_pBuffer;

    return true;
}

void CRingBuffer::flush()
{
    m_pGet = m_pBuffer;
    m_pPut = m_pBuffer;
}

bool CRingBuffer::isEmpty()
{
    return (m_pGet == m_pPut);
}

bool CRingBuffer::isFull()
{
    return (((m_pGet - m_pPut) == 1) || ((m_pPut - m_pGet) == (m_size - 1)));
}

int CRingBuffer::get(char* pBuffer, int size)
{
    int copySize;
    int diff        = m_pPut - m_pGet;

    if (diff >= 0)
    {
    //    <------------------- m_size --------------------->
    //    +------------------------------------------------+
    //    |           |x x x x x x x x x x x|              |
    //    +------------------------------------------------+
    //     ^           ^                     ^
    //     |           |                     |
    // m_pBuffer     m_pGet                m_pPut

        copySize = (diff >= size) ? size : diff;
        memcpy(pBuffer, m_pGet, copySize);
        m_pGet += copySize;
    }
    else
    {
    //    <------------------- m_size -------------------->
    //    +-----------------------------------------------+
    //    |x x x x x x|                     |x x x x x x x|
    //    +-----------------------------------------------+
    //     ^           ^                     ^             ^
    //     |           |                     |             |
    // m_pBuffer     m_pPut                m_pGet    m_pBuffer + m_size

        int diff1 = m_pBuffer + m_size - m_pGet;
        if (diff1 >= size)
        {
            copySize = size;
            memcpy(pBuffer, m_pGet, copySize);
            if ((m_pGet + copySize) == (m_pBuffer + m_size))
            {
                // wrap around
                m_pGet = m_pBuffer;
            }
            else
            {
                m_pGet += copySize;
            }
        }
        else
        {
            memcpy(pBuffer, m_pGet, diff1);

            int diff2 = m_pPut - m_pBuffer;
            int copySize2 = (diff2 >= (size - diff1)) ? (size - diff1) : diff2;
            memcpy(pBuffer + diff1, m_pBuffer, copySize2);

            copySize = diff1 + copySize2;
            m_pGet -= (m_size - copySize);
        }
    }

    return copySize;
}

int CRingBuffer::put(char* pBuffer, int size)
{
    int copySize;
    int diff        = m_pGet - m_pPut;

    if (diff > 0)
    {
        //    <------------------- m_size -------------------->
        //    +-----------------------------------------------+
        //    |x x x x x x|                     |x x x x x x x|
        //    +-----------------------------------------------+
        //     ^           ^                     ^
        //     |           |                     |
        // m_pBuffer     m_pPut                m_pGet

        // at least 1 char difference between m_pGet & m_pPut
        copySize = (diff > size) ? size : (diff - 1);
        memcpy(m_pPut, pBuffer, copySize);
        m_pPut += copySize;
    }
    else
    {
        //    <------------------- m_size --------------------->
        //    +------------------------------------------------+
        //    |           |x x x x x x x x x x x|              |
        //    +------------------------------------------------+
        //    ^           ^                     ^               ^
        //    |           |                     |               |
        // m_pBuffer     m_pGet                m_pPut       m_pBuffer + m_size

        int diff1 = m_pBuffer + m_size - m_pPut;
        if (diff1 > size)
        {
            copySize = size;
            memcpy(m_pPut, pBuffer, copySize);
            m_pPut += copySize;
        }
        else
        {
            if (m_pGet == m_pBuffer)
            {
                copySize = diff1 - 1;
                memcpy(m_pPut, pBuffer, copySize);
                m_pPut += copySize;
            }
            else
            {
                memcpy(m_pPut, pBuffer, diff1);

                int diff2 = m_pGet - m_pBuffer;
                int copySize2 = (diff2 > (size - diff1)) ? (size - diff1) : diff2 - 1;
                memcpy(m_pBuffer, pBuffer + diff1, copySize2);

                copySize = diff1 + copySize2;
                m_pPut -= (m_size - copySize);
            }
        }
    }

    return copySize;
}

int CRingBuffer::getNbBytes()
{
    int diff = m_pPut - m_pGet;
    return (diff >= 0) ? diff : diff + m_size;
}

