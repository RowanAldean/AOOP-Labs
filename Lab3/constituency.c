#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "constituency.h"

void constructConstituency(struct Constituency *const obj,
                           char const *name,
                           unsigned int *const neighbours,
                           unsigned int numNeighbours)
{
    //Clearing any existing data in the object pointer
    obj->name = NULL;
    obj->neighbours = NULL;
    obj->numNeighbours = 0;

    //Malloc sufficient storage for name and neighbours array
    obj->name = malloc(sizeof(name) * sizeof(char));
    obj->neighbours = malloc(numNeighbours * sizeof(unsigned int));

    //Copy the passed in memory values to the addresses
    //We now use strlen() to not copy over the terminator char "\0".
    memcpy(obj->name, name, strlen(name) * sizeof(char));
    memcpy(obj->neighbours, neighbours, numNeighbours * sizeof(unsigned int));

    obj->numNeighbours = numNeighbours;
}

void destructConstituency(struct Constituency *const obj)
{
    if (obj->name != NULL)
    {
        free(obj->name);
        obj->name = NULL;
    }
    if (obj->neighbours != NULL)
    {
        free(obj->neighbours);
        obj->neighbours = NULL;
    }
    obj->numNeighbours = 0;
}

void printConstituency(struct Constituency *const obj)
{
    printf("%s | %d neighbours | [", obj->name, obj->numNeighbours);
    int i;
    for (i = 0; i < obj->numNeighbours; i++)
    {
        printf(" %d ", obj->neighbours[i]);
    }
    printf("] \n");
}

struct Constituency * copyConstituencies(struct Constituency *all,
                                        const unsigned int numConstituencies)
{
    struct Constituency *output = (struct Constituency*) malloc(numConstituencies * sizeof(struct Constituency));
    int i;
    for(i = 0; i < numConstituencies; i++){
        struct Constituency *source = &all[i];
        constructConstituency(&output[i], source->name, source->neighbours, source->numNeighbours);
    }
    return output;
}