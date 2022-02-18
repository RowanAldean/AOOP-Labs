#include <iostream>
#include "cat.h"

void printStatus(Cat &cat);

int main(int argc, char **argv)
{
    const int CAT_COUNT = argc / 2;
    std::cout << "Allocating clowder of size " << CAT_COUNT << std::endl;
    Cat *clowder = new Cat[CAT_COUNT]();

    for (int i = 0; i < CAT_COUNT; i++)
    {
        std::string name = argv[i * 2 + 1];
        unsigned int lives;

        /*If we're on the last round and our argument count
        is even (the ./task3 counts as an argument thus our cat arg count must be
        odd), then we can set lives to 9.
        */
        if ((i == CAT_COUNT - 1) && (argc%2 == 0))
        {
            lives = 9;
        }
        else
        {
            lives = strtol(argv[i * 2 + 2], NULL, 10);
        }
        Cat newCat = Cat(name, lives);
        clowder[i] = std::move(newCat);
        //Comment this out and see the next comment if you want exact output of the PDF
        printStatus(clowder[i]);
    }

    //Uncomment this if you want exact output to match the PDF
    // for (int i = 0; i < CAT_COUNT; i++)
    // {
    //     printStatus(clowder[i]);
    // }
    
    //There was no need for 2 for loops imo
    
    delete [] clowder;

    return 0;
}

void printStatus(Cat &cat)
{
    std::cout << cat.getName() << " has "
              << cat.getLives() << " lives." << std::endl;
}