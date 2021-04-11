#pragma once

#include "Drawing/Point.h"
#include "Drawing/Topologies/ITopology.h"

class ThorusTopology : public ITopology
{
public:
	ThorusTopology(unsigned int width, unsigned int height);
	virtual ~ThorusTopology();

	virtual bool TryAdd(const Point& a, const Point& b, Point& result) const override;

private:
	unsigned int m_width;
	unsigned int m_height;
};
