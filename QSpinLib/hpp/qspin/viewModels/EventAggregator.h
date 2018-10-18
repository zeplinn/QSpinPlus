#ifndef EVENTAGGREGATOR_H
#define EVENTAGGREGATOR_H
#include<QObject>
#include <QDebug>
#include <QLinkedList>
#include <QLinkedListIterator>
#include <QMutex>
#include <QPointer>
#include <memory>
template<class T>
class ISubscriber{

	public:
		virtual ~ISubscriber(){}
		virtual void subscriber(const std::shared_ptr<T> event)=0;
};

class EventAggregator: public QObject{
		typedef  QPointer<QObject> s_ptr;
		typedef QLinkedList<s_ptr> list_type;
		QHash<size_t,list_type> hs;
		QMutex mutex;

	public:
        explicit EventAggregator(QObject* parent=nullptr);

		template<typename T>
		bool subscribe(ISubscriber<T>* subsrciber){
			mutex.lock();
			size_t id = typeid (ISubscriber< T>).hash_code();
			QObject* obj = dynamic_cast<QObject*>(subsrciber);
			if(!obj){
				qFatal("ISubscriber object is not a QObject");
			}
			if(!hs.contains(id)){
				hs[id]=  list_type();
			}
			hs[id].append(s_ptr(obj));
			mutex.lock();
			return true;
		}
		template<typename T>
		void publish(const std::shared_ptr<T> object){
			size_t id = typeid (ISubscriber<T>).hash_code();
			QLinkedList<s_ptr> subcribersToRemove;
            QLinkedList<s_ptr> subscribers(getSubsrcibers(id));

			if(!hs.contains(id)) return; // post error msg?
			QMutableLinkedListIterator<s_ptr>iq(subscribers);
			ISubscriber<T>* item=nullptr;
			while (iq.hasNext()) {
				s_ptr ptr = iq.next();
				if(ptr){
					item = dynamic_cast<ISubscriber<T>*>( ptr.data());
					item->subscriber(object);
				}
				else subcribersToRemove.append(ptr);

			}
			QMutableLinkedListIterator<s_ptr> it(subcribersToRemove);
			mutex.lock();
			while (it.hasNext()) {
				subscribers.removeOne(it.next());
			}
			mutex.unlock();
		}
	private:
        QLinkedList<s_ptr> getSubsrcibers(size_t id);

};
#endif // EVENTAGGREGATOR_H
