#ifndef QSQSPINMAINHANDLER_H
#define QSQSPINMAINHANDLER_H
#include <QObject>
#include <qspin/Qs.h>
#include <qspin/viewModels/EventAggregator.h>
#include "qspin/eventObjects/SelectedToolTabUpdated.h"
class QsQSpinMainHandler: public QObject, public ISubscriber<SelectedToolTabUpdated>{
		Q_OBJECT
		//########################## begin properties
		Q_PROPERTY(bool isVerificationTabSelected READ isVerificationTabSelected NOTIFY selectedToolTabChanged)
		Q_PROPERTY(bool isVerificationResultTabSelected READ isVerificationResultTabSelected NOTIFY selectedToolTabChanged)
		Q_PROPERTY(bool isSimulationTabSelected READ isSimulationTabSelected NOTIFY selectedToolTabChanged)
		bool _isVerificationTabSelected
		, _isVerificationResultTabSelected
		, _isSimulationTabSelected;

	public:
		bool isVerificationTabSelected()const;
		bool isVerificationResultTabSelected()const;
		bool isSimulationTabSelected()const;

	signals :
		void selectedToolTabChanged();
		//########################## end properties

	public:
		explicit QsQSpinMainHandler(QObject* parent = nullptr):QObject(parent)
		,_isVerificationTabSelected(true)
		  ,_isVerificationResultTabSelected(false)
		  ,_isSimulationTabSelected(false)
		{}


		// ISubscriber interface
	public:
		virtual void subscriber(const SelectedToolTabUpdated& event) override;

};

#endif // QSQSPINMAINHANDLER_H
