#include "Drawing/Colors/ColorUtil.h"
#include "Drawing/Drawers/RandomDrawer.h"

RandomDrawer::RandomDrawer(IColorGenerator* colorGenerator) :
	m_colorGenerator(colorGenerator)
{}

RandomDrawer::~RandomDrawer() {}

void RandomDrawer::Draw(Field<uint32_t>& field, unsigned int dotCount)
{
	std::uniform_int_distribution<unsigned int> widthDistribution(0, field.GetWidth()-1);
	std::uniform_int_distribution<unsigned int> heightDistribution(0, field.GetHeight()-1);

	for(unsigned int i = 0; i < dotCount; ++i)
	{
		field.SetCell(
			widthDistribution(m_generator),
			heightDistribution(m_generator),
			m_colorGenerator->GenerateColor());
	}
}
