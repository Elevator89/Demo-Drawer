#include "ChanceBasedDrawer.h"
#include "Color.h"

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

void ChanceBasedDrawer::Draw(Field<uint32_t>& colorField, Field<uint32_t>& containerField)
{
	if (m_visitedPoints.size() > (size_t)(m_fieldFillBeforeFlush * colorField.GetWidth() * colorField.GetHeight()))
	{
		m_visitedPoints.clear();
	}

	if (m_container->IsEmpty())
	{
		std::uniform_int_distribution<unsigned int> widthDistribution(0, colorField.GetWidth() - 1);
		std::uniform_int_distribution<unsigned int> heightDistribution(0, colorField.GetHeight() - 1);

		m_visitedPoints.clear();
		Point newPoint(widthDistribution(*m_randomGenerator), heightDistribution(*m_randomGenerator));

		m_container->Push(newPoint);
		containerField.SetCell(newPoint, uint32_t(Color::White));

		m_visitedPoints.insert(newPoint);
	}

	const Point pointToVisit = m_container->Pick();
	containerField.SetCell(pointToVisit, uint32_t(Color::Black));

	std::uniform_real_distribution<float> chanceDistribution{ 0.0f, 1.0f};
	if (chanceDistribution(*m_randomGenerator) < m_chanceToPick)
	{
		colorField.SetCell(pointToVisit, m_colorGenerator->GenerateColor());

		std::vector<Point> nextPoints;

		m_pointsTraverser->GetNextPoints(pointToVisit, m_topology, m_visitedPoints, nextPoints);

		for (std::vector<Point>::const_iterator nextPointIt = nextPoints.cbegin(); nextPointIt != nextPoints.cend(); ++nextPointIt)
		{
			Point nextPoint = *nextPointIt;

			if (chanceDistribution(*m_randomGenerator) < m_chanceToPush) {
				m_visitedPoints.insert(nextPoint);

				m_container->Push(nextPoint);
				containerField.SetCell(nextPoint, uint32_t(Color::White));
			}
		}
	}
}
