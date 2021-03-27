#include "Generator.h"
#include "ColorUtil.h"

Generator::Generator(unsigned int width, unsigned int height) :
	m_distribution(0, 255),
	m_field(width, height, (uint32_t)Color::White),
	m_total(0)
{}

Generator::~Generator() {}

void Generator::Generate(int steps)
{
	for(unsigned int y = 0; y < GetHeight(); ++y)
		for(unsigned int x = 0; x < GetWidth(); ++x)
		{
			uint32_t color = ColorEncode(
								 (unsigned char)m_distribution(m_generator),
								 (unsigned char)m_distribution(m_generator),
								 (unsigned char)m_distribution(m_generator),
								 (unsigned char)m_distribution(m_generator));

//			Color color(
//				(unsigned char)(m_total / 255),
//				(unsigned char)(m_total / 2 / 255),
//				(unsigned char)(m_total / 3 / 255)
//			);
			m_field.SetCell(x,y,color);
		}

	m_total += steps;
}

