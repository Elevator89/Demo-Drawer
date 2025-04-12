#include "Bouncing.h"

float BounceValue(float valueIn, float& delta)
{
	float valueOut = valueIn;
	valueOut += delta;

	if (valueOut < 0.0f)
	{
		valueOut = -valueOut;
		delta = -delta;
	}

	if (valueOut > 1.0f)
	{
		valueOut = 2.0f - valueOut;
		delta = -delta;
	}

	return valueOut;
}

unsigned char BounceValue(unsigned char valueIn, short& delta)
{
	short valueOut = valueIn;
	valueOut += delta;

	if (valueOut < 0)
	{
		valueOut = -valueOut;
		delta = -delta;
	}

	if (valueOut > 255)
	{
		valueOut = 510 - valueOut;
		delta = -delta;
	}

	return valueOut;
}