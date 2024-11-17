#pragma once

#include <vector>
#include "Drawing/Drawers/IPointPicker.h"

class PointFromEndPicker : public IPointPicker
{
public:
	virtual ~PointFromEndPicker();
	virtual std::vector<Point>::const_iterator PickPoint(const std::vector<Point>& points) const override;
};
