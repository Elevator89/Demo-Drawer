#ifndef GENERATOR_H
#define GENERATOR_H

#include <random>
#include <stdint.h>
#include "Field.h"

class Generator
{
public:
	Generator(unsigned int width, unsigned int height);
	virtual ~Generator();

	void Generate(int steps);

	inline const uint32_t* GetImage() const
	{
		return m_field.GetData();
	}

	inline unsigned int GetWidth() const
	{
		return m_field.GetWidth();
	}

	inline unsigned int GetHeight() const
	{
		return m_field.GetHeight();
	}

private:
	std::default_random_engine m_generator;
	std::uniform_int_distribution<uint32_t> m_distribution;

	Field<uint32_t> m_field;
	int m_total;
};

#endif // GENERATOR_H
