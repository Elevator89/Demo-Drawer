#include "../ColorUtil.h"
#include "RandomDrawer.h"

RandomDrawer::RandomDrawer(IColorGenerator* colorGenerator) :
	m_colorGenerator(colorGenerator)
{}

RandomDrawer::~RandomDrawer() {}

void RandomDrawer::Draw(Field<uint32_t>& field)
{
	std::uniform_int_distribution<unsigned int> widthDistribution(0, field.GetWidth()-1);
	std::uniform_int_distribution<unsigned int> heightDistribution(0, field.GetHeight()-1);

	field.SetCell(
		widthDistribution(m_generator),
		heightDistribution(m_generator),
		m_colorGenerator->GenerateColor());
}
