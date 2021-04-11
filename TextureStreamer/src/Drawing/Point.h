#pragma once

#include <functional>

struct Point
{
public:
	int X;
	int Y;

	Point();
	Point(int x, int y);
	virtual ~Point();

	inline static Point Zero()
	{
		return Point(0,0);
	}

	inline static Point Up()
	{
		return Point(0,1);
	}

	inline static Point Down()
	{
		return Point(0,-1);
	}

	inline static Point Left()
	{
		return Point(-1,0);
	}

	inline static Point Right()
	{
		return Point(1,0);
	}
};

inline static bool operator==(const Point& a, const Point& b)
{
	return a.X == b.X && a.Y == b.Y;
}

inline static bool operator!=(const Point& a, const Point& b)
{
	return a.X != b.X || a.Y != b.Y;
}

namespace std
{
template<> struct hash<Point>
{
	std::size_t operator()(const Point& p) const noexcept
	{
		return p.Y * 10000 + p.X;
	}
};
}
