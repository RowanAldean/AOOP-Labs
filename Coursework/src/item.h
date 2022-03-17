// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: <STUDENT NUMBER>
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

//TODO: Use generics for everything instead of just string?
class Item
{
private:
    std::string identifier;
    std::map<std::string, std::string> entries;

public:
    Item(std::string identifier);

    /*We are returning by value (copy) and so const isn't needed as 
    the caller can do as they please with their copy without
    impacting our entry data.*/
    std::string getEntry(std::string const key);

    //Return the length of the entries map.
    unsigned int size();

    //Checks if entries are empty
    bool empty();

    void setIdent(std::string newIdentifier);

    std::string getIdent();

    bool addEntry(const std::string key, const std::string value);

    bool deleteEntry(const std::string key);

    friend bool operator==(const Item &lhs, const Item &rhs);
    
    std::string str();

    Item operator+=(const Item& rhs);
    
    friend Item operator+(Item lhs, const Item &rhs);
};

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
           << typeid(T).name() << ": " << containerName
           << "Entry key: " << searchInput;
    }
};

#endif // ITEM_H
