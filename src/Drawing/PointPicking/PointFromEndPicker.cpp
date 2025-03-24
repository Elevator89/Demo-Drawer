#include "PointFromEndPicker.h"

PointFromEndPicker::~PointFromEndPicker() {}

std::list<Point>::const_iterator PointFromEndPicker::PickPoint(const std::list<Point>& points) const
{
	if(points.size() == 0) return points.cend();
	return --points.cend();
}
