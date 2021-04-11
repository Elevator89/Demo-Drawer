#include "Drawing/Colors/ColorUtil.h"
#include "Drawing/Drawers/PopWithChanceDrawer.h"

PopWithChanceDrawer::PopWithChanceDrawer(const ITopology* topology, IColorGenerator* colorGenerator, float chanceToUsePoppedItem, float fieldFillBeforeFlush) :
	m_topology(topology),
	m_colorGenerator(colorGenerator),
	m_chanceToUsePoppedItem(chanceToUsePoppedItem),
	m_fieldFillBeforeFlush(fieldFillBeforeFlush),
	m_chanceDistribution(0, 1.0f)
{}

PopWithChanceDrawer::~PopWithChanceDrawer() {}

void PopWithChanceDrawer::Draw(Field<uint32_t>& field)
{
	if(m_visitedPoints.size() > (size_t)(m_fieldFillBeforeFlush * field.GetWidth() * field.GetHeight()))
	{
		m_visitedPoints.clear();
	}

	uint32_t color = m_colorGenerator->GenerateColor();

	if(m_queue.empty())
	{
		std::uniform_int_distribution<unsigned int> widthDistribution(0, field.GetWidth()-1);
		std::uniform_int_distribution<unsigned int> heightDistribution(0, field.GetHeight()-1);

		m_visitedPoints.clear();
		Point newPoint(widthDistribution(m_generator), heightDistribution(m_generator));
		if(TryPushPoint(newPoint))
			field.SetCell(newPoint, color);
	}

	Point point = m_queue.front();
	m_queue.pop();

	if(m_chanceDistribution(m_generator) > m_chanceToUsePoppedItem)
		return;

	Point pointToUp;
	if(m_topology->TryAdd(point, Point::Up(), pointToUp) && TryPushPoint(pointToUp))
		field.SetCell(pointToUp, color);

	Point pointToDown;
	if(m_topology->TryAdd(point, Point::Down(), pointToDown) && TryPushPoint(pointToDown))
		field.SetCell(pointToDown, color);

	Point pointToLeft;
	if(m_topology->TryAdd(point, Point::Left(), pointToLeft) && TryPushPoint(pointToLeft))
		field.SetCell(pointToLeft, color);

	Point pointToRight;
	if(m_topology->TryAdd(point, Point::Right(), pointToRight) && TryPushPoint(pointToRight))
		field.SetCell(pointToRight, color);
}

bool PopWithChanceDrawer::TryPushPoint(const Point& point)
{
	if(m_visitedPoints.find(point) != m_visitedPoints.end())
		return false;

	m_visitedPoints.insert(point);
	m_queue.push(point);

	return true;
}


