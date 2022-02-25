#include "Shape.h"
#include <iostream>
#include <sstream>
#include <cmath>

// Shape functions

Shape::Shape(){};

Shape::~Shape(){};

// Circle functions

Circle::Circle(double x, double y, double r) : x(x), y(y), r(r), Shape()
{
    std::cout << "Circle constructed with 3 doubles \n";
};

Circle::~Circle(){};

std::string Circle::to_string() const
{
    std::stringstream stream;
    stream << "Circle centered at (" << this->x << "," << this->y << ") with radius " << this->r << "...";
    std::string str = stream.str();
    return str;
};

void Circle::centre_at(double x, double y)
{
    this->x = x;
    this->y = y;
};

// Rectangle functions

Rectangle::Rectangle(double x0, double y0, double x1, double y1) : x0(x0), y0(y0), x1(x1), y1(y1), Shape()
{
    std::cout << "Rectangle constructed with 4 doubles... \n";
};

Rectangle::~Rectangle(){};

std::string Rectangle::to_string() const
{
    std::stringstream stream;
    stream << "Rectangle at [(" << this->x0 << "," << this->y0 << "),";
    stream << " (" << this->x1 << "," << this->y1 << ")] ";
    stream << "with width " << abs(this->x1 - this->x0) << ", height " << abs(this->y1 - this->y0) << "...";
    std::string str = stream.str();
    return str;
};

void Rectangle::centre_at(double x, double y)
{
    // This should be absolute, but then it doesn't work?
    double width = this->x1 - this->x0;
    double height = this->y1 - this->y0;

    this->x0 = x - (width / 2);
    this->x1 = x + (width / 2);
    this->y0 = y - (height / 2);
    this->y1 = y + (height / 2);
};

// Triangle functions

