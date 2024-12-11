#pragma once

#include <vector>
#include <random>
#include "Drawing/Drawers/IPointPusher.h"

class PointToEndPusher : public IPointPusher
{
public:
	PointToEndPusher();
	virtual ~PointToEndPusher();

	virtual void PushPoint(std::vector<Point>& points, const Point& pointToPush) const override;
};
