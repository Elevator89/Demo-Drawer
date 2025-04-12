#pragma once

#include <random>
#include "../IColorFilter.h"
#include "../Color4f.h"

class LowPassColor4fFilter : public IColorFilter<Color4f>
{
public:
	LowPassColor4fFilter(unsigned int order, float alpha);
	virtual ~LowPassColor4fFilter();

	Color4f Filter(const Color4f& value) override;

private:
	unsigned int m_order;
	float m_alpha;
	Color4f* m_orderColors;
};
