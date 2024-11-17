#include "PointFromEndPicker.h"

PointFromEndPicker::~PointFromEndPicker() {}

std::vector<Point>::const_iterator PointFromEndPicker::PickPoint(const std::vector<Point>& points) const
{
	if(points.size() == 0) return points.cend();
	return --points.cend();
}
