#include "BouncingColor4fFilter.h"
#include "Bouncing.h"

BouncingColor4fFilter::BouncingColor4fFilter(Color4f delta) : m_delta(delta) {}
BouncingColor4fFilter::~BouncingColor4fFilter() {}

Color4f BouncingColor4fFilter::Filter(const Color4f& value)
{
	return Color4f(
		BounceValue(value.R, m_delta.R),
		BounceValue(value.G, m_delta.G),
		BounceValue(value.B, m_delta.B),
		BounceValue(value.A, m_delta.A));
}
