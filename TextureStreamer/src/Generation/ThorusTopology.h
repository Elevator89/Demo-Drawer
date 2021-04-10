#ifndef THORUSTOPOLOGY_H
#define THORUSTOPOLOGY_H

#include "Generation/Point.h"
#include "Generation/ITopology.h"

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

#endif // THORUSTOPOLOGY_H
