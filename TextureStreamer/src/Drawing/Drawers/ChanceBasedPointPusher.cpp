#include "ChanceBasedPointPusher.h"

ChanceBasedPointPusher::ChanceBasedPointPusher(const IPointPusher* pusherToDecorate, std::default_random_engine* randomGenerator, float chanceToPush):
	m_pusherToDecorate(pusherToDecorate),
	m_randomGenerator(randomGenerator),
	m_chanceToPush(chanceToPush)
{}

ChanceBasedPointPusher::~ChanceBasedPointPusher()
{
	delete m_pusherToDecorate;
}

void ChanceBasedPointPusher::PushPoint(std::vector<Point>& points, const Point& pointToPush) const
{
	std::discrete_distribution<bool> chanceDistribution{1.0f - m_chanceToPush, m_chanceToPush};

	if(chanceDistribution(*m_randomGenerator))
		m_pusherToDecorate->PushPoint(points, pointToPush);
}
