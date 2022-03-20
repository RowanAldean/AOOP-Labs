// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: 973765
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------

#include "wallet.h"

// TODO Write a Wallet constructor that takes no parameters and constructs an
//  empty wallet.
//
// Example:
//  Wallet wObj{};

Wallet::Wallet() : categoryList() {}

// TODO Write a function, size, that takes no parameters and returns an unsigned
//  int of the number of categories in the Wallet contains.
//
// Example:
//  Wallet wObj{};
//  auto size = wObj.size();
unsigned int Wallet::size() const
{
    return categoryList.size();
}
// TODO Write a function, empty, that takes no parameters and returns true
//  if the number of categories in the Wallet is zero, false otherwise.
//
// Example:
//  Wallet wwObj{};
//  auto isEmpty = wObj.empty();
bool Wallet::empty() const
{
    return categoryList.empty();
}

// TODO Write a function, newCategory, that takes one parameter, a category
//  identifier, and returns the Category object as a reference. If an object
//  with the same identifier already exists, then the existing object should be
//  returned. Throw a std::runtime_error if the Category object cannot be
//  inserted into the container.
//
// Example:
//  Wallet wObj{};
//  wObj.newCategory("categoryIdent");
Category &Wallet::newCategory(const std::string catIdent)
{
    auto it = std::find_if(categoryList.begin(), categoryList.end(),
                           [&catIdent](Category &someCategory)
                           { return someCategory.getIdent() == catIdent; });
    if (it != categoryList.end())
    {
        //found it
        auto index = std::distance(categoryList.begin(), it);
        return categoryList.at(index);
    }
    else
    {
        //doesn't exist
        Category newCategoryMade(catIdent);
        try
        {
            categoryList.push_back(newCategoryMade);
            return categoryList.back();
        }
        catch (const std::exception &ex)
        {
            throw std::runtime_error("Category cannot be inserted into this wallet for some reason.");
        }
    }
}

// TODO Write a function, addCategory, that takes one parameter, a Category
//  object, and returns true if the object was successfully inserted. If an
//  object with the same identifier already exists, then the contents should be
//  merged and then return false. Throw a std::runtime_error if the Category
//  object cannot be inserted into the container for whatever reason.
//
// Example:
//  Wallet wObj{};
//  Category cObj{"categoryIdent"};
//  wObj.addCategory(cObj);

bool Wallet::addCategory(Category &newCat)
{
    std::string newCatID = newCat.getIdent();
    auto it = std::find_if(categoryList.begin(), categoryList.end(),
                           [&newCatID](Category someCategory)
                           { return someCategory.getIdent() == newCatID; });
    if (it != categoryList.end())
    {
        //found it
        auto index = std::distance(categoryList.begin(), it);
        newCat += categoryList.at(index);
        // I implemented addition between items to merge entry lists together and retain the values for the lhs.
        categoryList.at(index) = newCat;
        //The above keeps the newItem values (if there are duplicates), otherwise combines the entry lists.
        return false;
    }
    else
    {
        try
        {
            categoryList.push_back(newCat);
        }
        catch (const std::exception &ex)
        {
            throw std::runtime_error("Item cannot be inserted into this category for some reason.");
        }
        return true;
    }
}

// TODO Write a function, getCategory, that takes one parameter, a Category
//  identifier and returns the Category. If no Category exists, throw an
//  appropriate exception.
//
// Example:
//  Wallet wObj{};
//  wObj.newCategory("categoryIdent");
//  auto cObj = wObj.getCategory("categoryIdent");

Category &Wallet::getCategory(const std::string &catIdent)
{
    auto it = std::find_if(categoryList.begin(), categoryList.end(),
                           [catIdent](Category someCategory)
                           { return someCategory.getIdent() == catIdent; });
    if (it != categoryList.end())
    {
        //found it
        auto index = std::distance(categoryList.begin(), it);
        return categoryList.at(index);
    }
    else
    {
        throw DoesntExistException<Wallet>(catIdent, "Wallet");
    }
}

// TODO Write a function, deleteCategory, that takes one parameter, a Category
//  identifier, and deletes it from the container, and returns true if the
//  Category was deleted. If no Category exists, throw an appropriate exception.
//
// Example:
//  Wallet wObj{};
//  wObj.newCategory("categoryIdent");
//  wObj.deleteCategory("categoryIdent");

bool Wallet::deleteCategory(const std::string &catIdent)
{
    auto it = std::find_if(categoryList.begin(), categoryList.end(),
                           [catIdent](Category someCategory)
                           { return someCategory.getIdent() == catIdent; });
    if (it != categoryList.end())
    {
        //found it
        categoryList.erase(it);
        return true;
    }
    else
    {
        throw DoesntExistException<Wallet>(catIdent, "Wallet");
    }
}

// TODO Write a function, load, that takes one parameter, a std::string,
//  containing the filename for the database. Open the file, read the contents,
//  and populates the container for this Wallet. If the file does open throw an
//  appropriate exception (either std::runtime_error or a derived class).
//
// A note on clashes:
//  If you encounter two categories with the same key, the categories should be
//  merged (not replaced!). If you encounter two items with the same key in the
//  same category, the items should be merged (not replaced!). If you encounter
//  two entries with the same key in the same item, the entries should be merged
//  (undefined as to which value is picked). Two items in different categories
//  can have the same key, as can two entries in different items.
//
// JSON formatting:
//  The JSON file has the following format (see the sample database.json file
//  also provided with the coursework framework):
//    {
//      "Category 1" : {
//        "Item 1":  {
//          "detail 1 key": "detail 1 value",
//          "detail 2 key": "detail 2 value",
//          ...
//        },
//        "Item 2":  {
//          "detail 1 key": "detail 1 value",
//          "detail 2 key": "detail 2 value"
//        },
//        ...
//      },
//      "Category 2": {
//        "Item 1": {
//          "detail 1 key": "detail 1 value"
//        }
//        ...
//      }
//    }
//
// More help:
//  To help you with this function, I've selected the nlohmann::json
//  library that you must use for your coursework. Read up on how to use it
//  here: https://github.com/nlohmann/json. You may not use any other external
//  library other than the one I have provided. You may choose to process the
//  JSON yourself without the help of the library but I guarantee this will be
//  more work.
//
//  Understanding how to use external libraries is part of this coursework! You
//  will need to use this file to deserialize the JSON from string
//  to the JSON object provided by this library. Don't just look at the code
//  provided below, or in the README on the GitHub and despair. Google search,
//  look around, try code out in a separate file to all figure out how to use
//  this library.
//
//  Once you have deserialized the JSON string into an object, you will need to
//  loop through this object, constructing Category and Item objects according
//  to the JSON data in the file.
//
// Example:
//  Wallet wObj{};
//  wObj.load("database.json");

void Wallet::load(const std::string filename)
{
    std::ifstream databaseFile(filename, std::ifstream::binary);
    json myjson;
    databaseFile >> myjson;
    //So this is 1 category
    // std::cout << myjson.items().begin() << "is the first category element"
    //           << "\n";

    for (auto &el : myjson.items())
    {
        // Category is el.key
        // el.value is the item list
        Category newCat(el.key());
        json categories = el.value();
        for (auto &cat : categories.items())
        {
            //Item id is the el.key
            //el.value is the key:value entries
            //So we can use add entry with the key and val as args.
            Item newItem(cat.key());
            json items = cat.value();
            for (auto &entry : items.items())
            {
                newItem.addEntry(entry.key(), entry.value());
            }
            newCat.addItem(newItem);
        }
        addCategory(newCat);
    }
    databaseFile.close();
}

// TODO Write a function ,save, that takes one parameter, the path of the file
//  to write the database to. The function should serialise the Wallet object
//  as JSON.
//
// Example:
//  Wallet wObj{};
//  wObj.load("database.json");
//  ...
//  wObj.save("database.json");
void Wallet::save(const std::string filename) const
{
    std::ofstream newfile;
    newfile.open(filename);
    try
    {
        newfile << str();
    }
    catch (std::exception &e)
    {
        std::cout << "This is what " << e.what() << "\n";
    }
    newfile.close();
}

// TODO Write an == operator overload for the Wallet class, such that two
//  Wallet objects are equal only if they have the exact same data.
//
// Example:
//  Wallet wObj1{};
//  Wallet wObj2{};
//  if(wObj1 == wObj2) {
//    ...
//  }
bool operator==(const Wallet &lhs, const Wallet &rhs)
{
    if ((lhs.categoryList == rhs.categoryList))
    {
        return true;
    }
    return false;
}

// TODO Write a function, str, that takes no parameters and returns a
//  std::string of the JSON representation of the data in the Wallet.
//
// Hint:
//  See the coursework specification for how this JSON should look.
//
// Example:
//  Wallet wObj{};
//  std::string s = wObj.str();
std::string Wallet::str() const {
    std::vector<Category> ourList = categoryList;
    json jwallet;
    for (Category &cat : ourList)
    {
        json catJson = json::parse(cat.str());
        jwallet.emplace(cat.getIdent(), catJson);
    }
    return jwallet.dump();
}
