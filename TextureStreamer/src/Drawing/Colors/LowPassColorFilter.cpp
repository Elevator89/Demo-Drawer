#include <cmath>
#include "Drawing/Colors/ColorUtil.h"
#include "LowPassColorFilter.h"

float Clamp01(float value);

LowPassColorFilter::LowPassColorFilter(unsigned int order, float alpha) :
	m_order(order),
	m_alpha(alpha)
{
	m_orderColors = new float[3 * m_order];
	for(unsigned int order = 0; order < m_order; ++order)
	{
		m_orderColors[3 * order + 0] = 0.5f;
		m_orderColors[3 * order + 1] = 0.5f;
		m_orderColors[3 * order + 2] = 0.5f;
	}
}

LowPassColorFilter::~LowPassColorFilter() {}

uint32_t LowPassColorFilter::Filter(uint32_t value)
{
	float colorR, colorG, colorB, colorA;

	ColorDecode(value, colorR, colorG, colorB, colorA);

	for(unsigned int order = 0; order < m_order; ++order)
	{
		float oneMinusAlpha = 1.0f - m_alpha;

		colorR = oneMinusAlpha * m_orderColors[3 * order + 0] + m_alpha * colorR;
		colorG = oneMinusAlpha * m_orderColors[3 * order + 1] + m_alpha * colorG;
		colorB = oneMinusAlpha * m_orderColors[3 * order + 2] + m_alpha * colorB;
		m_orderColors[3 * order + 0] = colorR;
		m_orderColors[3 * order + 1] = colorG;
		m_orderColors[3 * order + 2] = colorB;
	}

	return ColorEncode(colorR, colorG, colorB, 1.0f);
}
