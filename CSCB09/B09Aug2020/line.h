#ifndef _LINE_H
#define _LINE_H

typedef struct {
    double m, c; // as in y=mx+c
} line;

double compute_y(const line *L, double x);

#endif