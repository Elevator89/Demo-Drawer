#include <random>
#include "Drawing/Colors/Color.h"
#include "PointsTraverserDrawer.h"

PointsTraverserDrawer::PointsTraverserDrawer(const ITopology* topology, const IPointPicker* pointPicker, const IPointPusher* pointPusher, const IPointsTraverser* pointsTraverser, IColorGenerator* colorGenerator, float fieldFillBeforeFlush, std::default_random_engine* randomGenerator):
	m_topology(topology),
	m_pointPicker(pointPicker),
	m_pointPusher(pointPusher),
	m_pointsTraverser(pointsTraverser),
	m_colorGenerator(colorGenerator),
	m_fieldFillBeforeFlush(fieldFillBeforeFlush),
	m_randomGenerator(randomGenerator)
{}

PointsTraverserDrawer::~PointsTraverserDrawer() {}

void PointsTraverserDrawer::Draw(Field<uint32_t>& field)
{
	if(m_visitedPoints.size() > (size_t)(m_fieldFillBeforeFlush * field.GetWidth() * field.GetHeight()))
	{
		m_visitedPoints.clear();
	}

	if(m_pointsToVisit.empty())
	{
		std::uniform_int_distribution<unsigned int> widthDistribution(0, field.GetWidth()-1);
		std::uniform_int_distribution<unsigned int> heightDistribution(0, field.GetHeight()-1);

		m_visitedPoints.clear();
		Point newPoint(widthDistribution(*m_randomGenerator), heightDistribution(*m_randomGenerator));

		m_pointsToVisit.push_back(newPoint);
		m_visitedPoints.insert(newPoint);
	}

	std::list<Point>::const_iterator pointToVisitIt = m_pointPicker->PickPoint(m_pointsToVisit);
	if(pointToVisitIt == m_pointsToVisit.cend()) return;

	Point pointToVisit = *pointToVisitIt;

	field.SetCell(pointToVisit, m_colorGenerator->GenerateColor());
	m_pointsToVisit.erase(pointToVisitIt);

	std::vector<Point> nextPoints;

	m_pointsTraverser->GetNextPoints(pointToVisit, m_topology, m_visitedPoints, nextPoints);

	for(std::vector<Point>::const_iterator nextPointIt = nextPoints.cbegin(); nextPointIt != nextPoints.cend(); ++nextPointIt)
	{
		Point nextPoint = *nextPointIt;
		m_visitedPoints.insert(nextPoint);
		m_pointPusher->PushPoint(m_pointsToVisit, nextPoint);

		field.SetCell(nextPoint, (uint32_t)Color::White);
	}
}
