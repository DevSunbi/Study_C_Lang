#include <iostream>
#include "Triangle.h"

using namespace std;

Triangle::Triangle()
{
	width = height = 0;
	cout << "Triangle Class Default Constructor" << endl;
}
void Triangle::set_width(int w)
{
	width = w;
}

int Triangle::get_width()
{
	return width;
}

void Triangle::set_height(int h)
{
	height = h;
}

int Triangle::get_height()
{
	return height;
}

void Triangle::calculate_area()
{
	set_area(width * height * 0.5);
}