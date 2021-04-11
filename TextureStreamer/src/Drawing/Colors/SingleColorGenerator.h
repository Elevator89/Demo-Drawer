#pragma once

#include <stdint.h>
#include "IColorGenerator.h"

class SingleColorGenerator : public IColorGenerator
{
public:
	SingleColorGenerator(uint32_t color);
	virtual ~SingleColorGenerator();

	uint32_t GenerateColor() override;

	inline uint32_t GetColor()
	{
		return m_color;
	}

	inline void SetColor(uint32_t color)
	{
		m_color = color;
	}

private:
	uint32_t m_color;
};
