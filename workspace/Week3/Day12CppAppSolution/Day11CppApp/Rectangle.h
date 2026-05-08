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
    int *ptr;
    Rectangle();
    Rectangle(int width, int height);
    Rectangle(const Rectangle& rect);


public:
    static string my_name;
    static string get_my_name();
    //Rectangle();
    //Rectangle(int width, int height);
    //Rectangle(const Rectangle &rect);//복사 생성자
    ~Rectangle();
    void set_width(int w);
    int get_width();
    void set_height(int h);
    int get_height();
    virtual void calculate_area() override;

    static Rectangle* createRectangle(int width, int height);

    Rectangle operator+(const Rectangle& rect);
};