#pragma once

#include <list>
#include <random>
#include "../IPointPicker.h"

class RandomPointPicker : public IPointPicker
{
public:
	RandomPointPicker(std::default_random_engine* generator);
	virtual ~RandomPointPicker();
	virtual std::list<Point>::const_iterator PickPoint(const std::list<Point>& points) const override;

private:
	std::default_random_engine* m_generator;
};
