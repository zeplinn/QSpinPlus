#include "qspin/viewModels/QsSpinRunner.h"

QsSpinRunner::QsSpinRunner(QObject *parent, EventAggregator*msgService) : QObject(parent)
{
	if(msgService==nullptr)
		this->msgService = &Qs::instance().msgService();
	else {
		this->msgService=msgService;
	}
}
