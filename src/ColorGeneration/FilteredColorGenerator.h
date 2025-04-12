#pragma once

#include <random>
#include "../IColorGenerator.h"
#include "../IColorFilter.h"

template <typename TColor>
class FilteredColorGenerator : public IColorGenerator<TColor>
{
public:
	FilteredColorGenerator(IColorGenerator<TColor>* colorGenerator, IColorFilter<TColor>* colorFilter) :
		m_fillingColorGenerator(colorGenerator),
		m_colorFilter(colorFilter)
	{}

	virtual ~FilteredColorGenerator() {}

	TColor GenerateColor() override
	{
		return m_colorFilter->Filter(m_fillingColorGenerator->GenerateColor());
	}

private:
	IColorGenerator<TColor>* m_fillingColorGenerator;
	IColorFilter<TColor>* m_colorFilter;
};
