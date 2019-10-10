#pragma once

#include"utilities.h"
#include"geometry.h"
#include"material.h"
#include"interaction.h"


class Surface
{
public:
	//only determine whether the ray hit the surface
	virtual bool IntersectP(const Ray& r) = 0;

	//determine whether the ray hit the surface.
	//If it is, return information about the intersection to inte.
	virtual bool Intersect(const Ray& r, Interaction* inte) = 0;

	//determine whether the point is inside.
	virtual bool isInside(const Point2d &p) = 0;

	//determine whether the point is inside.
	virtual bool isOnBoundary(const Point2d &p) = 0;

	virtual Vector2d getNormal(const Point2d& p) = 0;
};

//Define half-plane(or line): a * x + b * y + c > 0
//Normal is (a/c,b/c)
class HalfPlane :public Surface
{
public:
	double a;
	double b;
	double c;
	Vector2d normal;

	HalfPlane(double A, double B, double C) :a(A), b(B), c(C), normal(Vector2d(-a, -b)) {}

	virtual bool isInside(const Point2d &p)
	{
		return p.x* a + p.y * b + c >= 0.f;
	}
	virtual bool isOnBoundary(const Point2d &p)
	{
		return fabs(p.x * a + p.y * b + c) <= EPSILON;
	}
	virtual Vector2d getNormal(const Point2d& p)
	{
		return normal;
	}
	virtual bool IntersectP(const Ray& ray)
	{
		if (isInside(ray.o)) return true;

		if (Dot(ray.d, normal) < 0)	//判断光线与法线是否异向
			return true;
		return false;
	}
	virtual bool Intersect(const Ray& ray, Interaction* rec)
	{
		if (isInside(ray.o)) 
		{
			Point2d inter;
			inter.x = (b * ray.d.y * ray.o.x - b * ray.d.x * ray.o.y - c * ray.d.x) / (a * ray.d.x + b * ray.d.y);
			if (ray.d.x) inter.y = (inter.x - ray.o.x) * ray.d.y / ray.d.x + ray.o.y;
			else inter.y = (-c - a * inter.x) / b;

			if ((rec->t = (inter - ray.o).x / ray.d.x) < ray.tMax && rec->t > 0)
			{
				rec->p = inter;
				rec->n = normal;
				rec->wo = Vector2d(-ray.d);
				if (Dot(ray.d, (inter - ray.o)) < 0)	//射线的反向与直线相交
				{
					rec->t = 0;
					rec->p = ray(0);
					rec->n = normal;
					rec->wo = Vector2d(-ray.d);
					return true;
				};
			}

			return true;
		}


		Vector2d ab = Vector2d(a, b);
		double t = -(c + Dot((Vector2d)ray.o, ab)) / Dot(ray.d, ab);

		if (Dot(ray.d, normal) < 0)
			if (t < ray.tMax && t > 0)
			{
				rec->t = t;
				rec->p = ray(t);
				rec->n = normal;
				rec->wo = Vector2d(-ray.d);
				return true;
			}
			else
				return false;
		else
			return false;
	}
};
//Define disk
class Disk :public Surface
{
public:
	Point2d c;	//centre
	double r;	//radius

	Disk(Point2d _c, double _r) :c(_c), r(_r) {}

	virtual bool isInside(const Point2d &p)
	{
		return Distance(p, c) <= r;
	}
	virtual bool isOnBoundary(const Point2d &p)
	{
		return fabs((c - p).Length() - r) <= EPSILON;
	}
	virtual Vector2d getNormal(const Point2d& p)
	{
		return Normalize((p - this->c) / r);
	}
	virtual bool IntersectP(const Ray& ray)
	{
		if (isInside(ray.o)) return true;

		//determine the distance of centre and p
		double proj = Dot(c - ray.o, ray.d) / ray.d.Length();
		if (proj < 0)return false;
		double d = sqrt((c - ray.o).Length() * (c - ray.o).Length() - proj * proj);

		return d <= r;
		//if (isInside(ray.o)) return true;				//在圆内则必然相交
		//double proj = Dot((c - ray.o) , ray.d)/ray.d.Length();					//向量po在射线上垂足的距离
		//if (proj < 0) return false;				//反向射线
		//Point2d foot = ray.o + ray.d * proj;					//垂足位置
		//double dis = (c - foot).Length();				//圆心到垂足的距离
		//return dis <= r;
	}
	virtual bool Intersect(const Ray & ray, Interaction * rec)
	{
		Vector2d oc = ray.o - c;
		double a = Dot(ray.d, ray.d);
		double b = Dot(ray.d, oc);
		double c = Dot(oc, oc) - r * r;

		double discriminant = (b * b - a * c);
		if (discriminant >= 0)
		{
			double t = (-b - sqrt(discriminant)) / a;
			if (t < ray.tMax && t >= 0)
			{
				rec->t = t;
				rec->p = ray(t);
				rec->n = Normalize((rec->p - this->c) / r);
				rec->wo = Vector2d(-ray.d);
				return true;
			}
			t = (-b + sqrt(discriminant)) / a;
			if (t < ray.tMax && t >= 0)
			{
				rec->t = t;
				rec->p = ray(t);
				rec->n = Normalize((rec->p - this->c) / r);
				rec->wo = Vector2d(-ray.d);
				return true;
			}
		}
		return false;
	}
};

class ShapeUnion :public Surface
{
private:
	Surface* m_shape1;
	Surface* m_shape2;
public:
	ShapeUnion(Surface* shape1, Surface* shape2)
	{
		m_shape1 = shape1, m_shape2 = shape2;
	}
	~ShapeUnion()
	{
		delete m_shape1;
		delete m_shape2;
	}

	virtual bool isInside(const Point2d &p)
	{
		return m_shape1->isInside(p) || m_shape2->isInside(p);
	}
	virtual bool isOnBoundary(const Point2d& p)
	{
		return m_shape1->isOnBoundary(p) || m_shape2->isOnBoundary(p);
	}
	virtual Vector2d getNormal(const Point2d& p)
	{
		if (m_shape1->isOnBoundary(p) && m_shape2->isOnBoundary(p))
			return (m_shape1->getNormal(p) + m_shape2->getNormal(p)) / 2.f;
		if (m_shape1->isOnBoundary(p))
			return m_shape1->getNormal(p);
		if (m_shape2->isOnBoundary(p))
			return m_shape2->getNormal(p);
		return{ 0.f, 1.f };
	}
	virtual bool IntersectP(const Ray & ray)
	{
		Interaction rec1, rec2;
		if (!(m_shape1->Intersect(ray,&rec1) || m_shape2->Intersect(ray, &rec2)))
			return false;
		return true;
	}

	virtual bool Intersect(const Ray& ray, Interaction * rec)
	{
		Interaction rec1, rec2;
		bool res1 = m_shape1->Intersect(ray, &rec1);
		bool res2 = m_shape2->Intersect(ray, &rec2);
		if (!res1 && !res2)
			return false;
		if (!res1)
			*rec = rec2;
		else if (!res2)
			*rec = rec1;
		else
			*rec = (rec1.p - ray.o).Length() > (rec2.p - ray.o).Length() ? rec2 : rec1;
		return true;
	}
};

class ShapeIntersect : public Surface
{
private:
	Surface* m_shape1;
	Surface* m_shape2;
public:
	ShapeIntersect(Surface* shape1, Surface* shape2)
	{
		m_shape1 = shape1, m_shape2 = shape2;
	}
	~ShapeIntersect()
	{
		delete m_shape1;
		delete m_shape2;
	}
	virtual bool isInside(const Point2d& p)
	{
		return m_shape1->isInside(p) && m_shape2->isInside(p);
	}

	virtual bool isOnBoundary(const Point2d& p)
	{
		return m_shape1->isOnBoundary(p) || m_shape2->isOnBoundary(p);
	}
	virtual Vector2d getNormal(const Point2d& p)
	{
		if (m_shape1->isOnBoundary(p) && m_shape2->isOnBoundary(p))
			return ((m_shape1->getNormal(p)) + (m_shape2->getNormal(p))) / 2.f;
		if (m_shape1->isOnBoundary(p))
			return m_shape1->getNormal(p);
		if (m_shape2->isOnBoundary(p))
			return m_shape2->getNormal(p);
		return{ 0.f, 1.f };
	}

	virtual bool IntersectP(const Ray&ray)
	{
		Interaction rec1, rec2;
		if (!(m_shape1->Intersect(ray, &rec1) && m_shape2->Intersect(ray, &rec2)))
			return false;
		return m_shape2->isInside(rec1.p) || m_shape1->isInside(rec2.p);
	}

	virtual bool Intersect(const Ray& ray, Interaction* inter)
	{
		Interaction rec1, rec2;
		if (!(m_shape1->Intersect(ray, &rec1) && m_shape2->Intersect(ray, &rec2)))
			return false;
		if (m_shape2->isInside(rec1.p) && m_shape1->isInside(rec2.p))	//两个交点都合法，则取最近的交点
			*inter = (rec1.p - ray.o).Length() > (rec2.p - ray.o).Length() ? rec2 : rec1;
		else if (m_shape2->isInside(rec1.p))
			*inter = rec1;
		else if (m_shape1->isInside(rec2.p))
			*inter = rec2;
		else
			return false;
		return true;
	}
};


class ShapeSubstract : public Surface
{
private:
	Surface* m_shape1;
	Surface* m_shape2;
public:
	ShapeSubstract(Surface* shape1, Surface* shape2)
	{
		m_shape1 = shape1, m_shape2 = shape2;
	}
	~ShapeSubstract()
	{
		delete m_shape1;
		delete m_shape2;
	}
	virtual bool isInside(const Point2d& p)
	{
		return m_shape1->isInside(p) && m_shape2->isInside(p);
	}

	virtual bool isOnBoundary(const Point2d& p)
	{
		return m_shape1->isOnBoundary(p) || m_shape2->isOnBoundary(p);
	}
	virtual Vector2d getNormal(const Point2d& p)
	{
		if (m_shape1->isOnBoundary(p) && m_shape2->isOnBoundary(p))
			return ((m_shape1->getNormal(p)) + (m_shape2->getNormal(p))) / 2.f;
		if (m_shape1->isOnBoundary(p))
			return m_shape1->getNormal(p);
		if (m_shape2->isOnBoundary(p))
			return m_shape2->getNormal(p);
		return{ 0.f, 1.f };
	}

	virtual bool IntersectP(const Ray & ray)
	{
		Interaction rec1, rec2;
		if (!(m_shape1->Intersect(ray, &rec1) && m_shape2->Intersect(ray, &rec2)))
			return false;
		return m_shape2->isInside(rec1.p) || m_shape1->isInside(rec2.p);
	}

	virtual bool Intersect(const Ray & ray, Interaction * inter)
	{
		Interaction rec1, rec2;
		if (!(m_shape1->Intersect(ray, &rec1) && m_shape2->Intersect(ray, &rec2)))
			return false;
		if (m_shape2->isInside(rec1.p) && m_shape1->isInside(rec2.p))	//两个交点都合法，则取最近的交点
			* inter = (rec1.p - ray.o).Length() > (rec2.p - ray.o).Length() ? rec2 : rec1;
		else if (m_shape2->isInside(rec1.p))
			* inter = rec1;
		else if (m_shape1->isInside(rec2.p))
			* inter = rec2;
		else
			return false;
		return true;
	}
};
