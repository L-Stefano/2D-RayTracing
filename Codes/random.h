#pragma once
#include<random>
#include<time.h>

std::uniform_real_distribution<double> uniform_Minus1_to_1(-1, 1);
std::uniform_real_distribution<double> uniform_0_to_1(0, 1);

std::mt19937 engine(time(NULL));

inline double real_rand_uniform_Minus1_to_1()
{
	return uniform_Minus1_to_1(engine);
}
inline double real_rand_uniform_0_to_1()
{
	return uniform_0_to_1(engine);
}
Vector2d sample_in_unit_disk()
{
	Vector2d p;
	do
	{
		p = 2.0f * Point2d(real_rand_uniform_Minus1_to_1(), real_rand_uniform_Minus1_to_1()) - Point2d(1.0, 1.0);
	} while (p.LengthSquared() >= 1);
	return p;

}

