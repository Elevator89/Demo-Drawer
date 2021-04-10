#ifndef IGENERATOR_H
#define IGENERATOR_H

#include <stdint.h>
#include "Drawing/Field.h"

class IDrawer
{
public:
	virtual ~IDrawer() {}

	virtual void Generate(Field<uint32_t>& field) = 0;
};

#endif // IGENERATOR_H
