#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <random>
#include <stdint.h>
#include "IGenerator.h"
#include "Field.h"

class RandomGenerator : public IGenerator
{
public:
	RandomGenerator(unsigned int dotsPerStep);
	virtual ~RandomGenerator() override;

	void Generate(Field<uint32_t>& field) override;

private:
	std::default_random_engine m_generator;
	std::uniform_int_distribution<uint32_t> m_colorDistribution;
	unsigned int m_dotsPerStep;
};

#endif
