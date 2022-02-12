#include <stdlib.h>
#include <stdio.h>
#include "constituency.h"

int main()
{
    const int numConstituencies = 5;
    struct Constituency constituencies[numConstituencies];
    constructConstituency(
        &constituencies[0], "Swansea East",
        (unsigned int[]){1, 2, 3, 4}, 4);
    constructConstituency(
        &constituencies[1], "Swansea West",
        (unsigned int[]){0, 2}, 2);
    constructConstituency(
        &constituencies[2], "Gower",
        (unsigned int[]){0, 1, 3}, 3);
    constructConstituency(
        &constituencies[3], "Neath",
        (unsigned int[]){0, 2, 4}, 3);
    constructConstituency(
        &constituencies[4], "Aberavon",
        (unsigned int[]){0, 3}, 2);

    struct Constituency *copy = copyConstituencies(constituencies,
                                                   numConstituencies);
    int i;
    for (i = 0; i < numConstituencies; i++)
    {
        destructConstituency(&constituencies[i]);
    }

    struct Constituency most, least;
    for (i = 0; i < numConstituencies; i++)
    {
        if ((&copy[i])->numNeighbours > (&most)->numNeighbours)
        {
            most = copy[i];
        }
        if ((&copy[i])->numNeighbours < (&least)->numNeighbours || least.name == NULL)
        {
            least = copy[i];
        }
        printConstituency(&copy[i]);
    }

    //Print most
    printf("\n%s has the most bordering constituencies: \n", most.name);
    for (i = 0; i < most.numNeighbours; i++)
    {
        printf("%4s%s\n", "", copy[most.neighbours[i]].name);
    }
    //Print least
    printf("\n%s has the least bordering constituencies: \n", least.name);
    for (i = 0; i < least.numNeighbours; i++)
    {
        printf("%4s%s\n", "", copy[least.neighbours[i]].name);
    }

    free(copy);
}