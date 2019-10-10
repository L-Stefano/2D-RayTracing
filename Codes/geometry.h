#pragma once
#include"header.h"
#include"utilities.h"

//Vector Declarations
template <typename T>
class Vector2
{
public:
	//Public Data
	T x, y;

	//Constructors
	Vector2() :x(0), y(0) {}
	Vector2(T _x, T _y) :x(_x), y(_y) {}

	//HasNaNs
	inline bool HasNaNs() const { return isNaN(x) || isNaN(y); }

	//Operations
	Vector2<T> operator+(const Vector2<T>& v) const
	{
		assert(!v.HasNaNs());
		return Vector2(x + v.x, y + v.y);
	}
	Vector2<T>& operator+=(const Vector2<T> & v)
	{
		assert(!v.HasNaNs());
		x += v.x;
		y += v.y;
		return *this;
	}
	Vector2<T> operator-(const Vector2<T> & v) const
	{
		assert(!v.HasNaNs());
		return Vector2(x - v.x, y - v.y);
	}
	Vector2<T>& operator-=(const Vector2<T> & v)
	{
		assert(!v.HasNaNs());
		x -= v.x;
		y -= v.y;
		return *this;
	}
	template<typename U>
	Vector2<T> operator*(U scalar) const
	{
		return Vector2<T>(x * scalar, y * scalar);
	}
	template<typename U>
	Vector2<T> operator*=(U scalar)
	{
		assert(!isNaN(scalar));
		x *= scalar;
		y *= scalar;
		return *this;
	}
	template<typename U>
	Vector2<T> operator/(U scalar) const
	{
		assert(scalar);
		double inv = (double)1 / scalar;
		return Vector2<T>(x * inv, y * inv);
	}
	template<typename U>
	Vector2<T> operator/=(U scalar)
	{
		assert(scalar);
		double inv = (double)1 / scalar;
		x *= inv;
		y *= inv;
		return *this;
	}
	bool operator==(const Vector2<T> & v) { return x == v.x && y == v.y; }
	bool operator!=(const Vector2<T> & v) const { return x != v.x || y != v.y; }
	Vector2<T> operator-() const { return Vector2<T>(-x, -y); }

	T operator[](int i) const {
		assert(i >= 0 && i <= 1);
		if (i == 0) return x;
		return y;
	}

	T & operator[](int i) {
		assert(i >= 0 && i <= 1);
		if (i == 0) return x;
		return y;
	}

	double LengthSquared() const { return x * x + y * y; }
	double Length() const { return sqrt(this->LengthSquared()); }
};
template <typename T>
inline std::ostream& operator<<(std::ostream & os, const Vector2<T> & v) {
	os << "[ " << v.x << ", " << v.y << " ]";
	return os;
}
template <typename T, typename U>
inline Vector2<T> operator*(U scalar, const Vector2<T> & v) {
	return v * scalar;
}
//Absolute Value
template <typename T>
inline Vector2<T> abs(const Vector2<T> & v) { return Vector2<T>(std::abs(v.x), std::abs(v.y)); }
//Dot Product
template <typename T>
inline double Dot(const Vector2<T> & v1, const Vector2<T> & v2) {
	assert(!v1.HasNaNs() && !v2.HasNaNs());
	return v1.x* v2.x + v1.y * v2.y;
}
template <typename T>
inline double AbsDot(const Vector2<T> & v1, const Vector2<T> & v2) {
	assert(!v1.HasNaNs() && !v2.HasNaNs());
	return std::abs(Dot(v1, v2));
}
template <typename T>
inline Vector2<T> Normalize(const Vector2<T> & v)
{
	return v / v.Length();
}

template <typename T>
class Vector3
{
public:
	//Public Data
	T x, y, z;

	//Constructors
	Vector3() :x(0), y(0), z(0) {}
	Vector3(T _x, T _y, T _z) :x(_x), y(_y), z(_z) {}
	explicit Vector3<T>(const Normal3<T>& n) : x(n.x), y(n.y), z(n.z) {}

	//HasNaNs
	inline bool HasNaNs() const { return isNaN(x) || isNaN(y) || isNaN(z); }

	//Operations
	Vector3<T> operator+(const Vector3<T>& v) const
	{
		assert(!v.HasNaNs());
		return Vector3(x + v.x, y + v.y, z + v.z);
	}
	Vector3<T>& operator+=(const Vector3<T> & v)
	{
		assert(!v.HasNaNs());
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	Vector3<T> operator-(const Vector3<T> & v) const
	{
		assert(!v.HasNaNs());
		return Vector3(x - v.x, y - v.y, z - v.z);
	}
	Vector3<T>& operator-=(const Vector3<T> & v)
	{
		assert(!v.HasNaNs());
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
	template<typename U>
	Vector3<T> operator*(U scalar) const
	{
		return Vector3<T>(x * scalar, y * scalar, z * scalar);
	}
	template<typename U>
	Vector3<T> operator*=(U scalar)
	{
		assert(!isNaN(scalar));
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}
	template<typename U>
	Vector3<T> operator/(U scalar) const
	{
		assert(scalar);
		double inv = (double)1 / scalar;
		return Vector3<T>(x * inv, y * inv, z * inv);
	}
	template<typename U>
	Vector3<T> operator/=(U scalar)
	{
		assert(scalar);
		double inv = (double)1 / scalar;
		x *= inv;
		y *= inv;
		z *= inv;
		return *this;
	}
	bool operator==(const Vector3<T> & v) { return x == v.x && y == v.y && z == v.z; }
	bool operator!=(const Vector3<T> & v) const { return x != v.x || y != v.y || z != v.z; }
	Vector3<T> operator-()const { return Vector3<T>(-x, -y, -z); }

	T operator[](int i) const {
		assert(i >= 0 && i <= 1);
		if (i == 0) return x;
		else if (i == 1) return y;
		else return z;
	}

	T & operator[](int i) {
		assert(i >= 0 && i <= 1);
		if (i == 0) return x;
		else if (i == 1) return y;
		else return z;
	}

	double LengthSquared() const { return x * x + y * y + z * z; }
	double Length() const { return sqrt(this->LengthSquared()); }
};
template <typename T>
inline std::ostream& operator<<(std::ostream & os, const Vector3<T> & v)
{
	os << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
	return os;
}
template <typename T, typename U>
inline Vector3<T> operator*(U scalar, const Vector3<T> & v)
{
	return v * scalar;
}
//Absolute Value
template <typename T>
inline Vector3<T> abs(const Vector3<T> & v) { return Vector3<T>(std::abs(v.x), std::abs(v.y), std::abs(v.z)); }
//Dot Product
template <typename T>
inline double Dot(const Vector3<T> & v1, const Vector3<T> & v2)
{
	assert(!v1.HasNaNs() && !v2.HasNaNs());
	return v1.x* v2.x + v1.y * v2.y + v1.z * v2.z;
}
template <typename T>
inline double AbsDot(const Vector3<T> & v1, const Vector3<T> & v2)
{
	assert(!v1.HasNaNs() && !v2.HasNaNs());
	return std::abs(Dot(v1, v2));
}
template <typename T>
inline Vector3<T> Normalize(const Vector3<T> & v)
{
	return v / v.Length();
}
//In this routine, cross product is left handeness
template <typename T>
inline Vector3<T> Cross(const Vector3<T> & v1, const Vector3<T> & v2) {
	assert(!v1.HasNaNs() && !v2.HasNaNs());
	double v1x = v1.x, v1y = v1.y, v1z = v1.z;
	double v2x = v2.x, v2y = v2.y, v2z = v2.z;
	return Vector3<T>((v1y * v2z) - (v1z * v2y), (v1z * v2x) - (v1x * v2z),
		(v1x * v2y) - (v1y * v2x));
}

typedef Vector2<int> Vector2i;
typedef Vector2<double> Vector2d;
typedef Vector3<int> Vector3i;
typedef Vector3<double> Vector3d;


//Point Declarations
template <typename T>
class Point2 {
public:
	// Point2 Public Methods
	explicit Point2(const Point3<T>& p) : x(p.x), y(p.y) { assert(!HasNaNs()); }
	Point2() { x = y = 0; }
	Point2(T xx, T yy) : x(xx), y(yy) { assert(!HasNaNs()); }

	template <typename U>
	explicit Point2(const Point2<U>& p) {
		x = (T)p.x;
		y = (T)p.y;
		assert(!HasNaNs());
	}

	template <typename U>
	explicit Point2(const Vector2<U>& p) {
		x = (T)p.x;
		y = (T)p.y;
		assert(!HasNaNs());
	}

	template <typename U>
	explicit operator Vector2<U>() const {
		return Vector2<U>(x, y);
	}

	Point2<T> operator+(const Vector2<T>& v) const {
		assert(!v.HasNaNs());
		return Point2<T>(x + v.x, y + v.y);
	}

	Point2<T>& operator+=(const Vector2<T> & v) {
		assert(!v.HasNaNs());
		x += v.x;
		y += v.y;
		return *this;
	}
	Vector2<T> operator-(const Point2<T> & p) const {
		assert(!p.HasNaNs());
		return Vector2<T>(x - p.x, y - p.y);
	}

	Point2<T> operator-(const Vector2<T> & v) const {
		assert(!v.HasNaNs());
		return Point2<T>(x - v.x, y - v.y);
	}
	Point2<T> operator-() const { return Point2<T>(-x, -y); }
	Point2<T>& operator-=(const Vector2<T> & v) {
		assert(!v.HasNaNs());
		x -= v.x;
		y -= v.y;
		return *this;
	}
	Point2<T>& operator+=(const Point2<T> & p) {
		assert(!p.HasNaNs());
		x += p.x;
		y += p.y;
		return *this;
	}
	Point2<T> operator+(const Point2<T> & p) const {
		assert(!p.HasNaNs());
		return Point2<T>(x + p.x, y + p.y);
	}
	template <typename U>
	Point2<T> operator*(U f) const {
		return Point2<T>(f * x, f * y);
	}
	template <typename U>
	Point2<T>& operator*=(U f) {
		x *= f;
		y *= f;
		return *this;
	}
	template <typename U>
	Point2<T> operator/(U f) const {
		assert(f);
		double inv = (double)1 / f;
		return Point2<T>(inv * x, inv * y);
	}
	template <typename U>
	Point2<T>& operator/=(U f) {
		assert(f);
		double inv = (double)1 / f;
		x *= inv;
		y *= inv;
		return *this;
	}
	T operator[](int i) const {
		assert(i >= 0 && i <= 1);
		if (i == 0) return x;
		return y;
	}

	T & operator[](int i) {
		assert(i >= 0 && i <= 1);
		if (i == 0) return x;
		return y;
	}
	bool operator==(const Point2<T> & p) const { return x == p.x && y == p.y; }
	bool operator!=(const Point2<T> & p) const { return x != p.x || y != p.y; }
	bool HasNaNs() const { return isNaN(x) || isNaN(y); }

	// Point2 Public Data
	T x, y;
};

template <typename T>
inline std::ostream& operator<<(std::ostream & os, const Point2<T> & v) {
	os << "[ " << v.x << ", " << v.y << " ]";
	return os;
}
template <typename T, typename U>
inline Point2<T> operator*(U f, const Point2<T> & p) {
	assert(!p.HasNaNs());
	return p * f;
}
template <typename T>
inline double Distance(const Point2<T> & p1, const Point2<T> & p2) {
	return (p1 - p2).Length();
}
template <typename T>
inline double DistanceSquared(const Point2<T> & p1, const Point2<T> & p2) {
	return (p1 - p2).LengthSquared();
}


template <typename T>
class Point3 {
public:
	// Point3 Public Methods
	Point3() { x = y = z = 0; }
	Point3(T x, T y, T z) : x(x), y(y), z(z) { assert(!HasNaNs()); }
	template <typename U>
	explicit Point3(const Point3<U>& p)
		: x((T)p.x), y((T)p.y), z((T)p.z) {
		assert(!HasNaNs());
	}
	template <typename U>
	explicit operator Vector3<U>() const {
		return Vector3<U>(x, y, z);
	}
	Point3<T> operator+(const Vector3<T>& v) const {
		assert(!v.HasNaNs());
		return Point3<T>(x + v.x, y + v.y, z + v.z);
	}
	Point3<T>& operator+=(const Vector3<T> & v) {
		assert(!v.HasNaNs());
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	Vector3<T> operator-(const Point3<T> & p) const {
		assert(!p.HasNaNs());
		return Vector3<T>(x - p.x, y - p.y, z - p.z);
	}
	Point3<T> operator-(const Vector3<T> & v) const {
		assert(!v.HasNaNs());
		return Point3<T>(x - v.x, y - v.y, z - v.z);
	}
	Point3<T>& operator-=(const Vector3<T> & v) {
		assert(!v.HasNaNs());
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
	Point3<T>& operator+=(const Point3<T> & p) {
		assert(!p.HasNaNs());
		x += p.x;
		y += p.y;
		z += p.z;
		return *this;
	}
	Point3<T> operator+(const Point3<T> & p) const {
		assert(!p.HasNaNs());
		return Point3<T>(x + p.x, y + p.y, z + p.z);
	}
	template <typename U>
	Point3<T> operator*(U f) const {
		return Point3<T>(f * x, f * y, f * z);
	}
	template <typename U>
	Point3<T>& operator*=(U f) {
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}
	template <typename U>
	Point3<T> operator/(U f) const {
		assert(f);
		double inv = (double)1 / f;
		return Point3<T>(inv * x, inv * y, inv * z);
	}
	template <typename U>
	Point3<T>& operator/=(U f) {
		assert(f);
		double inv = (double)1 / f;
		x *= inv;
		y *= inv;
		z *= inv;
		return *this;
	}
	T operator[](int i) const {
		assert(i >= 0 && i <= 2);
		if (i == 0) return x;
		if (i == 1) return y;
		return z;
	}

	T & operator[](int i) {
		assert(i >= 0 && i <= 2);
		if (i == 0) return x;
		if (i == 1) return y;
		return z;
	}
	bool operator==(const Point3<T> & p) const {
		return x == p.x && y == p.y && z == p.z;
	}
	bool operator!=(const Point3<T> & p) const {
		return x != p.x || y != p.y || z != p.z;
	}
	bool HasNaNs() const { return isNaN(x) || isNaN(y) || isNaN(z); }
	Point3<T> operator-() const { return Point3<T>(-x, -y, -z); }

	// Point3 Public Data
	T x, y, z;
};

template <typename T>
inline std::ostream& operator<<(std::ostream & os, const Point3<T> & v)
{
	os << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
	return os;
}
template <typename T, typename U>
inline Point3<T> operator*(U f, const Point3<T> & p)
{
	assert(!p.HasNaNs());
	return p * f;
}
template <typename T>
inline double Distance(const Point3<T> & p1, const Point3<T> & p2)
{
	return (p1 - p2).Length();
}

template <typename T>
inline double DistanceSquared(const Point3<T> & p1, const Point3<T> & p2)
{
	return (p1 - p2).LengthSquared();
}

typedef Point2<int> Point2i;
typedef Point2<double> Point2d;
typedef Point3<int> Point3i;
typedef Point3<double> Point3d;

template <typename T>
Point3<T> Lerp(double t, const Point3<T> & p0, const Point3<T> & p1)
{
	return p0 * (1 - t) + p1 * t;
}

template <typename T>
Point2<T> Floor(const Point2<T> & p) {
	return Point2<T>(std::floor(p.x), std::floor(p.y));
}

template <typename T>
Point2<T> Ceil(const Point2<T> & p) {
	return Point2<T>(std::ceil(p.x), std::ceil(p.y));
}

template <typename T>
Point2<T> Lerp(double t, const Point2<T> & v0, const Point2<T> & v1) {
	return (1 - t) * v0 + t * v1;
}

template <typename T>
Point2<T> Min(const Point2<T> & pa, const Point2<T> & pb) {
	return Point2<T>(std::min(pa.x, pb.x), std::min(pa.y, pb.y));
}

template <typename T>
Point2<T> Max(const Point2<T> & pa, const Point2<T> & pb) {
	return Point2<T>(std::max(pa.x, pb.x), std::max(pa.y, pb.y));
}

template <typename T>
Point3<T> Permute(const Point3<T> & p, int x, int y, int z) {
	return Point3<T>(p[x], p[y], p[z]);
}

template <typename T>
Point2<T> Abs(const Point2<T> & p) {
	return Point2<T>(std::abs(p.x), std::abs(p.y));
}


template <typename T>
Point3<T> Min(const Point3<T> & p1, const Point3<T> & p2) {
	return Point3<T>(std::min(p1.x, p2.x), std::min(p1.y, p2.y),
		std::min(p1.z, p2.z));
}

template <typename T>
Point3<T> Max(const Point3<T> & p1, const Point3<T> & p2) {
	return Point3<T>(std::max(p1.x, p2.x), std::max(p1.y, p2.y),
		std::max(p1.z, p2.z));
}

template <typename T>
Point3<T> Floor(const Point3<T> & p) {
	return Point3<T>(std::floor(p.x), std::floor(p.y), std::floor(p.z));
}

template <typename T>
Point3<T> Ceil(const Point3<T> & p) {
	return Point3<T>(std::ceil(p.x), std::ceil(p.y), std::ceil(p.z));
}

template <typename T>
Point3<T> Abs(const Point3<T> & p) {
	return Point3<T>(std::abs(p.x), std::abs(p.y), std::abs(p.z));
}

//Normal Declaration
template <typename T>
class Normal3
{
public:
	T x, y, z;

	//Constructs
	Normal3() :x(0), y(0), z(0) {}
	Normal3(T _x, T _y, T _z) :x(_x), y(_y), z(_z) {}
	explicit Normal3<T>(const Vector3<T>& v) : x(v.x), y(v.y), z(v.z) { assert(!v.HasNaNs()); }

	bool HasNaNs() const { return isNaN(x) || isNaN(y) || isNaN(z); }

	Normal3<T> operator-() const { return Normal3<T>(-x, -y, -z); }
	Normal3<T> operator+(const Normal3<T> & n) const
	{
		assert(!HasNaNs());
		return Normal3<T>(x + n.x, y + n.y, z + n.z);
	}
	Normal3<T>& operator+=(const Normal3<T> & n)
	{
		assert(!HasNaNs());
		x += n.x;
		y += n.y;
		z += n.z;
		return *this;
	}
	Normal3<T> operator-(const Normal3<T> & n) const
	{
		assert(!HasNaNs());
		return Normal3<T>(x - n.x, y - n.y, z - n.z);
	}
	Normal3<T>& operator-=(const Normal3<T> & n)
	{
		assert(!HasNaNs());
		x -= n.x;
		y -= n.y;
		z -= n.z;
		return *this;
	}
	template <typename U>
	Normal3<T> operator*(U scalar) const
	{
		return Normal3<T>(scalar * x, scalar * y, scalar * z);
	}
	template <typename U>
	Normal3<T>& operator*=(U scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}
	template <typename U>
	Normal3<T> operator/(U scalar) const
	{
		assert(scalar);
		double inv = (double)1 / scalar;
		return Normal3<T>(x * inv, y * inv, z * inv);
	}

	template <typename U>
	Normal3<T>& operator/=(U scalar)
	{
		assert(scalar);
		double inv = (double)1 / scalar;
		x *= inv;
		y *= inv;
		z *= inv;
		return *this;
	}

	bool operator==(const Normal3<T> & n)const { return x == n.x && y == n.y && z == n.z; }
	bool operator!=(const Normal3<T> & n) const { return x != n.x || y != n.y || z != n.z; }

	T operator[](int i) const {
		assert(i >= 0 && i <= 2);
		if (i == 0) return x;
		if (i == 1) return y;
		return z;
	}

	T & operator[](int i) {
		assert(i >= 0 && i <= 2);
		if (i == 0) return x;
		if (i == 1) return y;
		return z;
	}

	double LengthSquared() const { return x * x + y * y + z * z; }
	double Length() const { return std::sqrt(LengthSquared()); }
};

template <typename T>
inline std::ostream& operator<<(std::ostream & os, const Normal3<T> & n)
{
	os << "[ " << n.x << ", " << n.y << ", " << n.z << " ]";
	return os;
}

typedef Normal3<double> Normal3d;

template <typename T>
inline Normal3<T> Normalize(const Normal3<T> & n)
{
	return n / n.Length();
}
template <typename T, typename U>

Normal3<T> operator*(U scalar, const Normal3<T> & n)
{
	return Normal3<T>(scalar * n.x, scalar * n.y, scalar * n.z);
}

template <typename T>
inline T Dot(const Normal3<T> & n1, const Vector3<T> & v2) {
	assert(!n1.HasNaNs() && !v2.HasNaNs());
	return n1.x* v2.x + n1.y * v2.y + n1.z * v2.z;
}

template <typename T>
inline T Dot(const Vector3<T> & v1, const Normal3<T> & n2) {
	assert(!v1.HasNaNs() && !n2.HasNaNs());
	return v1.x* n2.x + v1.y * n2.y + v1.z * n2.z;
}

template <typename T>
inline T Dot(const Normal3<T> & n1, const Normal3<T> & n2) {
	assert(!n1.HasNaNs() && !n2.HasNaNs());
	return n1.x* n2.x + n1.y * n2.y + n1.z * n2.z;
}

template <typename T>
inline T AbsDot(const Normal3<T> & n1, const Vector3<T> & v2) {
	assert(!n1.HasNaNs() && !v2.HasNaNs());
	return std::abs(n1.x * v2.x + n1.y * v2.y + n1.z * v2.z);
}

template <typename T>
inline T AbsDot(const Vector3<T> & v1, const Normal3<T> & n2) {
	assert(!v1.HasNaNs() && !n2.HasNaNs());
	return std::abs(v1.x * n2.x + v1.y * n2.y + v1.z * n2.z);
}

template <typename T>
inline T AbsDot(const Normal3<T> & n1, const Normal3<T> & n2) {
	assert(!n1.HasNaNs() && !n2.HasNaNs());
	return std::abs(n1.x * n2.x + n1.y * n2.y + n1.z * n2.z);
}

//Faceforword: the first parameter is one might be flipped;
//the sec para is the reference
template <typename T>
inline Normal3<T> Faceforword(const Normal3<T> & n, const Normal3<T> & r)
{
	return (Dot(n, r) > 0.f) ? n : -n;
}
template <typename T>
inline Normal3<T> Faceforword(const Normal3<T> & n, const Vector3<T> & r)
{
	return (Dot(n, r) > 0.f) ? n : -n;
}
template <typename T>
inline Vector3<T> Faceforword(const Vector3<T> & v, const Normal3<T> & r)
{
	return (Dot(v, r) > 0.f) ? v : -v;
}
template <typename T>
inline Vector3<T> Faceforword(const Vector3<T> & v, const Vector3<T> & r)
{
	return (Dot(v, r) > 0.f) ? v : -v;
}

template <typename T>
Normal3<T> Abs(const Normal3<T> & v)
{
	return Normal3<T>(std::abs(v.x), std::abs(v.y), std::abs(v.z));
}

//Ray Declarations
class Ray
{
public:
	Point2d o;
	Vector2d d;
	mutable double tMax;

	//Constructors
	Ray() :tMax(InfinityDouble) {}
	Ray(const Point2d& _o, const Vector2d& _d,
		double _tMax = InfinityDouble)
		:o(_o), d(_d), tMax(_tMax) {}

	Ray(const Point2d& _o, double dx,double dy,
		double _tMax = InfinityDouble)
		:o(_o), tMax(_tMax) 
	{
		d = Vector2d(dx, dy);
	}

	bool HasNaNs() { return (o.HasNaNs() || d.HasNaNs() || isNaN(tMax)); }
	//o + d * t
	Point2d operator()(double t) const { return o + d * t; }
	bool operator ==(const Ray& r)
	{
		if (o == r.o && d == r.d)
			return true;
		else
			return false;
	}
};


inline double Distance(const Point2d& p, const Ray& r)
{
	double proj = Dot(p-r.o, r.d) / r.d.Length();

	return sqrt((p - r.o).Length() * (p - r.o).Length() - proj * proj);
}

inline std::ostream & operator<<(std::ostream & os, const Ray & r)
{
	os << "[o=" << r.o << ", d=" << r.d << ", tMax=" << r.tMax << "]";
	return os;
}
