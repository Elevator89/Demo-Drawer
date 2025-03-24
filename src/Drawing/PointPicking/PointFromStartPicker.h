#pragma once

#include <list>
#include "../IPointPicker.h"

class PointFromStartPicker : public IPointPicker
{
public:
	virtual ~PointFromStartPicker();
	virtual std::list<Point>::const_iterator PickPoint(const std::list<Point>& points) const override;
};
