#pragma once

#include <list>
#include <random>
#include "Drawing/Drawers/IPointPusher.h"

class ChanceBasedPointPusher : public IPointPusher
{
public:
	ChanceBasedPointPusher(const IPointPusher* pusherToDecorate, std::default_random_engine* randomGenerator, float chanceToPush);
	virtual ~ChanceBasedPointPusher();

	virtual void PushPoint(std::list<Point>& points, const Point& pointToPush) const override;

	inline float GetChanceToPush() const
	{
		return m_chanceToPush;
	}

	inline void SetChanceToPick(float chanceToPush)
	{
		m_chanceToPush = chanceToPush;
	}

private:
	const IPointPusher* m_pusherToDecorate;
	std::default_random_engine* m_randomGenerator;
	float m_chanceToPush;
};
