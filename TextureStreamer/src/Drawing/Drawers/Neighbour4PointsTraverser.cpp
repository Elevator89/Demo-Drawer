#include "Neighbour4PointsTraverser.h"

Neighbour4PointsTraverser::Neighbour4PointsTraverser() {}
Neighbour4PointsTraverser::~Neighbour4PointsTraverser() {}

void Neighbour4PointsTraverser::GetNextPoints(const Point& point, const ITopology* topology, std::unordered_set<Point>& visitedPoints, std::vector<Point>& nextPoints) const
{
	Point pointToUp;
	if(topology->TryAdd(point, Point::Up(), pointToUp))
		if(visitedPoints.find(pointToUp) == visitedPoints.end())
			nextPoints.push_back(pointToUp);

	Point pointToDown;
	if(topology->TryAdd(point, Point::Down(), pointToDown))
		if(visitedPoints.find(pointToDown) == visitedPoints.end())
			nextPoints.push_back(pointToDown);

	Point pointToLeft;
	if(topology->TryAdd(point, Point::Left(), pointToLeft))
		if(visitedPoints.find(pointToLeft) == visitedPoints.end())
			nextPoints.push_back(pointToLeft);

	Point pointToRight;
	if(topology->TryAdd(point, Point::Right(), pointToRight))
		if(visitedPoints.find(pointToRight) == visitedPoints.end())
			nextPoints.push_back(pointToRight);
}
