#include "RandomPointPicker.h"

RandomPointPicker::RandomPointPicker(std::default_random_engine* generator):
	m_generator(generator)
{}

RandomPointPicker::~RandomPointPicker() {}

std::list<Point>::const_iterator RandomPointPicker::PickPoint(const std::list<Point>& points) const
{
	if(points.size() == 0) return points.cend();

	std::uniform_int_distribution<size_t> pointsLengthDistribution(0, points.size()-1);

	std::list<Point>::const_iterator it = points.cbegin();
	for(size_t i = 0; i < pointsLengthDistribution(*m_generator); ++i)
		it++;

	return it;
}
