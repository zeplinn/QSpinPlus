#ifndef QS_H
#define QS_H
#include "qspin/viewModels/EventAggregator.h"
#include "qspin/viewModels/ColorScheme.h"
class Qs{
		EventAggregator _aggregator;
        ColorScheme _colorScheme;
		Qs();
	public:
		Qs(Qs const&)               = delete;
		void operator=(Qs const&)   = delete;

		static Qs& instance();
		// member functions
		EventAggregator& msgService();
        ColorScheme& colorScheme();

};

#endif // QS_H
