#include "timestables.h"
#include "arrays.h"
#include <stdio.h>

void generateTable(int num, int *table)
{
    int i;
    for (i = 0; i < MAX_TABLE_SIZE; i++)
    {
        table[i] = i * num;
    }
}

void printTable(int num, int *table)
{
    printf("%-2d times table\n‑‑‑‑‑‑‑‑‑‑‑‑‑‑\n", num);
    int i;
    for (i = 0; i < MAX_TABLE_SIZE; i++)
    {
        printf("%-2d * %-2d = %d\n", num, i, *(table + i));
    }
    printf("The mean for this table is %f\n\n", mean(MAX_TABLE_SIZE, table));
}

void printTables(int **tables)
{
    int i;
    for (i = 0; i <= MAX_TIMES_TABLE; i++)
    {
        printTable(i, tables[i]);
    }
}