#ifndef CAT_H
#define CAT_H
#include <string>
#include <sstream>
#include <functional>

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

    friend std::ostream &operator<<(std::ostream &os, const Cat &cat);

    friend bool operator==(const Cat& lhs, const Cat& rhs);
    
    friend bool operator<(const Cat &lhs, const Cat &rhs);
};

namespace std
{
    template <>
    struct hash<Cat>
    {
        size_t operator()(const Cat &obj) const
        {
            std::stringstream stream;
            stream << obj;
            
            size_t output = std::hash<std::string>{}(stream.str());
            // integer and return it...
            return output;
        }
    };
}

#endif