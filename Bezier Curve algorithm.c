#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#define PI 3.14
float speed,theta=0;
void init()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0,500,0,500);
}
void bino(int n, int c[])
{
  int i,j;
  for(i=0;i<=n;i++)
  {
    c[i]=1;
    for(j=n;j>=i+1; j--)
    c[i]=c[i]*j;
    for(j=n-i;j>=2;j--)
    c[i]=c[i]/j;
  }
}
void bezier(int c[],int cp[][2],int n)
{
  float x,y,t,val;
  int i;
  glBegin(GL_POINTS);
  for(t=0;t<1.0;t+=0.01)
  {
    x=0;
    y=0;
    for(i=0;i<4;i++)
    {
      val=c[i]*pow(t,i)*pow(1-t,n-i);
      x=x+cp[i][0]*val;
      y=y+cp[i][1]*val;
    }
    glVertex2f(x,y);
  }
  glEnd();
}
void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  int c[4],k,n=3;
  int cp[4][2]={{100,400},{150,450},{250,350},{300,400}};
  cp[1][0] +=50*sin(theta * PI/180.0);
  cp[1][1] +=25*sin(theta * PI/180.0);
  cp[2][0] -= 50*sin((theta+30) * PI/180.0);
  cp[2][1] -= 50*sin((theta+30) * PI/180.0);
  cp[3][0] -= 25*sin(theta * PI/180.0);
  cp[3][1] += sin((theta-30) * PI/180.0);
  theta+=speed; //speed is controlled by menu
  glClear(GL_COLOR_BUFFER_BIT);
  glPointSize(5);
  bino(n,c);
  glPushMatrix();
  glLineWidth(5);//To set the width of a line
  glColor3f(1, 0.4, 0.2); //Indian flag: Orange color code
  for(int i=0;i<50;i++)
  {
    glTranslatef(0, -0.8, 0);
    bezier(c,cp,n);
  }
    glColor3f(1, 1, 1); //Indian flag: white color code
    for(int i=0;i<50;i++)
  {
    glTranslatef(0, -0.8, 0);
    bezier(c,cp,n);
  }
    glColor3f(0, 1, 0); //Indian flag: green color code
    for(int i=0;i<50;i++)
    {
      glTranslatef(0, -0.8, 0);
      bezier(c,cp,n);
    }
    glPopMatrix();
    glColor3f(0.7, 0.5,0.3);
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2f(100,400);
    glVertex2f(100,40);
    glEnd();
    glutPostRedisplay();
    glutSwapBuffers();
}
void mymenu(int option)
{
  if(option==1)
    speed=5;
  if(option==2)
    speed=1;
  glutPostRedisplay();
}
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(500,500);
  glutCreateWindow("Bezier Curve");
  glutDisplayFunc(display);
  glutCreateMenu(mymenu);
  glutAddMenuEntry("Faster waving",1);
  glutAddMenuEntry("Slower waving",2);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  init();
  glutMainLoop();
}
