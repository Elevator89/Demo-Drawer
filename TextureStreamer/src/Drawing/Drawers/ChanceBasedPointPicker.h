#pragma once

#include <vector>
#include <random>
#include "Drawing/Drawers/IPointPicker.h"

class ChanceBasedPointPicker : public IPointPicker
{
public:
	ChanceBasedPointPicker(const IPointPicker* pickerToDecorate, std::default_random_engine* randomGenerator, float chanceToPick);
	virtual ~ChanceBasedPointPicker();
	virtual std::vector<Point>::const_iterator PickPoint(const std::vector<Point>& points) const override;

	inline float GetChanceToPick() const
	{
		return m_chanceToPick;
	}

	inline void SetChanceToPick(float chanceToPick)
	{
		m_chanceToPick = chanceToPick;
	}

private:
	const IPointPicker* m_pickerToDecorate;
	std::default_random_engine* m_randomGenerator;
	float m_chanceToPick;
};
