#include "FilteredColorGenerator.h"

FilteredColorGenerator::FilteredColorGenerator(IColorGenerator* colorGenerator, IColorFilter* colorFilter) :
	m_colorGenerator(colorGenerator),
	m_colorFilter(colorFilter)
{}

FilteredColorGenerator::~FilteredColorGenerator() {}

uint32_t FilteredColorGenerator::GenerateColor()
{
	return m_colorFilter->Filter(m_colorGenerator->GenerateColor());
}
