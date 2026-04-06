### 실습 1
```Cpp title="main.cpp"
#include <iostream>
#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
using namespace std;

int main()
{
	Shape s1;
	Rectangle r1;
	Triangle t1;
	Circle c1;

	r1.set_width(10);
	r1.set_height(20);
	cout << "r1's len : " << r1.get_width() <<", height: " << r1.get_height() << endl;

	t1.set_width(10);
	t1.set_height(20);
	cout << "t1's len : " << t1.get_width() << ", height: " << t1.get_height() << endl;

	c1.set_radius(10);
	cout << "c1's len : " << c1.get_radius() << ", height: " << c1.get_raduis() << endl;

	return 0;
}
```
```Cpp title=Rectangle.cpp
#include <iostream>
#include "Rectangle.h"

using namespace std;

Rectangle::Rectangle()
{
	width = height = 0;
	cout << "Rectangle Class Default Constructor" << endl;
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
```
```cpp title=Rectangle.h
#pragma once
#include "Shape.h"
class Rectangle :
    public Shape
{
private:
    int width;
    int height;
public:
    Rectangle();
    void set_width(int w);
    int get_width();
    void set_height(int h);
    int get_height();
};
```
```cpp title=Triangle.cpp
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
```
```cpp title=triangle.h
#pragma once
#include "Shape.h"
class Triangle :
    public Shape
{
private:
    int width;
    int height;
public:
    Triangle();
    void set_width(int w);
    int get_width();
    void set_height(int h);
    int get_height();
};
```
```cpp title=circle.cpp
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
```
```cpp title=circle.h
#pragma once
#include "Shape.h"
class Circle :
    public Shape
{
private:
    int radius;
public:
    Circle();
    void set_radius(int r);
    int get_radius();
};
```
---
### 실습2
