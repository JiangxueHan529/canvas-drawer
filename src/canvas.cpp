#include "canvas.h"
#include <cassert>
#include <vector>

using namespace std;
using namespace agl;

canvas::canvas(int w, int h): _canvas(w,h)
{
	width = w;
	height = h;
	curShape = UNDEFINED;
	curColor = new unsigned char[9];
	numVec = 0;
	numColor = 0;
	vertices = {};
	tracker = new int[100];
	color_tracker = new int[100];
	radius = {};
	line_width = {};
}

canvas::~canvas()
{
	delete[] tracker;
	delete[] curColor;
	delete[] color_tracker;
	vertices.clear();
	radius.clear();
	line_width.clear();
}

void canvas::save(const std::string& filename)
{
	_canvas.save(filename);
}

void canvas::begin(PrimitiveType type)
{
	vertices.clear();
	vector<vector <int>> vertices(100, vector<int>(2, 0));
	curShape = type;
	numVec = 0;
	numColor = 0;
	tracker = 0;
	delete[] curColor;
	curColor = new unsigned char[100];
	delete[] tracker;
	tracker = new int[100];
	delete[] color_tracker;
	color_tracker = new int[100];
	if (type == CIRCLES) {
		radius.clear();
	}
	line_width.clear();
	vector<int> vec(100, 1);
	line_width = vec;
}

void canvas::end()
{   // need to update the thing with tracker
	if (curShape == LINES) {
		for (int i = 0; i < vertices.size() - 1;i += 2) {
			vector<int> vertex1 = vertices[i];
			vector<int> vertex2 = vertices[i + 1];
			int color_index = tracker[i];
			int color_track = color_tracker[i + 1];
			int lw = line_width[i + 1];
			for (int j = 0; j < lw;j++) {
				if (j > 0) {
					vertex1[1] += 1;
					vertex2[1] += 1;
				}
				if (vertex1[0] == vertex2[0]) {
					int start;
					int end;
					if (vertex1[1] > vertex2[1]) {
						start = vertex2[1];
						end = vertex1[1];
					}
					else {
						start = vertex1[1];
						end = vertex2[1];
					}
					for (int i = start; i < end + 1; i++) {
						_canvas.set(i, vertex1[0], ppm_pixel{ curColor[0], curColor[1],curColor[2] });
					}
				}
				else if (vertex1[1] == vertex2[1]) {
					int start;
					int end;
					if (vertex1[0] > vertex2[0]) {
						start = vertex2[0];
						end = vertex1[0];
					}
					else {
						start = vertex1[0];
						end = vertex2[0];
					}
					for (int i = start; i < end + 1; i++) {
						_canvas.set(vertex1[1], i, ppm_pixel{ curColor[0], curColor[1],curColor[2] });
					}
				}
				else {

					float m = ((float)vertex2[1] - (float)vertex1[1]) / ((float)vertex2[0] - (float)vertex1[0]);
					int flag = 0;
					if (m <= 1 && m >= 0) {
						flag = 0;
					}
					else if (m <= 0 && m >= -1) {
						vertex1[1] = -vertex1[1];
						vertex2[1] = -vertex2[1];
						flag = 1;
					}
					else if (m > 1) {
						int temp = vertex1[0];
						vertex1[0] = vertex1[1];
						vertex1[1] = temp;
						int temp2 = vertex2[0];
						vertex2[0] = vertex2[1];
						vertex2[1] = temp2;
						flag = 2;
					}
					else {
						int temp = vertex1[0];
						vertex1[0] = vertex1[1];
						vertex1[1] = -temp;
						int temp2 = vertex2[0];
						vertex2[0] = vertex2[1];
						vertex2[1] = -temp2;
						flag = 3;
					}
					if (vertex2[0] < vertex1[0]) {
						int vertex1_x = vertex1[0];
						int vertex1_y = vertex1[1];
						vertex1 = { vertex2[0], vertex2[1] };
						vertex2 = { vertex1_x,vertex1_y };
					}
					int y = vertex1[1];
					int w = vertex2[0] - vertex1[0];
					int h = vertex2[1] - vertex1[1];
					int f = 2 * h - w;
					int line_length = vertex2[0] - vertex1[0] + 1;
					for (int x = vertex1[0]; x <= vertex2[0];x++) {
						if (flag == 0) {
							if (color_track * 3 - color_index == 3) {
								_canvas.set(y, x, ppm_pixel{ (unsigned char)((int)curColor[0] * (1 - (float)(x - vertex1[0]) / (float)line_length
								) + (int)curColor[3] * (float)(x - vertex1[0]) / (float)line_length), (unsigned char)((int)curColor[1] * (1 - (float)(x - vertex1[0]) / (float)line_length) + (int)curColor[4] * (float)(x - vertex1[0]) / (float)line_length),(unsigned char)((int)curColor[2] * (1 - (float)(x - vertex1[0]) / (float)line_length) + (int)curColor[5] * (float)(x - vertex1[0]) / (float)line_length) });
							}
							else {
								_canvas.set(y, x, ppm_pixel{ curColor[0], curColor[1],curColor[2] });
							}

						}
						else if (flag == 1) {
							if (color_track * 3 - color_index == 3) {
								_canvas.set(-y, x, ppm_pixel{ (unsigned char)((int)curColor[0] * (1 - (float)(x - vertex1[0]) / (float)line_length
								) + (int)curColor[3] * (float)(x - vertex1[0]) / (float)line_length), (unsigned char)((int)curColor[1] * (1 - (float)(x - vertex1[0]) / (float)line_length) + (int)curColor[4] * (float)(x - vertex1[0]) / (float)line_length),(unsigned char)((int)curColor[2] * (1 - (float)(x - vertex1[0]) / (float)line_length) + (int)curColor[5] * (float)(x - vertex1[0]) / (float)line_length) });
							}
							else {
								_canvas.set(-y, x, ppm_pixel{ curColor[0], curColor[1],curColor[2] });
							}
						}
						else if (flag == 2) {
							if (color_track * 3 - color_index == 3) {
								_canvas.set(x, y, ppm_pixel{ (unsigned char)((int)curColor[0] * (1 - (float)(x - vertex1[0]) / (float)line_length
								) + (int)curColor[3] * (float)(x - vertex1[0]) / (float)line_length), (unsigned char)((int)curColor[1] * (1 - (float)(x - vertex1[0]) / (float)line_length) + (int)curColor[4] * (float)(x - vertex1[0]) / (float)line_length),(unsigned char)((int)curColor[2] * (1 - (float)(x - vertex1[0]) / (float)line_length) + (int)curColor[5] * (float)(x - vertex1[0]) / (float)line_length) });
							}
							else {
								_canvas.set(x, y, ppm_pixel{ curColor[0], curColor[1],curColor[2] });
							}
						}
						else {
							if (color_track * 3 - color_index == 3) {

								_canvas.set(x, -y, ppm_pixel{ (unsigned char)((int)curColor[0] * (1 - (float)(x - vertex1[0]) / (float)line_length
								) + (int)curColor[3] * (float)(x - vertex1[0]) / (float)line_length), (unsigned char)((int)curColor[1] * (1 - (float)(x - vertex1[0]) / (float)line_length) + (int)curColor[4] * (float)(x - vertex1[0]) / (float)line_length),(unsigned char)((int)curColor[2] * (1 - (float)(x - vertex1[0]) / (float)line_length) + (int)curColor[5] * (float)(x - vertex1[0]) / (float)line_length) });
							}
							else {
								_canvas.set(x, -y, ppm_pixel{ curColor[0], curColor[1],curColor[2] });
							}
						}
						if (f > 0) {
							y++;
							f += 2 * (h - w);
						}
						else {
							f += 2 * h;
						}
					}
				}
			}
		}
	}
	else if (curShape == TRIANGLES) {
	for (int i = 0; i < vertices.size() - 2;i += 3) {
		vector<int> vertex1 = vertices[i];
		vector<int> vertex2 = vertices[i+1];
		vector<int> vertex3 = vertices[i+2];
		//see if can pass in color
		//need to have a thing that keeps track of how many colors each shape uses
		int color_index = tracker[i];
		int color_track = color_tracker[i + 2];
		barycentric_fill(vertex1, vertex2, vertex3, color_index, color_track);
	}
}
	else if (curShape == CIRCLES) {
		for (int i = 0; i < vertices.size();i++) {
			if (vertices[i][0] + radius[i] > width) {
				vertices[i][0] = width - radius[i];
			}
			else if (vertices[i][1] + radius[i] > width) {
				vertices[i][1] = height - radius[i];
			}
			else if (vertices[i][1] - radius[i] < 0) {
				vertices[i][1] = radius[i];
			}
			else if (vertices[i][0] - radius[i] > 0) {
				vertices[i][0] =  radius[i];
			}
		}
			for (int i = 0; i < vertices.size();i++) {
				int color_index = tracker[i];
				draw_circle(vertices[i][0], vertices[i][1], radius[i], color_index);
			}
		}

	}

// need to consider only two colors for a triangle
void canvas::barycentric_fill(vector<int> a, vector<int> b, vector<int> c, int color_index, int color_track) {
	int xmin = min(min(a[0], b[0]), c[0]);
	int xmax = max(max(a[0], b[0]), c[0]);
	int ymin = min(min(a[1], b[1]), c[1]);
	int ymax = max(max(a[1], b[1]), c[1]);
	int f_alpha = helper(b, c, a);
	int f_beta = helper(a, c, b);
	int f_gamma = helper(a, b, c);
	ppm_pixel pure = ppm_pixel{ curColor[color_index], curColor[color_index + 1],curColor[color_index + 2] };
	
	for (int row = ymin; row < ymax + 1;row++) {
		for (int col = xmin; col < xmax + 1;col++) {
			float alpha = (float)helper(b, c, vector<int>{col, row}) / (float)f_alpha;
			float beta = (float)helper(a, c, vector<int>{col, row}) / (float)f_beta;
			float gamma = (float)helper(a, b, vector<int>{col, row}) / (float)f_gamma;

			int r = (int)curColor[color_index] * alpha +
				(int)curColor[color_index + 3] * beta + (int)curColor[color_index + 6] * gamma;
			int g = (int)curColor[color_index + 1] * alpha + (int)curColor[color_index + 4] * beta +
				(int)curColor[color_index + 7] * gamma;
			int blue = (int)curColor[color_index + 2] * alpha +
				(int)curColor[color_index + 5] * beta + (int)curColor[color_index + 8] * gamma;

			ppm_pixel interpolated = ppm_pixel{ (unsigned char)r,(unsigned char)g ,(unsigned char)blue };
			if (alpha >= 0 && beta >= 0 && gamma >= 0) {
				if (alpha > 0 || f_alpha * helper(b, c, vector<int>{-1, -1}) > 0) {
					if (color_track*3 -  color_index == 3) {
						_canvas.set(row, col,pure);
					}
					else {
				

						_canvas.set(row, col,interpolated);
					}
					if (alpha > 0 || f_beta * helper(a, c, vector<int>{-1, -1}) > 0) {
						if (color_track * 3 - color_index == 3) {
							_canvas.set(row, col, pure);
						}
						else {
							_canvas.set(row, col, interpolated);
						}

					}
					if (alpha > 0 || f_gamma * helper(a, b, vector<int>{-1, -1}) > 0) {
						if (color_track * 3 - color_index == 3) {
							_canvas.set(row, col, pure);
						}
						else {
							_canvas.set(row, col, interpolated);
						}
					}
				}
			}
		}
	}
}
void canvas::drawC(int x, int y, int x1, int y1, ppm_pixel* our_color) {
	_canvas.set(x + x1, y + y1, *our_color);
	_canvas.set(x - x1, y + y1, *our_color);
	_canvas.set(x + x1, y - y1, *our_color);
	_canvas.set(x - x1, y - y1, *our_color);
	_canvas.set(x - y1, y - x1, *our_color);
	_canvas.set(x + y1, y - x1, *our_color);
	_canvas.set(x - y1, y + x1, *our_color);
	_canvas.set(x + y1, y + x1, *our_color);

}

void canvas::draw_circle(int x, int y, int radius, int color_index) {
	int x1 = 0;
	int y1 = radius;
	int d = 3 - 2 * radius;
	ppm_pixel our_color = ppm_pixel{ curColor[color_index],curColor[color_index + 1] ,curColor[color_index + 2] };
	drawC(x, y, x1, y1, &our_color);
	while (y1 >= x1)
	{
		x1++;
		if (d > 0)
		{
			y1--;
			d = d + 4 * (x1 - y1) + 10;
		}
		else
			d = d + 4 * x1 + 6;
		
		drawC(x, y, x1, y1, &our_color);
	}
}

int canvas::helper(vector<int> a, vector<int> b, vector<int> c) {
	return (b[1] - a[1]) * (c[0] - a[0]) - (b[0] - a[0])*(c[1] - a[1]);
}

void canvas::input_radius(int r) {
	radius.push_back(r);
}

void canvas::input_line_width(int lw) {
	line_width[numVec] = lw;
}

void canvas::vertex(int x, int y)
{
	if (x >= width) {
		x = width - 1;
	}
	if (y >= height) {
		y = height - 1;
	}
		vector<int> vertex(2);

	vertex[0] = x;
	vertex[1] = y;
	vertices.push_back(vertex);
	numVec++;
	color_tracker[numVec] = numColor;
}


void canvas::color(unsigned char r, unsigned char g, unsigned char b)
{
	/*if ((vertices.size() % 2 == 0 && curShape == LINES) ||(vertices.size() %3 ==0 && curShape == TRIANGLES) ) {
		delete[] curColor;
		curColor = new unsigned char[9];
		curColor[0] = r;
		curColor[1] = g;
		curColor[2] = b;
		numColor = 1;
	}
	else {
		if (numColor == 1) {
			curColor[3] = r;
			curColor[4] = g;
			curColor[5] = b;
			numColor = 2;
		}
		else {
			curColor[6] = r;
			curColor[7] = g;
			curColor[8] = b;
			numColor = 3;
		}
	}*/
	if ((vertices.size() % 2 == 0 && curShape == LINES) || (vertices.size() % 3 == 0 && curShape == TRIANGLES || curShape == CIRCLES)) {
		tracker[numVec] = numColor * 3;
	}


	curColor[numColor * 3] = r;
	curColor[numColor * 3 + 1] = g;
	curColor[numColor * 3 + 2] = b;
	numColor++;

	
 }

void canvas::background(unsigned char r, unsigned char g, unsigned char b)
{
	int total = width * height;
	ppm_pixel* data = _canvas.getData();
	for (int i = 0; i < total; i++) {
		data[i] = ppm_pixel{ r,g,b };
	}

}

