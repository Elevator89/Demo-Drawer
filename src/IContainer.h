#pragma once

#include "Point.h"

class IContainer
{
public:
	virtual ~IContainer() {}

	virtual bool IsEmpty() = 0;

	virtual void Push(Point& point) = 0;
	virtual Point Pick() = 0;
};
