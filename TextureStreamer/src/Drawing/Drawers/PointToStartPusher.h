#pragma once

#include <vector>
#include <random>
#include "Drawing/Drawers/IPointPusher.h"

class PointToStartPusher : public IPointPusher
{
public:
	PointToStartPusher();
	virtual ~PointToStartPusher();

	virtual void PushPoint(std::vector<Point>& points, const Point& pointToPush) const override;
};
