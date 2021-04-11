#include "ColorUtil.h"

uint32_t ColorSum(uint32_t colorA, uint32_t colorB)
{
	unsigned char rA, rB;
	unsigned char gA, gB;
	unsigned char bA, bB;
	unsigned char aA, aB;

	ColorDecode(colorA, rA, gA, bA, aA);
	ColorDecode(colorB, rB, gB, bB, aB);

	return ColorEncode(
			   (unsigned char)(rA + rB),
			   (unsigned char)(gA + gB),
			   (unsigned char)(bA + bB),
			   (unsigned char)(aA + aB));
}

uint32_t ColorEncode(float r, float g, float b, float a)
{
	return ColorEncode(
			   (unsigned char)(r * 255.0f),
			   (unsigned char)(g * 255.0f),
			   (unsigned char)(b * 255.0f),
			   (unsigned char)(a * 255.0f));
}

uint32_t ColorEncode(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	return r << 24 | g << 16 | b << 8 | a;
}

void ColorDecode(uint32_t intData, float& r, float& g, float& b, float& a)
{
	unsigned char r_;
	unsigned char g_;
	unsigned char b_;
	unsigned char a_;

	ColorDecode(intData, r_, g_, b_, a_);

	r = (float)r_ / 255.0f;
	g = (float)g_ / 255.0f;
	b = (float)b_ / 255.0f;
	a = (float)a_ / 255.0f;
}

void ColorDecode(uint32_t intData, unsigned char& r, unsigned char& g, unsigned char& b, unsigned char& a)
{
	a =  intData & 0x000000ff;
	b = (intData & 0x0000ff00) >> 8;
	g = (intData & 0x00ff0000) >> 16;
	r = (intData & 0xff000000) >> 24;
}

float Bounce01(float value)
{
	bool lessThan0 = value < 0.0f;
	bool greaterThan1 = value > 1.0f;
	while(lessThan0 || greaterThan1)
	{
		if(lessThan0)
			value -= value;

		// make the value "bounce" from 1.0 value
		if(greaterThan1)
			value = 2.0f - value;

		lessThan0 = value < 0.0f;
		greaterThan1 = value > 1.0f;
	}
	return value;
}
