#include "rand.h"
#include <stdlib.h>
#include <time.h>

unsigned int RandZ (unsigned char places)
{
    unsigned char j=1;
    double d=0.;
    if (places)
    {
        if (places>9) places = 1 + places%9; // unsigned places cannot be <0
        d = ((double) time(NULL)) / rand();
        //  extract all positions to right of comma
        d = d - (unsigned int) d;
        // shift the positions to left
        while (d*=10, j<places) j++;
    }
    else
    {
        srand(time(NULL));  //  if places == 0 then init
    }
    return (unsigned int) d;  // unsigned int = xxx xxx xxx
}