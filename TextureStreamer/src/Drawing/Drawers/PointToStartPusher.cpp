#include "PointToStartPusher.h"

PointToStartPusher::PointToStartPusher() {}
PointToStartPusher::~PointToStartPusher() {}

void PointToStartPusher::PushPoint(std::vector<Point>& points, const Point& pointToPush) const
{
	points.insert(points.cbegin(), pointToPush);
}
