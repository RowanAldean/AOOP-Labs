// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: <STUDENT NUMBER>
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

#include "371pass.h"
#include "lib_cxxopts.hpp"
#include "wallet.h"

// TODO Complete this function. You have been provided some skeleton code which
//  retrieves the database file name from cxxopts.
//  1. Load the database file by calling load() on a Wallet object
//  2. Parse the 'action' argument to decide what action should be taken (
//     create, read, update, or delete). Read is the easiest to implement, and
//     update is the hardest. The details of how these arguments work is in the
//     coursework specification.
//  4. Save the updated Wallet object to the JSON file if there have been
//     changes (calling save() on the Wallet object).
//
// Some commented out code has been provided. Using some of this will be
// demonstrated in the coursework video on Canvas. Remember, this coursework is
// meant to be challenging and testing your understanding of programming in C++.
// Part of the challenge is figuring things out on your own. That is a major
// part of software development.
//
// Example:
//  int main(int argc, char *argv[]) { return App::run(argc, argv); }
int App::run(int argc, char *argv[])
{
  auto options = App::cxxoptsSetup();
  auto args = options.parse(argc, argv);

  // Print the help usage if requested
  if (args.count("help"))
  {
    std::cout << options.help() << '\n';
    return 0;
  }

  // Open the database and construct the Wallet
  const std::string db = args["db"].as<std::string>();
  Wallet wObj{};
  // Only uncomment this once you have implemented the load function!
  wObj.load(db);

  const Action a = parseActionArgument(args);
  switch (a)
  {
  case Action::CREATE:
    try
    {
      //Try to get category (this is needed!)
      const std::string categoryName = args["category"].as<std::string>();
      Category newCategory(categoryName);
      //Check if there's an item to add
      if (args.count("item"))
      {
        const std::string itemName = args["item"].as<std::string>();
        Item newItem(itemName);
        if (args.count("entry"))
        {
          std::string entryString = args["entry"].as<std::string>();
          std::vector<std::string> strings;      //A vector to hold the split strings (if any)
          std::stringstream stream(entryString); //Use a stream so we can look for a comma
          while (stream.good())
          {
            std::string substr;
            getline(stream, substr, ','); //get first string delimited by comma
            strings.push_back(substr);
          }
          std::string entryKey, entryValue;
          if (strings.size() >= 2)
          {
            //There is some value
            entryValue = strings.at(1);
          }
          //Set the key to the first thing before a comma (or the whole string).
          entryKey = strings.at(0);
          newItem.addEntry(entryKey, entryValue);
          newCategory.addItem(newItem);
          wObj.addCategory(newCategory);
        }
        else
        {
          newCategory.addItem(newItem);
          wObj.addCategory(newCategory);
        }
      }
      else
      {
        wObj.addCategory(newCategory);
      }
      exit(0);
    }
    catch (cxxopts::OptionException &e)
    {
      std::cout << e.what() << std::endl;
    }
    break;

  case Action::READ:
    if (args.count("category"))
    {
      std::string output;
      std::string searchCat = args["category"].as<std::string>();
      try
      {
        Category foundCat = wObj.getCategory(searchCat);
        if (args.count("item"))
        {
          std::string searchItem = args["item"].as<std::string>();
          Item foundItem = foundCat.getItem(searchItem);
          if (args.count("entry"))
          {
            std::string searchEntry = args["entry"].as<std::string>();
            output += foundItem.getEntry(searchEntry);
          }
          else
          {
            output += foundItem.str();
          }
        }
        else
        {
          output += foundCat.str();
        }
        std::cout << output << std::endl;
      }
      catch (DoesntExistException<Wallet> &e)
      {
        std::cerr << "Error: invalid category argument(s)." << std::endl;
        exit(1);
      }
      catch (DoesntExistException<Category> &e)
      {
        std::cerr << "Error: invalid item argument(s)." << std::endl;
        exit(1);
      }
      catch (DoesntExistException<Item> &e)
      {
        std::cerr << "Error: invalid entry argument(s)." << std::endl;
        exit(1);
      }
    }
    else
    {
      std::cout << wObj.str() << std::endl;
    }
    exit(0);
    break;

  case Action::UPDATE:
    throw std::runtime_error("update not implemented");
    break;

  case Action::DELETE:
    if (args.count("category"))
    {
      std::string output;
      std::string searchCat = args["category"].as<std::string>();
      try
      {
        Category foundCat = wObj.getCategory(searchCat);
        if (args.count("item"))
        {
          std::string searchItem = args["item"].as<std::string>();
          if (args.count("entry"))
          {
            Item foundItem = foundCat.getItem(searchItem);
            std::string searchEntry = args["entry"].as<std::string>();
            foundItem.deleteEntry(searchEntry);
          }
          else
          {
            foundCat.deleteItem(searchItem);
          }
        }
        else
        {
          wObj.deleteCategory(searchCat);
        }
      }
      catch (DoesntExistException<Wallet> &e)
      {
        std::cerr << "Error: invalid category argument(s)." << std::endl;
        exit(1);
      }
      catch (DoesntExistException<Category> &e)
      {
        std::cerr << "Error: invalid item argument(s)." << std::endl;
        exit(1);
      }
      catch (DoesntExistException<Item> &e)
      {
        std::cerr << "Error: invalid entry argument(s)." << std::endl;
        exit(1);
      }
    }
    else
    {
      std::cerr << "Error: missing category, item or entry argument(s)." << std::endl;
      exit(1);
    }
    exit(0);
    break;

  default:
    throw std::runtime_error("Unknown action not implemented");
  }

  return 0;
}

// Create a cxxopts instance. You do not need to modify this function.
//
// Example:
//  auto options = App::cxxoptsSetup();
//  auto args = options.parse(argc, argv);
cxxopts::Options App::cxxoptsSetup()
{
  cxxopts::Options cxxopts("371pass", "Student ID: " + STUDENT_NUMBER + "\n");

  cxxopts.add_options()(
      "db", "Filename of the 371pass database",
      cxxopts::value<std::string>()->default_value("database.json"))(

      "action", "Action to take, can be: 'create', 'read', 'update', 'delete'.",
      cxxopts::value<std::string>())(

      "category",
      "Apply action to a category (e.g., if you want to add a category, set the"
      " action argument to 'add' and the category argument to your chosen"
      " category identifier).",
      cxxopts::value<std::string>())(

      "item",
      "Apply action to an item (e.g., if you want to add an item, set the "
      "action argument to 'add', the category argument to your chosen category "
      "identifier and the item argument to the item identifier).",
      cxxopts::value<std::string>())(

      "entry",
      "Apply action to an entry (e.g., if you want to add an entry, set the "
      "action argument to 'add', the category argument to your chosen category "
      "identifier, the item argument to your chosen item identifier, and the "
      "entry argument to the string 'key,value'). If there is no comma, an "
      "empty entry is inserted. If you are simply retrieving an entry, set the "
      "entry argument to the 'key'. If you are updating an entry key, use a : "
      "e.g., oldkey:newkey,newvalue.",
      cxxopts::value<std::string>())(

      "h,help", "Print usage.");

  return cxxopts;
}

// TODO Rewrite this function so that it works. This function should
//  case-insensitively check the action argument retrieved from cxxopts and
//  convert this to a value from the ACTION enum. If an invalid value is given
//  in a string, throw an std::invalid_argument exception.
//
// Example:
//  auto options = App::cxxoptsSetup();
//  auto args = options.parse(argc, argv);
//  App::Action action = parseActionArgument(args);
App::Action App::parseActionArgument(cxxopts::ParseResult &args)
{
  std::string input = args["action"].as<std::string>();
  std::transform(input.begin(), input.end(), input.begin(),
                 [](unsigned char c)
                 { return std::tolower(c); });
  if (input == "read")
  {
    return Action::READ;
  }
  else if (input == "create")
  {
    return Action::CREATE;
  }
  else if (input == "delete")
  {
    return Action::DELETE;
  }
  else if (input == "update")
  {
    return Action::UPDATE;
  }
  else
  {
    throw std::invalid_argument("action");
  }
}

// TODO Write a function, getJSON, that returns a std::string containing the
//  JSON representation of a Wallet object.
//
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function).
//
// Example:
//  Wallet wObj{};
//  std::cout << getJSON(wObj);
std::string App::getJSON(Wallet &wObj)
{
  // Only uncomment this once you have implemented the functions used!
  return wObj.str();
}

// TODO Write a function, getJSON, that returns a std::string containing the
//  JSON representation of a specific Category in a Wallet object.
//
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function).
//
// Example:
//  Wallet wObj{};
//  std::string c = "category argument value";
//  std::cout << getJSON(wObj, c);
std::string App::getJSON(Wallet &wObj, const std::string &c)
{
  // Only uncomment this once you have implemented the functions used!
  auto cObj = wObj.getCategory(c);
  return cObj.str();
}

// TODO Write a function, getJSON, that returns a std::string containing the
//  JSON representation of a specific Item in a Wallet object.
//
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function).
//
// Example:
//  Wallet wObj{};
//  std::string c = "category argument value";
//  std::string i = "item argument value";
//  std::cout << getJSON(wObj, c, i);
std::string App::getJSON(Wallet &wObj, const std::string &c,
                         const std::string &i)
{
  // Only uncomment this once you have implemented the functions used!
  auto cObj = wObj.getCategory(c);
  const auto iObj = cObj.getItem(i);
  return iObj.str();
}

// TODO Write a function, getJSON, that returns a std::string containing the
//  JSON representation of a specific Entry in a Wallet object.
//
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function).
//
// Example:
//  Wallet wObj{};
//  std::string c = "category argument value";
//  std::string i = "item argument value";
//  std::string e = "entry argument value";
//  std::cout << getJSON(wObj, c, i, e);
std::string App::getJSON(Wallet &wObj, const std::string &c,
                         const std::string &i, const std::string &e)
{
  // Only uncomment this once you have implemented the functions used!
  auto cObj = wObj.getCategory(c);
  auto iObj = cObj.getItem(i);
  return iObj.getEntry(e);
}