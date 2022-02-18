#include <iostream>
#include "cat.h"

int main(int argc, char *argv[])
{
    Cat a("Garfield");
    std::cout << a.getName() << " has "
              << a.getLives() << " lives." << std::endl;
    Cat b("Mog", 10);
    std::cout << b.getName() << " has "
              << b.getLives() << " lives." << std::endl;
    return 0;
}