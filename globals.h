

//just a test comment
#ifndef GLOBALS_H
#define GLOBALS_H

 //for multigrid
 #define N_R 40
 #define N_Z 40



 #define U_TAU 1.0


 #define W_WIDTH 800
 #define W_HEIGHT 800

 #define RES2_MIN 0.000001

#define VIEW_U_R_PREV 1
#define VIEW_U_PHI_PREV 2
#define VIEW_U_Z_PREV 3
#define VIEW_U_R 4
#define VIEW_U_PHI 5
#define VIEW_U_Z 6
#define VIEW_DIV0 7
#define VIEW_DIV  8
#define VIEW_PHI  9



extern double RHS[N_R][N_Z],RHS_p[N_R][N_Z];


//multigr--------------------------------------------


extern double u_phi_prev[N_R][N_Z],u_phi_star[N_R][N_Z],
       u_r_prev[N_R][N_Z],u_r_star[N_R][N_Z],
       u_z_prev[N_R][N_Z],u_z_star[N_R][N_Z],u_r_prime[N_R][N_Z],u_z_prime[N_R][N_Z];
;


extern double div_prev[N_R][N_Z],p_prev[N_R][N_Z],
       p_prime[N_R][N_Z],div_0[N_R][N_Z];
extern double Re;



extern  double dr;
extern  double dz;


extern  double dt;

extern double OMEGA;

extern  int itn;
extern  int clear_w;


extern  float rx;
extern  float ry;
extern  int mx0,my0;
extern  int rotate;
extern  float rx0;
extern  float ry0;
extern double d_temp;
extern double mouse_x,mouse_y;

extern double r_2g;//cg res
#endif
