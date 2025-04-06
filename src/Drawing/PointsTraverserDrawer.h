#pragma once

#include <unordered_set>
#include <list>
#include "../Point.h"
#include "../ITopology.h"
#include "../IColorGenerator.h"
#include "../IDrawer.h"
#include "IPointsTraverser.h"
#include "IPointPicker.h"
#include "IPointPusher.h"

class PointsTraverserDrawer : public IDrawer
{
public:
	PointsTraverserDrawer(const ITopology* topology, const IPointPicker* pointPicker, const IPointPusher* pointPusher, const IPointsTraverser* pointsTraverser, IColorGenerator* colorGenerator, float fieldFillBeforeFlush, std::default_random_engine* randomGenerator);
	virtual ~PointsTraverserDrawer();

	void Draw(Field<uint32_t>& field) override;

	inline const ITopology* GetTopology() const
	{
		return m_topology;
	}

	inline void SetTopology(const ITopology* topology)
	{
		m_topology = topology;
	}

	inline const IPointPicker* GetPointPicker() const
	{
		return m_pointPicker;
	}

	inline void SetPointPicker(const IPointPicker* pointPicker)
	{
		m_pointPicker = pointPicker;
	}

	inline void SetPointPusher(const IPointPusher* pointPusher)
	{
		m_pointPusher = pointPusher;
	}

	inline const IPointsTraverser* GetPointsTraverser() const
	{
		return m_pointsTraverser;
	}

	inline void SetPointsTraverser(const IPointsTraverser* pointsTraverser)
	{
		m_pointsTraverser = pointsTraverser;
	}

private:
	const ITopology* m_topology;
	const IPointPicker* m_pointPicker;
	const IPointPusher* m_pointPusher;
	const IPointsTraverser* m_pointsTraverser;
	IColorGenerator* m_colorGenerator;
	float m_fieldFillBeforeFlush;

	std::default_random_engine* m_randomGenerator;
	std::list<Point> m_pointsToVisit;
	std::unordered_set<Point> m_visitedPoints;
};
