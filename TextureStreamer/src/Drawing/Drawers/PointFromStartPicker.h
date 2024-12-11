#pragma once

#include <list>
#include "Drawing/Drawers/IPointPicker.h"

class PointFromStartPicker : public IPointPicker
{
public:
	virtual ~PointFromStartPicker();
	virtual std::list<Point>::const_iterator PickPoint(const std::list<Point>& points) const override;
};
