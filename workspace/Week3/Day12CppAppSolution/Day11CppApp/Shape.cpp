#include <iostream>
#include "Shape.h"

using namespace std;

Shape::Shape() : Shape(0)
{
	//area = 0;
	cout << "Shape Calss Default Constructor" << endl;
}

Shape::~Shape()
{
	cout << "Shape Class Destructor" << endl;
}

Shape::Shape(int area)
{
	this->area = area;
	cout << "Shape Class Param Constructor" << endl;
}

int Shape::get_area()
{
	return area;
}

void Shape::set_area(int a)
{
	area = a;
}

void Shape::calculate_area()
{
	cout << "develop..." << endl;
}