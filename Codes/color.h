#pragma once
#include"header.h"
#include"utilities.h"

class Color
{
public:
	union
	{
		struct { double r, g, b; };
		double rgb[3];
	};

	bool hasNaNs() const {
		return false;
	}

	Color(double r, double g, double b)
	{
		rgb[0] = r;
		rgb[1] = g;
		rgb[2] = b;
		assert(!hasNaNs());
	}
	Color(const Color &c)
	{
		assert(!c.hasNaNs());
		r = c.r;
		g = c.g;
		b = c.b;
	}

	Color operator+(const Color &c) const 
	{
		Color result(r + c.r, g + c.g, b + c.b);
		assert(!(c.hasNaNs()||result.hasNaNs()));
		return result;
	}
	Color operator-() const
	{
		return Color(-r, -g, -b);
	}
	Color &operator+=(const Color &c)
	{
		r += c.r;
		g += c.g;
		b += c.b;
		return *this;
	}
	Color operator-(const Color &c) const 
	{
		Color result(r - c.r, g - c.g, b - c.b);
		assert(!(c.hasNaNs() || result.hasNaNs()));
		return result;
	}
	Color &operator-=(const Color &c)
	{
		r -= c.r;
		g -= c.g;
		b -= c.b;
		assert(!(c.hasNaNs() || this->hasNaNs()));
		return *this;
	}
	Color operator*(double scalar) const
	{
		Color result(r *scalar, g *scalar, b *scalar);
		assert(!(isNaN(scalar) || result.hasNaNs()));
		return result;
	}
	Color &operator*=(double scalar)
	{
		r *= scalar;
		g *= scalar;
		b *= scalar;
		assert(!(isNaN(scalar) || this->hasNaNs()));
		return *this;
	}
	Color operator/(double d) const
	{
		Color result(int(r /d), int(g /d), int(b /d));
		assert(!(isNaN(d) || result.hasNaNs()));
		return result;
	}
	Color &operator/=(double d)
	{
		r /= d;
		g /= d;
		b /= d;
		assert(!(isNaN(d) || this->hasNaNs()));
		return *this;
	}

	//lhs is source var;
	//rhs is target var;
	//lhs is modulated by rhs;
	Color operator*(const Color &c) const
	{
		double inv = 1.f / 255.f;
		Color result(r *(c.r*inv), g *(c.r*inv), b *(c.r*inv));
		assert(!(c.hasNaNs() || result.hasNaNs()));
		return result;
	}
};

inline Color Rounding(const Color& c)
{
	return Color(int(0.999*c.r), int(0.999 * c.g), int(0.999 * c.b));
}
inline Color sqrtColor(const Color& c)
{
	return Rounding(Color(pow(c.r/256.0f,0.9)*255, pow(c.g / 256.0f, 0.9) *255, pow(c.b / 256.0f, 0.9) *255));
}