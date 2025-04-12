#pragma once

#include "../IColorGenerator.h"
#include "../IColorFilter.h"

template <typename TColor>
class RecurrentFilteringColorGenerator : public IColorGenerator<TColor>
{
public:
	RecurrentFilteringColorGenerator(TColor initalColor, IColorFilter<TColor>* colorFilter) : m_colorFilter(colorFilter), m_currentColor(initalColor) {}
	virtual ~RecurrentFilteringColorGenerator() {}

	TColor GenerateColor() override
	{
		m_currentColor = m_colorFilter->Filter(m_currentColor);
		return m_currentColor;
	}

private:
	IColorFilter<TColor>* m_colorFilter;
	TColor m_currentColor;
};
