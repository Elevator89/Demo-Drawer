#include "ChanceBasedPointsTraverser.h"

ChanceBasedPointsTraverser::ChanceBasedPointsTraverser(const IPointsTraverser* traverserToDecorate, std::default_random_engine* randomGenerator, float chanceToReturn) :
	m_traverserToDecorate(traverserToDecorate),
	m_randomGenerator(randomGenerator),
	m_chanceToReturn(chanceToReturn)
{}

ChanceBasedPointsTraverser::~ChanceBasedPointsTraverser() {}

const std::vector<Point> ChanceBasedPointsTraverser::GetNextPoints(const Point& point, const ITopology* topology, std::unordered_set<Point>& visitedPoints) const
{
	const std::vector<Point> nextPointsToFilter = m_traverserToDecorate->GetNextPoints(point, topology, visitedPoints);

	std::discrete_distribution<bool> chanceDistribution{1.0f - m_chanceToReturn, m_chanceToReturn};

	std::vector<Point> nextPoints;

	for(std::vector<Point>::const_iterator nextPointToFilter = nextPointsToFilter.cbegin(); nextPointToFilter != nextPointsToFilter.cend(); ++nextPointToFilter)
	{
		if(chanceDistribution(*m_randomGenerator))
			nextPoints.push_back(*nextPointToFilter);
	}

	return nextPoints;
}
