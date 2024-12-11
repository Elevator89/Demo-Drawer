#pragma once

#include <list>
#include "Drawing/Point.h"

class IPointPicker
{
public:
	virtual ~IPointPicker() {}
	virtual std::list<Point>::const_iterator PickPoint(const std::list<Point>& points) const = 0;
};
