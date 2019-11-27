#include<stdlib.h>
#include<GL/glut.h>
#include<time.h>
#include<stdio.h>
#include<math.h>


float bspd=0.01; // block dx value

char name[25];

float b1x=50.0,b1y=20;//block 1 init position

float hm=0.0;//ball moving dy value

int i=0,sci=1;float scf=1; // for increment score score_int score_flag

char scs[20],slevel[20];
//to store score_string using itoa() and level as well

int level=1,lflag=1,wflag=1; //level_flag & welcome_flag init w/ 1

void delay(float secs)
{
	float end = clock()/CLOCKS_PER_SEC + secs;
	while((clock()/CLOCKS_PER_SEC) < end);
}

void init(void)
{
srand(time(0));
b1y=(rand()%45)+10;//b/w 10 to 44

glClearColor (0.0, 1.0, 1.0, 0.0);
glShadeModel (GL_SMOOTH);
glLoadIdentity ();
glOrtho(0.0, 100.0, 0.0,100.0, -1.0 , .0);
}

void drawCircle()
{
		glColor3f(0.51,0.04,0.93);
		float x=10,y=50,r=4;
        float i = 0.0f;
        
        glBegin(GL_TRIANGLE_FAN);
        
        glVertex2f(x, y); // Center
        for(i = 0.0f; i <= 360; i++)
        glVertex2f(r*cos(M_PI * i / 180.0) + x, r*sin(M_PI * i / 180.0) + y);
        
        glEnd();
}

void renderBitmapString(float x,float y,float z,void *font,char*string)
{

char *c;

glRasterPos3f(x, y,z);

for(c=string; *c != '\0'; c++)
{
glutBitmapCharacter(font, *c);
}
}

void display(void)
{
glClear(GL_COLOR_BUFFER_BIT);
//GameOver Checking

if(
(i==1200||i==-1150)
||
(((int)b1x==1||(int)b1x==2 ||(int)b1x==3||(int)b1x==4||(int)b1x==5||(int)b1x==6)&& (int)b1y<53+(int)hm&&(int)b1y+35>46+(int)hm))
// collision checking

{

glColor3f(0.0,0.0,1.0);
glRectf(0.0,0.0,100.0,100.0);
glColor3f(1.0,0.0,0.0);
renderBitmapString(40,70,0,GLUT_BITMAP_HELVETICA_18,"GAME OVER!!!");
glColor3f(1.0,1.0,1.0);
renderBitmapString(25,58,0,GLUT_BITMAP_TIMES_ROMAN_24,"You");
renderBitmapString(45,58,0,GLUT_BITMAP_TIMES_ROMAN_24,"scored:");
renderBitmapString(70,58,0,GLUT_BITMAP_TIMES_ROMAN_24,scs);
glutSwapBuffers();
glFlush();
delay(2);
printf("\nGAME OVER\n\n");
printf("\n%s \You scored  %s" ,name,scs);
printf("\n%s \You reached level  %s" ,name,slevel);
printf("\n\nClose the console window to exit...\n");
exit(0);
}

else if(wflag==1)//Welcome Screen
{

wflag=0;

glColor3f(0.9,0.5,0.7);
glRectf(0.0,0.0,100.0,10.0);//ceil
glRectf(0.0,100.0,100.0,90.0);//floor

glColor3f(0.0,0.1,1.0);
renderBitmapString(32,85,0,GLUT_BITMAP_HELVETICA_18,"MIT ACADEMY OF ENGINEERING");

renderBitmapString(41,80,0,GLUT_BITMAP_HELVETICA_18,"Alandi(D),Pune");

glColor3f(0.0,0,0.0);
renderBitmapString(40,65,0,GLUT_BITMAP_TIMES_ROMAN_24,"Bouncing Ball");

glColor3f(1.0,0.0,0.0);
renderBitmapString(40,45,0,GLUT_BITMAP_TIMES_ROMAN_24,"Welcome ");
renderBitmapString(53,45,0,GLUT_BITMAP_TIMES_ROMAN_24,name);
renderBitmapString(43,30,0,GLUT_BITMAP_TIMES_ROMAN_24,"Click To Start");
renderBitmapString(17,24,0,GLUT_BITMAP_9_BY_15,"CLICK AND HOLD LEFT MOUSE BUTTON TO GO UP RELEASE TO GO DOWN");

glColor3f(0.0,0.0,0.0);
drawCircle();

glutSwapBuffers();
glFlush();

}

else
{

//on every increase by 50 in score in each level
if(sci%50==0&&lflag==1)
{
lflag=0; //make level_flag=0
level++;//increase level by 1
bspd+=0.01;//increase block_dx_speed by 0.01
}

//within every level make level_flag=1
else if(sci%50!=0&&lflag!=1)
{
lflag=1;
}

glPushMatrix();

glColor3f(0.9,0.5,0.7);
glRectf(0.0,0.0,100.0,10.0);      //ceil
glRectf(0.0,100.0,100.0,90.0);    //floor

glColor3f(0.0,0.0,0.0);   //score
renderBitmapString(1,3,0,GLUT_BITMAP_TIMES_ROMAN_24,"Distance:");
//glColor3f(0.7,0.7,0.7);

sprintf(slevel,"%d",level);   //level
renderBitmapString(80,3,0,GLUT_BITMAP_TIMES_ROMAN_24,"Level:");
renderBitmapString(93,3,0,GLUT_BITMAP_TIMES_ROMAN_24,slevel);

scf+=0.00100;              //so less as program run very fast
sci=(int)scf;
sprintf(scs,"%d",sci);
//from int to char convertion to display score

renderBitmapString(20,3,0,GLUT_BITMAP_TIMES_ROMAN_24,scs);

glTranslatef(0.0,hm,0.0);
// hm(=dy) changes occur by mouse func

drawCircle();
//code for ball

//if wall move towards left & get out of projection volume
if(b1x<-10)
{

b1x=50;            //total width is 50
b1y=(rand()%25)+20;
//10 for selling+10 for giving enough space
// block bottom limit 0+20 & top limit 24+20=44

}

else
b1x-=bspd;
//within the projection volume dec its x value by block_speed

glTranslatef(b1x,-hm,0.0);

glColor3f(0.0,1.0,0.0);
glRectf(b1x,b1y,b1x+5,b1y+35);//block 1

glPopMatrix();

glutSwapBuffers();
glFlush();

}

}

void moveHeliU(void)
{

hm+=0.03;
i++;
glutPostRedisplay();

}

void moveHeliD()
{

hm-=0.03;
i--;
glutPostRedisplay();

}


void mouse(int button, int state, int x, int y)
{

switch (button)
{

case GLUT_LEFT_BUTTON:

if (state == GLUT_DOWN)
glutIdleFunc(moveHeliU);

else if (state == GLUT_UP)
glutIdleFunc(moveHeliD);
break;

default: break;

}

}


void keys(unsigned char key,int x,int y)
{

if(key=='u') glutIdleFunc(moveHeliU);
if(key=='d') glutIdleFunc(moveHeliD);

}

int main(int argc, char** argv)
{

printf("enter your name to play: ");
scanf("%s",name);
glutInit(&argc, argv);
glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
glutInitWindowSize (800, 600);
glutInitWindowPosition (200,200);
glutCreateWindow ("");
init();
glutDisplayFunc(display);
glutMouseFunc(mouse);
glutKeyboardFunc(keys);
glutMainLoop();
return 0;

}


