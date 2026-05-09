#pragma once
#include "Shape.h"
#include<string>
#include<iostream>
using namespace std;

class Rectangle :
    public Shape
{
private:
    int width;
    int height;

public:
    static std::string my_name;
    Rectangle();
    Rectangle(int width, int height);
    void set_width(int w);
    int get_width();
    void set_height(int h);
    int get_height();
    void calculate_area();
};