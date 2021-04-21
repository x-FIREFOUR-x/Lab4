#pragma once
#include <fstream>
#include <cstdlib>
#include "BMPstruct.h"
using namespace std;
class Picture
{
	BMP_head head;
	Pixel_triplet** pixels;
	uint8_t interpolate(double, double, double, double, double, double, double, double, double, double);
	void reflection_horizontal();
	void reflectionVertical();
public:
	void read_picture(string);
	void write_picture(string);
	void enlarge_picture(int);
	void enlarge_picture(double);
	void reflection(int orientation);
};

