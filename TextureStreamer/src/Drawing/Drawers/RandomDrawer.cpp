#include "ColorUtil.h"
#include "Drawing/Drawers/RandomDrawer.h"

RandomDrawer::RandomDrawer(unsigned int dotsPerStep) :
	m_colorDistribution(0, 0xFFFFFFFF),
	m_dotsPerStep(dotsPerStep)
{}

RandomDrawer::~RandomDrawer() {}

void RandomDrawer::Generate(Field<uint32_t>& field)
{
	std::uniform_int_distribution<unsigned int> widthDistribution(0, field.GetWidth()-1);
	std::uniform_int_distribution<unsigned int> heightDistribution(0, field.GetHeight()-1);

	for(unsigned int i = 0; i < m_dotsPerStep; ++i)
	{
		unsigned int x = widthDistribution(m_generator);
		unsigned int y = heightDistribution(m_generator);
		uint32_t color = m_colorDistribution(m_generator);

		field.SetCell(x,y,color);
	}
}
