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
    void calculate_area();
};

