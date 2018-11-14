#include "qspin/viewModels/QsMainHandler.h"

bool QsQSpinMainHandler::isVerificationTabSelected() const{ return _isVerificationTabSelected;}

bool QsQSpinMainHandler::isVerificationResultTabSelected() const{ return _isVerificationResultTabSelected;}

bool QsQSpinMainHandler::isSimulationTabSelected() const{ return _isSimulationTabSelected;}

void QsQSpinMainHandler::subscriber(const SelectedToolTabUpdated&event){
	_isVerificationTabSelected = event.value() ==0;
	_isVerificationResultTabSelected = event.value() == 1;
	_isSimulationTabSelected =event.value() == 2;
	emit selectedToolTabChanged();
}
