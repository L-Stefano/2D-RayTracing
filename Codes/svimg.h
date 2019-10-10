#pragma once
#include"header.h"
#include"color.h"
#include"geometry.h"

struct Pixel
{
	Pixel();
	double xyz[3];
};


class Image
{
public:
	const std::string filename;
	Point2i fullResolution;
	Pixel* pixel;

	Image(const Point2i& resolution, const std::string& filename);
	void writeImage();

	Pixel& getPixel(const Point2i& p)
	{
		assert((p.x < fullResolution.x) && (p.y < fullResolution.y));
		return pixel[p.y * fullResolution.x + p.x];
	}
	void setPixel(const Point2i& p,const Color& c)
	{
		assert((p.x < fullResolution.x) && (p.y < fullResolution.y));
		pixel[p.y * fullResolution.x + p.x].xyz[0] = c.r;
		pixel[p.y * fullResolution.x + p.x].xyz[1] = c.g;
		pixel[p.y * fullResolution.x + p.x].xyz[2] = c.b;
	}
	std::ofstream out;
};