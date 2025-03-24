#include "PointFromStartPicker.h"

PointFromStartPicker::~PointFromStartPicker() {}

std::list<Point>::const_iterator PointFromStartPicker::PickPoint(const std::list<Point>& points) const
{
	if(points.size() == 0) return points.cend();
	return points.cbegin();
}
