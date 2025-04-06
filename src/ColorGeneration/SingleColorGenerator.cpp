#include "SingleColorGenerator.h"

SingleColorGenerator::SingleColorGenerator(uint32_t color) :
	m_color(color)
{}

SingleColorGenerator::~SingleColorGenerator() {}

uint32_t SingleColorGenerator::GenerateColor()
{
	return GetColor();
}

