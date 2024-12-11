#include "PointToEndPusher.h"

PointToEndPusher::PointToEndPusher() {}
PointToEndPusher::~PointToEndPusher() {}

void PointToEndPusher::PushPoint(std::vector<Point>& points, const Point& pointToPush) const
{
	points.push_back(pointToPush);
}
