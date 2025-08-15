#ifndef UTILS_H
#define UTILS_H

#include <limits.h>
#include <cstdlib>

inline double random_double(){
    return ((double)rand() / (RAND_MAX) );
}

#endif