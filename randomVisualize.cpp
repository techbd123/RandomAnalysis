#include <bits/stdc++.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#define pi 3.14159265358979
#define eps 1e-9
#define sqr(x) ((x)*(x))
using namespace std;

typedef long long int ll;
typedef struct POINT Point;

const int Size=1000;
const int minX=0,maxX=Size,minY=0,maxY=Size;
const int screenX = 1000, screenY = 1000;
const double ptSize=max(screenX,screenY)/Size;
int arr[Size+1][Size+1];

struct POINT
{
    double x,y;
};

int Random(int i,int j)
{
    int d=abs(j-i+1);
    return rand()%d+i;
}

void Delay(int milis)
{
    long long ftime=clock()+milis;
    while(clock()<ftime);
    return ;
}

bool hEqual(double a,double b)
{
    a-=b;
    if(a>=-eps&&a<=eps) return 1;
    return 0;
}

void DrawLine(Point A,Point B)
{
    glBegin(GL_LINES);
    glVertex2d(A.x,A.y);
    glVertex2d(B.x,B.y);
    glEnd();
    glFlush();
    return ;
}

void DrawPoint(Point A)
{
    glBegin(GL_POINTS);
    glVertex2d(A.x,A.y);
    glEnd();
    glFlush();
    return ;
}

void DrawReferenceFrame()
{
    Point A,B;
    glColor3d(1.0,1.0,1.0);
    A.x=minX;A.y=(minY+maxY)/2.0;B.x=maxX,B.y=(minY+maxY)/2.0;DrawLine(A,B);
    A.x=(minX+maxX)/2.0;A.y=minY;B.x=(minX+maxX)/2.0,B.y=maxY;DrawLine(A,B);
    A.x=minX;A.y=minY;B.x=maxX,B.y=maxY;DrawLine(A,B);
    A.x=minX;A.y=maxY;B.x=maxX,B.y=minY;DrawLine(A,B);
    return ;
}

bool hRange(double a,double b,double c)
{
    if(a+eps<=b&&b+eps<=c) return 1;
    return 0;
}

int Check(Point A,Point B)
{
    double dx=A.x-B.x;
    double dy=A.y-B.y;
    //if(hRange(.5,A.x,1)&&hRange(.5,A.y,1)&&hRange(.5,B.x,1)&&hRange(.5,B.y,1))
    {
        if(dy>dx&&dx>=0&&dy>0) return 1;
        return 0;
    }
    return 0;
}

void DrawBitMap()
{
    glColor3d(0.5,0.5,0.5);
    glBegin(GL_POINTS);
    int i,j;
    for(i=minY;i<=maxY;i++)
    {
        for(j=minX;j<=maxX;j++)
        {
            glVertex2i(i,j);
        }
    }
    glEnd();
    glFlush();
    return ;
}

void DrawCircle(double x,double y,double r)
{
    double i,j,c;
    glBegin(GL_POINTS);
    for(i=x-r,c=1;i+eps<=x+r;i+=c)
    {
        j=sqr(r)-sqr(i-x);j=sqrt(j);;
        glVertex2d(i,y+j);
        glVertex2d(i,y-j);
    }
    glEnd();
    glFlush();
    return ;
}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3d(1.0,1.0,0.0);
    int i=0,maX=0;Point A,B;
    glPointSize(ptSize);
    while(true)
    {
        i++;
        A.x=Random(minX,maxX);A.y=Random(minY,maxY);
        int x=A.x+eps,y=A.y+eps;
        arr[x][y]++;
        maX=max(maX,arr[x][y]);
        //B.x=Random(minX,maxX);B.y=Random(minY,maxY);
        //DrawLine(A,B);
        double r=(double)arr[x][y]/maX;
        printf("i = %d r = %lf\n",i,r);
        if(hRange(0,r,1.0/3)) glColor3d(1.0*3*r,0.0,0.0);
        else if(hRange(1.0/3+eps,r,2.0/3-eps)) glColor3d(0.0,1.0*(3*r-1),0.0);
        else glColor3d(0.0,0.0,1.0*(3*r-2));
        DrawPoint(A);
        //Delay(1);
    }
    return ;
}

void init(void)
{
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(minX,maxX,minY,maxY,0.0,1.0);
    return ;
}


/*
 *  Declare initial window size, position, and display mode
 *  (single buffer and RGBA).
 *  in its title bar.  Call initialization routines.
 *  Register callback function to display graphics.
 *  Enter main loop and process events.
 */
int main(int argc, char** argv)
{
    srand(time(0));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(screenX,screenY);
    glutInitWindowPosition(800,60);
    glutCreateWindow("Simple");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
