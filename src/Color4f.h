#pragma once

struct Color4f
{
	float R, G, B, A;

	Color4f() :
		R(0.0f),
		G(0.0f),
		B(0.0f),
		A(1.0f)
	{
	}

	Color4f(float r, float g, float b) :
		R(r),
		G(g),
		B(b),
		A(1.0f)
	{
	}

	Color4f(float r, float g, float b, float a) :
		R(r),
		G(g),
		B(b),
		A(a)
	{
	}

	Color4f(const Color4f& color) :
		R(color.R),
		G(color.G),
		B(color.B),
		A(color.A)
	{
	}

	~Color4f() {}

	Color4f& operator = (const Color4f& other);
	Color4f& operator += (const Color4f& rhs);
	Color4f& operator -= (const Color4f& rhs);
	Color4f& operator *= (float rhs);
	Color4f& operator /= (float rhs);

	static Color4f Black() { return Color4f(0.0f, 0.0f, 0.0f); }
	static Color4f Grey() { return Color4f(0.5f, 0.5f, 0.5f); }
	static Color4f White() { return Color4f(1.0f, 1.0f, 1.0f); }
	static Color4f Red() { return Color4f(1.0f, 0.0f, 0.0f); }
	static Color4f Green() { return Color4f(0.0f, 1.0f, 0.0f); }
	static Color4f Blue() { return Color4f(0.0f, 0.0f, 1.0f); }
};

inline Color4f operator- (const Color4f& rhs)
{
	return Color4f(-rhs.R, -rhs.G, -rhs.B, -rhs.A);
}

inline Color4f operator+ (const Color4f& lhs, const Color4f& rhs)
{
	return Color4f(lhs.R + rhs.R, lhs.G + rhs.G, lhs.B + rhs.B, lhs.A + rhs.A);
}

inline Color4f operator- (const Color4f& lhs, const Color4f& rhs)
{
	return Color4f(lhs.R - rhs.R, lhs.G - rhs.G, lhs.B - rhs.B, lhs.A - rhs.A);
}

inline Color4f operator* (const Color4f& lhs, float rhs)
{
	return Color4f(lhs.R * rhs, lhs.G * rhs, lhs.B * rhs, lhs.A * rhs);
}

inline Color4f operator* (float lhs, const Color4f& rhs)
{
	return Color4f(rhs.R * lhs, rhs.G * lhs, rhs.B * lhs, rhs.A * lhs);
}

inline Color4f operator/ (const Color4f& lhs, float rhs)
{
	return Color4f(lhs.R / rhs, lhs.G / rhs, lhs.B / rhs, lhs.A / rhs);
}

inline bool operator== (const Color4f& lhs, const Color4f& rhs)
{
	return lhs.R == rhs.R && lhs.G == rhs.G && lhs.B == rhs.B && lhs.A == rhs.A;
}

inline bool operator!= (const Color4f& lhs, const Color4f& rhs)
{
	return lhs.R != rhs.R || lhs.G != rhs.G || lhs.B != rhs.B || lhs.A != rhs.A;
}
