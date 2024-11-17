#include "PointFromStartPicker.h"

PointFromStartPicker::~PointFromStartPicker() {}

std::vector<Point>::const_iterator PointFromStartPicker::PickPoint(const std::vector<Point>& points) const
{
	if(points.size() == 0) return points.cend();
	return points.cbegin();
}
