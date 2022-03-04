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

Triangle::Triangle(double x0, double y0, double x1, double y1, double x2, double y2) : x0(x0), y0(y0), x1(x1),
                                                                                       y1(y1), x2(x2), y2(y2), Shape()
{
    std::cout << "Triangle constructed with 6 doubles... \n";
};

Triangle::~Triangle(){};

std::string Triangle::to_string() const
{

    std::stringstream stream;
    stream << "Triangle at [(" << this->x0 << "," << this->y0 << "), "
           << "(" << this->x1 << "," << this->y1 << "), "
           << "(" << this->x2 << "," << this->y2 << ")] ";
    stream << "with side lengths "
           << get_side(this->x2, this->y2, this->x0, this->y0) << ", "
           << get_side(this->x1, this->y1, this->x2, this->y2) << ", and "
           << get_side(this->x0, this->y0, this->x1, this->y1);
    std::string str = stream.str();
    return str;
};

void Triangle::centre_at(double x, double y)
{
    double translated_x = fabs(((this->x0 + this->x1 + this->x2) / 3) - x);
    double translated_y = fabs(((this->y0 + this->y1 + this->y2) / 3) - y);

    this->x0 += translated_x;
    this->x1 += translated_x;
    this->x2 += translated_x;

    this->y0 += translated_y;
    this->y1 += translated_y;
    this->y2 += translated_y;

    //The below was for testing accuracy - fabs or std::abs solved rounding problems

    // double centroid_x = ((this->x0 + this->x1 + this->x2) / 3);
    // double centroid_y = ((this->y0 + this->y1 + this->y2) / 3);
    // std::cout << "Centroid is now: " << "(" << centroid_x << "," << centroid_y << ")" << std::endl;
};

double Triangle::get_side(double xp0, double yp0, double xp1, double yp1) const
{
    /* We do pythagorus with the following to find their lengths,
    it's just using the 2 points to find a respective their point made up
    of their x and y's then finding their length via that.
    */
    // x0,y0 = A, x1,y0 = B, x1,y1 = C LINE A

    // x1,y1 = A, x2,y1 = B, x2,y2 = C LINE B

    // x2,y2 = A, x0,y2 = B, x0,y0 = C LINE C
    return sqrt(pow(fabs(yp0 - yp1), 2) +
                pow(fabs(xp0 - xp1), 2));
};
