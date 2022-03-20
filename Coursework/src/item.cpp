// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: 973765
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------

#include "item.h"

// TODO Write a constructor that takes one parameter, a string identifier
//  and initialises the object and member data.
//
// Example:
//  Item iObj{"identIdent"};
Item::Item(std::string ident) : identifier(ident), entries(){};

// TODO Write a function, size, that takes no parameters and returns an unsigned
//  int of the number of entries in the Item contains.
//
// Example:
//  Item iObj{"identIdent"};
//  auto size = iObj.size();
unsigned int Item::size()
{
    return entries.size();
};

// TODO Write a function, empty, that takes no parameters and returns true
//  if the number of entries in the Item is zero, false otherwise.
//
// Example:
//  Item iObj{"identIdent"};
//  auto empty = iObj.empty();
bool Item::empty()
{
    return entries.empty();
};
// TODO Write a function, setIdent, that takes one parameter, a string for a new
//  Item identifier, and updates the member variable. It returns nothing.
//
// Example:
//  Item iObj{"identIdent"};
//  iObj.setIdent("identIdent2");
void Item::setIdent(std::string newIdent)
{
    identifier = newIdent;
}
// TODO Write a function, getIdent, that returns the identifier for the Item.
//
// Example:
//  Item iObj{"identIdent"};
//  auto ident = iObj.getIdent();
std::string Item::getIdent()
{
    return identifier;
};
// TODO Write a function, addEntry, that takes two parameters, an entry
//  key and value and returns true if the entry was inserted into the
//  container or false if the entry already existed and was replaced.
//
// Example:
//  Item iObj{"identIdent"};
//  iObj.addEntry("key", "value");
bool Item::addEntry(std::string key, std::string value)
{
    std::map<std::string, std::string>::iterator it = entries.find(key);
    if (it == entries.end())
    {
        //not found
        entries.insert(std::pair<std::string, std::string>(key, value));
        return true;
    }
    else
    {
        it->second = value;
        return false;
    }
}
// TODO Write a function, getEntry, that takes one parameter, an entry
//  key and returns it's value. If no entry exists, throw an appropriate
//  exception.
//
// Example:
//  Item iObj{"identIdent"};
//  iObj.addEntry("key", "value");
//  auto value = iObj.getEntry("key");
std::string Item::getEntry(std::string keyToGet)
{
    std::map<std::string, std::string>::iterator it = entries.find(keyToGet);
    if (it != entries.end())
    {
        //found
        return it->second;
    }
    else
    {
        throw DoesntExistException<Item>(keyToGet, identifier);
    }
}
// TODO Write a function, deleteEntry, that takes one parameter, an entry
//  key, deletes it from the container, and returns true if the Item was
//  deleted. If no entry exists, throw an appropriate exception.
//
// Example:
//  Item iObj{"identIdent"};
//  iObj.addEntry("key", "value");
//  iObj.deleteEntry("key");
bool Item::deleteEntry(std::string keyToDelete)
{
    std::map<std::string, std::string>::iterator it = entries.find(keyToDelete);
    if (it != entries.end())
    {
        //found
        entries.erase(it);
        return true;
    }
    else
    {
        throw DoesntExistException<Item>(keyToDelete, identifier);
    }
}
// TODO Write an == operator overload for the Item class, such that two
//  Item objects are equal only if they have the same identifier and same
//  entries.
//
// Example:
//  Item iObj1{"identIdent"};
//  iObj1.addEntry("key", "value");
//  Item iObj2{"identIdent2"};
//  if(iObj1 == iObj2) {
//    ...
//  }
bool operator==(const Item& lhs, const Item& rhs){
    if((lhs.identifier == rhs.identifier) && (lhs.entries == rhs.entries)){
        return true;
    }
    return false;
}

Item Item::operator+=(const Item& rhs){
    entries.insert(rhs.entries.begin(), rhs.entries.end());
    return *this;
}

//Implementing addition for items. The item on the left hand side will keep it's entry values.
Item operator+(Item base, const Item& newsource){
    base += newsource;
    return base;
}

// TODO Write a function, str, that takes no parameters and returns a
//  std::string of the JSON representation of the data in the Item.
//
// See the coursework specification for how this JSON should look.
//
// Example:
//  Item iObj{"itemIdent"};
//  std::string s = iObj.str();
std::string Item::str() const{
    json j_map(entries);
    // std::cout << identifier << " item has a string: " << j_map.dump() << std::endl;
    return j_map.dump();
}