#include "PointToEndPusher.h"

PointToEndPusher::PointToEndPusher() {}
PointToEndPusher::~PointToEndPusher() {}

void PointToEndPusher::PushPoint(std::list<Point>& points, const Point& pointToPush) const
{
	points.push_back(pointToPush);
}
