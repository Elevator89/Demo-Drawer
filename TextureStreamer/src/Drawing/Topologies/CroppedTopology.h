#pragma once

#include "Drawing/Point.h"
#include "Drawing/Topologies/ITopology.h"

class CroppedTopology : public ITopology
{
public:
	CroppedTopology(unsigned int width, unsigned int height);
	virtual ~CroppedTopology();

	virtual bool TryAdd(const Point& a, const Point& b, Point& result) const override;

private:
	int m_width;
	int m_height;
};
