#pragma once

template <typename TColor>
class IColorFilter
{
public:
	virtual ~IColorFilter() {}

	virtual TColor Filter(const TColor& value) = 0;
};

