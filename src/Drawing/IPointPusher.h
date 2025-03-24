#pragma once

#include <list>
#include "../Point.h"

class IPointPusher
{
public:
	virtual ~IPointPusher() {}
	virtual void PushPoint(std::list<Point>& points, const Point& pointToPush) const = 0;
};
