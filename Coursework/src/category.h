// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: 973765
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------
// A category contains one or more Items, each with
// their own identifier ('ident').
// -----------------------------------------------------

#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>
#include <vector>
#include <algorithm>
#include "item.h"
class Category
{
private:
    std::string identifier;
    //A vector was used as the itemID -> itemObj relationship is implemented in an Item object
    //thus there is no real need for a map (despite the faster lookup and easier JSON implementation).
    std::vector<Item> itemList;

public:
    Category(std::string identifier);

    unsigned int size() const;

    bool empty() const;

    std::string getIdent() const;

    void setIdent(std::string newIdent);

    Item &newItem(std::string itemIdent);

    bool addItem(Item &newItem);

    Item &getItem(const std::string itemToGet);

    bool deleteItem(const std::string itemToDelete);

    friend bool operator==(const Category &lhs, const Category &rhs);

    std::string str() const;

    Category operator+=(const Category& rhs);
    
    friend Category operator+(Category lhs, const Category &rhs);
};

#endif // CATEGORY_H
