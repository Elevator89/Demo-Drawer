#pragma once

#include<stdint.h>

class IColorGenerator
{
public:
	virtual ~IColorGenerator() {}

	virtual uint32_t GenerateColor() = 0;
};
