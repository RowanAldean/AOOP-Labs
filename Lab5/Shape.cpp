#include "Shape.h"
#include <iostream>
#include <sstream>

Shape::Shape(){};

Shape::~Shape(){};

Circle::Circle(double x, double y, double r) : x(x), y(y), r(r)
{
    std::cout << "Circle constructed with 3 doubles \n";
};

Circle::~Circle(){};

std::string Circle::to_string() const{
    std::stringstream stream;
    stream << "Circle centered at (" << this->x << "," << this->y << ") with radius " << this->r << "...";
    std::string str = stream.str();
    return str; 
};

void Circle::centre_at(double x, double y){
    this->x = x;
    this->y = y;
};