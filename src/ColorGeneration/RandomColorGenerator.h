#pragma once

#include <random>
#include <stdint.h>
#include "../IColorGenerator.h"

class RandomColorGenerator : public IColorGenerator
{
public:
	RandomColorGenerator();
	virtual ~RandomColorGenerator();

	uint32_t GenerateColor() override;

private:
	std::default_random_engine m_generator;
	std::uniform_int_distribution<uint32_t> m_colorDistribution;
};
