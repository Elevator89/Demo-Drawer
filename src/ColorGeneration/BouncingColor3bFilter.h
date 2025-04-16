#pragma once

#include "../IColorFilter.h"
#include "../Color3b.h"

class BouncingColor3bFilter : public IColorFilter<Color3b>
{
public:
	BouncingColor3bFilter(unsigned int bouncePeriodR, unsigned int bouncePeriodG, unsigned int bouncePeriodB);
	virtual ~BouncingColor3bFilter();

	Color3b Filter(const Color3b& value) override;

private:
	unsigned int m_bouncePeriodR;
	unsigned int m_bouncePeriodG;
	unsigned int m_bouncePeriodB;

	unsigned int m_bounceCounterR;
	unsigned int m_bounceCounterG;
	unsigned int m_bounceCounterB;

	short m_deltaR;
	short m_deltaG;
	short m_deltaB;
};
