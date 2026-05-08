#include <iostream>
#include "Rectangle.h"

using namespace std;

string Rectangle::my_name = "rect";

Rectangle::Rectangle()// : width(0), height(0) //Rectangle(0,0) initializer
{
	width = height = 0;
	cout << "Rectangle Class Default Constructor" << endl;
}

Rectangle::Rectangle(int width, int height) : Shape(0) // overloading
{
	this->width = width;
	this->height = height;
	cout << "Rectangle Class Param Constructor" << endl;
}

void Rectangle::set_width(int w)
{
	width = w;
}

int Rectangle::get_width()
{
	return width;
}

void Rectangle::set_height(int h)
{
	height = h;
}

int Rectangle::get_height()
{
	return height;
}

void Rectangle::calculate_area()
{
	set_area(width * height);
}