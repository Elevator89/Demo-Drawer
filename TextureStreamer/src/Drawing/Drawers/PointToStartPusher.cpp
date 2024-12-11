#include "PointToStartPusher.h"

PointToStartPusher::PointToStartPusher() {}
PointToStartPusher::~PointToStartPusher() {}

void PointToStartPusher::PushPoint(std::list<Point>& points, const Point& pointToPush) const
{
	points.push_front(pointToPush);
}
