# **CSC371 Coursework** <font size=2>Rowan Aldean (973765)</font>
### **Summary**
I believe all the desired functionality has been implemented and all tests and Autograder outputs have passed. The implementation provides a simple CRUD system based on the CLI arguments provided with the build 371pass output file.
### **How to run the programme**
The coursework framework provided us with build files for both Windows and Unix-like systems (Linux/macOS). I have aimed to prevent altering these and thus the code has been structured in accordance with this aim. The code was developed using Linux (Manjaro) and g++ with the relevant build.sh file.

### **Remarks on design choice(s)**
- You'll find in [Item](src/item.cpp) and [Category](src/category.cpp) that I have overloaded the `+=` and `+` operators. After completing the coursework with this design I read into this choice on StackOverflow and it is generally seen as unconventional practice (albeit not *"wrong"* ) because it changes the meaning of `+=` to other developers. This choice doesn't impact the functionality of my code but it would have been wiser in retrospect to overload `insert()` or implement my own `append()`/custom function.

- The branching used in the [371pass](src/371pass.cpp) file is functional but can be difficult to follow. This is the nature of the coursework framework and lack of external non-standard libraries. I have tried to maintain a clear path throughout such that for all actions, you can see there is conditional logic looking for `category`,`item`,`entry` and relevant `else` statements after.

- To aim to reduce redundance I implemented a `tokenize()` function at the start of the [371pass.cpp](src/371pass.cpp) file. This would ideally be hidden in the relevant header file but due to the framework and the use of `#include 371pass.h` in multiple files it was causing multiple declaration warnings in the compiler. I feared this would impact my assessor and thus opted to place this utility function at the head of the file.

- There are instances where a `const` function is declared - `str()`- where I have created copies of member data on the stack. This has been done as we can't iterate over member data in a `const` function, and it makes sense that the relevant functions are `const` because they are not altering the objects state.

- Finally, I opted to use the `std::vector` container for lists of `Item` and `Category` where applicable. I did consider the `map` approach and understand the performance benefits (slight space overhead for increased lookup and sorting performance), however my choice came down to trying to follow good OOP relationship design. I don't think there is a need to store a identifier:object pair when this relationship is implemented in an object itself. I tried to separate responsibility and have an instance of an object act as a SSOT for a record in our JSON (no updating keys in maps besides for entries).