#include <iostream>
#include "Circle.h"

using namespace std;

Circle::Circle()
{
	radius = 0;
	cout << "Circle Class Default Constructor" << endl;
}

void Circle::set_radius(int r)
{
	radius = r;
}

int Circle::get_radius()
{
	return radius;
}

void Circle::calculate_area()
{
	set_area(radius * radius * 3.14);
}
