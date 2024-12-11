#include "RandomPointPusher.h"

RandomPointPusher::RandomPointPusher(std::default_random_engine* generator):
	m_generator(generator)
{}

RandomPointPusher::~RandomPointPusher() {}

void RandomPointPusher::PushPoint(std::vector<Point>& points, const Point& pointToPush) const
{
	if(points.size() == 0)
	{
		points.push_back(pointToPush);
		return;
	}

	std::uniform_int_distribution<unsigned int> pointsLengthDistribution(0, points.size()-1);
	std::vector<Point>::const_iterator randomPlace = points.cbegin() + pointsLengthDistribution(*m_generator);

	points.insert(randomPlace, pointToPush);
}
