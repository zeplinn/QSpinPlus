#include "qspin/viewModels/EventAggregator.h"

/*!
 * \brief EventAggregator is a message data system used to decouple views from eachother.
 * It makes sure that no view have to know about another view.
 * This makes the addition of adding and removing views easier for views sharing dynamic data
 * each view have to inheret from ISubcriber<T>, where T is the message message object that is being listened to.
 * Each view call EventAggregotor::subcribe<T>(ISubscriber subscriber) to add itself to the messsage system in its contructor.
 * It has to do so for each message object it want to listen to.
 *
 * The implementation is loosly based on C# implentation provided by:
 * www.pluralsight.com
 *course: Design Patterns Library
 *
 * \param parent
 * \fn subcribe<T>(ISubstriber<T> subscriber)
 * \fn publish<T>(T publisher)
 * \
 */

EventAggregator::EventAggregator(QObject *parent):QObject(parent){}



QLinkedList<EventAggregator::s_ptr> EventAggregator::getSubsrcibers(size_t id){
    mutex.lock();
    QLinkedList<s_ptr> tmp(hs[id]);
    mutex.lock();
    return tmp;
}

