#pragma once

#include <stdint.h>
#include "Field.h"

class IDrawer
{
public:
	virtual ~IDrawer() {}

	virtual void Draw(Field<uint32_t>& colorField, Field<uint32_t>& containerField) = 0;
};
