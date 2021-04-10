#include "Generation/Point.h"

Point::Point() :
	Point(0,0)
{}

Point::Point(unsigned int x, unsigned int y) :
	X(x),
	Y(y)
{}

Point::~Point() {}
