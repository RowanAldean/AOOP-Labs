#include <iostream>
#include "Shape.h"

int main(int argc, char *argv[])
{
    // Shape **x = new Shape *[10];
    // x[0] = new Triangle(0, 0, 1, 1, 0, 1);
    // x[1] = new Rectangle(0, 2, 5, 7);
    // x[2] = new Circle(0, 5, 10);
    // x[3] = new Triangle(0, 0, 4, 4, 0, 4);
    // x[4] = new Rectangle(0, 1, 0, 1);
    // x[5] = new Rectangle(1, 2, 3, 4);
    // x[6] = new Rectangle(5, 7, 10, 11);
    // x[7] = new Circle(1, 8, 5);
    // x[8] = new Circle(2, 6, 8);
    // x[9] = new Circle(3, 4, 3);

    Triangle *x = new Triangle(0,0,1,1,0,1);
    // Gen 10 shapes w/ diff params
    // Loop over and to_string
    // Loop over and centre_at then to_string to prove it
    // Delete each shape and delete the array at the end
    std::cout << x->to_string() << std::endl;
    x->centre_at(4, 2);
    std::cout << x->to_string() << std::endl;
    std::cout << x->to_string() << std::endl;
    delete x;
    return 0;
}