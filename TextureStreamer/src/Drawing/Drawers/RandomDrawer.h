#pragma once

#include <random>
#include <stdint.h>
#include "Drawing/IDrawer.h"
#include "Drawing/Field.h"

class RandomDrawer : public IDrawer
{
public:
	RandomDrawer(unsigned int dotsPerStep);
	virtual ~RandomDrawer() override;

	void Draw(Field<uint32_t>& field) override;

private:
	std::default_random_engine m_generator;
	std::uniform_int_distribution<uint32_t> m_colorDistribution;
	unsigned int m_dotsPerStep;
};
