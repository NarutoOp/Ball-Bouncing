#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define WIDTH 640
#define HEIGHT 480

void init()
{
	glClearColor(0.0,0.0,0.0,1.0);	
	glPointSize(10);
}

void Timer(int ex)
{
	glutPostRedisplay();
	glutTimerFunc(30,Timer,0);
}

float abs(float x)
{
	if(x<0)
	{
		x = -x;
	}
	return x;
}

void ddal(int x0,int y0,int x1,int y1)
{
    int dx;
    int dy;
    float steps;
    float xinc,yinc;
    float x,y;
    dx = x1 - x0;
	dy = y1 - y0;
	if(dx > dy)
    {
        steps = abs(dx);
    }
    else
    {
        steps = abs(dy);
    }

	xinc = dx/(float)steps;
	yinc = dy/(float)steps;

	glBegin(GL_POINTS);
	x=x0;
	y=y0;
	for(int i=0;i<steps;i++)
    {
        x = x + xinc;
        y = y + yinc;

        glVertex2f(round(x),round(y));

    }
    //glEnd();
}


void bre(float p,float q,float r)
{
	float x,y,d;
	
	x = 0;
	y = r;
	d = 3 - 2*r;
	
	while(x<=y)
	{
	    glPointSize(10);
	    glBegin(GL_POINTS);
	    glVertex2f(x+p,y+q);
	    glVertex2f(y+p,x+q);
	    glVertex2f(-x+p,y+q);
	    glVertex2f(-y+p,x+q);
	    glVertex2f(-x+p,-y+q);
	    glVertex2f(-y+p,-x+q);
	    glVertex2f(y+p,-x+q);
	    glVertex2f(x+p,-y+q);
	
	    if(d<0)
	    {
	        d = d + 4*x + 6;
	        x = x + 1;
	    }
	    else if(d>=0)
	    {
	        d = d + 4*(x - y) + 10;
	        x = x + 1;
	        y = y - 1;
	    }
	}
}

void line(int x0,int x1)
{	
	glLineWidth(10);
	glBegin(GL_LINES);
	glVertex2f(x0,0);
	glVertex2f(x1,0);
	//glEnd();
}


int k=-240,r=5,flag=0,move = 0,ulimit = -180,hflag=0;
int x1 = 0,xn=10;
void display()
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor4f(0.0,1.0,1.0,1.0);
	glBegin(GL_POINTS);
	
	bre(move,k,r);
	
		
	if(flag==0)
	{
		if((k+r)<=ulimit)
		{
			k=k+10;
		}
		
		if((k+r)>=ulimit)
		{
			ulimit = -180;
			flag=1;
		}
	}
	
	if(flag==1)
	{
		k=k-10;
		if((k-r)<=-240)
		{
			flag=0;
			
			//if(r!=10)
			//{
			//	r=r-10;
			//}
		}
	}
	ddal(x1,0,xn,0);
	if(hflag==0)
	{
		if(xn<=240)
		{
			x1=x1+10;
			xn=xn+10;
		}
		
		if(x1>240)
		{
			hflag=1;
		}
	}
	
	if(hflag==1)
	{
		x1=x1-10;
		xn=xn-10;
		if(x1<=-240)
		{
			hflag=0;
		}
	}

	glEnd();
	glutSwapBuffers();
	
	
	

}

void processSpecialKeys(int key, int x, int y)
{
	
	switch(key) {
		case GLUT_KEY_LEFT :
			if(move>-240)
			{
				move = move - 10;
				break;
			}
			break;
		case GLUT_KEY_RIGHT :
			if(move<240)
			{
				move = move + 10;
				break;
			}
			break;
		case GLUT_KEY_UP :
			ulimit = -100;	
			break;
		
	}

}

int main(int argc, char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(640,480);
	glutCreateWindow(argv[0]);
	init();
	glOrtho(-WIDTH/2,WIDTH/2-1,-HEIGHT/2,HEIGHT/2-1,-1,1);
	glutSpecialFunc(processSpecialKeys);
	glutDisplayFunc(display);
	
	glutTimerFunc(0,Timer,0);
	glutMainLoop();
	return 0;
}
// Created By Arpit Gupta(MITAOE)

