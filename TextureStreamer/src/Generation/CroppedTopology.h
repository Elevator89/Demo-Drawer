#ifndef CROPPEDTOPOLOGY_H
#define CROPPEDTOPOLOGY_H

#include "Generation/Point.h"
#include "Generation/ITopology.h"

class CroppedTopology : public ITopology
{
public:
	CroppedTopology(unsigned int width, unsigned int height);
	virtual ~CroppedTopology();

	virtual bool TryAdd(const Point& a, const Point& b, Point& result) const override;

private:
	unsigned int m_width;
	unsigned int m_height;
};

#endif // CROPPEDTOPOLOGY_H
