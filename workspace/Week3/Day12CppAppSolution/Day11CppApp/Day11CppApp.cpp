#include <iostream>
#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
using namespace std;

int main()
{
	Rectangle* ptr = Rectangle::createRectangle(10, 20);
	cout << Rectangle::get_my_name() << endl;//r1.get_my_name() 가라 방법

	//Shape s1;
	//s1.calculate_area();
	////Shape s1(10);
	//Rectangle r1(10, 20), r2(20, 30);
	//Rectangle r3 = r1 + r2;
	//Shape* ptr = new Rectangle(10, 20);
	//ptr->calculate_area();
	//delete ptr;
	//Triangle t1;
	//Circle c1;

	//r1.set_width(10);
	//r1.set_height(20);
	//cout << "r1's len : " << r1.get_width() <<", height: " << r1.get_height() << endl;

	//t1.set_width(10);
	//t1.set_height(20);
	//cout << "t1's len : " << t1.get_width() << ", height: " << t1.get_height() << endl;

	//c1.set_radius(10);
	//cout << "c1's len : " << c1.get_radius() << endl;

	//Shape* pr = &r1; // 형변환 됨, overwrite 불가
	//pr->calculate_area();
	//cout << "r1's area : " << r1.get_area() << endl;

	//Shape* pc = &c1;
	//pc->calculate_area();
	//cout << "c1's area : " << c1.get_area() << endl;

	//r1.calculate_area();
	//cout << "r1's area : " << r1.get_area() << endl;

	//t1.calculate_area();
	//cout << "t1's area : " << t1.get_area() << endl;

	//c1.calculate_area();
	//cout << "c1's area : " << c1.get_area() << endl;

	return 0;
}