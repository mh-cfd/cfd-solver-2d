

#include <stdio.h>
#include <stdlib.h>


#include "interp.h"



//this is data for iterations, first index is to ditiguish between a,b,phi, see defines.
double t_it[NX+1][NY+1][NZ+1],it_2[(NX-1)/2+1][(NY-1)/2+1][(NZ-1)/2+1];
double c_[NX+NY+NZ+1],f_[NX+NY+NZ+1],up_,down_;




//the date is transfered through the function f,  dim- dimension of an array






double s_(double x)
{

   if (x<=-2.0)
     return 0;
   else
   if ((x>-2)&&(x<=-1))
    return (2.0+x)*(2.0+x)*(2.0+x);
   else
   if ((x>-1)&&(x<=0))
     return 1.0+3.0*(1.0+x)+3.0*(1.0+x)*(1.0+x)- 3.0*(1.0+x)*(1.0+x)*(1.0+x);
   else
   if ((x>0)&&(x<=1))
     return 1.0+3.0*(1.0-x)+3.0*(1.0-x)*(1.0-x)- 3.0*(1.0-x)*(1.0-x)*(1.0-x);
   else 
   if((x>1)&&(x<=2))
     return (2.0-x)*(2.0-x)*(2.0-x);
   else
   if (x>2.0)
     return 0;
   else return 0;
 

}


void s_sweep(int dim)
{


  int i;



  
  double a_[NX+NY+NZ],y[NX+NY+NZ];
  





  a_[2]=4.0; y[2]=f_[2]-f_[1]/6.0+down_/6.0;


  for (i=3;i<=dim;i++)
  {

    a_[i]=4.0-1.0/a_[i-1];
    
    y[i]=f_[i]-y[i-1]/a_[i-1];

    
  }



  c_[dim+1]=f_[dim+1]/6.0-up_/6.0;



  for (i=dim;i>1;i--)
  {

    c_[i]=(y[i]-c_[i+1])/a_[i];


  }

  c_[1]=f_[1]/6.0-down_/6.0;

  c_[0]=down_+2.0*c_[1]-c_[2];

  c_[dim+2]=up_+2.0*c_[dim+1]-c_[dim];






}




double S__(double x,int dim) //0..N
{
  
  int i,j;

  double ff;

  ff=x+1.0;

  j=(int) ff;

  double sum=0;


  sum=0.0;


  for (i=j-1;i<=j+2;i++)
  {




   if ((i>=0)&&(i<=dim+2))
     {
       sum+=s_(ff-(i))*c_[i];

       // printf("i=%d j=%d c(i)=%f %f sum=%f \n",i,j,c_[i],s_(ff-(i)),sum);
     }
  }


 
  return sum;
}




double S_(double x) //0..N
{

  int i,j;

  double ff;

  ff=x+1.0;

  j=(int) ff;

  double sum=0;





  for (i=j-1;i<=j+2;i++)
  {




    //   if ((i>=0)&&(i<=dim+2))
     {
    sum+=s_(ff-(i))*c_[i];

        printf("i=%d j=%d c(i)=%f %f \n",i,j,c_[i],ff-i);
     }
  }
  return sum;
}


//lev is an upper level must be 2 or 4 or 8
void inter2(int lev_)
{

  int i,j,k,dim;
  double dd,DX,DY;

  

 
  //сначала пробегаем по каждой строчке грубой сетки, с инетрполяцией сплайном, чтобы 
  //интерполировалась второая производная, на краях задаем значение второй производной
  //так чтобы она было равна rhs, так как перпендикулярные производные на границе равны нулю
  for (j=0;j<=(NY-1)/lev_;j++)
    {

     for (k=0;k<=(NZ-1)/lev_;k++)
     {



       dim=(NX-1)/lev_;


      //f and up_,down_ are silently sent to sweep
       switch(lev_)
       {
        case 2:
	  for (i=0;i<=dim;i++)
	    f_[i+1]=it_2[i][j][k];
	  break;


        default:
	  assert((1<0)&&(lev_<0));

       }

  

      //s"=6(c-1-c0+c1)/h^2
       down_=-RHS[0][j*2][k*2]*lev_*lev_*dx*dx/6.0;
       up_=-RHS[NX-1][j*2][k*2]*lev_*lev_*dx*dx/6.0;
    


       s_sweep(dim);//rows

       for (i=0;i<=dim*2;i++)
        {

	   t_it[i][j*2][k*2]=S_(i*0.5);
	}
     }
    }

  

  for (j=0;j<=(NX-1)/lev_;j++)
    {

     for (k=0;k<=(NZ-1)/lev_;k++)
     {


      dim=(NY-1)/lev_;

      switch(lev_)
      {
       case 2:
       for (i=0;i<=dim;i++)
	 f_[i+1]=it_2[j][i][k];
       break;

     

      }

      

       down_=-RHS[j*2][0][k*2]*lev_*lev_*dy*dy/6.0;
       up_= -RHS[j*2][NY-1][k*2]*lev_*lev_*dy*dy/6.0;
		 
      



      s_sweep(dim);//columns

         for (i=0;i<=dim*2;i++)
	 {

	   t_it[j*2][i][k*2]=S_(i*0.5);
	 }
     }
    }

  
  for (i=0;i<=(NX-1)/lev_;i++)
    {

     for (j=0;j<=(NY-1)/lev_;j++)
     {


      dim=(NZ-1)/lev_;

      switch(lev_)
      {
       case 2:
       for (k=0;k<=dim;k++)
	 f_[k+1]=it_2[i][j][k];
       break;

      }

      

       down_=-RHS[i*2][j*2][0]*lev_*lev_*dz*dz/6.0;
       up_= -RHS[i*2][j*2][NZ-1]*lev_*lev_*dz*dz/6.0;
		 
      



      s_sweep(dim);//columns

         for (k=0;k<=dim*2;k++)
	 {

	   t_it[i*2][j*2][k]=S_(k*0.5);
	 }
     }
    }


  
//сначала для точек в середине граней вычислеям плоский лаплас, так чтбы он блы равен сумме средних вторых производных.

  DX=dx*(dim-1);
  DY=dy*(dim-1);
  dd=2.0/(DX*DX)+2.0/(DY*DY);

double lapl_temp;

  for (k=1;k<(NZ-1)/lev_;k++)
  {

   for (i=0;i<(NX-1)/lev_;i++)
   {
    for (j=0;j<(NY-1)/lev_;j++)
    {


      // 1. xy edges k=k*2=const
    
      lapl_temp=0.5*( (t_it[i*2][j*2][k*2]+t_it[i*2+2][j*2][k*2]-2.0*t_it[i*2+1][j*2][k*2])+
		      (t_it[i*2][j*2+2][k*2]+t_it[i*2+2][j*2+2][k*2]-2.0*t_it[i*2+1][j*2+2][k*2]) )/(dx*dx) +

               	0.5*( (t_it[i*2][j*2][k*2]+t_it[i*2][j*2+2][k*2]    -2.0*t_it[i*2][j*2+1][k*2])+
		      (t_it[i*2+2][j*2][k*2]+t_it[i*2+2][j*2+2][k*2]-2.0*t_it[i*2+2][j*2+1][k*2]) )/(dy*dy);


      t_it[i*2+1][j*2+1][k*2] = ( -lapl_temp + (t_it[i*2+2][j*2+1][k*2]  + t_it[i*2][j*2+1][k*2])/(dx*dx) + 
			     (t_it[i*2+1][j*2+2][k*2] + t_it[i*2+1][j*2][k*2])/(dy*dy))*dx*dx*dy*dy/(2.0*(dx*dx+dy*dy));


  
    }
  }
  }
  

  for (k=0;k<(NZ-1)/lev_;k++)
  {

   for (i=0;i<(NX-1)/lev_;i++)
   {
    for (j=1;j<(NY-1)/lev_;j++)
    {


      // 1. xz edges j=j*2=const
    
      lapl_temp=0.5*( (t_it[i*2][j*2][k*2]+t_it[i*2+2][j*2][k*2]-2.0*t_it[i*2+1][j*2][k*2])+
		      (t_it[i*2][j*2][k*2+2]+t_it[i*2+2][j*2][k*2+2]-2.0*t_it[i*2+1][j*2][k*2+2]) )/(dx*dx) +

            	0.5*( (t_it[i*2][j*2][k*2]+t_it[i*2][j*2][k*2+2]    -2.0*t_it[i*2][j*2][k*2+1])+
		      (t_it[i*2+2][j*2][k*2]+t_it[i*2+2][j*2][k*2+2]-2.0*t_it[i*2+2][j*2][k*2+1]) )/(dz*dz);

    
      t_it[i*2+1][j*2][k*2+1] = ( -lapl_temp + (t_it[i*2+2][j*2][k*2+1]  + t_it[i*2][j*2][k*2+1])/(dx*dx) + 
			     (t_it[i*2+1][j*2][k*2+2] + t_it[i*2+1][j*2][k*2])/(dz*dz))*dx*dx*dz*dz/(2.0*(dx*dx+dz*dz));


  
    }
  }
  }



  for (k=0;k<(NZ-1)/lev_;k++)
  {

   for (i=1;i<(NX-1)/lev_;i++)
   {
    for (j=0;j<(NY-1)/lev_;j++)
    {


      // 1. yz edges i=i*2=const
    
      lapl_temp=0.5*( (t_it[i*2][j*2][k*2]+t_it[i*2][j*2][k*2+2]-2.0*t_it[i*2][j*2][k*2+1])+
		      (t_it[i*2][j*2+2][k*2]+t_it[i*2][j*2+2][k*2+2]-2.0*t_it[i*2][j*2+2][k*2+1]) )/(dz*dz) +


               	0.5*( (t_it[i*2][j*2][k*2]+t_it[i*2][j*2+2][k*2]-2.0*t_it[i*2][j*2+1][k*2])+
		      (t_it[i*2][j*2][k*2+2]+t_it[i*2][j*2+2][k*2+2]-2.0*t_it[i*2][j*2+1][k*2+2]) )/(dy*dy);
       


      t_it[i*2+1][j*2][k*2+1] = ( -lapl_temp + (t_it[i*2][j*2+2][k*2+1]  + t_it[i*2][j*2][k*2+1])/(dy*dy) + 
			     (t_it[i*2][j*2+1][k*2+2] + t_it[i*2][j*2+1][k*2])/(dz*dz))*dy*dy*dz*dz/(2.0*(dy*dy+dz*dz));


  
    }
  }
  }


//теперь для центра кубиков, вычисляем значения исходя из того чтобы лаплас был равен в этих точках rhs


// это может быть неправильно когда мы принципиально понимаем, что уравнение еще не сошлось.
  for (k=0;k<(NZ-1)/lev_;k++)
  {

   for (i=0;i<(NX-1)/lev_;i++)
   {
    for (j=0;j<(NY-1)/lev_;j++)
    {


      t_it[i*2+1][j*2+1][k*2+1] = ( RHS[i*2+1][j*2+1][k*2+1] +
				    (t_it[i*2+2][j*2+1][k*2+1]  + t_it[i*2][j*2+1][k*2+1])/(dx*dx)+
                             (t_it[i*2+1][j*2+2][k*2+1]  + t_it[i*2+1][j*2][k*2+1])/(dy*dy) + 
			     (t_it[i*2+1][j*2+1][k*2+2] + t_it[i*2+1][j*2+1][k*2])/(dz*dz))*dx*dx*dy*dy*dz*dz/(2.0*(dx*dx+dy*dy+dz*dz));


  
    }
  }
  }


}

