#include "Color4b.h"

Color4b& Color4b::operator=(const Color4b& rhs)
{
	R = rhs.R;
	G = rhs.G;
	B = rhs.B;
	A = rhs.A;
	return *this;
}

Color4b& Color4b::operator += (const Color4b& rhs)
{
	R += rhs.R;
	G += rhs.G;
	B += rhs.B;
	A += rhs.A;
	return *this;
}

Color4b& Color4b::operator -= (const Color4b& rhs)
{
	R -= rhs.R;
	G -= rhs.G;
	B -= rhs.B;
	A -= rhs.A;
	return *this;
}

Color4b& Color4b::operator *= (float rhs)
{
	R *= rhs;
	G *= rhs;
	B *= rhs;
	A *= rhs;
	return *this;
}

Color4b& Color4b::operator /= (float rhs)
{
	R /= rhs;
	G /= rhs;
	B /= rhs;
	A /= rhs;
	return *this;
}
