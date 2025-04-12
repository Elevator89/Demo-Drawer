#pragma once

#include <random>
#include <stdint.h>
#include "../Color4f.h"
#include "../IColorGenerator.h"

class RandomColor4fGenerator : public IColorGenerator<Color4f>
{
public:
	RandomColor4fGenerator();
	virtual ~RandomColor4fGenerator();

	Color4f GenerateColor() override;

private:
	std::default_random_engine m_generator;
	std::uniform_real_distribution<float> m_colorDistribution;
};
