#include "cat.h"
#include <iostream>

Cat::Cat(): name("Tom"), lives(9){
     std::cout << "Default constructor called... \n";
};

Cat::Cat(std::string name): name(name), lives(9){
     std::cout << "Constructor called with name... \n";
};

Cat::Cat(std::string name, unsigned int lives) : name(name), lives(lives){
    std::cout << "Constructor called with name and lives... \n";
};

Cat::~Cat(){
    std::cout << "Destructor called... \n";
}

void Cat::setName(std::string const name){
    std::cout << "setName called... \n";
    this->name = name;
}

void Cat::setLives(unsigned int const lives){
    std::cout << "setLives called... \n";
    if(lives >= this->lives){
        return;
    }
    else if ((this->lives > 0) && (lives == 0))
    {
        setName("The Cat formerly known as " + getName());
    }
    
    this->lives = lives;
}

std::ostream &operator<<(std::ostream &os, const Cat& cat){
    os << cat.name << cat.lives;
    return os;
}

bool operator==(const Cat& lhs, const Cat& rhs){
    if((lhs.name == rhs.name) && (lhs.lives == rhs.lives)){
        return true;
    }
    return false;
}

bool operator<(const Cat &lhs, const Cat &rhs){
    if(lhs.name == rhs.name){
        if(lhs.lives < rhs.lives){
            return true;
        }
        else{
            return false;
        }
    } else if(lhs.name < rhs.name){
        return true;
    }
    else{
        return false;
    }
}
