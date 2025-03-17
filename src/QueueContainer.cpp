#include "QueueContainer.h"

bool QueueContainer::IsEmpty()
{
	return m_queue.empty();
}

void QueueContainer::Push(Point& point)
{
	m_queue.push(point);
}

Point QueueContainer::Pick()
{
	Point point = m_queue.front();
	m_queue.pop();
	return point;
}
