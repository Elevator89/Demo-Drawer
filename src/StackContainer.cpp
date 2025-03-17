#include "StackContainer.h"

bool StackContainer::IsEmpty()
{
	return m_stack.empty();
}

void StackContainer::Push(Point& point)
{
	m_stack.push(point);
}

Point StackContainer::Pick()
{
	Point point = m_stack.top();
	m_stack.pop();
	return point;
}
