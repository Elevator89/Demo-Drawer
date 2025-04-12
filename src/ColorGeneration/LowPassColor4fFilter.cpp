#include <cmath>
#include "LowPassColor4fFilter.h"

LowPassColor4fFilter::LowPassColor4fFilter(unsigned int order, float alpha) :
	m_order(order),
	m_alpha(alpha)
{
	m_orderColors = new Color4f[m_order];
	for(unsigned int order = 0; order < m_order; ++order)
	{
		m_orderColors[order] = Color4f::Grey();
	}
}

LowPassColor4fFilter::~LowPassColor4fFilter() {}

Color4f LowPassColor4fFilter::Filter(const Color4f& color)
{
	float oneMinusAlpha = 1.0f - m_alpha;

	Color4f newColor = color;

	for(unsigned int order = 0; order < m_order; ++order)
	{
		newColor = oneMinusAlpha * m_orderColors[order] + m_alpha * newColor;
		m_orderColors[order] = newColor;
	}

	return newColor;
}
