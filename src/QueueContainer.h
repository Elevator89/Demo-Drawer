#pragma once

#include <queue>
#include "IContainer.h"

class QueueContainer : public IContainer {

public:
	bool IsEmpty() override;

	void Push(Point& point) override;
	Point Pick() override;

private:
	std::queue<Point> m_queue;
};