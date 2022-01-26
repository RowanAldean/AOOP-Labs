//Header files are used to access utility functions provided by the C language.
#include <stdio.h>

/**
 * C programs begin via a main function (in a hosted environment - an OS) and can take command line arguments.
 * @param argc Argument count - The number of command line arguments being passed in.
 * @param argv Argument vector - A pointer array that points to each argument that is passed in. It's equivalent to char** argv
 * @return An exit code - 0 represents normal exit, non-zero is abnormal.
 * There is no agreed upon convention in a main() function.
 * */
int main(int argc, char* argv[]){
    printf("Hello World!\n");
    //0 is simply the returned exit code in this case
    return 0;
}