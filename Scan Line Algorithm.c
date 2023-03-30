#include <stdio.h>
#include <GL/glut.h>
#define BLACK 0
float x1,x2,x3,x4,y1,y2,y3,y4;
void myinit()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0,500,0.0,500);
}
void draw_pixel(int x,int y,int value)
{
  glBegin(GL_POINTS);
  glVertex2i(x,y);
  glEnd();
}
void edge(float x1,float y1,float x2,float y2,int *le,int *re)
{
  float mx,x,temp;
  int i;
  if((y2-y1)<0)
  {
    temp=y1;
    y1=y2;
    y2=temp;
    temp=x1;
    x1=x2;
    x2=temp;
  }
  if((y2-y1)!=0)
    mx=(x2-x1)/(y2-y1);
  else
    mx=x2-x1;
    x=x1;
   for(i=y1;i<=y2;i++)
  {
    if(x<le[i])
    le[i]=x;
    if(x>re[i])
    re[i]=x;
    x+=mx;
  }
}
void scanfill(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float
y4)
{
  int le[500],re[500];
  int i,y;
  for(i=0;i<500;i++)
  {
    le[i]=500;
    re[i]=0;
  }
  edge(x1,y1,x2,y2,le,re);
  edge(x2,y2,x3,y3,le,re);
  edge(x3,y3,x4,y4,le,re);
  edge(x4,y4,x1,y1,le,re);
  for(y=0;y<500;y++)
  {
    if(le[y]<=re[y])
      for(i=le[y];i<re[y];i++)
        draw_pixel(i,y,BLACK);
  }
}
void display()
{
  x1=100,y1=100;
  x2=50,y2=150;
  x3=100,y3=200;
  x4=150,y4=150;
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_LINE_LOOP);
  glVertex2f(100,100);
  glVertex2f(50,150);
  glVertex2f(100,200);
  glVertex2f(150,150);
  glEnd();
  scanfill(x1,y1,x2,y2,x3,y3,x4,y4);
  glFlush();
 }
void menufunc(int n)
{
  switch(n)
  {
    case 1: glColor3f(1.0, 0.0, 0.0);break;
    case 2: glColor3f(0.0, 1.0, 0.0);break;
    case 3: glColor3f(0.0, 0.0, 1.0);break;
  }
}
int main(int argc, char** argv)
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowSize(500,500);
  glutInitWindowPosition(0,0);
  glutCreateWindow("Filling a Polygon using Scan-line Algorithm");
  glutCreateMenu(menufunc);
  glutAddMenuEntry("RED",1);
  glutAddMenuEntry("GREEN",2);
  glutAddMenuEntry("BLUE",3);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  glutDisplayFunc(display);
  myinit();
  glutMainLoop();
}
