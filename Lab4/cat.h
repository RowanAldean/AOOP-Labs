#ifndef CAT_H
#define CAT_H
#include <string>
class Cat
{
private:
    std::string name;
    unsigned int lives;

public:
    Cat(std::string name);
    Cat(std::string name, unsigned int lives);
    ~Cat();

    std::string getName() const{
        return name;
    }

    unsigned int getLives() const{
        return lives;
    }
};

#endif