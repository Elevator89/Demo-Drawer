#include "../ColorUtil.h"
#include "BouncingColorGenerator.h"

BouncingColorGenerator::BouncingColorGenerator(float deltaR, float deltaG, float deltaB) :
	m_colorR(0.5f),
	m_colorG(0.5f),
	m_colorB(0.5f),
	m_deltaR(deltaR),
	m_deltaG(deltaG),
	m_deltaB(deltaB)
{}

BouncingColorGenerator::~BouncingColorGenerator() {}

uint32_t BouncingColorGenerator::GenerateColor()
{
	BounceValue(m_colorR, m_deltaR);
	BounceValue(m_colorG, m_deltaG);
	BounceValue(m_colorB, m_deltaB);

	return ColorEncode(m_colorR, m_colorG, m_colorB, 1.0f);
}

void BouncingColorGenerator::BounceValue(float& value, float& delta)
{
	value += delta;

	if(value < 0.0f)
	{
		value = -value;
		delta = -delta;
	}

	if(value > 1.0f)
	{
		value = 2.0f - value;
		delta = -delta;
	}
}
