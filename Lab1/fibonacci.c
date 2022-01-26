#include "fibonacci.h"

int fibonacci(int input){
    if(input == 0){
        return 0;
    }
    else if(input == 1){
        return 1;
    }
    else{
        return (fibonacci(input-1) + fibonacci(input-2));
    }
}