#pragma once

#include <random>
#include <unordered_set>
#include <stack>
#include <stdint.h>
#include "Drawing/Point.h"
#include "Drawing/Field.h"
#include "Drawing/Drawers/IDrawer.h"
#include "Drawing/Topologies/ITopology.h"
#include "Drawing/Colors/IColorGenerator.h"

class StackPopWithChanceDrawer : public IDrawer
{
public:
	StackPopWithChanceDrawer(const ITopology* topology, IColorGenerator* colorGenerator, float chanceToUsePoppedItem, float fieldFillBeforeFlush);
	virtual ~StackPopWithChanceDrawer();

	void Draw(Field<uint32_t>& field) override;

private:
	bool TryPushPoint(const Point& point);

private:
	const ITopology* m_topology;
	IColorGenerator* m_colorGenerator;
	float m_chanceToUsePoppedItem;
	float m_fieldFillBeforeFlush;

	std::unordered_set<Point> m_visitedPoints;
	std::stack<Point> m_stack;
	std::default_random_engine m_generator;
	std::uniform_real_distribution<float> m_chanceDistribution;
};
