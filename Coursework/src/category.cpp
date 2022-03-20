// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: 973765
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------

#include "category.h"

// TODO Write a constructor that takes one parameter, a string identifier
//  and initialises the object and member data.
//
// Example:
//  Category c{"categoryIdent"};
Category::Category(std::string ident) : identifier(ident), itemList() {}

// TODO Write a function, size, that takes no parameters and returns an unsigned
//  int of the number of Items in the Category contains.
//
// Example:
//  Category c{"categoryIdent"};
//  auto size = c.size();
unsigned int Category::size() const
{
    return itemList.size();
}

// TODO Write a function, empty, that takes no parameters and returns true
//  if the number of Items in the Category is zero, false otherwise.
//
// Example:
//  Category c{"categoryIdent"};
//  auto empty = c.empty();
bool Category::empty() const
{
    return itemList.empty();
}

// TODO Write a function, getIdent, that returns the identifier for the
//  Category.
//
// Example:
//  Category cObj{"categoryIdent"};
//  auto ident = cObj.getIdent();
std::string Category::getIdent() const
{
    return identifier;
}

// TODO Write a function, setIdent, that takes one parameter, a string for a new
//  Category identifier, and updates the member variable. It returns nothing.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.setIdent("categoryIdent2");
void Category::setIdent(const std::string newIdent)
{
    identifier = newIdent;
}

// TODO Write a function, newItem, that takes one parameter, an Item identifier,
//  (a string) and returns the Item object as a reference. If an object with the
//  same identifier already exists, then the existing object should be returned.
//  Throw a std::runtime_error if the Item object cannot be inserted into the
//  container for whatever reason.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("itemIdent");
Item &Category::newItem(const std::string itemIdent)
{
    auto it = std::find_if(itemList.begin(), itemList.end(),
                           [&itemIdent](Item &someItem)
                           { return someItem.getIdent() == itemIdent; });
    if (it != itemList.end())
    {
        //found it
        auto index = std::distance(itemList.begin(), it);
        return itemList.at(index);
    }
    else
    {
        //doesn't exist
        Item newItemMade(itemIdent);
        try
        {
            itemList.push_back(newItemMade);
            return itemList.back();
        }
        catch (const std::exception &ex)
        {
            throw std::runtime_error("Item cannot be inserted into this category for some reason.");
        }
    }
}

// TODO Write a function, addItem, that takes one parameter, an Item object,
//  and returns true if the object was successfully inserted. If an object with
//  the same identifier already exists, then the contents should be merged and
//  return false.
//
// Example:
//  Category cObj{"categoryIdent"};
//  Item iObj{"itemIdent"};
//  cObj.addItem(iObj);
bool Category::addItem(Item &newItem)
{
    std::string newID = newItem.getIdent();
    auto it = std::find_if(itemList.begin(), itemList.end(),
                           [&newID](Item &someItem)
                           { return someItem.getIdent() == newID; });
    if (it != itemList.end())
    {
        //found it
        auto index = std::distance(itemList.begin(), it);
        newItem += itemList.at(index);
        // I implemented addition between items to merge entry lists together and retain the values for the lhs.
        itemList.at(index) = newItem;
        //The above keeps the newItem values (if there are duplicates), otherwise combines the entry lists.
        return false;
    }
    else
    {
        try
        {
            itemList.push_back(newItem);
        }
        catch (const std::exception &ex)
        {
            throw std::runtime_error("Item cannot be inserted into this category for some reason.");
        }
        return true;
    }
}

// TODO Write a function, getItem, that takes one parameter, an Item
//  identifier (a string) and returns the Item as a reference. If no Item
//  exists, throw an appropriate exception.
//
// Hint:
//  See the test scripts for the exception expected.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("itemIdent");
//  auto iObj = cObj.getItem("itemIdent");
Item &Category::getItem(const std::string itemIdent)
{
    auto it = std::find_if(itemList.begin(), itemList.end(),
                           [&itemIdent](Item &someItem)
                           { return someItem.getIdent() == itemIdent; });
    if (it != itemList.end())
    {
        //found it
        auto index = std::distance(itemList.begin(), it);
        return itemList.at(index);;
    }
    else
    {
        throw DoesntExistException<Category>(itemIdent, identifier);
    }
}

// TODO Write a function, deleteItem, that takes one parameter, an Item
//  identifier (a string), deletes it from the container, and returns true if
//  the Item was deleted. If no Item exists, throw an appropriate exception.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("itemIdent");
//  bool result = cObj.deleteItem("itemIdent");
bool Category::deleteItem(const std::string itemIdent)
{
    auto it = std::find_if(itemList.begin(), itemList.end(),
                           [&itemIdent](Item &someItem)
                           { return someItem.getIdent() == itemIdent; });
    if (it != itemList.end())
    {
        //found it
        itemList.erase(it);
        std::cout << "Deleted an item" << std::endl;
        return true;
    }
    else
    {
        throw DoesntExistException<Category>(itemIdent, identifier);
    }
}

// TODO Write an == operator overload for the Category class, such that two
//  Category objects are equal only if they have the same identifier and same
//  Items.
//
// Example:
//  Category cObj1{"categoryIdent1"};
//  cObj1.newItem("itemIdent");
//  Category cObj2{"categoryIdent2"};
//  if(cObj1 == cObj2) {
//    ...
//  }
bool operator==(const Category &lhs, const Category &rhs)
{
    if ((lhs.identifier == rhs.identifier) && (lhs.itemList == rhs.itemList))
    {
        return true;
    }
    return false;
}

// These operator overloads represent how to merge two category objects
// I have learned that overloading this operator as opposed to the "append" method
// is not best practice as it changes the meaning of what += is typically.
// There is nothing inherently wrong about this approach, it's just not advised on SO.
Category Category::operator+=(const Category &rhs)
{
    for (auto &item : rhs.itemList)
    {
        Item newItem = (Item) item;
        addItem(newItem);
    }
    return *this;
}

//Implementing addition for items. The item on the left hand side will keep it's entry values.
Category operator+(Category base, const Category &newsource)
{
    base += newsource;
    return base;
}

// TODO Write a function, str, that takes no parameters and returns a
//  std::string of the JSON representation of the data in the Category.
//
// See the coursework specification for how this JSON should look.
//
// Example:
//  Category cObj{"categoryIdent"};
//  std::string s = cObj.str();
std::string Category::str() const
{
    json jcat;
    //Doing this means we can use the copy value as an iterator and thus
    //keep our function as a const (no altering of real data).
    std::vector<Item> ourList = itemList;
    for (Item &something : ourList)
    {
        json jsonItem = json::parse(something.str());
        jcat.emplace(something.getIdent(), jsonItem);
    }
    // std::cout << identifier << " category has a string: " << jcat.dump() << std::endl;
    return jcat.dump();
}