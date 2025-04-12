#include "BouncingColor4bFilter.h"
#include "Bouncing.h"

BouncingColor4bFilter::BouncingColor4bFilter(unsigned int bouncePeriodR, unsigned int bouncePeriodG, unsigned int bouncePeriodB, unsigned int bouncePeriodA) :
	m_bouncePeriodR(bouncePeriodR),
	m_bouncePeriodG(bouncePeriodG),
	m_bouncePeriodB(bouncePeriodB),
	m_bouncePeriodA(bouncePeriodA),
	m_bounceCounterR(0),
	m_bounceCounterG(0),
	m_bounceCounterB(0),
	m_bounceCounterA(0),
	m_deltaR(1),
	m_deltaG(1),
	m_deltaB(1),
	m_deltaA(1)
{
}

BouncingColor4bFilter::~BouncingColor4bFilter() {}

Color4b BouncingColor4bFilter::Filter(const Color4b& value)
{
	Color4b newColor(value);

	m_bounceCounterR++;
	if (m_bounceCounterR >= m_bouncePeriodR) {
		newColor.R = BounceValue(value.R, m_deltaR);
		m_bounceCounterR = 0;
	}

	m_bounceCounterG++;
	if (m_bounceCounterG >= m_bouncePeriodG) {
		newColor.G = BounceValue(value.G, m_deltaG);
		m_bounceCounterG = 0;
	}

	m_bounceCounterB++;
	if (m_bounceCounterB >= m_bouncePeriodB) {
		newColor.B = BounceValue(value.B, m_deltaB);
		m_bounceCounterB = 0;
	}

	return newColor;
}
