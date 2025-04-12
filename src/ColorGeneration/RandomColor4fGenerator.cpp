#include "RandomColor4fGenerator.h"

RandomColor4fGenerator::RandomColor4fGenerator() :
	m_colorDistribution(0.0f, 1.0f)
{
}

RandomColor4fGenerator::~RandomColor4fGenerator()
{
}

Color4f RandomColor4fGenerator::GenerateColor()
{
	return Color4f(
		m_colorDistribution(m_generator),
		m_colorDistribution(m_generator),
		m_colorDistribution(m_generator));
}
