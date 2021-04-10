#ifndef POPWITHCHANCEPOOLGENERATOR_H
#define POPWITHCHANCEPOOLGENERATOR_H

#include <random>
#include <unordered_set>
#include <queue>
#include <stdint.h>
#include "Drawing/Point.h"
#include "Drawing/IDrawer.h"
#include "Drawing/Field.h"
#include "Drawing/ITopology.h"

class PopWithChanceDrawer : public IDrawer
{
public:
	PopWithChanceDrawer(const ITopology* topology, float chanceToUsePoppedItem, unsigned int dotsPerStep);
	virtual ~PopWithChanceDrawer();

	void Generate(Field<uint32_t>& field) override;

private:
	bool TryPushPoint(const Point& point);

private:
	const ITopology* m_topology;
	float m_chanceToUsePoppedItem;
	unsigned int m_dotsPerStep;

	std::unordered_set<Point> m_visitedPoints;
	std::queue<Point> m_queue;
	std::default_random_engine m_generator;
	std::uniform_real_distribution<float> m_chanceDistribution;
};

#endif // PROBABILITYBASEDGENERATOR_H
