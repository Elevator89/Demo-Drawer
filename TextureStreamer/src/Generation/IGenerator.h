#ifndef IGENERATOR_H
#define IGENERATOR_H

#include <stdint.h>
#include "Field.h"

class IGenerator
{
public:
	virtual ~IGenerator() {}

	virtual void Generate(Field<uint32_t>& field) = 0;
};

#endif // IGENERATOR_H
