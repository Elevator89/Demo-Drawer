#pragma once

#include <unordered_set>
#include <list>
#include <random>
#include "../IContainer.h"
#include "../Point.h"
#include "../ITopology.h"
#include "../IColorGenerator.h"
#include "../IDrawer.h"
#include "IPointsTraverser.h"

class ChanceBasedDrawer : public IDrawer
{
public:
	ChanceBasedDrawer(const ITopology* topology, IContainer* container, const IPointsTraverser* pointsTraverser, float chanceToPick, float chanceToPush, IColorGenerator* colorGenerator, float fieldFillBeforeFlush, std::default_random_engine* randomGenerator);
	virtual ~ChanceBasedDrawer();

	void Draw(Field<uint32_t>& colorField, Field<uint32_t>& containerField) override;

	inline const ITopology* GetTopology() const { return m_topology; }
	inline void SetTopology(const ITopology* topology) { m_topology = topology; }

	inline float GetChanceToPick() const { return m_chanceToPick; }
	inline void SetChanceToPick(float chanceToPick) { m_chanceToPick = chanceToPick; }

	inline float GetChanceToPush() const { return m_chanceToPush; }
	inline void SetChanceToPush(float chanceToPush) { m_chanceToPush = chanceToPush; }

	inline const IPointsTraverser* GetPointsTraverser() const { return m_pointsTraverser; }
	inline void SetPointsTraverser(const IPointsTraverser* pointsTraverser) { m_pointsTraverser = pointsTraverser; }

	inline IContainer* GetContainer() const { return m_container; }
	inline void SetContainer(IContainer* container) { m_container = container; }

private:
	const ITopology* m_topology;
	IContainer* m_container;
	float m_chanceToPick;
	float m_chanceToPush;
	const IPointsTraverser* m_pointsTraverser;
	IColorGenerator* m_colorGenerator;
	float m_fieldFillBeforeFlush;

	std::default_random_engine* m_randomGenerator;
	std::unordered_set<Point> m_visitedPoints;
};