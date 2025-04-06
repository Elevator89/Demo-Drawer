#pragma once

#include <list>
#include <random>
#include "../IPointPusher.h"

class PointToEndPusher : public IPointPusher
{
public:
	PointToEndPusher();
	virtual ~PointToEndPusher();

	virtual void PushPoint(std::list<Point>& points, const Point& pointToPush) const override;
};
