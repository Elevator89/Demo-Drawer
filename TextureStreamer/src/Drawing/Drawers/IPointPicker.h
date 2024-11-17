#pragma once

#include <vector>
#include "Drawing/Point.h"

class IPointPicker
{
public:
	virtual ~IPointPicker() {}
	virtual std::vector<Point>::const_iterator PickPoint(const std::vector<Point>& points) const = 0;
};
