#include "Neighbour4PointsTraverser.h"

Neighbour4PointsTraverser::Neighbour4PointsTraverser() {}
Neighbour4PointsTraverser::~Neighbour4PointsTraverser() {}

const std::vector<Point> Neighbour4PointsTraverser::GetNextPoints(const Point& point, const ITopology* topology, std::unordered_set<Point>& visitedPoints) const
{
	std::vector<Point> nextPoints;

	Point pointToUp;
	if(topology->TryAdd(point, Point::Up(), pointToUp) && visitedPoints.find(pointToUp) == visitedPoints.end())
		nextPoints.push_back(pointToUp);

	Point pointToDown;
	if(topology->TryAdd(point, Point::Down(), pointToDown) && visitedPoints.find(pointToDown) == visitedPoints.end())
		nextPoints.push_back(pointToDown);

	Point pointToLeft;
	if(topology->TryAdd(point, Point::Left(), pointToLeft) && visitedPoints.find(pointToLeft) == visitedPoints.end())
		nextPoints.push_back(pointToLeft);

	Point pointToRight;
	if(topology->TryAdd(point, Point::Right(), pointToRight) && visitedPoints.find(pointToRight) == visitedPoints.end())
		nextPoints.push_back(pointToRight);

	return nextPoints;
}
