#pragma once
#include"header.h"
#include"surface.h"
class Object
{
public:
	Surface* surface;
	Material* material;

	Object(Surface* shape, Material* mat) :surface(shape), material(mat) {}

	//Intersection
	bool IntersectP(const Ray& ray)
	{
		return surface->IntersectP(ray);
	}
	bool Intersect(const Ray& ray, Interaction* rec)
	{
		bool result = surface->Intersect(ray, rec);
		rec->mat = material;
		return result;
	}
};
class Scene
{
public:
	std::vector<Object*> scene_list;

	bool Intersect(const Ray& ray, Interaction* rec)
	{
		bool hitted = false;
		double closest_t = ray.tMax;
		Interaction temp_rec;
		for (auto& i : scene_list)
		{
			ray.tMax = closest_t;
			if (i->Intersect(ray, &temp_rec))
			{
				hitted = true;
				closest_t > temp_rec.t ? closest_t = temp_rec.t : closest_t;
				*rec = temp_rec;
			}
		}
		return hitted;
	}
	bool isInside(const Ray& ray)
	{
		bool isinside = false;
		for (auto& i : scene_list)
		{
			if (i->surface->isInside(ray.o))
				isinside = true;
		}
		return isinside;
	}
};