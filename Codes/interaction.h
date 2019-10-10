#pragma once
#include"geometry.h"
#include"material.h"

class Interaction
{
public:
	//Parameter t of ray when hit at a point
	double t;
	Point2d p;
	Vector2d n;
	Vector2d wo;
	Material* mat;
	double dis;
	

	Interaction(double _t, const Point2d& _p, const Vector2d& _n, const Vector2d& _wo,double distance, Material* material = nullptr)
		:t(_t), p(_p), n(_n), wo(_wo),dis(distance), mat(material) {}
	Interaction() {  }

	Ray SpawnRay(const Vector2d& d) const
	{
		return Ray(p, d, InfinityDouble);
	}
	Ray SpawnRayTo(const Point2d& p2) const
	{
		Vector2d d = p2 - p;
		return Ray(p, d, 1 - 0.0001f);
	}
	Ray SpawnRayTo(const Interaction & it) const
	{
		Vector2d d = it.p - p;
		return Ray(p, d, 1 - 0.0001f);
	}

};
