#include "Drawing/Colors/Color.h"
#include "Drawing/Colors/ColorUtil.h"
#include "Drawing/Drawers/StackPopWithChanceDrawer.h"

StackPopWithChanceDrawer::StackPopWithChanceDrawer(const ITopology* topology, IColorGenerator* colorGenerator, float chanceToUsePoppedItem, float fieldFillBeforeFlush) :
	m_topology(topology),
	m_colorGenerator(colorGenerator),
	m_chanceToUsePoppedItem(chanceToUsePoppedItem),
	m_fieldFillBeforeFlush(fieldFillBeforeFlush),
	m_chanceDistribution(0, 1.0f)
{}

StackPopWithChanceDrawer::~StackPopWithChanceDrawer() {}

void StackPopWithChanceDrawer::Draw(Field<uint32_t>& field)
{
	if(m_visitedPoints.size() > (size_t)(m_fieldFillBeforeFlush * field.GetWidth() * field.GetHeight()))
	{
		m_visitedPoints.clear();
	}

	if(m_stack.empty())
	{
		std::uniform_int_distribution<unsigned int> widthDistribution(0, field.GetWidth()-1);
		std::uniform_int_distribution<unsigned int> heightDistribution(0, field.GetHeight()-1);

		m_visitedPoints.clear();
		Point newPoint(widthDistribution(m_generator), heightDistribution(m_generator));
		TryPushPoint(newPoint);
	}

	Point point = m_stack.top();
	m_stack.pop();

	if(m_chanceDistribution(m_generator) >= m_chanceToUsePoppedItem)
	{
		field.SetCell(point, (uint32_t)Color::Black);
		return;
	}

	field.SetCell(point, m_colorGenerator->GenerateColor());

	Point pointToUp;
	if( m_topology->TryAdd(point, Point::Up(), pointToUp) && TryPushPoint(pointToUp))
		field.SetCell(pointToUp, (uint32_t)Color::White);

	Point pointToDown;
	if(m_topology->TryAdd(point, Point::Down(), pointToDown) && TryPushPoint(pointToDown))
		field.SetCell(pointToDown, (uint32_t)Color::White);

	Point pointToLeft;
	if(m_topology->TryAdd(point, Point::Left(), pointToLeft) && TryPushPoint(pointToLeft))
		field.SetCell(pointToLeft, (uint32_t)Color::White);

	Point pointToRight;
	if(m_topology->TryAdd(point, Point::Right(), pointToRight) && TryPushPoint(pointToRight))
		field.SetCell(pointToRight, (uint32_t)Color::White);
}

bool StackPopWithChanceDrawer::TryPushPoint(const Point& point)
{
	if(m_visitedPoints.find(point) != m_visitedPoints.end())
		return false;

	m_visitedPoints.insert(point);
	m_stack.push(point);

	return true;
}
