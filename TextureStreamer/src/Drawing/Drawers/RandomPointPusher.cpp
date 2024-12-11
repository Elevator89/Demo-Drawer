#include "RandomPointPusher.h"

RandomPointPusher::RandomPointPusher(std::default_random_engine* generator):
	m_generator(generator)
{}

RandomPointPusher::~RandomPointPusher() {}

void RandomPointPusher::PushPoint(std::list<Point>& points, const Point& pointToPush) const
{
	if(points.size() == 0)
	{
		points.push_back(pointToPush);
		return;
	}

	std::uniform_int_distribution<unsigned int> pointsLengthDistribution(0, points.size()-1);

	std::list<Point>::const_iterator it = points.cbegin();
	for(unsigned int i = 0; i < pointsLengthDistribution(*m_generator); ++i)
		it++;

	points.insert(it, pointToPush);
}
