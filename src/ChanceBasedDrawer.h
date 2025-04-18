#pragma once

#include <unordered_set>
#include <vector>
#include <algorithm>
#include <random>
#include "IContainer.h"
#include "Point.h"
#include "Field.h"
#include "ITopology.h"
#include "IColorGenerator.h"

template <typename TColor>
class ChanceBasedDrawer
{
public:
	ChanceBasedDrawer(const ITopology* topology, IContainer* container, float chanceToPick, float chanceToPush, IColorGenerator<TColor>* colorGenerator, IColorGenerator<TColor>* containerColorGenerator, float fieldFillBeforeFlush, std::default_random_engine* randomGenerator) :
		m_topology(topology),
		m_container(container),
		m_chanceToPick(chanceToPick),
		m_chanceToPush(chanceToPush),
		m_fillingColorGenerator(colorGenerator),
		m_containerColorGenerator(containerColorGenerator),
		m_fieldFillBeforeFlush(fieldFillBeforeFlush),
		m_randomGenerator(randomGenerator),
		m_directions{ Point::Up(), Point::Down(), Point::Left(), Point::Right() }
	{
	}

	~ChanceBasedDrawer() {}

	void Draw(Field<TColor>& colorField, Field<TColor>& containerField) {
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
			containerField.SetCell(newPoint, m_containerColorGenerator->GenerateColor());

			m_visitedPoints.insert(newPoint);
		}

		const Point pointToVisit = m_container->Pick();
		containerField.SetCell(pointToVisit, TColor());

		std::uniform_real_distribution<float> chanceDistribution{ 0.0f, 1.0f };
		if (chanceDistribution(*m_randomGenerator) < m_chanceToPick)
		{
			colorField.SetCell(pointToVisit, m_fillingColorGenerator->GenerateColor());

			std::shuffle(m_directions.begin(), m_directions.end(), *m_randomGenerator);

			for (Point direction : m_directions)
			{
				Point pointAtDirection;
				if (chanceDistribution(*m_randomGenerator) < m_chanceToPush && m_topology->TryAdd(pointToVisit, direction, pointAtDirection) && m_visitedPoints.find(pointAtDirection) == m_visitedPoints.end())
				{
					m_visitedPoints.insert(pointAtDirection);
					m_container->Push(pointAtDirection);
					containerField.SetCell(pointAtDirection, m_containerColorGenerator->GenerateColor());
				}
			}
		}
	}

	inline const ITopology* GetTopology() const { return m_topology; }
	inline void SetTopology(const ITopology* topology) { m_topology = topology; }

	inline float GetChanceToPick() const { return m_chanceToPick; }
	inline void SetChanceToPick(float chanceToPick) { m_chanceToPick = chanceToPick; }

	inline float GetChanceToPush() const { return m_chanceToPush; }
	inline void SetChanceToPush(float chanceToPush) { m_chanceToPush = chanceToPush; }

	inline IContainer* GetContainer() const { return m_container; }
	inline void SetContainer(IContainer* container) { m_container = container; }

private:
	const ITopology* m_topology;
	IContainer* m_container;
	float m_chanceToPick;
	float m_chanceToPush;
	IColorGenerator<TColor>* m_fillingColorGenerator;
	IColorGenerator<TColor>* m_containerColorGenerator;
	float m_fieldFillBeforeFlush;

	std::default_random_engine* m_randomGenerator;
	std::unordered_set<Point> m_visitedPoints;
	std::vector<Point> m_directions;
};