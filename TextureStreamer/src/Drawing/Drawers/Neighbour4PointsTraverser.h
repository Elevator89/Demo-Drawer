#pragma once

#include <unordered_set>
#include <vector>
#include "Drawing/Point.h"
#include "Drawing/Topologies/ITopology.h"
#include "Drawing/Drawers/IPointsTraverser.h"

class Neighbour4PointsTraverser : public IPointsTraverser
{
public:
	Neighbour4PointsTraverser();
	virtual ~Neighbour4PointsTraverser();

	virtual const std::vector<Point> GetNextPoints(const Point& point, const ITopology* topology, std::unordered_set<Point>& visitedPoints) const override;
};
