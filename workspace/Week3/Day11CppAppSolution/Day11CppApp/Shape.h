#pragma once
class Shape
{
private :
	int area;
public :
	Shape();
	Shape(int area);
	int get_area();
	void set_area(int a);
	virtual void calculate_area();
};