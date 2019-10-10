#include"header.h"
#include"geometry.h"
#include"color.h"
#include"utilities.h"
#include"surface.h"
#include"svimg.h"
#include"random.h"
#include"object.h"
#include"material.h"

#include<omp.h>

//#define DEBUG

const int W = 450;
const int H = 450;
const int N = 32;
const int DEPTH = 50;

Image i(Point2i(W, H), "asd");
Image debug(Point2i(W, H), "debug");



void drawLine(Image& img, const Point2d& p1, const Point2d& p2)
{

	int dx = p2.x - p1.x, dy = p2.y - p1.y, steps, k;
	float xIncrement, yIncrement, x = p1.x, y = p1.y;

	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);

	xIncrement = float(dx) / float(steps);
	yIncrement = float(dy) / float(steps);

	img.setPixel(Point2i(round(x), round(y)), Color(255, 0, 0));
	for (k = 0; k < steps; k++) {
		x += xIncrement;
		y += yIncrement;

		//if (y >= H)y = H - 1;
		//else if (y < 0)y = 0;

		//if (x >= W)x = W - 1;
		//else if (x < 0)x = 0;


		img.setPixel(Point2i(round(x), round(y)), Color(255, 0, 0));
	}
}
//通过递归获取光线r上的总贡献
Color trace(const Ray& r, Interaction* inte, Scene& s, int depth = 0)
{

	if (s.Intersect(r, inte))
	{
#ifdef DEBUG
		drawLine(debug, r.o, inte->p);
#endif DEBUG
		Ray scattered;
		Color attenuation(0, 0, 0);
		double absorb = 1.0;
		double transmittance;
		Color sum = inte->mat->Li();
		Interaction inte_temp;

		inte->dis = Distance(r.o, inte->p) * /*3.527777778 **/ 0.001;


		if (inte->mat->isMedium)
		{
			if (depth < DEPTH && inte->mat->scattered(r, *inte, &attenuation, &scattered,&transmittance))
				sum += trace(scattered, inte, s, depth + 1) * absorb*transmittance;
		}
		else if (depth < DEPTH && inte->mat->scattered(r, *inte, &attenuation, &scattered, &transmittance))
		{
			if (s.isInside(r))
			{
				absorb = beerLambert(0.34f, inte->dis);
			}
			sum += trace(scattered, inte, s, depth + 1) * absorb;
		}
		return sum;
	}
	else
		return Color(6, 6, 6);
}

//分层抖动采样
Color jitterSample(const Point2d & p, Scene & s, int samples)
{
	Color c(0, 0, 0);
#ifdef DEBUG 
	if (p != Point2d(250, 250))
	{
		return c;
	}
#endif DEBUG

	for (int n = 0; n < N; n++)
	{
		Interaction inte;
		Ray r = Ray(Point2d(p.x, p.y), cosf(PI * 2 * (n + real_rand_uniform_Minus1_to_1()) / samples), sinf(PI * 2 * (n + real_rand_uniform_Minus1_to_1()) / N));
		//Ray r = Ray(Point2d(p.x, p.y),sample_in_unit_disk());
		c += trace(r, &inte, s);
	}
	c /= samples;
	c = Color(std::min(c.r, 255.0), std::min(c.g, 255.0), std::min(c.b, 255.0));

	c = sqrtColor(c);
	//c = Rounding(c);
	return c;
}
//Color uniformSample(const Point2d& p, Scene& s, int samples)
//{
//	Color c(0, 0, 0);
//#ifdef DEBUG 
//	if (p != Point2d(100, 420))
//	{
//		return c;
//	}
//#endif DEBUG
//
//	for (int n = 0; n < N; n++)
//	{
//		Interaction inte;
//		//Ray r = Ray(Point2d(p.x, p.y), cosf(PI * 2 * (n + real_rand_uniform_Minus1_to_1()) / samples), sinf(PI * 2 * (n + real_rand_uniform_Minus1_to_1()) / N));
//		Ray r = Ray(Point2d(p.x, p.y),sample_in_unit_disk());
//		c += trace(r, &inte, s);
//	}
//	c /= samples;
//	c = Rounding(c);
//	return c;
//}



int main()
{




	Scene s;

	Disk d(Point2d(54, 110), 10);
	Disk d2(Point2d(225, -230), 215);
	Disk d3(Point2d(323, 170), 21);

	Disk upperright(Point2d(460, -70), 160);
	Disk upperleft(Point2d(-10, -70), 160);



	Disk Center(Point2d(225, 225), 65);

	Disk light_l(Point2d(90, 70), 57);
	Disk light_r(Point2d(100, 330), 57);

	ShapeIntersect line(
		new ShapeIntersect(new HalfPlane(-1, 0, 70), new HalfPlane(1, 0, -14)),
		new ShapeIntersect(new HalfPlane(0, 1, -125), new HalfPlane(0, -1, 189)));

	ShapeIntersect reflect1(
		new ShapeIntersect(new HalfPlane(-1, 0, 130), new HalfPlane(1, 0, -30)),
		new ShapeIntersect(new HalfPlane(0, 1, -150), new HalfPlane(0, -1, 220)));

	ShapeIntersect reflect2(
		new ShapeIntersect(new HalfPlane(-1, 0, 250), new HalfPlane(1, 0, -170)),
		new ShapeIntersect(new HalfPlane(0, 1, -180), new HalfPlane(0, -1, 270)));

	ShapeIntersect boxCenter(
		new ShapeIntersect(new HalfPlane(-1, 0, 290), new HalfPlane(1, 0, -150)),
		new ShapeIntersect(new HalfPlane(0, 1, -150), new HalfPlane(0, -1, 290)));

	ShapeIntersect convexLens(
		new ShapeIntersect(
			new ShapeIntersect(new HalfPlane(-1, 0, 390), new HalfPlane(1, 0, -60)),
			new ShapeIntersect(new HalfPlane(0, 1, -165), new HalfPlane(0, -1, 390))),
		new Disk(Point2d(225, 168), 126));

	ShapeUnion boundingBox(
		new ShapeIntersect(new HalfPlane(1, 0, 450), new HalfPlane(-1, 0, -0)),
		new ShapeIntersect(new HalfPlane(0, -1, -0), new HalfPlane(0, 1, 450)));

	ShapeIntersect d4(new Disk(Point2d(220, 226), 60), new Disk(Point2d(220, 274), 60) /*new HalfPlane(0, 1, -220)*/);
	//HalfPlane line(0, -1, 125);

	//Disk d4(Point2d(220, 220), 70);

	Light left(Color(255, 133, 180));
	Light right(Color(145, 200, 255));

	Light l(Color(255, 111, 101));
	Light l2(Color(188, 244, 256));
	Light l3(Color(490, 490, 490));
	Reflector r(Color(254, 254, 254));
	Reflector r2(Color(210, 210, 210));

	Refractor refr(1.58, Color(254, 254, 254));

	Object o(&d, &l);
	Object o2(&d2, &l3);
	Object o3(&line, &r);
	Object o4(&d4, &refr);


	Object bounding(&boundingBox, &r);

	Object l_upperright(&upperright, &l3);
	Object l_upperleft(&upperleft, &l2);


	Object refl1(&reflect1, &r);
	Object refl2(&reflect2, &r2);

	Object o_l_l(&light_l, &left);
	Object o_l_r(&light_r, &right);


	Object o_first(&Center, &l3);

	Object refr1(&boxCenter, &refr);
	Object convLens(&convexLens, &refr);


	//s.scene_list.push_back(&bounding);//绑定盒

	//s.scene_list.push_back(&o);
	//s.scene_list.push_back(&o2);//上方最大白色
	s.scene_list.push_back(&l_upperright);//右上方小白色
	//s.scene_list.push_back(&l_upperleft);//右上方小白色

	//s.scene_list.push_back(&o_l_l);
	//s.scene_list.push_back(&o_l_r);

	//s.scene_list.push_back(&o3);
	//s.scene_list.push_back(&o4);
	s.scene_list.push_back(&refr1);
	//s.scene_list.push_back(&convLens);
	//s.scene_list.push_back(&refl1);
	//s.scene_list.push_back(&refl2);
	//s.scene_list.push_back(&o_first);

	//turn on OpenMP to accelerate
	omp_set_nested(1);
#pragma omp parallel for schedule(dynamic)
	for (int y = 0; y < H; y++)
		for (int x = 0; x < W; x++)
		{
#ifdef DEBUG
			debug.setPixel(
				Point2i(x, y),
				Color(0, 0, 0)
			);
#endif
			i.setPixel(
				Point2i(x, y),
				jitterSample(Point2d(x, y), s, N)
			);

		}

	i.writeImage();
#ifdef DEBUG
	debug.writeImage();
#endif
	std::cout << d.IntersectP(Ray(Point2d(188, 188), Vector2d(-1, -1)));


	return 0;
}
