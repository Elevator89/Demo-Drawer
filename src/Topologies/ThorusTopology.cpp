#include "ThorusTopology.h"

ThorusTopology::ThorusTopology(unsigned int width, unsigned int height) :
	m_width(width),
	m_height(height)
{}

ThorusTopology::~ThorusTopology() {}

bool ThorusTopology::TryAdd(const Point& a, const Point& b, Point& result) const
{
	result.X = a.X + b.X;
	result.Y = a.Y + b.Y;

	while(result.X < 0)
		result.X += m_width;

	while(result.X >= m_width)
		result.X -= m_width;

	while(result.Y < 0)
		result.Y += m_height;

	while(result.Y >= m_height)
		result.Y -= m_height;

	return true;
}
