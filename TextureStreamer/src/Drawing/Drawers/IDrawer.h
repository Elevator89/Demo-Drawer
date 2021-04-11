#pragma once

#include <stdint.h>
#include "Drawing/Field.h"

class IDrawer
{
public:
	virtual ~IDrawer() {}

	virtual void Draw(Field<uint32_t>& field, unsigned int dotCount) = 0;
};
