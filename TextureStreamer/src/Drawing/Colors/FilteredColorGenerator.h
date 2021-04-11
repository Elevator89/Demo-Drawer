#pragma once

#include <random>
#include <stdint.h>
#include "Drawing/Colors/IColorGenerator.h"
#include "Drawing/Colors/IColorFilter.h"

class FilteredColorGenerator : public IColorGenerator
{
public:
	FilteredColorGenerator(IColorGenerator* colorGenerator, IColorFilter* colorFilter);
	virtual ~FilteredColorGenerator();

	uint32_t GenerateColor() override;

private:
	IColorGenerator* m_colorGenerator;
	IColorFilter* m_colorFilter;
};
