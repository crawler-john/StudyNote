#include <stdio.h>
#include "sync.h"
#include "thread.h"
#include "msgQueue.h"
#include "timemath.h"
#include "timer.h"
#include "event.h"
#include "singleInst.h"
#include "serial.h"

class CSyncTestThread: public CThread
{
    public:
        CSyncTestThread(CSync *syncItem, int id);
        virtual ~CSyncTestThread(void);

        CSync *syncTestItem;
        int nid;

    private:
        int run();

};

CSyncTestThread::CSyncTestThread(CSync *syncItem, int id)
    : syncTestItem(syncItem),
      nid(id)
{
    //create the Thread
    CThread::initInstance("SyncTest", THREAD_DEFAULT_STACK_SIZE, THREAD_MEDIUM_PRIORITY);

    // start date time display thread
    start();

    // wait to syncronous threads
    waitStarted();
}

CSyncTestThread::~CSyncTestThread()
{
    if (CThread::getExitCode() == RUNNING) {
        CThread::stop();
        CThread::join();
    }
}

int CSyncTestThread::run(void)
{
    while(!CThread::m_stopRequest)
    {
        printf("Thread %d in running\n", nid);
        syncTestItem->wait((nid != 0) ? (7000/nid) : WAIT_INFINITE);
    }

    printf("Thread %d in stopped\n", nid);

    return SUCCESS;
}

class CTestThread: public CThread
{
    public:
        CTestThread(void);
        virtual ~CTestThread(void);

    private:
        int run();

};

CTestThread::CTestThread()
{
    //create the Thread
    CThread::initInstance("ThreadTest", THREAD_DEFAULT_STACK_SIZE, THREAD_MEDIUM_PRIORITY);

    // start date time display thread
    start();

    // wait to syncronous threads
    waitStarted();
}

CTestThread::~CTestThread()
{
    if (CThread::getExitCode() == RUNNING) {
        CThread::stop();
        CThread::join();
    }
}

int CTestThread::run(void)
{
    while(!CThread::m_stopRequest)
    {
        printf("Thread in running\n");
        sleep(2000);
    }
    return SUCCESS;
}

class CTestTimer: public CTimer
{
    public:
        CTestTimer(EMode mode, int id);
        ~CTestTimer();

        int idNum;
        //timespec l_tvStart;

    private:
        void timeout();
};

CTestTimer::CTestTimer(EMode mode, int id)
    : CTimer(mode),
      idNum(id)
{
}

CTestTimer::~CTestTimer()
{
}

void CTestTimer::timeout()
{
/*
    timespec l_tv;
    clock_gettime(CLOCK_REALTIME, &l_tv);

    timespec l_tvElapsed = timespec_sub(l_tv, l_tvStart);
    printf("Timer %d: started at %ld.%09ld(S), stopped at %ld.%09ld(S), elapsed %ld.%09ld(S)\n", 
           idNum, l_tvStart.tv_sec, l_tvStart.tv_nsec, l_tv.tv_sec, l_tv.tv_nsec, 
           l_tvElapsed.tv_sec, l_tvElapsed.tv_nsec);
    l_tvStart = timespec_to_timespec(l_tv);*/
}

class CEvtNoParam: public IEvent 
{
    public:
        CEvtNoParam(){}
        ~CEvtNoParam(){}
};

class CEvtTimeParam: public IEvent 
{
    public:
        unsigned long tickWhileEventOccured;

        CEvtTimeParam() {tickWhileEventOccured = 0;}
        CEvtTimeParam(unsigned long tickCnt)
        {
            tickWhileEventOccured = tickCnt;
        }
        ~CEvtTimeParam(){}
};

class CEvtProvider: public CEventProvider
{
    public:
        CEvtProvider()
        {
            declare(CEvtNoParam());
            declare(CEvtTimeParam());
        }
        ~CEvtProvider(){}

        void noParamEventNotify()
        {
            notify(CEvtNoParam());
        }

        void tickEventNotify(unsigned long tickCnt)
        {
            notify(CEvtTimeParam(tickCnt));
        }
};

class CEvtObserver: private CEventObserverT<CEvtNoParam>,
                    private CEventObserverT<CEvtTimeParam>
{
    public:
        CEvtObserver(CEvtProvider &evtProv)
        {
            pEvtProvider = &evtProv;
            pEvtProvider->subscribe(EVENT(CEvtNoParam));
            pEvtProvider->subscribe(EVENT(CEvtTimeParam));
        }
        ~CEvtObserver()
        {
            pEvtProvider->unsubscribe(EVENT(CEvtNoParam));
            pEvtProvider->unsubscribe(EVENT(CEvtTimeParam));
        }
        void onEvent(CEventProvider& rProvider, const CEvtNoParam& rEvent)
        {
            printf("A no parameter event occurred\n");
        }
        void onEvent(CEventProvider& rProvider, const CEvtTimeParam& rEvent)
        {
            printf("A tick event occurred at OS tick %ld\n", rEvent.tickWhileEventOccured);
        }

    private:
        CEvtProvider *pEvtProvider;
};

class CSingleInstTest
{
    public:
        CSingleInstTest()
        {
            printf("Single instant test class instant constructed\n");
        }
        ~CSingleInstTest()
        {
            printf("Single instant test class instant destructed\n");
        }
        void showClockTick(unsigned long tick)
        {
            printf("The OS clock tick is %ld\n", tick);
        }
};

DECLARE_SINGLE_INST(CSingleInstTest);

// The instance of explicit singleton CSingleInstTest class
typedef CSingleInst<CSingleInstTest> CSingleInstTest_;
#define TheSingleInstTest (CSingleInstTest_::instance())

class CSerialExt: public CSerial
{
    public:
        CSerialExt(const char* pPortName)
            : CSerial(pPortName, 115200, HARD_OPT_CS8, RS232)
        {
        }

    private:

        bool receiveCharHook(int c)
        {
            return false;
        }
};

class CTestSerial: public CThread, public CSerial
{
    public:
        CTestSerial(void);
        virtual ~CTestSerial(void);

    private:
        int run();

};

CTestSerial::CTestSerial()
{
    //create the Thread
    CThread::initInstance("SerialTest", THREAD_DEFAULT_STACK_SIZE, THREAD_MEDIUM_PRIORITY);

    // start date time display thread
    start();

    // wait to syncronous threads
    waitStarted();
}

CTestSerial::~CTestSerial()
{
    if (CThread::getExitCode() == RUNNING) {
        CThread::stop();
        CThread::join();
    }
}

int CTestSerial::run(void)
{
    size_t sizeofdata = 0;
    char buffer[100];

    CSerialExt serialExt1("COM1:");
    CSerialExt serialExt2("COM2:");

    while(!CThread::m_stopRequest)
    {
        if((sizeofdata = serialExt1.read(buffer, sizeof(buffer), 100)) > 0)
        {
            serialExt1.write(buffer, sizeofdata);
            serialExt2.write(buffer, sizeofdata);
        }
    }
    return SUCCESS;
}

#if defined (__cplusplus)
extern "C"
{
#endif
void testCCountingSem()
{
    CCountingSem sem(0x7FFFFF, 0x7FFFFF);

    printf("Initialized 0x7FFFFF counting semaphore ... \n");
    sem.release();
    sem.release();
    sem.release(4);

    printf("Try to take counting semaphore ... ");
    int nCount = 0;
    while(sem.take(2000))
    {
        nCount++;
    }
    printf("Semaphore available 0x%X\n", nCount);

    printf("Try to take counting semaphore ... ");
    if(sem.take(2000))
    {
        printf("Result: take semaphore OK\n");
    }
    else
    {
        printf("Result: take semaphore timeout\n");
    }

    printf("Release a counting semaphore ... \n");
    sem.release();

    printf("Try to take counting semaphore ... ");
    if(sem.take())
    {
        printf("Result: take semaphore OK\n");
    }
    else
    {
        printf("Result: take semaphore timeout\n");
    }

    printf("Try to take counting semaphore ... ");
    if(sem.take(2000))
    {
        printf("Result: take semaphore OK\n");
    }
    else
    {
        printf("Result: take semaphore timeout\n");
    }

    printf("Release two counting semaphore ... \n");
    sem.release();
    sem.release();

    printf("Try to take counting semaphore ... ");
    if(sem.take(2000))
    {
        printf("Result: take semaphore OK\n");
    }
    else
    {
        printf("Result: take semaphore timeout\n");
    }

    printf("Try to take counting semaphore ... ");
    if(sem.take(2000))
    {
        printf("Result: take semaphore OK\n");
    }
    else
    {
        printf("Result: take semaphore timeout\n");
    }

    printf("Try to take counting semaphore ... ");
    if(sem.take(2000))
    {
        printf("Result: take semaphore OK\n");
    }
    else
    {
        printf("Result: take semaphore timeout\n");
    }

    printf("Release 6 counting semaphore ... ");
    sem.release();
    sem.release();
    sem.release(4);

    printf("Try to take counting semaphore ... ");
    nCount = 0;
    while(sem.take(2000))
    {
        nCount++;
    }
    printf("Semaphore available %d\n", nCount);
}

void testCBinarySem()
{
    CBinarySem sem(CBinarySem::FULL);

    printf("Initialized binary semaphore in FULL ... \n");
    sem.release();
    sem.release();
    sem.release();

    printf("Try to take binary semaphore ... ");
    int nCount = 0;
    while(sem.take(2000))
    {
        nCount++;
    }
    printf("Semaphore available %d\n", nCount);

    printf("Release two binary semaphore ... \n");
    sem.release();
    sem.release();

    printf("Try to take binary semaphore ... ");
    if(sem.take())
    {
        printf("Result: take semaphore OK\n");
    }
    else
    {
        printf("Result: take semaphore timeout\n");
    }

    printf("Try to take binary semaphore ... ");
    if(sem.take(2000))
    {
        printf("Result: take semaphore OK\n");
    }
    else
    {
        printf("Result: take semaphore timeout\n");
    }
}

void testCMutex()
{
    CMutex mut;

    printf("Try to take mutex ... ");
    if(mut.take())
    {
        printf("Result: take mutex OK\n");
    }
    else
    {
        printf("Result: take mutex timeout\n");
    }

    printf("Try to take mutex ... ");
    if(mut.take(2000))
    {
        printf("Result: take mutex OK\n");
    }
    else
    {
        printf("Result: take mutex timeout\n");
    }

    printf("Release a mutex ... \n");
    mut.release();

    printf("Try to take mutex ... ");
    if(mut.take(2000))
    {
        printf("Result: take mutex OK\n");
    }
    else
    {
        printf("Result: take mutex timeout\n");
    }

    printf("Try to take mutex ... ");
    if(mut.take(2000))
    {
        printf("Result: take mutex OK\n");
    }
    else
    {
        printf("Result: take mutex timeout\n");
    }

    printf("Release two mutex ... \n");
    mut.release();
    mut.release();

    printf("Try to take mutex ... ");
    if(mut.take())
    {
        printf("Result: take mutex OK\n");
    }
    else
    {
        printf("Result: take mutex timeout\n");
    }

    printf("Try to take mutex ... ");
    if(mut.take(2000))
    {
        printf("Result: take mutex OK\n");
    }
    else
    {
        printf("Result: take mutex timeout\n");
    }

    printf("Release the mutex before destroying the mutex \n");
    mut.release();
}

void testCLock()
{
    CMutex mut;
    CLock lock(mut);

    printf("CLock Test in progress ... \n");
    printf("CLock Test Finished\n");
}

void testCSync()
{
    printf("CSync Test in progress ... \n");
    CSync syncItem;
    CSyncTestThread test1(&syncItem, 1);
    CSyncTestThread test2(&syncItem, 2);
    CSyncTestThread test3(&syncItem, 3);
    CSyncTestThread test0(&syncItem, 0);

    char cCh = 0;

    do {
        printf("Press 's' to synchronize the next thread\n");
        printf("Press 'b' to synchronize all threads\n");
        printf("Press 'q' to quit CSync test\n");
        do {
            cCh = getchar();
        } while(cCh == '\n');

        switch(cCh)
        {
            case 's':
                syncItem.signal();
                break;

            case 'b':
                syncItem.broadcast();
                break;

            case 'q':
                break;

            default:
                break;
        }
    } while(cCh != 'q');
    test1.stop();
    test2.stop();
    test3.stop();
    test0.stop();
    syncItem.broadcast();
    printf("CSync Test finished\n");
}

void syncTest()
{
    char cCh = 0;

    printf("*******************\n");
    printf("*    Sync Test    *\n");
    printf("*******************\n\n");

    do {
        printf("    Please Select a Menu Item:\n");
        printf("        1 - CCountingSem\n");
        printf("        2 - CBinarySem\n");
        printf("        3 - CSync\n");
        printf("        4 - CMutex\n");
        printf("        5 - CLock\n");
        printf("        6 - CCondition\n");
        printf("        0 - Main Menu\n");

        do {
            cCh = getchar();
        } while(cCh == '\n');

        switch(cCh)
        {
            case '1':
                testCCountingSem();
                break;

            case '2':
                testCBinarySem();
                break;

            case '3':
                testCSync();
                break;

            case '4':
                testCMutex();
                break;

            case '5':
                testCLock();
                break;

            case '0':
                break;

            default:
                break;
        }
    } while(cCh != '0');
}

void testCThread()
{
    printf("Initialized binary semaphore in FULL ... \n");
    CTestThread test;
    CThread::sleep(15000);
}

void threadTest()
{
    char cCh = 0;

    printf("*********************\n");
    printf("*    Thread Test    *\n");
    printf("*********************\n\n");

    do {
        printf("    Please Select a Menu Item:\n");
        printf("        1 - CThread\n");
        printf("        0 - Main Menu\n");

        do {
            cCh = getchar();
        } while(cCh == '\n');

        switch(cCh)
        {
            case '1':
                testCThread();
                break;

            case '0':
                break;

            default:
                break;
        }
    } while(cCh != '0');
}

const static char* cMsgStr[] = 
{
    "This is the 1st sentence\n",
    "A paragraph of message queue test\n",
    "Hope it works\n",
    "No problem or not\n"
};

void testCMsgQueue()
{
    char *pStr;
    printf("Test message queue ... \n");
    CMsgQueueT<char *> msgqueue(4);
    msgqueue.enqueue((char *)cMsgStr[0]);
    msgqueue.enqueue((char *)cMsgStr[1]);
    msgqueue.enqueue((char *)cMsgStr[2]);
    msgqueue.enqueue((char *)cMsgStr[3], true);
    msgqueue.enqueue((char *)cMsgStr[0], false, 2000);
    if(msgqueue.dequeue(pStr))
    {
        printf("%s", pStr);
    }
    if(msgqueue.dequeue(pStr, 2000))
    {
        printf("%s", pStr);
    }
    if(msgqueue.dequeue(pStr))
    {
        printf("%s", pStr);
    }
    if(msgqueue.dequeue(pStr, 2000))
    {
        printf("%s", pStr);
    }
    if(msgqueue.dequeue(pStr, 2000))
    {
        printf("%s", pStr);
    }
}

void msgqueueTest()
{
    char cCh = 0;

    printf("****************************\n");
    printf("*    Message Queue Test    *\n");
    printf("****************************\n\n");

    do {
        printf("    Please Select a Menu Item:\n");
        printf("        1 - CMsgQueue\n");
        printf("        0 - Main Menu\n");

        do {
            cCh = getchar();
        } while(cCh == '\n');

        switch(cCh)
        {
            case '1':
                testCMsgQueue();
                break;

            case '0':
                break;

            default:
                break;
        }
    } while(cCh != '0');
}

void timerTest()
{
    char cCh = 0;
    CTestTimer *testTimer1 = NULL;
    CTestTimer *testTimer2 = NULL;
    CTestTimer *testTimer3 = NULL;
    CTestTimer *testTimer4 = NULL;

    printf("********************\n");
    printf("*    Timer Test    *\n");
    printf("********************\n\n");

    do {
        int selection = -1;
        printf("    Please Select a Menu Item:\n");
        printf("        1 - Start a timer(UNTHREADED)\n");
        printf("        2 - Stop the timer(UNTHREADED)\n");
        printf("        3 - Start a timer(THREADED)\n");
        printf("        4 - Stop the timer(THREADED)\n");
        printf("        5 - Start a timer(COMMON_THREADED)\n");
        printf("        6 - Stop the timer(COMMON_THREADED)\n");
        printf("        7 - Start a timer(THREADED)\n");
        printf("        8 - Stop the timer(THREADED)\n");
        printf("        0 - Main Menu\n");

        do {
            cCh = getchar();
        } while(cCh == '\n');

        switch(cCh)
        {
            case '1':
                printf("    Timer 1 (UNTHREADED) timeout value (ms): \n");
                if(scanf("%d", &selection) != EOF)
                {
                    if(!testTimer1)
                        testTimer1 = new CTestTimer(CTimer::UNTHREADED, 1);
                    if(testTimer1)
                    {
                        //clock_gettime(CLOCK_REALTIME, &(testTimer1->l_tvStart));
                        testTimer1->start(selection);
                    }
                }
                break;

            case '2':
                if(testTimer1)
                {
                    testTimer1->cancel();
                }
                break;

            case '3':
                printf("    Timer 2 (THREADED) timeout value (ms): \n");
                if(scanf("%d", &selection) != EOF)
                {
                    if(!testTimer2)
                        testTimer2 = new CTestTimer(CTimer::THREADED, 2);
                    if(testTimer2)
                    {
                        //clock_gettime(CLOCK_REALTIME, &(testTimer2->l_tvStart));
                        testTimer2->start(selection);
                    }
                }
                break;

            case '4':
                if(testTimer2)
                {
                    testTimer2->cancel();
                }
                break;

            case '5':
                printf("    Timer 3 (COMMON_THREADED) timeout value (ms): \n");
                if(scanf("%d", &selection) != EOF)
                {
                    if(!testTimer3)
                        testTimer3 = new CTestTimer(CTimer::COMMON_THREADED, 3);
                    if(testTimer3)
                    {
                        //clock_gettime(CLOCK_REALTIME, &(testTimer3->l_tvStart));
                        testTimer3->start(selection);
                    }
                }
                break;

            case '6':
                if(testTimer3)
                {
                    testTimer3->cancel();
                }
                break;

            case '7':
                printf("    Timer 4 (THREADED) timeout value (ms): \n");
                if(scanf("%d", &selection) != EOF)
                {
                    if(!testTimer4)
                        testTimer4 = new CTestTimer(CTimer::THREADED, 4);
                    if(testTimer4)
                    {
                        //clock_gettime(CLOCK_REALTIME, &(testTimer4->l_tvStart));
                        testTimer4->start(selection, true);
                    }
                }
                break;

            case '8':
                if(testTimer4)
                {
                    testTimer4->cancel();
                }
                break;

            case '0':
                break;

            default:
                break;
        }
    } while(cCh != '0');

    if(testTimer1)
    {
        delete testTimer1;
        testTimer1 = NULL;
    }
    if(testTimer2)
    {
        delete testTimer2;
        testTimer2 = NULL;
    }
    if(testTimer3)
    {
        delete testTimer3;
        testTimer3 = NULL;
    }
    if(testTimer4)
    {
        delete testTimer4;
        testTimer4 = NULL;
    }
}

void eventProcTest()
{
    CEvtProvider evtProv;
    CEvtObserver evtObsv(evtProv);

    evtProv.noParamEventNotify();
    evtProv.tickEventNotify(GetTickCount());
}

void singleInstTest()
{
    CREATE_SINGLE_INST(CSingleInstTest);

    TheSingleInstTest.showClockTick(GetTickCount());

    if(SINGLE_INST_CREATED(CSingleInstTest))
    {
        DELETE_SINGLE_INST(CSingleInstTest);
    }
}

void serialTest()
{
    char cCh = 0;
    CTestSerial testSerial;

    printf("**************************\n");
    printf("*    Serial Port Test    *\n");
    printf("**************************\n\n");

    do {
        printf("    Please Select a Menu Item:\n");
        printf("        0 - Main Menu\n\n");
        printf("The program is receiving data from COM1 port \nand transfering received data to COM2 ...\n");

        do {
            cCh = getchar();
        } while(cCh == '\n');
    } while(cCh != '0');
}

int main(int argc, char* argv[])
{
    char cCh = 0;

    //CREATE_SINGLE_INST(CTimersInterruptEmulationThread);
    CREATE_SINGLE_INST(CCommonThreadedTimersThread);

    printf("\n********************************\n");
    printf("*    Common Function Tester    *\n");
    printf("********************************\n\n");

    do {
        printf("    Please Select a Menu Item:\n");
        printf("        s - Sync\n");
        printf("        t - Thread\n");
        printf("        m - Message Queue\n");
        printf("        i - Timer\n");
        printf("        e - Event Process\n");
        printf("        l - Single Instant\n");
        printf("        r - Serial\n");
        printf("        q - Quit\n");

        do {
            cCh = getchar();
        } while(cCh == '\n');

        switch(cCh)
        {
            case 's':
                syncTest();
                break;

            case 't':
                threadTest();
                break;

            case 'm':
                msgqueueTest();
                break;

            case 'i':
                timerTest();
                break;

            case 'e':
                eventProcTest();
                break;

            case 'l':
                singleInstTest();
                break;

            case 'r':
                serialTest();
                break;

            case 'q':
                break;

            default:
                break;
        }
    } while(cCh != 'q');

    DELETE_SINGLE_INST(CCommonThreadedTimersThread);
    //DELETE_SINGLE_INST(CTimersInterruptEmulationThread);
    return 0;
}
#if defined (__cplusplus)
} // end of extern "C"
#endif

