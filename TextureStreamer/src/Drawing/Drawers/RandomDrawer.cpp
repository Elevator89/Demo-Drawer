#include "Drawing/Colors/ColorUtil.h"
#include "Drawing/Drawers/RandomDrawer.h"

RandomDrawer::RandomDrawer(IColorGenerator* colorGenerator, unsigned int dotsPerStep) :
	m_colorGenerator(colorGenerator),
	m_dotsPerStep(dotsPerStep)
{}

RandomDrawer::~RandomDrawer() {}

void RandomDrawer::Draw(Field<uint32_t>& field)
{
	std::uniform_int_distribution<unsigned int> widthDistribution(0, field.GetWidth()-1);
	std::uniform_int_distribution<unsigned int> heightDistribution(0, field.GetHeight()-1);

	for(unsigned int i = 0; i < m_dotsPerStep; ++i)
	{
		field.SetCell(
			widthDistribution(m_generator),
			heightDistribution(m_generator),
			m_colorGenerator->GenerateColor());
	}
}
