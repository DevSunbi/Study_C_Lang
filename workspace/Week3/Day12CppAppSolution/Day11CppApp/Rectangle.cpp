#include <iostream>
#include "Rectangle.h"

using namespace std;

string Rectangle::my_name = "rect";

Rectangle::Rectangle()// : width(0), height(0) //Rectangle(0,0) initializer
{
	width = height = 0;
	ptr = new int[10];
	cout << "Rectangle Class Default Constructor" << endl;
}

Rectangle::Rectangle(int width, int height) : Shape(0) // overloading
{
	this->width = width;
	this->height = height;
	ptr = new int[10];
	cout << "Rectangle Class Param Constructor" << endl;
}

Rectangle::Rectangle(const Rectangle& rect)
{
	width = rect.width;
	height = rect.height;
	ptr = new int[10];
	for (int i = 0; i < 10; i++)
	{
		ptr[i] = rect.ptr[i];
	}
}

Rectangle::~Rectangle()
{
	if (ptr != nullptr)
	{
		delete[] ptr;
		ptr = nullptr;
	}
	cout << "Rectangle Class Destructor" << endl;
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

Rectangle Rectangle::operator+(const Rectangle& rect)
{
	this->width += rect.width;
	this->height += rect.height;
	return *this;
}

string Rectangle::get_my_name()
{
	return Rectangle::my_name;
}

Rectangle* Rectangle::createRectangle(int width, int height)
{
	Rectangle* rect = new Rectangle(width, height);
	return rect;
}