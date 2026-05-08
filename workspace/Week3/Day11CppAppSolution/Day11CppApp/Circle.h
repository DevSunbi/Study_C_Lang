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
    virtual void calculate_area();
};

