#include "RandomColorGenerator.h"

RandomColorGenerator::RandomColorGenerator() :
	m_colorDistribution(0, 0xFFFFFFFF)
{}

RandomColorGenerator::~RandomColorGenerator()
{}

uint32_t RandomColorGenerator::GenerateColor()
{
	return m_colorDistribution(m_generator);
}
