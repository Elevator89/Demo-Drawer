#ifndef ITOPOLOGY_H
#define ITOPOLOGY_H

#include "Drawing/Point.h"

class ITopology
{
public:
	virtual ~ITopology() {}

	virtual bool TryAdd(const Point& a, const Point& b, Point& result) const = 0;
};

#endif // TOPOLOGY_H
