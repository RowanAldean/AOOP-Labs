#include <stdio.h>
#include <stdlib.h>
#include "fibonacci.c"

int main(int argc, char* argv[]) {
    /*strtol(input string, end pointer, base) - this function is the same as atoi(string) but doesn't just return
    undefined if there's an error (so the error handling is better).*/
    int fibnumber = strtol(argv[1], NULL, 10); //String to Long utility function - could use ASCII to Int (atoi()) in the same way
    int result = fibonacci(fibnumber);
    printf("Fibonacci of %d = %d\n", fibnumber, result);
    return 0;
}