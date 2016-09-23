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
/*  2012-11-15 * Ricky Gong      * Fixed a bug, which not break immediately  */
/*             *                 * in case of WaitCommEvent returns failure  */
/*             *                 * and cause the thread busy abnormally      */
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

#include <map>
#include <string>

#if defined(__linux)
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <errno.h>
#endif

#include "thread.h"
#include "serial.h"


/*****************************************************************************/
/*                                                                           */
/*  Definitions                                                              */
/*                                                                           */
/*****************************************************************************/
#if defined(_WIN32)
class CSerialInterruptEmulationThread: public CThread
{
    public:

        /*********************************************************************/
        /*                     Constructor & Destructor                      */
        /*********************************************************************/
        CSerialInterruptEmulationThread(CSerial* pSerialCom)
            : CThread(),
              m_pSerialCom(pSerialCom),
              m_startSync()
        {
            CThread::initInstance(NULL, 10000, THREAD_MAX_PRIORITY);

            start();
            m_startSync.wait();
        }
        ~CSerialInterruptEmulationThread()
        {
            // call stop() in the destructor since stop() is overloaded
            // (CThread::~CThread() can't call the overloaded stop() in the derived class)
            stop();
        }
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
        CSerial* m_pSerialCom;
        CSync m_startSync;


        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/
        int run()
        {
        #if defined(_WIN32) && !defined(UNDER_CE)
            OVERLAPPED  overlapped = {0};
            // manual reset event with initial state false
            overlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        #endif
            if((m_pSerialCom != NULL) && (m_pSerialCom->m_id != INVALID_SERIAL_ID))
            {
                SetCommMask(m_pSerialCom->m_id, EV_RXCHAR | EV_CTS | EV_DSR | EV_RING);
            }

            m_startSync.signal();

            // here to check the status of modem status bits on initialization
            unsigned char modemStatus = 0;
            DWORD curStatus;
            if((m_pSerialCom != NULL) && (m_pSerialCom->m_id != INVALID_SERIAL_ID))
            {
                if(GetCommModemStatus(m_pSerialCom->m_id, &curStatus))
                {
                    if (curStatus & MS_CTS_ON)
                    {
                        modemStatus |= MODEM_CTS;
                    }
                    if (curStatus & MS_DSR_ON)
                    {
                        modemStatus |= MODEM_DSR;
                    }
                    if (curStatus & MS_RING_ON)
                    {
                        modemStatus |= MODEM_RI;
                    }
                    m_pSerialCom->modemStatusChangeHook(modemStatus);
                }
            }

            DWORD   eventFlags;
            do
            {
                DWORD   nbCharRead;

                if((m_pSerialCom != NULL) && (m_pSerialCom->m_id != INVALID_SERIAL_ID))
                {
                    if (!WaitCommEvent(m_pSerialCom->m_id, &eventFlags,
                                    #if defined(_WIN32) && !defined(UNDER_CE)
                                       &overlapped))
                                    #elif defined(_WIN32) && defined(UNDER_CE)
                                       0))
                                    #endif
                    {
                        DWORD lastError = GetLastError();
                    #if defined(_WIN32) && !defined(UNDER_CE)
                        if (lastError == ERROR_IO_PENDING)
                        {
                            // Wait forever until a char is received or modem lines status has changed
                            GetOverlappedResult(m_pSerialCom->m_id, &overlapped,
                                                &nbCharRead, TRUE);
                        }
                        else
                    #endif
                        {
                            ASSERT(false);
                        }
                    }

                    if (eventFlags & EV_RXCHAR)
                    {
                        DWORD   errorFlags  = 0;
                        COMSTAT comStat;

                        if (!ClearCommError(m_pSerialCom->m_id, &errorFlags, &comStat))
                        {
                            //DWORD lastError = GetLastError();
                            ASSERT(false);
                        }

                        if (errorFlags != 0)
                        {
                            //  WARNING : errorFlags apply to all characters in queue
                        }
                        else
                        {
                            while (comStat.cbInQue)
                            {
                                const int   TMPBUF_SIZE = 100;
                                BYTE        tmpBuf[TMPBUF_SIZE];
                                DWORD       nbCharToRead = (comStat.cbInQue <= (unsigned int)TMPBUF_SIZE) ? comStat.cbInQue : TMPBUF_SIZE;

                                if (!ReadFile(m_pSerialCom->m_id, tmpBuf, 
                                              nbCharToRead, &nbCharRead,
                                        #if defined(_WIN32) && !defined(UNDER_CE)
                                              &overlapped))
                                        #elif defined(_WIN32) && defined(UNDER_CE)
                                              0))
                                        #endif
                                {
                                    DWORD lastError = GetLastError();
                                #if defined(_WIN32) && !defined(UNDER_CE)
                                    if (lastError == ERROR_IO_PENDING)
                                    {
                                        // should not block since we get what has been received
                                        GetOverlappedResult(m_pSerialCom->m_id, 
                                                            &overlapped, &nbCharRead,
                                                            TRUE);
                                    }
                                    else
                                #endif
                                    {
                                        ASSERT(false);
                                    }
                                }

                                for (unsigned int i = 0; i < nbCharRead; i++)
                                {
                                    m_pSerialCom->receiveCharHook0(tmpBuf[i]);
                                }

                                comStat.cbInQue -= nbCharRead;
                            }
                        }
                    }


                    if (eventFlags & (EV_CTS | EV_DSR | EV_RING))
                    {
                        modemStatus = 0;
                        if(GetCommModemStatus(m_pSerialCom->m_id, &curStatus))
                        {
                            if (curStatus & MS_CTS_ON)
                            {
                                modemStatus |= MODEM_CTS;
                            }
                            if (curStatus & MS_DSR_ON)
                            {
                                modemStatus |= MODEM_DSR;
                            }
                            if (curStatus & MS_RING_ON)
                            {
                                modemStatus |= MODEM_RI;
                            }
                            m_pSerialCom->modemStatusChangeHook(modemStatus);
                        }
                    }
                }
                else
                {
                    break;
                }
            } while(!m_stopRequest);

        #if defined(_WIN32) && !defined(UNDER_CE)
            CloseHandle(overlapped.hEvent);
        #endif

            return STOPPED;
        }

        void stop()
        {
            m_stopRequest = true;
            // Change CommMask => the InterruptEmulationThread will return from WaitCommEvent() with a eventFlags = 0
            if((m_pSerialCom != NULL) && (m_pSerialCom->m_id != INVALID_SERIAL_ID))
            {
                SetCommMask(m_pSerialCom->m_id, 0);
            }
        }


};
#elif defined(__linux)
class CSerialInterruptEmulationThread: public CThread
{
    public:

        /*********************************************************************/
        /*                     Constructor & Destructor                      */
        /*********************************************************************/
        CSerialInterruptEmulationThread(CSerial* pSerialCom)
            : CThread(),
              m_pSerialCom(pSerialCom),
              m_startSync()
        {
            CThread::initInstance(NULL, 10000, THREAD_MAX_PRIORITY);

            start();
            m_startSync.wait();
        }
        ~CSerialInterruptEmulationThread()
        {
            // call stop() in the destructor since stop() is overloaded
            // (CThread::~CThread() can't call the overloaded stop() in the derived class)
            stop();
        }
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
        CSerial* m_pSerialCom;
        CSync m_startSync;


        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/
        int run()
        {
            m_startSync.signal();

            int nret = -1;
            fd_set rfds;
            struct timeval tv;

            do
            {
                /* Wait until character received or timeout. Recover in case of an
                 * interrupted read system call. */
                if((m_pSerialCom!= NULL) && (m_pSerialCom->m_id != INVALID_SERIAL_ID))
                {
                    // wait every 1ms
                    tv.tv_sec = 0;
                    tv.tv_usec = 1000;
                    FD_ZERO(&rfds);
                    FD_SET(m_pSerialCom->m_id, &rfds);

                    nret = select(m_pSerialCom->m_id + 1, &rfds, NULL, NULL, &tv);

                    // timeout if zero
                    if(nret == 0)
                    {
                    }
                    // data available to read
                    else if(nret > 0)
                    {
                        // check if there's data to read on serial port
                        if(FD_ISSET(m_pSerialCom->m_id, &rfds))
                        {
                            const int TMPBUF_SIZE = 100;
                            char tmpBuf[TMPBUF_SIZE];
                            ssize_t nbCharRead = 0;

                            while((nbCharRead = ::read(m_pSerialCom->m_id, tmpBuf, TMPBUF_SIZE)) == -1)
                            {
                                if(errno == EINTR)
                                {
                                    continue; // continue reading on interrupted by a signal
                                }
                                else
                                {
                                    printf("serial port read: %s\n", strerror(errno));
                                    ASSERT(false);
                                    break;
                                }
                            }

                            for(ssize_t i = 0; i < nbCharRead; i++)
                            {
                                m_pSerialCom->receiveCharHook0(tmpBuf[i]);
                            }
                        }
                    }
                    // errors
                    else
                    {
                        // continue reading on interrupted by a signal
                        if(errno != EINTR)
                        {
                            printf("serial port select: %s\n", strerror(errno));
                            ASSERT(false);
                            break;
                        }
                    }

                    int controlbits = 0;
                    nret = ioctl(m_pSerialCom->m_id, TIOCMGET, &controlbits);
                    if(nret != -1)
                    {
                        // some USB to RS232 cables can't support this and will return -1
                        unsigned char modemStatus = 0;
                        if(controlbits & TIOCM_CTS)
                        {
                            modemStatus |= MODEM_CTS;
                        }
                        if(controlbits & TIOCM_DSR)
                        {
                            modemStatus |= MODEM_DSR;
                        }
                        if(controlbits & TIOCM_RNG)
                        {
                            modemStatus |= MODEM_RI;
                        }
                        if(controlbits & TIOCM_CAR)
                        {
                            modemStatus |= MODEM_DCD;
                        }
                        m_pSerialCom->modemStatusChangeHook(modemStatus);
                    }
                }
                else
                {
                    // file discriptor error
                    break;
                }
            } while(!m_stopRequest);

            return STOPPED;
        }

        void stop()
        {
            m_stopRequest = true;
        }


};
#endif


/*****************************************************************************/
/*                                                                           */
/*  Variable Declarations                                                    */
/*                                                                           */
/*****************************************************************************/
CSerial::TSerialComMap  CSerial::s_comPortsInUse;
CMutex                  CSerial::s_comPortsInUseMutex;


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
/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Constructor                                                             */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
CSerial::CSerial()
    : m_baudRate(0),
      m_id(INVALID_SERIAL_ID),
      m_sharedInstance(false),
      m_portName(),
      m_receiveCharSync(),
      m_waitingForReceivedChar(false),
      m_nbExpectedChar(0),
      m_nbReceivedChar(0),
      m_receiveEnabled(false),
      m_receiveOverflow(false),
      m_receiveBuffer(),
      m_modemStatus(0),
      m_pInterruptEmulationThread(0),
      m_lockMutex()
{
#if defined(_WIN32) && !defined(UNDER_CE)
    m_writeOverlapped.hEvent = INVALID_HANDLE_VALUE;
#endif
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Constructor                                                             */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   pPortName[in]:         serial port name string                          */
/*   baudRate[in]:          serial port baud rate                            */
/*   hwOptions[in]:         hardware options settings                        */
/*   rsMode[in]:            serial port mode                                 */
/*   recvBufSize[in]:       receive buffer size                              */
/*   sharedInstance[in]:    shared serial port or not                        */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
CSerial::CSerial(const char* pPortName, unsigned long baudRate,
                 unsigned short hwOptions, ERsMode rsMode,
                 unsigned long recvBufSize, bool sharedInstance)
    : m_baudRate(baudRate),
      m_id(INVALID_SERIAL_ID),
      m_sharedInstance(false),
      m_portName(),
      m_receiveCharSync(),
      m_waitingForReceivedChar(false),
      m_nbExpectedChar(0),
      m_nbReceivedChar(0),
      m_receiveEnabled(false),
      m_receiveOverflow(false),
      m_receiveBuffer(),
      m_modemStatus(0),
      m_pInterruptEmulationThread(0),
      m_lockMutex()
{
#if defined(_WIN32) && !defined(UNDER_CE)
    m_writeOverlapped.hEvent = INVALID_HANDLE_VALUE;
#endif
    initInstance(pPortName, baudRate, hwOptions, 
                 rsMode, recvBufSize, sharedInstance);
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Destructor                                                              */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
CSerial::~CSerial()
{
    TSerialComMap::iterator i;
    if ((i = s_comPortsInUse.find(m_portName)) != s_comPortsInUse.end())
    {
        s_comPortsInUse.erase(i);
    }
    m_portName = "";

    delete m_pInterruptEmulationThread;
#if defined(_WIN32)
    if (m_id != INVALID_SERIAL_ID)
    {
        CloseHandle(m_id);
        m_id = INVALID_SERIAL_ID;
    }

#if defined(_WIN32) && !defined(UNDER_CE)
    if (m_writeOverlapped.hEvent != INVALID_HANDLE_VALUE)
    {
        CloseHandle(m_writeOverlapped.hEvent);
    }
#endif
#elif defined(__linux)
    if(m_id != INVALID_SERIAL_ID )
    {
        close(m_id);
        m_id = INVALID_SERIAL_ID;
    }
#endif
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Initialise function                                                     */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   pPortName[in]:         serial port name string                          */
/*   baudRate[in]:          serial port baud rate                            */
/*   hwOptions[in]:         hardware options settings                        */
/*   rsMode[in]:            serial port mode                                 */
/*   recvBufSize[in]:       receive buffer size                              */
/*   sharedInstance[in]:    shared serial port or not                        */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
bool CSerial::initInstance(const char* pPortName, unsigned long baudRate,
                           unsigned short hwOptions, ERsMode rsMode,
                           unsigned long recvBufSize, bool sharedInstance)
{
    CLock lockComPorts(s_comPortsInUseMutex);

    m_portName = std::string(pPortName);

    if (s_comPortsInUse.find(std::string(pPortName)) != s_comPortsInUse.end())
    {
        // port already in use
        ASSERT(false);
        return false;
    }

    m_baudRate = baudRate;
    m_sharedInstance = sharedInstance;

    if (!m_receiveBuffer.allocBuffer(recvBufSize))
    {
        ASSERT(false);
        return false;
    }

    m_nbReceivedChar = 0;
    m_nbExpectedChar = 0;
    m_receiveOverflow = false;
    m_waitingForReceivedChar = false;

#if defined(_WIN32)
    // TODO : use GetLastError() to retrieve Win32 error if needed
    if ((m_id = CreateFile(TEXT_PTR(pPortName), GENERIC_READ | GENERIC_WRITE,
                           0, NULL, OPEN_EXISTING,
                        #if defined(_WIN32) && !defined(UNDER_CE)
                           FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
                        #elif defined(_WIN32) && defined(UNDER_CE)
                           FILE_ATTRIBUTE_NORMAL,
                        #endif
                           NULL)) == INVALID_SERIAL_ID)
    {
        ASSERT(false);
        return false;
    }

    // Note : baudRate = 0 is used when the serial port is assumed to be shared
    //        ==> initialization has already been done
    if (baudRate)
    {
        // TODO : use GetLastError() to retrieve Win32 error if needed
        DCB dcb;
        dcb.DCBlength = sizeof(DCB);
        if (!GetCommState(m_id, &dcb))
        {
            //DWORD lastError = GetLastError();
            ASSERT(false);
        }

        dcb.BaudRate = baudRate;
        dcb.fBinary = FALSE;
        dcb.fOutxCtsFlow = FALSE;
        dcb.fOutxDsrFlow = FALSE;
        dcb.fDtrControl = DTR_CONTROL_DISABLE;
        dcb.fDsrSensitivity = FALSE;
        dcb.fTXContinueOnXoff = FALSE;
        dcb.fOutX = FALSE;
        dcb.fInX = FALSE;
        dcb.fErrorChar = FALSE;
        dcb.fNull = FALSE;
        if (rsMode == RS485_AUTO_RTS_POSITIVE_POLARITY)
        {
            dcb.fRtsControl = RTS_CONTROL_TOGGLE;
        }
        else
        {
            dcb.fRtsControl = RTS_CONTROL_DISABLE;
        }
        dcb.fAbortOnError = FALSE;

        switch(hwOptions & HARD_OPT_CSIZE)
        {
            case HARD_OPT_CS5:
            {
                dcb.ByteSize = 5;
            }
            break;

            case HARD_OPT_CS6:
            {
                dcb.ByteSize = 6;
            }
            break;

            case HARD_OPT_CS7:
            {
                dcb.ByteSize = 7;
            }
            break;

            case HARD_OPT_CS8:
            {
                dcb.ByteSize = 8;
            }
            break;
        }

        switch(hwOptions & HARD_OPT_CPARITY)
        {
            case 0x00:
            case HARD_OPT_PARODD:   // HARD_OPT_PARENB not set
            {
                dcb.Parity = NOPARITY;
            }
            break;

            case HARD_OPT_PARENB:
            {
                dcb.Parity = EVENPARITY;
            }
            break;

            case (HARD_OPT_PARENB | HARD_OPT_PARODD):
            {
                dcb.Parity = ODDPARITY;
            }
            break;
        }

        if (hwOptions & HARD_OPT_STOPB)
        {
            dcb.StopBits = TWOSTOPBITS;
        }
        else
        {
            dcb.StopBits = ONESTOPBIT;
        }

        if (!SetCommState(m_id, &dcb))
        {
            ASSERT(false);
        }

        if (!PurgeComm(m_id, (PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR)))
        {
            ASSERT(false);
        }

        COMMTIMEOUTS    commTimeouts;
        commTimeouts.ReadIntervalTimeout = MAXDWORD;
        commTimeouts.ReadTotalTimeoutMultiplier = 0;
        commTimeouts.ReadTotalTimeoutConstant = 0;
        commTimeouts.WriteTotalTimeoutMultiplier = 0;
        commTimeouts.WriteTotalTimeoutConstant = 0;
        if (!SetCommTimeouts(m_id, &commTimeouts))
        {
            ASSERT(false);
        }

    #if defined(_WIN32) && !defined(UNDER_CE)
        memset(&m_writeOverlapped, 0, sizeof(OVERLAPPED));
        // manual reset event with initial state FALSE
        m_writeOverlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    #endif
    }
#elif defined(__linux)
    if((m_id = open(pPortName, O_RDWR | O_NOCTTY )) == INVALID_SERIAL_ID)
    {
        printf("serial port open: %s\n", strerror(errno));
        ASSERT(false);
        return false;
    }

    // Note : baudRate = 0 is used when the serial port is assumed to be shared
    //        ==> initialization has already been done
    if (baudRate)
    {
        struct termios xTIO;

        if(tcgetattr(m_id, &xTIO) == 0)
        {
            speed_t xNewSpeed = B9600;

            xTIO.c_cflag &= ~CSIZE;
            xTIO.c_cflag |= CREAD | CLOCAL;
            xTIO.c_lflag  &= ~(ICANON | ECHO | ECHOE | ISIG);  /*Input*/
            xTIO.c_oflag  &= ~OPOST;   /*Output*/
            xTIO.c_iflag &= ~(ICRNL | IXON); // avoid transfering 0x0d, 0x11, 0x13 being lost

            switch(hwOptions & HARD_OPT_CPARITY)
            {
                case 0x00:
                case HARD_OPT_PARODD:   // HARD_OPT_PARENB not set
                {
                    xTIO.c_cflag &= ~PARENB;
                    xTIO.c_iflag &= ~INPCK;
                }
                break;

                case HARD_OPT_PARENB:
                {
                    xTIO.c_cflag |= PARENB;
                    xTIO.c_cflag &= ~PARODD;
                    xTIO.c_iflag |= INPCK;
                }
                break;

                case (HARD_OPT_PARENB | HARD_OPT_PARODD):
                {
                    xTIO.c_cflag |= (PARODD | PARENB);
                    xTIO.c_iflag |= INPCK;
                }
                break;
            }
            switch(hwOptions & HARD_OPT_CSIZE)
            {
                case HARD_OPT_CS5:
                {
                    xTIO.c_cflag |= CS5;
                }
                break;

                case HARD_OPT_CS6:
                {
                    xTIO.c_cflag |= CS6;
                }
                break;

                case HARD_OPT_CS7:
                {
                    xTIO.c_cflag |= CS7;
                }
                break;

                case HARD_OPT_CS8:
                {
                    xTIO.c_cflag |= CS8;
                }
                break;
            }
            if (hwOptions & HARD_OPT_STOPB)
            {
                xTIO.c_cflag |= CSTOPB;
            }
            else
            {
                xTIO.c_cflag &= ~CSTOPB;
            }
            switch(baudRate)
            {
                case 0:
                    xNewSpeed = B0;
                    break;
                case 50:
                    xNewSpeed = B50;
                    break;
                case 75:
                    xNewSpeed = B75;
                    break;
                case 110:
                    xNewSpeed = B110;
                    break;
                case 134:
                    xNewSpeed = B134;
                    break;
                case 150:
                    xNewSpeed = B150;
                    break;
                case 200:
                    xNewSpeed = B200;
                    break;
                case 300:
                    xNewSpeed = B300;
                    break;
                case 600:
                    xNewSpeed = B600;
                    break;
                case 1200:
                    xNewSpeed = B1200;
                    break;
                case 1800:
                    xNewSpeed = B1800;
                    break;
                case 2400:
                    xNewSpeed = B2400;
                    break;
                case 4800:
                    xNewSpeed = B4800;
                    break;
                case 9600:
                    xNewSpeed = B9600;
                    break;
                case 19200:
                    xNewSpeed = B19200;
                    break;
                case 38400:
                    xNewSpeed = B38400;
                    break;
                case 57600:
                    xNewSpeed = B57600;
                    break;
                case 115200:
                    xNewSpeed = B115200;
                    break;
                case 230400:
                    xNewSpeed = B230400;
                    break;
		case 460800:
			xNewSpeed = B460800;
			break;
		case 500000:
			xNewSpeed = B500000;
			break;
		case 576000:
			xNewSpeed = B576000;
			break;
		case 921600:
			xNewSpeed = B921600;
			break;
		case 1000000:
			xNewSpeed = B1000000;
			break;
		case 1152000:
			xNewSpeed = B1152000;
			break;
		case 1500000:
			xNewSpeed = B1500000;
			break;
		case 2000000:
			xNewSpeed = B2000000;
			break;
		case 2500000:
			xNewSpeed = B2500000;
			break;
            }
            xTIO.c_cc[VTIME] = 0; // timeout
            xTIO.c_cc[VMIN] = 1; // define the minimum bytes data to be readed
            tcflush(m_id, TCIOFLUSH);
            if(cfsetispeed(&xTIO, xNewSpeed) == -1)
            {
                printf("serial port cfsetispeed: %s\n", strerror(errno));
                ASSERT(false);
            }
            if(cfsetospeed(&xTIO, xNewSpeed) == -1)
            {
                printf("serial port cfsetospeed: %s\n", strerror(errno));
                ASSERT(false);
            }
            if(tcsetattr(m_id, TCSANOW, &xTIO) == -1)
            {
                printf("serial port tcsetattr: %s\n", strerror(errno));
                ASSERT(false);
            }
        }
        else
        {
            printf("serial port tcgetattr: %s\n", strerror(errno));
            ASSERT(false);
        }
    }
#endif
    m_pInterruptEmulationThread = new CSerialInterruptEmulationThread(this);
    m_receiveEnabled = true;

    s_comPortsInUse.insert(TSerialComMap::value_type(pPortName, this));

    return true;
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Send data out on serial port                                            */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   pBuffer[in]:           data buffer pointer                              */
/*   nbCharToWrite[in]:     data size in bytes                               */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
void CSerial::write(const char* pBuffer, size_t nbCharToWrite)
{
    if(m_id == INVALID_SERIAL_ID)
        return;

#if defined(_WIN32)
    DWORD       nbCharWritten;

    if (!WriteFile(m_id, pBuffer, nbCharToWrite, &nbCharWritten,
                #if defined(_WIN32) && !defined(UNDER_CE)
                   &m_writeOverlapped))
                #elif defined(_WIN32) && defined(UNDER_CE)
                   0))
                #endif
    {
        DWORD lastError = GetLastError();
    #if defined(_WIN32) && !defined(UNDER_CE)
        if (lastError == ERROR_IO_PENDING)
        {
        }
        else
    #endif
        {
            ASSERT(false);
        }
    }
#elif defined(__linux)
    ssize_t res;
    size_t left = (size_t)nbCharToWrite;
    size_t done = 0;

    while(left > 0)
    {
        if((res = ::write(m_id, pBuffer + done, left)) == -1)
        {
            if(errno != EINTR)
            {
                printf("serial port write: %s\n", strerror(errno));
                ASSERT(false);
                break;
            }
            /* call write again because of interrupted system call. */
            continue;
        }
        done += res;
        left -= res;
    }
#endif
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Receive data in on serial port                                          */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   pBuffer[out]:          data buffer pointer                              */
/*   nbCharToRead[in]:      data size to be read in bytes                    */
/*   timeout[in]:           data receive timeout                             */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   Data size read from serial port                                         */
/*                                                                           */
/*****************************************************************************/
size_t CSerial::read(char* pBuffer, size_t nbCharToRead, int timeout)
{
    bool            charReceived;
    int             nbCharRead;

    m_lockMutex.take();
    if (m_nbReceivedChar >= nbCharToRead)
    {
        charReceived = true;
    }
    else
    {
        m_nbExpectedChar = nbCharToRead;
        m_waitingForReceivedChar = true;
        charReceived = false;
    }

    if (!charReceived)
    {
        m_lockMutex.release();
        m_receiveCharSync.wait(timeout);
        m_lockMutex.take();

        if (m_nbReceivedChar != 0)
        {
            charReceived = true;
        }
    }

    if (!charReceived)
    {
        nbCharRead = 0;
    }
    else
    {
        nbCharRead = m_receiveBuffer.get(pBuffer, nbCharToRead);

        m_nbReceivedChar -= nbCharRead;
    }
    m_lockMutex.release();

    return nbCharRead;
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Abort the data receiving on serial port                                 */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
void CSerial::abortRead()
{
    m_receiveCharSync.signal();
    // Clean sync if no read() in progress
    m_receiveCharSync.wait(WAIT_ZERO);
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Flush the data receive buffer on serial port                            */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
void CSerial::flushReadBuffer()
{
    m_lockMutex.take();
    m_nbReceivedChar = 0;
    m_receiveOverflow = false;

    m_receiveBuffer.flush();
    m_lockMutex.release();
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Check if the data receive buffer is overflowed                          */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
bool CSerial::isOverflow()
{
    bool overflow = m_receiveOverflow;
    m_receiveOverflow = false;

    return overflow;
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Enable the data receiving on serial port                                */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
void CSerial::enableReceive()
{
    m_receiveEnabled = true;
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Disable the data receiving on serial port                               */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
void CSerial::disableReceive()
{
    m_receiveEnabled = false;
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Set the baud rate on serial port                                        */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   baudRate[in]:          baud rate to be set                              */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
void CSerial::setBaudRate(unsigned long baudRate)
{
    if(m_id == INVALID_SERIAL_ID)
        return;

#if defined(_WIN32)
    DCB dcb;
    dcb.DCBlength = sizeof(DCB);
    if (!GetCommState(m_id, &dcb))
    {
        ASSERT(false);
    }

    dcb.BaudRate = baudRate;

    if (!SetCommState(m_id, &dcb))
    {
        ASSERT(false);
    }
#elif defined(__linux)
    struct termios xTIO;

    if(tcgetattr(m_id, &xTIO) == 0)
    {
        speed_t xNewSpeed = B9600;

        switch(baudRate)
        {
            case 0:
                xNewSpeed = B0;
                break;
            case 50:
                xNewSpeed = B50;
                break;
            case 75:
                xNewSpeed = B75;
                break;
            case 110:
                xNewSpeed = B110;
                break;
            case 134:
                xNewSpeed = B134;
                break;
            case 150:
                xNewSpeed = B150;
                break;
            case 200:
                xNewSpeed = B200;
                break;
            case 300:
                xNewSpeed = B300;
                break;
            case 600:
                xNewSpeed = B600;
                break;
            case 1200:
                xNewSpeed = B1200;
                break;
            case 1800:
                xNewSpeed = B1800;
                break;
            case 2400:
                xNewSpeed = B2400;
                break;
            case 4800:
                xNewSpeed = B4800;
                break;
            case 9600:
                xNewSpeed = B9600;
                break;
            case 19200:
                xNewSpeed = B19200;
                break;
            case 38400:
                xNewSpeed = B38400;
                break;
            case 57600:
                xNewSpeed = B57600;
                break;
            case 115200:
                xNewSpeed = B115200;
                break;
            case 230400:
                xNewSpeed = B230400;
                break;
	    case 460800:
		xNewSpeed = B460800;
		break;
	    case 500000:
		xNewSpeed = B500000;
		break;
	    case 576000:
		xNewSpeed = B576000;
		break;
	    case 921600:
		xNewSpeed = B921600;
		break;
	    case 1000000:
		xNewSpeed = B1000000;
		break;
	    case 1152000:
		xNewSpeed = B1152000;
		break;
	    case 1500000:
		xNewSpeed = B1500000;
		break;
	    case 2000000:
		xNewSpeed = B2000000;
		break;
	    case 2500000:
		xNewSpeed = B2500000;
		break;
        }
        if(tcflush(m_id, TCIOFLUSH) == -1)
        {
            printf("serial port cfsetispeed: %s\n", strerror(errno));
            ASSERT(false);
            return;
        }
        if(cfsetispeed(&xTIO, xNewSpeed) == -1)
        {
            printf("serial port cfsetispeed: %s\n", strerror(errno));
            ASSERT(false);
            return;
        }
        if(cfsetospeed(&xTIO, xNewSpeed) == -1)
        {
            printf("serial port cfsetospeed: %s\n", strerror(errno));
            ASSERT(false);
            return;
        }
        if(tcsetattr(m_id, TCSANOW, &xTIO) == -1)
        {
            printf("serial port tcsetattr: %s\n", strerror(errno));
            ASSERT(false);
            return;
        }
    }
    else
    {
        printf("serial port tcgetattr: %s\n", strerror(errno));
        ASSERT(false);
        return;
    }
#endif
    m_baudRate = baudRate;
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Get the baud rate on serial port                                        */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   The current baud rate setting                                           */
/*                                                                           */
/*****************************************************************************/
unsigned long CSerial::getBaudRate()
{
    return m_baudRate;
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Set the modem control bits on serial port                               */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   control[in]:           the control bits state to be set                 */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
void CSerial::setModemControl(int control)
{
    doSetModemControl(control);
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Get the modem control bits on serial port                               */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   The current modem control bits state                                    */
/*                                                                           */
/*****************************************************************************/
int CSerial::getModemControl()
{
    return doGetModemControl();
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Get the modem status bits on serial port                                */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   The current modem status bits state                                     */
/*                                                                           */
/*****************************************************************************/
int CSerial::getModemStatus()
{
    return doGetModemStatus();
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Get the serial port handle                                              */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   The serial port handle                                                  */
/*                                                                           */
/*****************************************************************************/
SERIAL_ID CSerial::getId() const
{
    return m_id;
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Check if the serial port is shared or not                               */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   The serial port is shared or not                                        */
/*                                                                           */
/*****************************************************************************/
bool CSerial::isShared() const
{
    return m_sharedInstance;
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Get the shared serial port instance                                     */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   pPortName[in]:         serial port name to be got                       */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   The serial port instant                                                 */
/*                                                                           */
/*****************************************************************************/
CSerial* CSerial::getSharedComPort(const char* pSerialPortName)
{
    TSerialComMap::iterator i;
    if ((i = s_comPortsInUse.find(std::string(pSerialPortName))) 
         == s_comPortsInUse.end())
    {
        return 0;
    }

    if (!(i->second->m_sharedInstance))
    {
        return 0;
    }

    return i->second;
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Set the modem control bits on serial port                               */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   control[in]:           the control bits state to be set                 */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
void CSerial::doSetModemControl(int control)
{
    // To pacify the compiler
    control = control;

    // To be overloaded in a derived class if needed
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Get the modem control bits on serial port                               */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   The current modem control bits state                                    */
/*                                                                           */
/*****************************************************************************/
int CSerial::doGetModemControl()
{
    // To be overloaded in a derived class if needed
    return 0;
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Get the modem status bits on serial port                                */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   The current modem status bits state                                     */
/*                                                                           */
/*****************************************************************************/
int CSerial::doGetModemStatus()
{
    // To be overloaded in a derived class if needed
    return m_modemStatus;
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Data received process function                                          */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   receivedChar[out]:     data buffer to receive data                      */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   Always return true                                                      */
/*                                                                           */
/*****************************************************************************/
bool CSerial::receiveCharHook0(int receivedChar)
{
    if (!m_receiveEnabled)
    {
        return true;
    }

    bool receivedCharHooked = receiveCharHook(receivedChar);

    if (!receivedCharHooked)
    {
        // Received char not hooked => available for read()
        m_lockMutex.take();
        if (m_receiveBuffer.isFull())
        {
            // No more space
            m_receiveOverflow = true;
        }
        else
        {
            m_nbReceivedChar++;
            m_receiveBuffer.put((char*)&receivedChar, 1);
            if (m_waitingForReceivedChar)
            {
                if (m_nbReceivedChar >= m_nbExpectedChar)
                {
                    m_nbExpectedChar = 0;
                    m_waitingForReceivedChar = false;
                    m_lockMutex.release();
                    m_receiveCharSync.signal();
                    m_lockMutex.take();
                }
            }
        }
        m_lockMutex.release();
    }

    return true;
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   The callback function on data received on serial port                   */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   receivedChar[out]:     data buffer to receive data                      */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   Data received or not                                                    */
/*                                                                           */
/*****************************************************************************/
bool CSerial::receiveCharHook(int receivedChar)
{
    // To pacify the compiler
    receivedChar = receivedChar;

    // To be overloaded in a derived class if needed
    return false;   // => don't hook the received char
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   The callback function on modem status changed on serial port            */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   modemStatus[out]:      modem status to store                            */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
void CSerial::modemStatusChangeHook(unsigned char &modemStatus)
{
    m_modemStatus = modemStatus;
}

