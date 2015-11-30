
#include "globals.h"


double RHS[N_R][N_Z],RHS_p[N_R][N_Z];


//multigr--------------------------------------------


double u_phi_prev[N_R][N_Z],u_phi_star[N_R][N_Z],
       u_r_prev[N_R][N_Z],u_r_star[N_R][N_Z],
u_z_prev[N_R][N_Z],u_z_star[N_R][N_Z],u_r_prime[N_R][N_Z],u_z_prime[N_R][N_Z];


double div_prev[N_R][N_Z], div_0[N_R][N_Z], p_prev[N_R][N_Z],
       p_prime[N_R][N_Z];

 double Re=30.0;

 double OMEGA=0.1;

  double dr=1.0/40;
  double dz=1.0/40;


  double dt=0.0015;


 
  int itn=0;
  int clear_w=1.0;


  float rx=0;
  float ry=0;
  int mx0,my0;
  int rotate=0;
  float rx0=0;
  float ry0=0;
 double d_temp;
 double mouse_x,mouse_y;

double r_2g=0.0;//cg res
