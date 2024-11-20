#pragma once

#include <unordered_set>
#include <vector>
#include "Drawing/Point.h"
#include "Drawing/Topologies/ITopology.h"
#include "Drawing/Colors/IColorGenerator.h"
#include "Drawing/Drawers/IPointsTraverser.h"
#include "Drawing/Drawers/IPointPicker.h"
#include "Drawing/Drawers/IDrawer.h"

class PointsTraverserDrawer : public IDrawer
{
public:
	PointsTraverserDrawer(const ITopology* topology, const IPointPicker* pointPicker, const IPointsTraverser* pointsTraverser, IColorGenerator* colorGenerator, float fieldFillBeforeFlush, std::default_random_engine* randomGenerator);
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
	const IPointsTraverser* m_pointsTraverser;
	IColorGenerator* m_colorGenerator;
	float m_fieldFillBeforeFlush;

	std::default_random_engine* m_randomGenerator;
	std::vector<Point> m_pointsToVisit;
	std::unordered_set<Point> m_visitedPoints;
};
