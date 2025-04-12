#pragma once

#include <stdint.h>
#include "../IColorGenerator.h"

template <typename TColor>
class SingleColorGenerator : public IColorGenerator<TColor>
{
public:
	SingleColorGenerator(TColor color) : m_color(color) {}
	virtual ~SingleColorGenerator() {}

	TColor GenerateColor() override
	{
		return GetColor();
	}

	inline TColor GetColor() { return m_color; }
	inline void SetColor(TColor color) { m_color = color; }

private:
	TColor m_color;
};
