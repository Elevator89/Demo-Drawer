#pragma once

#include <random>
#include <unordered_set>
#include <stack>
#include <stdint.h>
#include "../IDrawer.h"
#include "../Point.h"
#include "../Field.h"
#include "../ITopology.h"
#include "../IColorGenerator.h"

class StackPushWithChanceDrawer : public IDrawer
{
public:
	StackPushWithChanceDrawer(const ITopology* topology, IColorGenerator* colorGenerator, float chanceToPushItem, float fieldFillBeforeFlush);
	virtual ~StackPushWithChanceDrawer();

	void Draw(Field<uint32_t>& field) override;

private:
	bool TryPushPoint(const Point& point);

private:
	const ITopology* m_topology;
	IColorGenerator* m_colorGenerator;
	float m_chanceToPushItem;
	float m_fieldFillBeforeFlush;

	std::unordered_set<Point> m_visitedPoints;
	std::stack<Point> m_stack;
	std::default_random_engine m_generator;
	std::uniform_real_distribution<float> m_chanceDistribution;
};
