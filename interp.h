


#ifndef INTERP_H
#define INTERP_H

#include "globals.h"
#include <math.h>
#include <assert.h>




extern double t_it[NX+1][NY+1][NZ+1],it_2[(NX-1)/2+1][(NY-1)/2+1][(NZ-1)/2+1];
extern double c_[NX+NY+NZ+1],f_[NX+NY+NZ+1],up_,down_;




void inter2(int lev_);
void s_sweep(int dim);
double S__(double x,int dim);
#endif
