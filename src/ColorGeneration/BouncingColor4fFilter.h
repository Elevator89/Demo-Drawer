#pragma once

#include "../IColorFilter.h"
#include "../Color4f.h"

class BouncingColor4fFilter : public IColorFilter<Color4f>
{
public:
	BouncingColor4fFilter(Color4f delta);
	virtual ~BouncingColor4fFilter();

	Color4f Filter(const Color4f& value) override;

private:
	Color4f m_delta;
};
