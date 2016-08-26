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

#include <typeinfo>
#include <string> 
#include "event.h"


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
IEvent::~IEvent()
{
}

CEventObserver::~CEventObserver()
{
    THREAD_SAFE

    for(TEventProviderList::iterator i = m_providers.begin(); 
        i != m_providers.end(); )
    {
        // unsubscribe() will call ackUnsubscribe() => use a temporary iterator 
        // iTmp to make the call
        // so that i points to the next item and is guaranteed to be valid 
        // since item pointed to by iTmp will be deleted
        TEventProviderList::iterator iTmp = i;
        i++;
        // NOTE: The provider manages lists of CEventObserver. These observers 
        // are registered as CEventObserver* or as CEventObserverT<>*.
        // In the following line 'this' is a CEventObserver*
        // Since CEventObserverT<> derive only from CEventObserver, a 
        // CEventObserverT<>* is always equal to a CEventObserver* and 
        // therefore the following line will unsubscribe every registered 
        // COsObserver/COsObserverT<>
        (*iTmp)->unsubscribe(this);
    }

//  TheEventProviders.unsubscribe(this);
}

void CEventObserver::ackSubscribe(CEventProvider* pProvider)
{
    THREAD_SAFE

    bool providerNotRegistered = true;
    for(TEventProviderList::iterator i = m_providers.begin(); 
        i != m_providers.end(); i++)
    {
        if(*i == pProvider)
        {
            // got it
            providerNotRegistered = false;
            break;
        }
    }

    if(providerNotRegistered)
    {
        m_providers.push_back(pProvider);
    }
}

void CEventObserver::ackUnsubscribe(CEventProvider* pProvider)
{
    THREAD_SAFE

    m_providers.remove(pProvider);
}

void CEventObserver::onEvent(CEventProvider& rProvider, const IEvent& rEvent)
{
}

CEventProvider::~CEventProvider()
{
    THREAD_SAFE

    for(TEventObserverMap::iterator i = m_observers.begin(); 
        i != m_observers.end(); i++)
    {
//      TheEventProviders.undeclare(i->first.c_str(), this);

        for(TEventObserverList::iterator j = (i->second).begin(); 
            j != i->second.end(); j++)
        {
            (*j)->ackUnsubscribe(this);
        }
    }
}

void CEventProvider::subscribe(CEventObserver* pObserver)
{
    THREAD_SAFE

    bool    observerNotRegistered   = true;

    if(!m_observers.empty())
    {
        for(TEventObserverMap::iterator i = m_observers.begin(); 
            i != m_observers.end(); i++)
        {
            TEventObserverList* pObserverList = &(i->second);

            bool observerNotRegisteredForThisEvent = true;
            for(TEventObserverList::iterator j = pObserverList->begin(); 
                j != pObserverList->end(); j++)
            {
                if(*j == pObserver)
                {
                    // Got it : already subscribed
                    observerNotRegisteredForThisEvent = false;
                    observerNotRegistered = false;
                    break;
                }
            }

            if(observerNotRegisteredForThisEvent)
            {
                pObserverList->push_back(pObserver);
            }
        }

        if(observerNotRegistered)
        {
            pObserver->ackSubscribe(this);
        }
    }
    else
    {
        // no event declared
    }
}

void CEventProvider::subscribe(CEventObserver* pObserver, const IEvent& rEvent)
{
    THREAD_SAFE

    TEventObserverMap::iterator i;
    if((i = m_observers.find(typeid(rEvent).name())) != m_observers.end())
    {
        // Known event (declared)

        TEventObserverList* pObserverList = &(i->second);

        bool observerNotRegisteredForThisEvent = true;
        for(TEventObserverList::iterator j = pObserverList->begin(); 
            j != pObserverList->end(); j++)
        {
            if(*j == pObserver)
            {
                // Got it : already subscribed
                observerNotRegisteredForThisEvent = false;
                break;
            }
        }

        if(observerNotRegisteredForThisEvent)
        {
            pObserverList->push_back(pObserver);
            pObserver->ackSubscribe(this);
        }
    }
    else
    {
        // Unknown event (not declared)
    }
}

void CEventProvider::unsubscribe(CEventObserver* pObserver)
{
    THREAD_SAFE

    for(TEventObserverMap::iterator i = m_observers.begin(); 
        i != m_observers.end(); i++)
    {
        i->second.remove(pObserver);
    }

    pObserver->ackUnsubscribe(this);
}

void CEventProvider::unsubscribe(CEventObserver* pObserver, 
                                 const IEvent& rEvent)
{
    THREAD_SAFE

    TEventObserverMap::iterator i;
    if((i = m_observers.find(typeid(rEvent).name())) != m_observers.end())
    {
        i->second.remove(pObserver);
    }

    bool observerNoLongerRegistered = true;
    for(i = m_observers.begin(); i != m_observers.end(); i++)
    {
        TEventObserverList* pObserverList = &(i->second);

        for(TEventObserverList::iterator j = pObserverList->begin(); 
            j != pObserverList->end(); j++)
        {
            if(*j == pObserver)
            {
                // Got it : pObserver still registered for other event
                observerNoLongerRegistered = false;
                break;
            }
        }
    }

    if(observerNoLongerRegistered)
    {
        pObserver->ackUnsubscribe(this);
    }
}

int CEventProvider::getNbObservers(const IEvent& rEvent) const
{
    THREAD_SAFE

    TEventObserverMap::const_iterator i;
    if((i = m_observers.find(typeid(rEvent).name())) != m_observers.end())
    {
        // Event declared
        return (i->second.size());
    }
    else
    {
        // Event not declared
        return -1;
    }
}

void CEventProvider::declare(const IEvent& rEvent)
{
    TEventObserverMap::iterator i;

    if((i = m_observers.find(typeid(rEvent).name())) != m_observers.end())
    {
        // event already declared (this should not happen : events should be 
        // declared once!)
        ASSERT(false);
        return;
    }

    // Event not yet declared => create entry in the map
    TEventObserverList emptyList;
    m_observers.insert(TEventObserverMap::value_type(typeid(rEvent).name(), 
                                                     emptyList));

//  TheEventProviders.declare(rEvent, this);
}

unsigned int CEventProvider::notify(const IEvent& rEvent)
{
    THREAD_SAFE

    TEventObserverMap::iterator i;
    unsigned int nbNotifiedObservers = 0;
    if((i = m_observers.find(typeid(rEvent).name())) != m_observers.end())
    {
        // use endIt in order to avoid calling new observers which subscribed 
        // during a onEvent()
        TEventObserverList::iterator endIt = (i->second).end();
        for(TEventObserverList::iterator j = (i->second).begin(); j != endIt; )
        {
            // onEvent() can call unsubscribe() => use a temporary iterator 
            // jTmp to make the call
            // so that j points to the next item and is guaranteed to be valid 
            // even if item pointed to by jTmp is deleted
            TEventObserverList::iterator jTmp = j++;
            (*jTmp)->onEvent(*this, rEvent);
            nbNotifiedObservers++;
        }
    }
    else
    {
        // Should not occur : derived class should not notify any event it has 
        // not declared
        ASSERT(false);
    }

    // Return the number of observers which have been notified (don't return 
    // (i->second).size() since an observer can unsubscribe in onEvent())
    return nbNotifiedObservers;
}

