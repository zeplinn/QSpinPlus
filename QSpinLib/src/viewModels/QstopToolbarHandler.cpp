#include "qspin/viewModels/QsTopToolbarHandler.h"

QstopToolbarHandler::QstopToolbarHandler(QObject*parent, EventAggregator*msgService)
	:QObject(parent),_currentToolTabIndex(0),_msgService(msgService){}
