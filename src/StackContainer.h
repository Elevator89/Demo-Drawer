#pragma once

#include <stack>
#include "IContainer.h"

class StackContainer : public IContainer {

public:
	bool IsEmpty() override;

	void Push(Point& point) override;
	Point Pick() override;

private:
	std::stack<Point> m_stack;
};