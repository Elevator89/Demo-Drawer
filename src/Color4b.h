#pragma once

struct Color4b
{
	unsigned char R, G, B, A;

	Color4b() : R(0), G(0), B(0), A(1) {}
	Color4b(unsigned char r, unsigned char g, unsigned char b) : R(r), G(g), B(b), A(255) {}
	Color4b(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : R(r), G(g), B(b), A(a) {}
	Color4b(const Color4b& color) : R(color.R), G(color.G), B(color.B), A(color.A) {}

	~Color4b() {}

	Color4b& operator = (const Color4b& other);
	Color4b& operator += (const Color4b& rhs);
	Color4b& operator -= (const Color4b& rhs);
	Color4b& operator *= (float rhs);
	Color4b& operator /= (float rhs);

	static Color4b Black() { return Color4b(0, 0, 0); }
	static Color4b Grey() { return Color4b(128, 128, 128); }
	static Color4b White() { return Color4b(255, 255, 255); }
	static Color4b Red() { return Color4b(255, 0, 0); }
	static Color4b Green() { return Color4b(0, 255, 0); }
	static Color4b Blue() { return Color4b(0, 0, 255); }
};

inline Color4b operator- (const Color4b& rhs)
{
	return Color4b(-rhs.R, -rhs.G, -rhs.B, -rhs.A);
}

inline Color4b operator+ (const Color4b& lhs, const Color4b& rhs)
{
	return Color4b(lhs.R + rhs.R, lhs.G + rhs.G, lhs.B + rhs.B, lhs.A + rhs.A);
}

inline Color4b operator- (const Color4b& lhs, const Color4b& rhs)
{
	return Color4b(lhs.R - rhs.R, lhs.G - rhs.G, lhs.B - rhs.B, lhs.A - rhs.A);
}

inline Color4b operator* (const Color4b& lhs, float rhs)
{
	return Color4b(lhs.R * rhs, lhs.G * rhs, lhs.B * rhs, lhs.A * rhs);
}

inline Color4b operator* (float lhs, const Color4b& rhs)
{
	return Color4b(rhs.R * lhs, rhs.G * lhs, rhs.B * lhs, rhs.A * lhs);
}

inline Color4b operator/ (const Color4b& lhs, float rhs)
{
	return Color4b(lhs.R / rhs, lhs.G / rhs, lhs.B / rhs, lhs.A / rhs);
}

inline bool operator== (const Color4b& lhs, const Color4b& rhs)
{
	return lhs.R == rhs.R && lhs.G == rhs.G && lhs.B == rhs.B && lhs.A == rhs.A;
}

inline bool operator!= (const Color4b& lhs, const Color4b& rhs)
{
	return lhs.R != rhs.R || lhs.G != rhs.G || lhs.B != rhs.B || lhs.A != rhs.A;
}
