#include <stdio.h>
#include "constituency.h"

int main() {
  struct Constituency test;
  constructConstituency(
    &test,
    "Swansea East",
    (unsigned int[]){1, 2, 3, 4},
    4);
  printConstituency(&test);
  
  printf("\n");
  
  destructConstituency(&test);
  
  return 0;
}