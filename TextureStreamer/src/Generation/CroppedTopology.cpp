#include "CroppedTopology.h"

CroppedTopology::CroppedTopology(unsigned int width, unsigned int height) :
	m_width(width),
	m_height(height)
{}

CroppedTopology::~CroppedTopology() {}

bool CroppedTopology::TryAdd(const Point& a, const Point& b, Point& result) const
{
	result.X = a.X + b.X;
	result.Y = a.Y + b.Y;

	if(result.X < 0 || m_width <= result.X)
		return false;

	if(result.Y < 0 || m_height <= result.Y)
		return false;

	return true;
}
