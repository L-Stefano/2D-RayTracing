#pragma once
#include"header.h"
/*==== Defines ====*/

#define EPSILON 1e-6f
#define t_max 99999999
#define t_min 1e-5f

/*==== Constexpr ====*/

constexpr double PI = 3.14159265358979323846;
constexpr double Inv_4PI = 0.7853981634;

//Infinity of Double
static constexpr double InfinityDouble = std::numeric_limits<double>::infinity();

/*==== Inline Functions ====*/

//isNaN
template <typename T>
inline bool isNaN(T x)
{
	return std::isnan(x);
}
template <>
inline bool isNaN(const int x) {
	return false;
}

template <typename T>
inline bool isOne(T x)
{
	return (x >= .999f && x <= 1.001f);
}
template <>
inline bool isOne(const int x) {
	return (x >= .999f && x <= 1.001f);
}
//Angle to Radians
inline double toRadians(const double theta)
{
	return PI / 180.0 * theta;
}
//Radians to Angle
inline double toAngle(const double radians)
{
	return 180.0 / PI * radians;
}

