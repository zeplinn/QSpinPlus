#include "qspin/Qs.h"

Qs::Qs(){}

Qs&Qs::instance() {
	static Qs self;
	return  self;
}

EventAggregator&Qs::msgService(){ return _aggregator; }
