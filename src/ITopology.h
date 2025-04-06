#pragma once

#include "Point.h"

class ITopology
{
public:
	virtual ~ITopology() {}

	virtual bool TryAdd(const Point& a, const Point& b, Point& result) const = 0;
};
