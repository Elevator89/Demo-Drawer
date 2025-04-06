#pragma once

#include <list>
#include "../IPointPicker.h"

class PointFromEndPicker : public IPointPicker
{
public:
	virtual ~PointFromEndPicker();
	virtual std::list<Point>::const_iterator PickPoint(const std::list<Point>& points) const override;
};
