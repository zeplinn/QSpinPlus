#ifndef VERIFICATIONMENUHANDLER_H
#define VERIFICATIONMENUHANDLER_H

#include <QObject>
#include "qspin/models/QsVerificationResults.h"
#include <QQmlEngine>
#include <memory>
#include "qspin/viewModels/EventAggregator.h"
#include "qspin/Qs.h"
#include "qspin/QmlImportNames.h"
class QsVerifyHandler : public QObject
{
		Q_OBJECT


		//#################### result properties end #########################
EventAggregator& msgService;
	public:
//		enum ResultCode{
//			PartialOrderReduction,
//			NeverClaim,
//			AssertionVioLations,
//			AcceptanceCycles,
//			InvalidEndStates
//		};
//		Q_ENUMS(ResultCode)
		static void registerAsQml();
        explicit QsVerifyHandler(QObject *parent = nullptr);
        //Q_INVOKABLE qreal verifyResults(ResultCode code);

	signals:
		void updateResults(const QsVerificationResults *);

	public slots:
};

#endif // VERIFICATIONMENUHANDLER_H
