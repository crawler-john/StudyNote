#ifndef __SERIAL_H__
#define __SERIAL_H__
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
/*  2013-05-27 * Ricky Gong      * Added return value on initInstatnce()     */
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

#include <map>
#include <string>
#if defined(_WIN32)
#include "windows.h"
#endif

#include "goodies.h"
#include "sync.h"


/*****************************************************************************/
/*                                                                           */
/*  Definitions                                                              */
/*                                                                           */
/*****************************************************************************/
#define SERIAL_DFLT_RECV_BUF_SIZE 512

#if defined(_WIN32)
#define SERIAL_ID                HANDLE
#define INVALID_SERIAL_ID        INVALID_HANDLE_VALUE
#define WAIT_INFINITE            INFINITE
#elif defined(__linux)
#define SERIAL_ID                int
#define INVALID_SERIAL_ID        (-1)
#define WAIT_INFINITE            (-1)
#endif

enum ERsMode
{
    RS232,
    RS422,
    RS485,
    RS485_AUTO_RTS_POSITIVE_POLARITY,
    RS485_AUTO_RTS_NEGATIVE_POLARITY
};

enum
{
    HARD_OPT_CSIZE      = 0x000C,   // bits 3 and 4 encode the character size
    HARD_OPT_CS5        = 0x0000,   // 5 bits
    HARD_OPT_CS6        = 0x0004,   // 6 bits
    HARD_OPT_CS7        = 0x0008,   // 7 bits
    HARD_OPT_CS8        = 0x000C,   // 8 bits

    HARD_OPT_STOPB      = 0x0020,   // send two stop bits (else one)

    HARD_OPT_CPARITY    = 0x00C0,
    HARD_OPT_PARENB     = 0x0040,   // parity detection enabled (else disabled)
    HARD_OPT_PARODD     = 0x0080,   // odd parity  (else even)

    HARD_OPT_FIFO_TRIGGER       = 0xFF00,
    HARD_OPT_FIFO_ENABLE        = 0x0700,   // TX_CLEAR | RX_CLEAR | FIFO_EN
    HARD_OPT_FIFO_TRIGGER_1     = (0x0000 | HARD_OPT_FIFO_ENABLE),
    HARD_OPT_FIFO_TRIGGER_4     = (0x4000 | HARD_OPT_FIFO_ENABLE),
    HARD_OPT_FIFO_TRIGGER_8     = (0x8000 | HARD_OPT_FIFO_ENABLE),
    HARD_OPT_FIFO_TRIGGER_14    = (0xC000 | HARD_OPT_FIFO_ENABLE)
};

enum EModemControl
{
    MODEM_DTR = 0x01,   // MCR_DTR
    MODEM_RTS = 0x02    // MCR_RTS
};

enum EModemStatus
{
    MODEM_CTS = 0x10,   // MSR_CTS
    MODEM_DSR = 0x20,   // MSR_DSR
    MODEM_RI  = 0x40,   // MSR_RI
    MODEM_DCD = 0x80    // MSR_DCD
};


/*****************************************************************************/
/* Class Description:                                                        */
/*****************************************************************************/
/*   Class packed with serial communication functions                        */
/*                                                                           */
/*****************************************************************************/
class CSerial 
{
    public:

        /*********************************************************************/
        /*                     Constructor & Destructor                      */
        /*********************************************************************/
        CSerial();
        CSerial(const char* pPortName, unsigned long baudRate,
                unsigned short hwOptions, ERsMode rsMode,
                unsigned long recvBufSize = SERIAL_DFLT_RECV_BUF_SIZE,
                bool sharedInstance = false);
        virtual ~CSerial();


        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/


        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/
        void write(const char* pBuffer, size_t nbCharToWrite);
        size_t read(char* pBuffer, size_t nbCharToRead,
                    int timeout = WAIT_INFINITE);
        void abortRead();
        void flushReadBuffer();
        bool isOverflow();
        void enableReceive();
        void disableReceive();
        void setBaudRate(unsigned long baudRate);
        unsigned long getBaudRate();
        void setModemControl(int control);
        int getModemControl();
        int getModemStatus();
        SERIAL_ID getId() const;
        bool isShared() const;
        static CSerial* getSharedComPort(const char* pSerialPortName);


    protected:
        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/
        unsigned long       m_baudRate;
        SERIAL_ID           m_id;
        bool                m_sharedInstance;


        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/
        bool initInstance(const char* pPortName, unsigned long baudRate,
                          unsigned short hwOptions, ERsMode rsMode,
                          unsigned long recvBufSize = SERIAL_DFLT_RECV_BUF_SIZE,
                          bool sharedInstance = false);


    private:
        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/
        std::string         m_portName;
        CSync               m_receiveCharSync;
        bool                m_waitingForReceivedChar;
        size_t              m_nbExpectedChar;
        size_t              m_nbReceivedChar;

        bool                m_receiveEnabled;
        bool                m_receiveOverflow;
        CRingBuffer         m_receiveBuffer;

    #if defined(_WIN32) && !defined(UNDER_CE)
        OVERLAPPED          m_writeOverlapped;
    #endif
        unsigned char       m_modemStatus;

        friend class CSerialInterruptEmulationThread;
        class CSerialInterruptEmulationThread*  m_pInterruptEmulationThread;

        typedef std::map<std::string, CSerial*> TSerialComMap;
        static TSerialComMap s_comPortsInUse;
        static CMutex       s_comPortsInUseMutex;

        CMutex          m_lockMutex;


        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/
        virtual void doSetModemControl(int control);
        virtual int doGetModemControl();
        virtual int doGetModemStatus();
        bool receiveCharHook0(int receivedChar);
        virtual bool receiveCharHook(int receivedChar);
        virtual void modemStatusChangeHook(unsigned char &modemStatus);


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


#endif // __SERIAL_H__
