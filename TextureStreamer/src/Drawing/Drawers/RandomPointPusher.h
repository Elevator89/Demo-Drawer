#pragma once

#include <vector>
#include <random>
#include "Drawing/Drawers/IPointPusher.h"

class RandomPointPusher : public IPointPusher
{
public:
	RandomPointPusher(std::default_random_engine* generator);
	virtual ~RandomPointPusher();

	virtual void PushPoint(std::vector<Point>& points, const Point& pointToPush) const override;

private:
	std::default_random_engine* m_generator;
};
