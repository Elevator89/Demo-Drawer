#pragma once

#include "Color4f.h"

template <typename TColor>
class IColorGenerator
{
public:
	virtual ~IColorGenerator() {}

	virtual TColor GenerateColor() = 0;
};
