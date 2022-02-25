#ifndef SHAPE_H
#define SHAPE_H
#include <string>

class Shape
{
public:
    Shape();
    virtual ~Shape();

    virtual std::string to_string() const = 0;
    virtual void centre_at(double x, double y) = 0;
};

struct Circle : public Shape
{
private:
    double x, y, r;

public:
    Circle(double x, double y, double r);
    virtual ~Circle();

    virtual std::string to_string() const;
    virtual void centre_at(double x, double y);
};

struct Rectangle : public Shape
{
private:
    double x0, y0, x1, y1;

public:
    Rectangle(double x0, double y0, double x1, double y1);
    virtual ~Rectangle();

    virtual std::string to_string() const;
    virtual void centre_at(double x, double y);
};


#endif