#ifndef CONSTITUENCY_H
#define CONSTITUENCY_H
/*
If we pack this to 1 byte then we will save 4 bytes but due to the
unaligned object data, there'd be performance implications when accessing our
pointers as the word size is likely 8 bytes for our system. 
If we were going to pack then what's best (imo) is to pack(4) instead of pack(1).
*/
struct Constituency
{
    char *name;                 //8 bytes
    unsigned int *neighbours;   //8 bytes
    unsigned int numNeighbours; //4 bytes
    //24 total (as the end is padded to 8 bytes)
    //#pragma pack adjusts the alignment of this padding and thus we can reduce size
};

void constructConstituency(struct Constituency *const obj,
                           char const *name,
                           unsigned int *const neighbours,
                           unsigned int numNeighbours);

void destructConstituency(struct Constituency *const obj);

void printConstituency(struct Constituency *const obj);

struct Constituency *copyConstituencies(struct Constituency all[],
                                        const unsigned int numConstituencies);

#endif