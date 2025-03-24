#pragma once

#include<stdint.h>

class IColorFilter
{
public:
	virtual ~IColorFilter() {}

	virtual uint32_t Filter(uint32_t value) = 0;
};

