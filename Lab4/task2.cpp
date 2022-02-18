#include <iostream>
#include "cat.h"

void printStatus(Cat& cat);

int main(int argc, char *argv[])
{
    Cat a("Garfield");
    printStatus(a);

    Cat b("Mog", 10);
    printStatus(b);
    
    b.setLives(42);
    printStatus(b);
    
    b.setName("Prince");
    printStatus(b);

    b.setLives(8);
    printStatus(b);

    b.setLives(0);
    printStatus(b);

    b.setLives(0);
    printStatus(b);
    return 0;
}

void printStatus(Cat& cat){
    std::cout << cat.getName() << " has "
              << cat.getLives() << " lives." << std::endl;
}