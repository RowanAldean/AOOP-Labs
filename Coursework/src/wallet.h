// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: 973765
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------
// The root object that holds all data for 371pass. This
// class contains Categories, which in turn hold Items,
// which hold a mapping of entries.
// -----------------------------------------------------

#ifndef WALLET_H
#define WALLET_H
#include <fstream>
#include "category.h"
class Wallet
{
private:
    //Similarly to categories, a vector seemed most sensible; however I understand why a map may have been chosen.
    std::vector<Category> categoryList;

public:
    Wallet();

    unsigned int size() const;

    bool empty() const;

    Category &newCategory(const std::string catIdent);

    bool addCategory(Category &catToAdd);

    Category &getCategory(const std::string &catIdent);

    bool deleteCategory(const std::string &catIdent);

    void load(const std::string fileName);

    void save(const std::string fileName) const;

    friend bool operator==(const Wallet &lhs, const Wallet &rhs);

    std::string str() const;
};

#endif // WALLET_H
