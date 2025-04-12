#pragma once

#include <unordered_set>
#include <vector>
#include "../Point.h"
#include "../ITopology.h"
#include "../IPointsTraverser.h"

class Neighbour4PointsTraverser : public IPointsTraverser
{
public:
	Neighbour4PointsTraverser();
	virtual ~Neighbour4PointsTraverser();

	virtual void GetNextPoints(const Point& point, const ITopology* topology, std::unordered_set<Point>& visitedPoints, std::vector<Point>& nextPoints) const override;
};
