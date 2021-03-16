#include "canvas.h"
#include <cassert>

using namespace std;
using namespace agl;

canvas::canvas(int w, int h) : _canvas(w, h)
{
	width = w;
	height = h;
	image = ppm_image(w, h);

}

canvas::~canvas()
{
	delete[] curColor;
	delete[] vertices;

}

void canvas::save(const std::string& filename)
{
   _canvas.save(filename);
}

void canvas::begin(PrimitiveType type)
{
	delete[] vertices;
	vertices = new int* [2];
	curShape = type;
	numVec = 0;
}

void canvas::end()
{
}

void canvas::vertex(int x, int y)
{
	int* vertex = new int[2];
	vertex[0] = x;
	vertex[1] = y;
	vertices[numVec] = vertex;
	numVec++;
}

void canvas::color(unsigned char r, unsigned char g, unsigned char b)
{
	delete[] curColor;
	curColor = new unsigned char[3];
	curColor[0] = r;
	curColor[1] = g;
	curColor[2] = b;
 }

void canvas::background(unsigned char r, unsigned char g, unsigned char b)
{
	int total = width * height;
	ppm_pixel* data = image.getData();
	for (int i = 0; i < total; i++) {
		data[i] = ppm_pixel{ r,g,b };
	}

}

