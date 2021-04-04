#include "Generator.h"
#include "ColorUtil.h"

Generator::Generator(unsigned int width, unsigned int height) :
	m_distribution(0, 0xFFFFFFFF),
	m_field(width, height, (uint32_t)Color::White),
	m_total(0)
{}

Generator::~Generator() {}

void Generator::Generate(int steps)
{
	for(unsigned int y = 0; y < GetHeight(); ++y)
		for(unsigned int x = 0; x < GetWidth(); ++x)
		{
			uint32_t color = m_distribution(m_generator);

			m_field.SetCell(x,y,color);
		}

	m_total += steps;
}

