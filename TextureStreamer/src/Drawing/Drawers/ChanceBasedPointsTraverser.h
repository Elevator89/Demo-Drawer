#pragma once

#include <unordered_set>
#include <vector>
#include <random>
#include "Drawing/Point.h"
#include "Drawing/Topologies/ITopology.h"
#include "Drawing/Drawers/IPointsTraverser.h"

class ChanceBasedPointsTraverser : public IPointsTraverser
{
public:
	ChanceBasedPointsTraverser(const IPointsTraverser* m_traverserToDecorate, std::default_random_engine* randomGenerator, float chanceToReturn);
	virtual ~ChanceBasedPointsTraverser();

	virtual const std::vector<Point> GetNextPoints(const Point& point, const ITopology* topology, std::unordered_set<Point>& visitedPoints) const override;

	inline float GetChanceToReturn() const
	{
		return m_chanceToReturn;
	}

	inline void SetChanceToPick(float chanceToReturn)
	{
		m_chanceToReturn = chanceToReturn;
	}

private:
	const IPointsTraverser* m_traverserToDecorate;
	std::default_random_engine* m_randomGenerator;
	float m_chanceToReturn;
};
