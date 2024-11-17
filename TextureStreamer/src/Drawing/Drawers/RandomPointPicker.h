#pragma once

#include <vector>
#include <random>
#include "Drawing/Drawers/IPointPicker.h"

class RandomPointPicker : public IPointPicker
{
public:
	RandomPointPicker(std::default_random_engine* generator);
	virtual ~RandomPointPicker();
	virtual std::vector<Point>::const_iterator PickPoint(const std::vector<Point>& points) const override;

private:
	std::default_random_engine* m_generator;
};
