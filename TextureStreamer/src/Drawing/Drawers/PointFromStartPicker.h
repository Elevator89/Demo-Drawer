#pragma once

#include <vector>
#include "Drawing/Drawers/IPointPicker.h"

class PointFromStartPicker : public IPointPicker
{
public:
	virtual ~PointFromStartPicker();
	virtual std::vector<Point>::const_iterator PickPoint(const std::vector<Point>& points) const override;
};
