
#include <stdio.h>
#include <stdlib.h>

#include  <GL/gl.h>
#include  <GL/glu.h>
#include  <GL/glut.h>/* glut.h includes gl.h and glu.h*/
#include  <math.h>
#include <time.h>
#include "globals.h"


#include "phi_mult.h"


//#include <sys/time.h>



void save_fields();
void load_fields();



void display(void);
void sweep_init();
void init();


void sweep();
int view=0;


double ck=0.10;











void get_div_prev(void)

{

    int i,j,k;

    double divmax,lapl_phi,div_1,dudx,dvdy,dwdz;

    divmax=0.0;


    double rur[N_R][N_Z];

    for (j=0;j<N_Z;j++)
    {

        for (i=0;i<N_R;i++)
        {

            rur[i][j]=u_r_prev[i][j]*i*dr;


        }
    }


    for (j=1;j<N_Z-1;j++)
    {

        for (i=1;i<N_R-1;i++)
        {








            div_prev[i][j]= ddr(rur,i,j)/(i*dr)+ddz(u_z_prev,i,j);



            if (fabs(div_prev[i][j])>divmax)
                divmax=fabs(div_prev[i][j]);

        }
    }




    printf ("divmax=%lE \n",divmax);


}




void get_div_0(void)

{

    int i,j,k;

    double divmax,lapl_phi,div_1,dudx,dvdy,dwdz;

    divmax=0.0;


    double rur[N_R][N_Z];

    for (j=0;j<N_Z;j++)
    {

        for (i=0;i<N_R;i++)
        {

            rur[i][j]=u_r_prev[i][j]*i*dr;


        }
    }


    for (j=1;j<N_Z-1;j++)
    {

        for (i=1;i<N_R-1;i++)
        {








            div_0[i][j]= ddr(rur,i,j)/(i*dr)+ddz(u_z_prev,i,j);



            if (fabs(div_0[i][j])>divmax)
                divmax=fabs(div_0[i][j]);

        }
    }




    printf ("div0max=%lE \n",divmax);


}






void display(void)
{

    int i,j,k,l;


    double l_2,tx,ty,tx0,ty0,vx,vy,v0x,v0y;
    /* clear window */


    // if (clear_w==1)
    glClear(GL_COLOR_BUFFER_BIT);


    glLoadIdentity();

    // glTranslatef(0,0.4,0);
    // glRotatef(-90,0,0,1);
    glRotatef(ry,1.0,0,0);
    glRotatef(rx,0.0,1.0,0);

    glColor3f(1,1,1);



       for (i=1;i<N_R-1;i++)
    {

        glBegin(GL_TRIANGLE_STRIP);


        for (j=1;j<N_Z-1;j++)
        {




            if (view==VIEW_DIV0)
                l_2=ck*(div_0[i][j]);

            if (view==VIEW_DIV)
                l_2=ck*(div_prev[i][j]);


            glColor3f(l_2,l_2,-l_2);

            glVertex2f(dr*i,dz*j);





            if (view==VIEW_DIV0)
                l_2=ck*(div_0[i+1][j]);

            if (view==VIEW_DIV)
                l_2=ck*(div_prev[i+1][j]);


            glColor3f(l_2,l_2,-l_2);



            glVertex2f(dr*(i+1),dz*j);
        }


        glEnd();
    }







    for (i=0;i<N_R;i++)
    {

        glBegin(GL_LINES);


        for (j=0;j<N_Z;j++)
        {




            glColor3f(1,1,1);

            glVertex2f(dr*i,dz*j);


            glColor3f(0.0,0.0,0.0);



            glVertex3f(dr*i+ck*(u_r_prev[i][j]),dz*j+ck*(u_z_prev[i][j]),ck*(u_phi_prev[i][j]));
        }


        glEnd();
    }




    for (i=0;i<N_R;i++)
    {

        glBegin(GL_LINES);


        for (j=0;j<N_Z;j++)
        {




            glColor3f(1,0,0);

            glVertex2f(dr*i,dz*j);


            glColor3f(0.0,0.0,0.0);



            glVertex3f(dr*i+ck*(u_r_prime[i][j]),dz*j+ck*(u_z_prime[i][j]),ck*(0));
        }


        glEnd();
    }

    glColor3f(1,1,1);

    glBegin(GL_LINE_LOOP);

    glVertex3f(0,0,0);
    glVertex3f(dr*(N_R-1),0,0);
    glVertex3f(dr*(N_R-1),dz*(N_Z-1),0);
    glVertex3f(0,dz*(N_Z-1),0);
    glEnd();



    glPointSize(3.0);

    glLineWidth(1.0);

    glutSwapBuffers();

}

void m_m(int x,int y)
{

    if (rotate==1)
    {
        rx=rx0+0.5*(x-mx0);
        ry=ry0+0.5*(y-my0);


    }

    glutPostRedisplay();


}



void m_d(int button, int state,int x, int y)
{

    if (state==GLUT_UP)
    {
        rotate=0;
        rx0=rx;
        ry0=ry;

    }
    if (state==GLUT_DOWN)
    {


        rotate=1;

        mx0=x;
        my0=y;



    }



    mouse_x=(1.0*x)/W_WIDTH;

    mouse_y=(W_HEIGHT-(1.0*y))/W_HEIGHT;

    glutPostRedisplay();
}

void kb(unsigned char key, int x, int y)
{
    int i,j,k,nn,n;
    double m,sum;
    double max_err=0.0;
    if (key=='.')
    {


        ck*=1.1;


    }


    if (key==',')
    {


        ck/=1.1;


    }


    if (key=='1')
    {

        view=VIEW_DIV;
        printf("viewing div_prev \n");

    }


    if (key=='2')
    {

        view=VIEW_DIV0;
        printf("viewing div_0 \n");

    }

/*
    if (key=='3')
    {

        view=VIEW_W;
        printf("viewing w \n");

    }



    if (key=='4')
    {

        view=VIEW_U1;
        printf("viewing u1 \n");

    }

    if (key=='5')
    {

        view=VIEW_V1;
        printf("viewing v1 \n");

    }


    if (key=='6')
    {

        view=VIEW_W1;
        printf("viewing w1 \n");

    }


    if (key=='7')
    {

        view=VIEW_DIV0;
        printf("viewing div0 \n");

    }


    if (key=='8')
    {

        view=VIEW_DIV;
        printf("viewing div \n");

    }


    if (key=='9')
    {

        view=VIEW_PHI;
        printf("viewing phi \n");

    }



*/






    if (key=='s')
    {

      //  for(int i=0;i<100;i++)
        sweep();
    }







    glutPostRedisplay();
}




void sweep_init()
{
    int i,j,k;
    double App,R_2,b,m;

    for (i=0;i<N_R;i++)
    {

        for (j=0;j<N_Z;j++)
        {



            u_phi_prev[i][j]=0; //0.6*rand()/RAND_MAX-0.30;
            u_phi_star[i][j]=0;
            u_r_prev[i][j]=0; //0.6*rand()/RAND_MAX-0.30;
            u_r_star[i][j]=0;

            u_z_prev[i][j]=0; //0.6*rand()/RAND_MAX-0.30;
            u_z_star[i][j]=0;


            div_prev[i][j]=0;
            p_prev[i][j]=0;
            p_prime[i][j]=0;


        }


    }
}

void bcuvw()
{
    int i_max=N_R/3;
    for (int j=0; j<N_Z; j++)
    {
        u_r_prev[0][j]=0;
        u_phi_prev[0][j]=0;
        u_z_prev[0][j]=u_z_prev[1][j];
        u_z_prev[N_R-1][j]=0;
        u_phi_prev[N_R-1][j]=0;
        u_r_prev[N_R-1][j]=0;
    }
    for (int i=0; i<N_R; i++)
    {
        u_r_prev[i][0]=0;
        u_phi_prev[i][0]=0;
        u_z_prev[i][0]=0;
        u_z_prev[i][N_Z-1]=0;

        if (i<i_max)
            u_phi_prev[i][N_Z-1]=OMEGA*dr*i;
        else
            u_phi_prev[i][N_Z-1]=u_phi_prev[i][N_Z-2];

        u_r_prev[i][N_Z-1]=u_r_prev[i][N_Z-2];
    }
}


//double ddr()


void sweep()
{
    bcuvw();
    /*===============================================================================
     * =================U_PHI==========================================================
     * ==============================================================================*/
    double duphidr[N_R][N_Z];
    for (int i=1; i<N_R-1; i++)
    {
        for (int j=1; j<N_Z-1; j++)
        {
            duphidr[i][j]=ddr(u_phi_prev,i,j);//(u_phi_prev[i][j]-u_phi_prev[i-1][j])/dr;
        }
    }
    double duphidz[N_R][N_Z];
    for (int i=1; i<N_R-1; i++)
    {
        for (int j=1; j<N_Z; j++)
        {
            duphidz[i][j]=ddz(u_phi_prev,i,j); //(u_phi_prev[i][j]-u_phi_prev[i-1][j])/dz;
        }
    }
    double dduphiddz[N_R][N_Z];
    for (int i=1; i<N_R-1; i++)
    {
        for (int j=1; j<N_Z-1; j++)
        {
            dduphiddz[i][j]=ddz(duphidz,i,j); //(duphidz[i][j]-duphidz[i-1][j])/dz;
        }
    }
    double druphidr[N_R][N_Z];
    for (int i=1; i<N_R-1; i++)
    {
        for (int j=1; j<N_Z-1; j++)
        {
            druphidr[i][j]=(dr*(i+1)*u_phi_prev[i+1][j]-dr*(i-1)*u_phi_prev[i-1][j])/(2.0*dr*dr*i);
        }
    }
    double ddruphiddr[N_R][N_Z];
    for (int i=1; i<N_R-1; i++)
    {
        for (int j=1; j<N_Z-1; j++)
        {
            ddruphiddr[i][j]=ddr(druphidr, i, j); //(druphidr[i][j]-druphidr[i-1][j])/dr;
        }
    }
    for (int i=1; i<N_R-1; i++)
    {
        for (int j=1; j<N_Z-1; j++)
        {
            RHS[i][j]=-u_r_prev[i][j]*duphidr[i][j]-u_r_prev[i][j]*u_phi_prev[i][j]/(dr*i)-u_z_prev[i][j]*duphidz[i][j]+1/Re*(ddruphiddr[i][j]+dduphiddz[i][j]);
        }
    }

    for (int i=1; i<N_R-1; i++)
    {
        for (int j=1; j<N_Z-1; j++)
        {
            u_phi_star[i][j]=RHS[i][j]*dt+u_phi_prev[i][j];
            u_phi_prev[i][j]=u_phi_star[i][j];
        }
    }
    /*===============================================================================
  * =================U_R==========================================================
  * ==============================================================================*/

    double durdz[N_R][N_Z];    //dur/dz
    for (int i=1; i<N_R-1; i++)
    {
        for (int j=1; j<N_Z-1; j++)
        {
            durdz[i][j]=ddz(u_r_prev, i, j); //(u_r_prev[i][j]-u_r_prev[i-1][j])/dz;
        }
    }
    double dduddz[N_R][N_Z];        //d^2ur/dz^2
    for (int i=1; i<N_R-1; i++)
    {
        for (int j=1; j<N_Z-1; j++)
        {
            dduddz[i][j]=ddz(durdz,i,j); //(durdz[i][j]-durdz[i-1][j])/dz;
        }
    }
    double durdr[N_R][N_Z];  //dur/dr
    for (int i=1; i<N_R-1; i++)
    {
        for (int j=1; j<N_Z-1; j++)
        {
            durdr[i][j]=ddr(u_r_prev, i,j); //(u_r_prev[i][j]-u_r_prev[i-1][j])/dr;
        }
    }
    double drurdr[N_R][N_Z];  // d(r*ur)/dr
    for (int i=1; i<N_R-1; i++)
    {
        for (int j=1; j<N_Z-1; j++)
        {

            drurdr[i][j]=(dr*(i+1)*u_r_prev[i+1][j]-dr*(i-1)*u_r_prev[i-1][j])/(2.0*dr*dr*i);
        }
    }
    double ddruddr[N_R][N_Z];
    for (int i=1; i<N_R-1; i++)
    {
        for (int j=1; j<N_Z-1; j++)
        {
            ddruddr[i][j]=ddr(drurdr,i,j); //(drurdr[i][j]-drurdr[i-1][j])/dr;
        }
    }
    for (int i=1; i<N_R-1; i++)
    {
        for (int j=1; j<N_Z-1; j++)
        {
            RHS[i][j]=-u_r_prev[i][j]*durdr[i][j]+u_phi_prev[i][j]/(dr*i)-u_z_prev[i][j]*durdz[i][j]+1/Re*(ddruddr[i][j]+dduddz[i][j]);
        }
    }
    for (int i=1; i<N_R-1; i++)
    {
        for (int j=1; j<N_Z-1; j++)
        {
            u_r_star[i][j]=RHS[i][j]*dt+u_r_prev[i][j];
            u_r_prev[i][j]=u_r_star[i][j];
        }
    }
    /*===============================================================================
     * =================U_Z==========================================================
     * ==============================================================================*/

    double duzdr[N_R][N_Z];  //dur/dr
    for (int i=1; i<N_R-1; i++)
    {
        for (int j=1; j<N_Z-1; j++)
        {
            duzdr[i][j]=ddr(u_z_prev,i,j); //(u_z_prev[i][j]-u_z_prev[i-1][j])/dr;
        }
    }
    double duzdz[N_R][N_Z];
    for (int i=1; i<N_R-1; i++)
    {
        for (int j=1; j<N_Z-1; j++)
        {
            duzdz[i][j]=ddz(u_z_prev,i,j); //(u_z_prev[i][j]-u_z_prev[i-1][j])/dz;
        }
    }
    double dduzddr[N_R][N_Z];
    for (int i=1; i<N_R-1; i++)
    {
        for (int j=1; j<N_Z-1; j++)
        {
            dduzddr[i][j]=(dr*(i+1)*duzdr[i+1][j]-dr*(i-1)*duzdr[i-1][j])/(2.0*dr);
        }
    }
    double dduzddz[N_R][N_Z];
    for (int i=1; i<N_R-1; i++)
    {
        for (int j=1; j<N_Z-1; j++)
        {
            dduzddz[i][j]=ddz(duzdz,i,j); //(duzdz[i][j]-duzdz[i-1][j])/dz;
        }
    }
    for (int i=1; i<N_R-1; i++)
    {
        for (int j=1; j<N_Z-1; j++)
        {
            RHS[i][j]=-0.01-u_r_prev[i][j]*duzdr[i][j]-u_z_prev[i][j]*duzdz[i][j]+1/Re*(dduzddr[i][j]/(i*dr)+dduzddz[i][j]);
        }
    }

    for (int i=1; i<N_R-1; i++)
    {
        for (int j=1; j<N_Z-1; j++)
        {
            u_z_star[i][j]=RHS[i][j]*dt+u_z_prev[i][j];
            u_z_prev[i][j]=u_z_star[i][j];

        }

    }


    get_div_prev();

    get_div_0();

    for (int i=1; i<N_R-1; i++)
    {
        for (int j=1; j<N_Z-1; j++)
        {
            div_prev[i][j]=(u_r_prev[i+1][j]-u_r_prev[i-1][j])/(2.0*dr)+(u_z_prev[i][j+1]-u_z_prev[i][j-1])/(2.0*dz);//+ddz(p_prime,i,j);
            div_0[i][j]=div_prev[i][j];
        }
    }

    jacobi(p_prime,div_prev,100);





    for (int i=1; i<N_R-1; i++)
    {
        for (int j=1; j<N_Z-1; j++)
        {
            u_z_star[i][j]=u_z_prev[i][j]-ddz(p_prime,i,j);
            u_r_star[i][j]=u_r_prev[i][j]-ddr(p_prime,i,j);

            u_z_prime[i][j]=ddz(p_prime,i,j);
            u_r_prime[i][j]=ddr(p_prime,i,j);

            u_z_prev[i][j]=u_z_star[i][j];
            u_r_prev[i][j]=u_r_star[i][j];
        }
    }

  get_div_prev();


/*  for (int i=1; i<N_R-1; i++)
  {
      for (int j=1; j<N_Z-1; j++)
      {
          div_prev[i][j]=(u_r_star[i+1][j]-u_r_star[i-1][j])/(2.0*dr)+(u_z_star[i][j+1]-u_z_star[i][j-1])/(2.0*dz);//+ddz(p_prime,i,j);
        //  div_0[i][j]=div_prev[i][j];
      }
  }*/
}



void init()
{
    /* set clear color to black */
    glClearColor (0.0, 0.0, 0.0, 0.0);

    /* set fill color to white */
    glColor3f(1.0, 1.0, 1.0);

    /* set up standard orthogonal view with clipping */
    /* box as cube of side 2 centered at origin */
    /* This is default view and these statement could be removed */
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(-0.1, 1.1, -0.1,1.1, -10.0, 10.0);
    glMatrixMode (GL_MODELVIEW);

    sweep_init();

get_div_0();
}

int main(int argc, char** argv)
{
    /* Initialize mode and open a window in upper left corner of screen */
    /* Window title is name of program (arg[0]) */


    srand(time(NULL));
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(W_WIDTH,W_HEIGHT);
    glutInitWindowPosition(0,0);
    glutCreateWindow("simple");
    glutDisplayFunc(display);
    glutMotionFunc(m_m);
    glutMouseFunc(m_d);
    glutKeyboardFunc(kb);
    init();
    glutMainLoop();
}
