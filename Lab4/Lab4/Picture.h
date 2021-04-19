#pragma once
#include <fstream>
#include <cstdlib>
#include "BMPstruct.h"
using namespace std;
class Picture
{
	BMP_head head;
	Pixel_triplet** pixels;
public:
	void read_picture(string);
	void write_picture(string);
	void enlarge_picture(int);
};

