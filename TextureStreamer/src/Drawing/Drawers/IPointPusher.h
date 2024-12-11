#pragma once

#include <vector>
#include "Drawing/Point.h"

class IPointPusher
{
public:
	virtual ~IPointPusher() {}
	virtual void PushPoint(std::vector<Point>& points, const Point& pointToPush) const = 0;
};
