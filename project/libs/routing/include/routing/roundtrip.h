#ifndef ROUND_PATHING_H_
#define ROUND_PATHING_H_

#include "routing/astar.h"
#include <string>

namespace routing {

class TheRoundTrip : public AStar {
public:
    TheRoundTrip() : AStar(new EuclideanDistance(), new ZeroDistance()) {}
	virtual ~TheRoundTrip() {}

	static const RoutingStrategy& Instance() {
		static TheRoundTrip trip;
		return trip;
	}
};

}

#endif
