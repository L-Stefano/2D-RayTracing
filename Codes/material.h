#pragma once
#include"geometry.h"
#include"surface.h"
#include"header.h"
#include"random.h"
#include"interaction.h"
#include "color.h"
#include"utilities.h"

inline Vector2d reflect(const Vector2d& normal, const Vector2d& wo)
{
	return wo - 2 * Dot(normal, wo) * normal;
}
inline double shlick(double cosine, double IOR)
{
	double r0 = (1 - IOR) / (1 + IOR);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}
inline bool refract(const Vector2d & normal, const Vector2d & wo, double Eta1OverEta2, Vector2d * wi) {
	double idotn = wo.x * normal.x + wo.y * normal.y;
	double k = 1.0f - Eta1OverEta2 * Eta1OverEta2 * (1.0f - idotn * idotn);
	if (k < 0.0f)
		return false; // 全内反射
	double a = Eta1OverEta2 * idotn + sqrtf(k);
	wi->x = Eta1OverEta2 * wo.x - a * normal.x;
	wi->y = Eta1OverEta2 * wo.y - a * normal.y;
	return true;
}
double beerLambert(double absorb, double dis)
{
	return exp(-absorb * dis);
}

double H_G(double g, const Vector2d & wo, const Vector2d & wi)
{
	double cosTheta = Dot(Normalize(wo), Normalize(wi));

	return Inv_4PI * (1 - g * g) / (pow(1 + g * g + 2 * g * cosTheta, 1.5));
}
void sample_H_G(double g, const Vector2d & wo, Vector2d * wi)
{
	double cosTheta;
	if (std::abs(g) < 1e-3) //g为0时是各向同性
		cosTheta = 1 - 2 * real_rand_uniform_0_to_1();
	else {
		double sqrTerm = (1 - g * g) / (1 - g + 2 * g * real_rand_uniform_0_to_1());
		cosTheta = (1 + g * g - sqrTerm * sqrTerm) / (2 * g);
	}
	double sinTheta = std::sqrt(std::max((double)0, 1 - cosTheta * cosTheta));

	*wi = Normalize(Vector2d(wo.x+cosTheta, wo.y+sinTheta));

}
//bool refract(const Vector2d& v, const Vector2d& n, float ni_over_nt, Vector2d* refracted) {
//	Vector2d uv = Normalize(v);
//	double dt = Dot(uv, n);
//	double discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
//	if (discriminant > 0) {
//		*refracted = (uv - n * dt)*ni_over_nt - n * sqrt(discriminant);
//		return true;
//	}
//	else
//		return false;
//}
//
class Material
{
public:
	bool isLight;
	bool isMedium;
	Material(bool light,bool medium) :isLight(light),isMedium(medium) {}

	virtual Color Li() = 0;
	virtual bool scattered(const Ray& wo, const Interaction& rec, Color* attenuation, Ray* wi, double* transmittance) = 0;
};



class Reflector :public Material
{
public:
	double reflectivity;
	Color albedo;

	Reflector() = default;
	Reflector(const Color& attenuation) :albedo(attenuation), Material(false,false) {}

	virtual Color Li()
	{
		return Color(0, 0, 0);
	}
	virtual bool scattered(const Ray& wo, const Interaction& rec, Color* attenuation, Ray* wi, double* transmittance)
	{
		*attenuation = albedo;

		*wi = Ray(rec.p + 0.001 * rec.n, Normalize(reflect(rec.n, wo.d)));
		double dotp = Dot(wi->d, rec.n);
		return (dotp > 0);
	}
};

class Refractor :public Material
{
public:
	double refractivity;
	Color albedo;
	double ior;

	Refractor() = default;
	Refractor(double IOR, const Color& attenuation) :albedo(attenuation), ior(IOR), Material(false,false) {}

	virtual Color Li()
	{
		return Color(0, 0, 0);
	}
	virtual bool scattered(const Ray& wo, const Interaction& rec, Color* attenuation, Ray* wi, double* transmittance)
	{
		if (Dot(wo.d, rec.n) > 0)//从内部向外散射
		{
			Vector2d normal = -rec.n;
			Vector2d refrVec;
			Vector2d wiDir;
			if (!refract(normal, wo.d, ior, &wiDir))
			{
				wiDir = reflect(normal, wo.d);

				*wi = Ray(rec.p, Normalize(wiDir));
				return true;
			}

			//double cosine;
			//cosine = ior * Dot(wo.d, rec.n) / wo.d.Length();

			//double reflQuan = shlick(cosine, ior);

			//if (real_rand_uniform_0_to_1() >= reflQuan)
			//{
			//	wi->d = Normalize(wiDir);
			//	wi->o = rec.p - 0.01 * normal;
			//}
			//else
			//{
			//	wi->d = Normalize(reflect(normal, wo.d));
			//	wi->o = rec.p + 0.01 * normal;
			//}
			wi->d = Normalize(wiDir);
			wi->o = rec.p - 0.01 * normal;
		}
		else
		{
			Vector2d normal = rec.n;
			Vector2d refrVec;
			Vector2d wiDir;

			if (!refract(normal, wo.d, 1 / ior, &wiDir))
			{
				wiDir = reflect(normal, wo.d);
			}

			double cosine;
			cosine = -Dot(wo.d, rec.n) / wo.d.Length();

			double reflQuan = shlick(cosine, ior);
			//double reflQuan =fo			
			if (real_rand_uniform_0_to_1() >= reflQuan)
			{
				wi->d = Normalize(wiDir);
				wi->o = rec.p - 0.01 * normal;
			}
			else
			{
				wi->d = Normalize(reflect(normal, wo.d));
				wi->o = rec.p + 0.01 * normal;
			}
			//wi->o = rec.p - 0.01 * normal;
			//wi->d = Normalize(wiDir);

			return true;
		}

	}
};

class Light :public Material
{
public:
	Color emissivity;
	Light(const Color& emi) :emissivity(emi), Material(true,false) {}

	virtual Color Li()
	{
		return emissivity;
	}
	virtual bool scattered(const Ray& wo, const Interaction& rec, Color* attenuation, Ray* wi, double* transmittance) { return false; }
};
class Medium :public Material
{
public:
	double g;
	double sigma_s, sigma_a, sigma_t;

	Medium() = default;
	Medium(double sigmaA, double sigmaT, double _g) :Material(false, true)
	{
		sigma_a = sigmaA;
		sigma_t = sigmaT;
		sigma_s = sigma_a + sigma_t;
		g = _g;
	}
	virtual Color Li()
	{
		return Color(0, 0, 0);
	}
	virtual bool scattered(const Ray& wo, const Interaction& rec, Color* attenuation, Ray* wi, double* transmittance)
	{
		*transmittance = beerLambert(sigma_s, rec.dis);
		sample_H_G(g, wo.d, &wi->d);

		if (Dot(wo.d, rec.n) > 0)
		{
			wi->o = rec.p + 0.001 * rec.n;
		}
		else
		{
			wi->o = rec.p - 0.001 * rec.n;

		}


		return true;
	}

};
