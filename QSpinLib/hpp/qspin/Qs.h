#ifndef QS_H
#define QS_H
#include "qspin/viewModels/EventAggregator.h"

class Qs{
		EventAggregator _aggregator;

		Qs();
	public:
		Qs(Qs const&)               = delete;
		void operator=(Qs const&)   = delete;

		static Qs& instance();
		// member functions
		EventAggregator& msgService();

};

#endif // QS_H
