#pragma once

#include <random>
#include <unordered_set>
#include <queue>
#include <stdint.h>
#include "Drawing/Point.h"
#include "Drawing/Field.h"
#include "Drawing/Drawers/IDrawer.h"
#include "Drawing/Topologies/ITopology.h"
#include "Drawing/Colors/IColorGenerator.h"

class PopWithChanceDrawer : public IDrawer
{
public:
	PopWithChanceDrawer(const ITopology* topology, IColorGenerator* colorGenerator, float chanceToUsePoppedItem, unsigned int dotsPerStep);
	virtual ~PopWithChanceDrawer();

	void Draw(Field<uint32_t>& field) override;

private:
	bool TryPushPoint(const Point& point);

private:
	const ITopology* m_topology;
	IColorGenerator* m_colorGenerator;
	float m_chanceToUsePoppedItem;
	unsigned int m_dotsPerStep;

	std::unordered_set<Point> m_visitedPoints;
	std::queue<Point> m_queue;
	std::default_random_engine m_generator;
	std::uniform_real_distribution<float> m_chanceDistribution;
};
