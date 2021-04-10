#ifndef POPWITHCHANCEPOOLGENERATOR_H
#define POPWITHCHANCEPOOLGENERATOR_H

#include <random>
#include <unordered_set>
#include <queue>
#include <stdint.h>
#include "Generation/Point.h"
#include "Generation/IGenerator.h"
#include "Generation/Field.h"
#include "Generation/ITopology.h"

class PopWithChancePoolGenerator : public IGenerator
{
public:
	PopWithChancePoolGenerator(const ITopology* topology, float chanceToUsePoppedItem, unsigned int dotsPerStep);
	virtual ~PopWithChancePoolGenerator();

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
