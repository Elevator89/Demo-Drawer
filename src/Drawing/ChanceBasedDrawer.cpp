#include "ChanceBasedDrawer.h"
#include "../Color.h"

ChanceBasedDrawer::ChanceBasedDrawer(const ITopology* topology, IContainer* container, const IPointsTraverser* pointsTraverser, float chanceToPick, float chanceToPush, IColorGenerator* colorGenerator, float fieldFillBeforeFlush, std::default_random_engine* randomGenerator) :
	m_topology(topology),
	m_container(container),
	m_chanceToPick(chanceToPick),
	m_chanceToPush(chanceToPush),
	m_pointsTraverser(pointsTraverser),
	m_colorGenerator(colorGenerator),
	m_fieldFillBeforeFlush(fieldFillBeforeFlush),
	m_randomGenerator(randomGenerator)
{
}

ChanceBasedDrawer::~ChanceBasedDrawer() {}

void ChanceBasedDrawer::Draw(Field<uint32_t>& field)
{
	if (m_visitedPoints.size() > (size_t)(m_fieldFillBeforeFlush * field.GetWidth() * field.GetHeight()))
	{
		m_visitedPoints.clear();
	}

	if (m_container->IsEmpty())
	{
		std::uniform_int_distribution<unsigned int> widthDistribution(0, field.GetWidth() - 1);
		std::uniform_int_distribution<unsigned int> heightDistribution(0, field.GetHeight() - 1);

		m_visitedPoints.clear();
		Point newPoint(widthDistribution(*m_randomGenerator), heightDistribution(*m_randomGenerator));

		m_container->Push(newPoint);
		m_visitedPoints.insert(newPoint);
	}

	const Point pointToVisit = m_container->Pick();

	std::discrete_distribution<int> chanceDistribution{ 1.0f - m_chanceToPick, m_chanceToPick };
	if (chanceDistribution(*m_randomGenerator))
	{
		field.SetCell(pointToVisit, m_colorGenerator->GenerateColor());

		std::vector<Point> nextPoints;

		m_pointsTraverser->GetNextPoints(pointToVisit, m_topology, m_visitedPoints, nextPoints);

		for (std::vector<Point>::const_iterator nextPointIt = nextPoints.cbegin(); nextPointIt != nextPoints.cend(); ++nextPointIt)
		{
			Point nextPoint = *nextPointIt;

			std::discrete_distribution<int> chanceDistribution{ 1.0f - m_chanceToPush, m_chanceToPush };
			if (chanceDistribution(*m_randomGenerator)) {
				m_visitedPoints.insert(nextPoint);
				m_container->Push(nextPoint);

				field.SetCell(nextPoint, (uint32_t)Color::White);
			}
		}
	}
	else
	{
		field.SetCell(pointToVisit, (uint32_t)Color::Black);
	}
}
