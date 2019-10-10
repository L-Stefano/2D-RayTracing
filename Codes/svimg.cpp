#include"svimg.h"

Pixel::Pixel() { xyz[0] = xyz[1] = xyz[2] = 0; }

Image::Image(const Point2i& resolution, const std::string& filename)
	:fullResolution(resolution), filename(filename), out("./Image/" + filename + ".ppm", std::ofstream::out)
{
	pixel = (Pixel*)malloc(fullResolution.x * fullResolution.y * sizeof(Pixel));
}

void Image::writeImage()
{
	out << "P3" << std::endl;
	out << fullResolution.x << ' ' << fullResolution.y << std::endl;
	out << "255" << std::endl;

	for (int p = 0; p < fullResolution.x * fullResolution.y; ++p)
	{
		out << pixel[p].xyz[0] << ' '
			<< pixel[p].xyz[1] << ' '
			<< pixel[p].xyz[2] << '\n';
	}
	out.close();
}

