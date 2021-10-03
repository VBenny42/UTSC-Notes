#ifndef _SOLVE_H
#define _SOLVE_H

#include "line.h"

typedef struct { 
    double x, y;
} point;

int solve(point *p, const line *L1, const line *L2);

#endif