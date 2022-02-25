#include <iostream>
#include "Shape.h"

int main(int argc, char *argv[])
{
    Shape *x = new Rectangle(0, 1, 1, 0); // x0, y0, x1, y1
    std::cout << x->to_string() << std::endl;
    x->centre_at(-2.5, 2.5);
    std::cout << x->to_string() << std::endl;
    delete x;
    return 0;
}