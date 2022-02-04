#include <stdio.h>
#include <stdlib.h>
#include "timestables.h"

int main(int argc, char *argv[])
{
    int *times_tables[13];
    // int values[MAX_TABLE_SIZE];
    int i;
    for(i = 0; i < MAX_TABLE_SIZE; i++){
        times_tables[i] = malloc(sizeof(int)*MAX_TABLE_SIZE);
        generateTable(i, times_tables[i]);
    }
    // int* values = malloc(sizeof(int)*MAX_TABLE_SIZE);
    // generateTable(num, values);
    // printTable(num, values);
    printTables(times_tables);

    for(i = 0; i < MAX_TABLE_SIZE; i++){
        free(times_tables[i]);
    }
    return 0;
}
