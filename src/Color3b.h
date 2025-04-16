#pragma once

struct Color3b
{
	unsigned char R, G, B;

	Color3b() : R(0), G(0), B(0) {}
	Color3b(unsigned char r, unsigned char g, unsigned char b) : R(r), G(g), B(b) {}
	Color3b(const Color3b& color) : R(color.R), G(color.G), B(color.B) {}

	~Color3b() {}

	Color3b& operator = (const Color3b& other);
	Color3b& operator += (const Color3b& rhs);
	Color3b& operator -= (const Color3b& rhs);
	Color3b& operator *= (float rhs);
	Color3b& operator /= (float rhs);

	static Color3b Black() { return Color3b(0, 0, 0); }
	static Color3b Grey() { return Color3b(128, 128, 128); }
	static Color3b White() { return Color3b(255, 255, 255); }
	static Color3b Red() { return Color3b(255, 0, 0); }
	static Color3b Green() { return Color3b(0, 255, 0); }
	static Color3b Blue() { return Color3b(0, 0, 255); }
};

inline Color3b operator- (const Color3b& rhs)
{
	return Color3b(-rhs.R, -rhs.G, -rhs.B);
}

inline Color3b operator+ (const Color3b& lhs, const Color3b& rhs)
{
	return Color3b(lhs.R + rhs.R, lhs.G + rhs.G, lhs.B + rhs.B);
}

inline Color3b operator- (const Color3b& lhs, const Color3b& rhs)
{
	return Color3b(lhs.R - rhs.R, lhs.G - rhs.G, lhs.B - rhs.B);
}

inline Color3b operator* (const Color3b& lhs, float rhs)
{
	return Color3b(lhs.R * rhs, lhs.G * rhs, lhs.B * rhs);
}

inline Color3b operator* (float lhs, const Color3b& rhs)
{
	return Color3b(rhs.R * lhs, rhs.G * lhs, rhs.B * lhs);
}

inline Color3b operator/ (const Color3b& lhs, float rhs)
{
	return Color3b(lhs.R / rhs, lhs.G / rhs, lhs.B / rhs);
}

inline bool operator== (const Color3b& lhs, const Color3b& rhs)
{
	return lhs.R == rhs.R && lhs.G == rhs.G && lhs.B == rhs.B;
}

inline bool operator!= (const Color3b& lhs, const Color3b& rhs)
{
	return lhs.R != rhs.R || lhs.G != rhs.G || lhs.B != rhs.B;
}
