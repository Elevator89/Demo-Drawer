#include "Color4f.h"

Color4f& Color4f::operator=(const Color4f& rhs)
{
	R = rhs.R;
	G = rhs.G;
	B = rhs.B;
	A = rhs.A;
	return *this;
}

Color4f& Color4f::operator += (const Color4f& rhs)
{
	R += rhs.R;
	G += rhs.G;
	B += rhs.B;
	A += rhs.A;
	return *this;
}

Color4f& Color4f::operator -= (const Color4f& rhs)
{
	R -= rhs.R;
	G -= rhs.G;
	B -= rhs.B;
	A -= rhs.A;
	return *this;
}

Color4f& Color4f::operator *= (float rhs)
{
	R *= rhs;
	G *= rhs;
	B *= rhs;
	A *= rhs;
	return *this;
}

Color4f& Color4f::operator /= (float rhs)
{
	R /= rhs;
	G /= rhs;
	B /= rhs;
	A /= rhs;
	return *this;
}
