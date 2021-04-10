#include "ColorUtil.h"
#include "Drawing/Drawers/PopWithChanceDrawer.h"

PopWithChanceDrawer::PopWithChanceDrawer(const ITopology* topology, float chanceToUsePoppedItem, unsigned int dotsPerStep) :
	m_topology(topology),
	m_chanceToUsePoppedItem(chanceToUsePoppedItem),
	m_dotsPerStep(dotsPerStep),
	m_chanceDistribution(0, 1.0f)
{}

PopWithChanceDrawer::~PopWithChanceDrawer() {}

void PopWithChanceDrawer::Draw(Field<uint32_t>& field)
{
	std::uniform_int_distribution<unsigned int> widthDistribution(0, field.GetWidth()-1);
	std::uniform_int_distribution<unsigned int> heightDistribution(0, field.GetHeight()-1);

	for(unsigned int i = 0; i < m_dotsPerStep; ++i)
	{
		if(m_queue.empty())
		{
			m_visitedPoints.clear();
			Point newPoint(widthDistribution(m_generator), heightDistribution(m_generator));
			if(TryPushPoint(newPoint))
				field.SetCell(newPoint, (uint32_t)Color::White);
		}

		Point point = m_queue.front();
		m_queue.pop();

		if(m_chanceDistribution(m_generator) > m_chanceToUsePoppedItem)
			continue;

		Point pointToUp;
		if(m_topology->TryAdd(point, Point::Up(), pointToUp) && TryPushPoint(pointToUp))
			field.SetCell(pointToUp, (uint32_t)Color::Yellow);

		Point pointToDown;
		if(m_topology->TryAdd(point, Point::Down(), pointToDown) && TryPushPoint(pointToDown))
			field.SetCell(pointToDown, (uint32_t)Color::Blue);

		Point pointToLeft;
		if(m_topology->TryAdd(point, Point::Left(), pointToLeft) && TryPushPoint(pointToLeft))
			field.SetCell(pointToLeft, (uint32_t)Color::Red);

		Point pointToRight;
		if(m_topology->TryAdd(point, Point::Right(), pointToRight) && TryPushPoint(pointToRight))
			field.SetCell(pointToRight, (uint32_t)Color::Green);
	}
}

bool PopWithChanceDrawer::TryPushPoint(const Point& point)
{
	if(m_visitedPoints.find(point) != m_visitedPoints.end())
		return false;

	m_visitedPoints.insert(point);
	m_queue.push(point);

	return true;
}


