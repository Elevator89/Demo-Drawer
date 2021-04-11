#pragma once

#include <random>
#include <stdint.h>
#include "Drawing/Colors/IColorFilter.h"

class LowPassColorFilter : public IColorFilter
{
public:
	LowPassColorFilter(unsigned int order, float alpha);
	virtual ~LowPassColorFilter();

	uint32_t Filter(uint32_t value) override;

private:
	unsigned int m_order;
	float m_alpha;
	float* m_orderColors;
};
