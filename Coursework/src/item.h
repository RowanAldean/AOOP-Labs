// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: 973765
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------
// An Item class contains multiple 'entries' as
// key/value pairs (e.g., a key might be 'username'
// and a value would be the username, another might be
// 'url' and the value is the website address the
// username is for.
// -----------------------------------------------------

#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>
#include <map>
#include "lib_json.hpp"
using json = nlohmann::json;

class Item
{
private:
    std::string identifier;
    //Here a map is the clearest and most sensible container to use.
    std::map<std::string, std::string> entries;

public:
    Item(std::string identifier);

    std::string getEntry(std::string const key) const;

    //Return the length of the entries map.
    unsigned int size() const;

    //Checks if entries are empty
    bool empty() const;

    void setIdent(std::string newIdentifier);

    std::string getIdent() const;

    bool addEntry(const std::string key, const std::string value);

    bool deleteEntry(const std::string key);

    friend bool operator==(const Item &lhs, const Item &rhs);
    
    std::string str() const;

    Item operator+=(const Item& rhs);
    
    friend Item operator+(Item lhs, const Item &rhs);
};

//Defined here is a custom exception - it could be defined in a seperate file but this would
// change our build and setup config so this seemed sensible for simplicity.
template<typename T>
class DoesntExistException : public std::out_of_range
{
private:
    std::string searchInput;
    std::string containerName;

public:
    DoesntExistException(const std::string searched, const std::string parentContainer) : out_of_range("Entry key is out of range"), searchInput(searched),
                                                                             containerName(parentContainer) {}

    virtual void describe(std::ostream &os) const
    {
        os << "The following search criterion does not exist:"
           << "\n"
           << typeid(T).name() << "  container: " << containerName
           << "Search query: " << searchInput;
    }
};

#endif // ITEM_H
