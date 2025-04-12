#pragma once

#include "../IColorFilter.h"
#include "../Color4b.h"

class BouncingColor4bFilter : public IColorFilter<Color4b>
{
public:
	BouncingColor4bFilter(unsigned int bouncePeriodR, unsigned int bouncePeriodG, unsigned int bouncePeriodB, unsigned int bouncePeriodA);
	virtual ~BouncingColor4bFilter();

	Color4b Filter(const Color4b& value) override;

private:
	unsigned int m_bouncePeriodR;
	unsigned int m_bouncePeriodG;
	unsigned int m_bouncePeriodB;
	unsigned int m_bouncePeriodA;

	unsigned int m_bounceCounterR;
	unsigned int m_bounceCounterG;
	unsigned int m_bounceCounterB;
	unsigned int m_bounceCounterA;

	short m_deltaR;
	short m_deltaG;
	short m_deltaB;
	short m_deltaA;
};
