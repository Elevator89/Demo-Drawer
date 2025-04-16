#include "Color3b.h"

Color3b& Color3b::operator=(const Color3b& rhs)
{
	R = rhs.R;
	G = rhs.G;
	B = rhs.B;
	return *this;
}

Color3b& Color3b::operator += (const Color3b& rhs)
{
	R += rhs.R;
	G += rhs.G;
	B += rhs.B;
	return *this;
}

Color3b& Color3b::operator -= (const Color3b& rhs)
{
	R -= rhs.R;
	G -= rhs.G;
	B -= rhs.B;
	return *this;
}

Color3b& Color3b::operator *= (float rhs)
{
	R *= rhs;
	G *= rhs;
	B *= rhs;
	return *this;
}

Color3b& Color3b::operator /= (float rhs)
{
	R /= rhs;
	G /= rhs;
	B /= rhs;
	return *this;
}
