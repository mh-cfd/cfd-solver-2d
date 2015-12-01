
#include <stdio.h>
#include <stdlib.h>

#include "phi_mult.h"
#include "globals.h"
#include <math.h>




/*

//calculate value on boundary from derivative value
double ddx_a(double var_[NX+1][NY+1][NZ+1],int i, int j,int k,double rhs)
{

    double res;

    if (i==0)
    {
        //      rhs=(-3.0*var_[i][j][k] + 4.0*var_[i+1][j][k] - var_[i+2][j][k])/(2.0*dx);
        res= (-rhs*2.0*dx+ 4.0*var_[i+1][j][k] - var_[i+2][j][k])/3.0;

    }else
    {

        if (i==NX-1)
        {

            //         rhs=(3.0*var_[i][j][k] - 4.0*var_[i-1][j][k] + var_[i-2][j][k])/(2.0*dx);
            res =(rhs*2.0*dx + 4.0*var_[i-1][j][k] - var_[i-2][j][k])/3.0;

        }else
        {

            res=0;

        }


    }


    return res;



}




double ddy_a(double var_[NX+1][NY+1][NZ+1],int i, int j,int k,double rhs)
{

    double res;

    if (j==0)
    {
        //    res=(-3.0*var_[i][j][k] + 4.0*var_[i][j+1][k] - var_[i][j+2][k])/2.0;
        res= (-rhs*2.0*dy+ 4.0*var_[i][j+1][k] - var_[i][j+2][k])/3.0;

    }else
    {

        if (j==NY-1)
        {

            //  res=(3.0*var_[i][j][k] - 4.0*var_[i][j-1][k] + var_[i][j-2][k])/2.0;

            res =(rhs*2.0*dy + 4.0*var_[i][j-1][k] - var_[i][j-2][k])/3.0;

        }else
        {

            res=0;

        }


    }



    return res;


}


double ddz_a(double var_[NX+1][NY+1][NZ+1],int i, int j,int k,double rhs)
{

    double res;

    if (k==0)
    {
        //      res=(-3.0*var_[i][j][k] + 4.0*var_[i][j][k+1] - var_[i][j][k+2])/2.0;
        res= (-rhs*2.0*dz+ 4.0*var_[i][j][k+1] - var_[i][j][k+2])/3.0;

    }else
    {

        if (k==NZ-1)
        {

            //         res=(3.0*var_[i][j][k] - 4.0*var_[i][j][k-1] + var_[i][j][k-2])/2.0;
            res =(rhs*2.0*dz + 4.0*var_[i][j][k-1] - var_[i][j][k-2])/3.0;

        }else
        {

            res=0;

        }


    }


    return res;




}
*/

double ddr(double var_[N_R][N_Z],int i, int j)
{

    double res;

    if (i==0)
    {
        res=(-3.0*var_[i][j] + 4.0*var_[i+1][j] - var_[i+2][j])/(dr*2.0);

    }else
    {

        if (i==N_R-1)
        {

            res=(3.0*var_[i][j] - 4.0*var_[i-1][j] + var_[i-2][j])/(dr*2.0);
        }else
        {

            res=(var_[i+1][j]-var_[i-1][j])/(2.0*dr);

        }


    }


    return res;



}


double ddz(double var_[N_R][N_Z],int i, int j)
{

    double res;

    if (j==0)
    {
        res=(-3.0*var_[i][j] + 4.0*var_[i][j+1] - var_[i][j+2])/(2.0*dz);

    }else
    {

        if (j==N_Z-1)
        {

            res=(3.0*var_[i][j] - 4.0*var_[i][j-1] + var_[i][j-2])/(2.0*dz);
        }else
        {

            res=(var_[i][j+1]-var_[i][j-1])/(2.0*dz);

        }


    }


    return res;



}




/*

double d2di_a(double var_[NX+1][NY+1][NZ+1],int i, int j,int k)
{

    double res;

    if (i==0)
    {
        res=1.0;//(var_[i][j][k] - 2.0*var_[i+1][j][k] + var_[i+2][j][k]);

    }else
    {

        if (i==NX-1)
        {

            res=1.0;//(var_[i][j][k] - 2.0*var_[i-1][j][k] + var_[i-2][j][k]);
        }else
        {

            res=-2.0;//(var_[i+1][j][k] - 2.0*var_[i][j][k] + var_[i-1][j][k]);

        }


    }



    return res;



}




double d2dj_a(double var_[NX+1][NY+1][NZ+1],int i, int j,int k)
{

    double res;

    if (j==0)
    {
        res=1.0;//(var_[i][j][k] - 2.0*var_[i+1][j][k] + var_[i+2][j][k]);

    }else
    {

        if (j==NY-1)
        {

            res=1.0;//(var_[i][j][k] - 2.0*var_[i-1][j][k] + var_[i-2][j][k]);
        }else
        {

            res=-2.0;//(var_[i+1][j][k] - 2.0*var_[i][j][k] + var_[i-1][j][k]);

        }


    }



    return res;



}


double d2dk_a(double var_[NX+1][NY+1][NZ+1],int i, int j,int k)
{

    double res;

    if (k==0)
    {
        res=1.0;//(var_[i][j][k] - 2.0*var_[i+1][j][k] + var_[i+2][j][k]);

    }else
    {

        if (k==NZ-1)
        {

            res=1.0;//(var_[i][j][k] - 2.0*var_[i-1][j][k] + var_[i-2][j][k]);
        }else
        {

            res=-2.0;//(var_[i+1][j][k] - 2.0*var_[i][j][k] + var_[i-1][j][k]);

        }


    }


    return res;




}






double d2di_res(double var_[NX+1][NY+1][NZ+1],int i, int j,int k)
{

    double res;

    if (i==0)
    {
        res=( - 2.0*var_[i+1][j][k] + var_[i+2][j][k]);

    }else
    {

        if (i==NX-1)
        {

            res=( - 2.0*var_[i-1][j][k] + var_[i-2][j][k]);
        }else
        {

            res=(var_[i+1][j][k] + var_[i-1][j][k]);

        }


    }



    return res;



}





double d2dj_res(double var_[NX+1][NY+1][NZ+1],int i, int j,int k)
{

    double res;

    if (j==0)
    {
        res=( - 2.0*var_[i][j+1][k] + var_[i][j+2][k]);

    }else
    {

        if (j==NY-1)
        {

            res=( - 2.0*var_[i][j-1][k] + var_[i][j-2][k]);
        }else
        {

            res=(var_[i][j+1][k]  + var_[i][j-1][k]);

        }


    }


    return res;




}


double d2dk_res(double var_[NX+1][NY+1][NZ+1],int i, int j,int k)
{

    double res;

    if (k==0)
    {
        res=( - 2.0*var_[i][j][k+1] + var_[i][j][k+2]);

    }else
    {

        if (k==NZ-1)
        {

            res=( - 2.0*var_[i][j][k-1] + var_[i][j][k-2]);
        }else
        {

            res=(var_[i][j][k+1]  + var_[i][j][k-1]);

        }


    }


    return res;




}


*/

double jacobi(double p[N_R][N_Z], double rhs[N_R][N_Z], int itn)
{
    int i,j,n;
    double res=0;

    double p_new[N_R][N_Z];

    double a,b_p,b_m,c_p,c_m;
    a=((2.0)/(dr*dr)+2.0/(dz*dz));
            b_p=-(1.0/(2.0*i*dr*dr))*(2.0*(i+1));
    b_m=-(1.0/(2.0*i*dr*dr))*(2.0*(i-1));
            c_p=-1.0/(dz*dz);
            c_m=-1.0/(dz*dz);


/*
            a=(2.0/(dr*dr)+ 2.0/(dz*dz));
            b_m=-1.0/(dr*dr); b_p=b_m;

            c_m=-1.0/(dz*dz); c_p=c_m;
*/

    for (i=0; i<N_R; i++)
        for (j=0; j<N_Z; j++)
        {
            //p[i][j]=0;


            p[i][j]=0.0;

            p_new[i][j]=0.0;
        }



    for(n=0;n<itn;n++)
    {
    for (i=1; i<N_R-1; i++)
        for (j=1; j<N_Z-1; j++)
        {
            //p[i][j]=0;


            p_new[i][j]=p[i][j];
            p[i][j]=-(rhs[i][j]-(b_p*p[i+1][j]+b_m*p[i-1][j]+c_p*p[i][j+1]+c_m*p[i][j-1]))
                              /a;

  /*         p_new[i][j]=(rhs[i][j]-(b_p*p[i+1][j]
                     +b_m*p[i-1][j]+c_p*p[i][j+1]+c_m*p[i][j-1]))
                    /a;


         /*   p_new[i][j]=rhs[i][j]+(
                         (1.0/(dz*dz))*(p[i+1][j]+p[i-1][j])
                    +(1.0/(dr*dr))*(p[i][j+1]+p[i][j-1]))
                     /(-2.0/(dz*dz)-2.0/(dr*dr));*/
        }

    for (i=1; i<N_R-1; i++)
        for (j=1; j<N_Z-1; j++)
        {
            //p[i][j]=0;
 res+=fabs(p[i][j]-p_new[i][j]);
// p[i][j]=p[i][j]*0.8+0.2*p_new[i][j];

        }

    //res/=(N_R*N_Z);
    printf("res=%f \n",res);
}

    return res;
}


double iter_phi_gs_bound(int in_) //poisson equation at the cell centers
{
/*

    int i,j,k,nn;



    double a,b,c,d,axb_max;



    a=dx*dx*2.0*(1.0/(dx*dx)+ 1.0/(dy*dy)+1.0/(dz*dz));
    b=-1.0*dx*dx/(dx*dx);
    c=-1.0*dx*dx/(dy*dy);
    d=-1.0*dx*dx/(dz*dz);

    axb_max=0.0;
    for (nn=0;nn<in_;nn++)
    {

        //neumann bc



        for (j=1;j<NY-1;j++)
        {


                phi_[0][j][k]=ddx_a(phi_,0,j,k,RHS[0][j][k]);
                phi_[NX-1][j][k]=ddx_a(phi_,NX-1,j,k,RHS[NX-1][j][k]);



        }



        for (i=1;i<NX-1;i++)
        {

            for (k=1;k<NZ-1;k++)
            {

                phi_[i][0][k]=ddy_a(phi_,i,0,k,RHS[i][0][k]);
                phi_[i][NY-1][k]=ddy_a(phi_,i,NY-1,k,RHS[i][NY-1][k]);


            }
        }




        for (i=1;i<NX-1;i++)
        {

            for (j=1;j<NY-1;j++)
            {

                phi_[i][j][0]=ddz_a(phi_,i,j,0,RHS[i][j][0]);
                phi_[i][j][NZ-1]=ddz_a(phi_,i,j,NZ-1,RHS[i][j][NZ-1]);


            }
        }


        for (i=1;i<NX-1;i++)
        {



            for (j=1;j<NY-1;j++)
            {

                for (k=1;k<NZ-1;k++)
                {



                    double d2phi_dx_a,d2phi_dy_a,d2phi_dz_a,d2phi_dx_res,d2phi_dy_res,d2phi_dz_res,phi_a,phi_res;

                    d2phi_dx_a=d2di_a(phi_,i,j,k)/(dx*dx);
                    d2phi_dy_a=d2dj_a(phi_,i,j,k)/(dy*dy);
                    d2phi_dz_a=d2dk_a(phi_,i,j,k)/(dz*dz);


                    d2phi_dx_res=d2di_res(phi_,i,j,k)/(dx*dx);
                    d2phi_dy_res=d2dj_res(phi_,i,j,k)/(dy*dy);
                    d2phi_dz_res=d2dk_res(phi_,i,j,k)/(dz*dz);


                    phi_a=d2phi_dx_a+d2phi_dy_a+d2phi_dz_a;

                    phi_res=d2phi_dx_res+d2phi_dy_res+d2phi_dz_res;




                    phi_[i][j][k]=-(phi_res+RHS[i][j][k])/phi_a;





                }
            }
        }








        for (i=1;i<NX-1;i++)
        {



            for (j=1;j<NY-1;j++)
            {

                for (k=1;k<NZ-1;k++)
                {
                    phi_[i][j][k]-=phi_[NX/2][NY/2][NZ/2];
                }
            }
        }










    }





    //___________________________________________________________
    printf ("axb_max=%lE \n",axb_max);
*/
    return 0;

}

