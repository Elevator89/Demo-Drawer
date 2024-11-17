#include "RandomPointPicker.h"

RandomPointPicker::RandomPointPicker(std::default_random_engine* generator):
	m_generator(generator)
{}

RandomPointPicker::~RandomPointPicker() {}

std::vector<Point>::const_iterator RandomPointPicker::PickPoint(const std::vector<Point>& points) const
{
	if(points.size() == 0) return points.cend();

	std::uniform_int_distribution<unsigned int> pointsLengthDistribution(0, points.size()-1);
	return points.cbegin() + pointsLengthDistribution(*m_generator);
}
