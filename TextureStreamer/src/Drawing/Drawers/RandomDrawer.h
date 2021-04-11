#pragma once

#include <random>
#include <stdint.h>
#include "Drawing/Field.h"
#include "Drawing/Drawers/IDrawer.h"
#include "Drawing/Colors/IColorGenerator.h"

class RandomDrawer : public IDrawer
{
public:
	RandomDrawer(IColorGenerator* colorGenerator);
	virtual ~RandomDrawer() override;

	void Draw(Field<uint32_t>& field) override;

private:
	std::default_random_engine m_generator;
	std::uniform_int_distribution<uint32_t> m_colorDistribution;
	IColorGenerator* m_colorGenerator;
};
