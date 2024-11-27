#pragma once

#include <unordered_set>
#include <vector>
#include "Drawing/Point.h"
#include "Drawing/Topologies/ITopology.h"

class IPointsTraverser
{
public:
	virtual ~IPointsTraverser() {}
	virtual void GetNextPoints(const Point& point, const ITopology* topology, std::unordered_set<Point>& visitedPoints, std::vector<Point>& nextPoints) const = 0;
};
