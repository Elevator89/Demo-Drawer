#pragma once

#include <list>
#include <random>
#include "Drawing/Drawers/IPointPusher.h"

class PointToStartPusher : public IPointPusher
{
public:
	PointToStartPusher();
	virtual ~PointToStartPusher();

	virtual void PushPoint(std::list<Point>& points, const Point& pointToPush) const override;
};
