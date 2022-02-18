#include "cat.h"
#include <iostream>

Cat::Cat(std::string name): name(name), lives(9){
     std::cout << "Constructor called with name... \n";
};

Cat::Cat(std::string name, unsigned int lives) : name(name), lives(lives){
    std::cout << "Constructor called with name and lives... \n";
};

Cat::~Cat(){
    std::cout << "Destructor called... \n";
}

