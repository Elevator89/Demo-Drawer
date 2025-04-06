#include "ChanceBasedPointPicker.h"

ChanceBasedPointPicker::ChanceBasedPointPicker(const IPointPicker* pickerToDecorate, std::default_random_engine* randomGenerator, float chanceToPick):
	m_pickerToDecorate(pickerToDecorate),
	m_randomGenerator(randomGenerator),
	m_chanceToPick(chanceToPick)
{}

ChanceBasedPointPicker::~ChanceBasedPointPicker()
{
	delete m_pickerToDecorate;
}

std::list<Point>::const_iterator ChanceBasedPointPicker::PickPoint(const std::list<Point>& points) const
{
	std::discrete_distribution<int> chanceDistribution{1.0f - m_chanceToPick, m_chanceToPick};

	if(chanceDistribution(*m_randomGenerator))
		return m_pickerToDecorate->PickPoint(points);

	return points.cend();
}
