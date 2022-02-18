#ifndef CAT_H
#define CAT_H
#include <string>
class Cat
{
private:
    std::string name;
    unsigned int lives;

public:
    Cat();
    Cat(std::string name);
    Cat(std::string name, unsigned int lives);
    ~Cat();

    std::string getName() const
    {
        return name;
    }

    unsigned int getLives() const
    {
        return lives;
    }

    void setName(std::string const name);

    void setLives(unsigned int const lives);
};

#endif