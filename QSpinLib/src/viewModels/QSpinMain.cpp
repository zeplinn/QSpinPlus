#include "qspin/viewModels/QSpinMain.h"

QSpinMain::QSpinMain(QObject *parent, EventAggregator& msgService)
	: QObject(parent), msgService(msgService)
{
}
