#pragma once

#include <random>
#include <stdint.h>
#include "../IColorGenerator.h"

class BouncingColorGenerator : public IColorGenerator
{
public:
	BouncingColorGenerator(float deltaR, float deltaG, float deltaB);
	virtual ~BouncingColorGenerator();

	uint32_t GenerateColor() override;

private:
	void BounceValue(float& value, float& delta);

private:
	float m_colorR;
	float m_colorG;
	float m_colorB;

	float m_deltaR;
	float m_deltaG;
	float m_deltaB;
};
