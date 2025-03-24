#pragma once

#include <list>
#include <random>
#include "../IPointPusher.h"

class RandomPointPusher : public IPointPusher
{
public:
	RandomPointPusher(std::default_random_engine* generator);
	virtual ~RandomPointPusher();

	virtual void PushPoint(std::list<Point>& points, const Point& pointToPush) const override;

private:
	std::default_random_engine* m_generator;
};
