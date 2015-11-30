

#ifndef PHI_MULT_H
#define PHI_MULT_H

#include "globals.h"




double ddr(double var_[N_R][N_Z],int i, int j);
double ddz(double var_[N_R][N_Z],int i, int j);

double iter_phi_gs_bound(int in_);


double jacobi(double p[N_R][N_Z], double rhs[N_R][N_Z], int itn);




#endif
