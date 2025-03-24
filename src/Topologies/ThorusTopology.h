#pragma once

#include "../Point.h"
#include "../ITopology.h"

class ThorusTopology : public ITopology
{
public:
	ThorusTopology(unsigned int width, unsigned int height);
	virtual ~ThorusTopology();

	virtual bool TryAdd(const Point& a, const Point& b, Point& result) const override;

private:
	int m_width;
	int m_height;
};
