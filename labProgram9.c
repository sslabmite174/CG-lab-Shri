#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

GLfloat ya=50,xa=10;
int yFlag=1;
int xFlag=1;
int drawFlag=0;
int animationFlag = 2;

void Animate(){
	if(animationFlag==2 && drawFlag==1){
	    if(ya>-50 && yFlag==1)
		    ya = ya-0.02;
	    if(ya<=-50 && yFlag==1)
		    yFlag=0;
	    if(ya<50 && yFlag==0)
		    ya = ya+0.02;
	    if(ya>=50 && yFlag==0)
		    yFlag=1;
		
	    if(xa>-10 && xFlag==1)
		    xa = xa-0.001;
	    if(xa<=-10 && xFlag==1)
		    xFlag=0;
	    if(xa<10 && xFlag==0)
		    xa = xa+0.001;
	    if(xa>=10 && xFlag==0)
		    xFlag=1;
	    glutPostRedisplay();
    }
}

void draw(){
	glClear(GL_COLOR_BUFFER_BIT);
	if(drawFlag==1){
	    GLfloat x[4],y1[4],y2[4],y3[4],y4[4];
	    GLdouble xt[201],yt1[201],yt2[200],yt3[201],yt4[201],t;

	    x[0] =100;	x[1]=200;		x[2]=200;		x[3]=300 - xa;
	    y1[0] =450;	y1[1]=450+ya;	y1[2]=450-ya;	y1[3]=450;
	    y2[0] =420;	y2[1]=420+ya;	y2[2]=420-ya;	y2[3]=420;
	    y3[0] =390;	y3[1]=390+ya;	y3[2]=390-ya;	y3[3]=390;
	    y4[0] =360;	y4[1]=360+ya;	y4[2]=360-ya;	y4[3]=360;
	    int i;

        /*Bazier Eqn
            xt = (1-t)^3 *x1 +3t(1-t)^2 *x2 +3t^2(1-t)*x3 + t^3*x4
            yt = (1-t)^3 *y1 +3t(1-t)^2 *y2 +3t^2(1-t)*y3 + t^3*y4
        */
	    for(i=0,t=0;t<=1;t+=0.01,i++){
		    xt[i] = pow(1-t,3)*x[0] + (3*t*pow(1-t,2)*x[1])+(3*pow(t,2)*x[2]*pow(1-t,1))+pow(t,3)*x[3];
		    yt1[i] = pow(1-t,3)*y1[0] + (3*t*pow(1-t,2)*y1[1])+(3*pow(t,2)*y1[2]*pow(1-t,1))+pow(t,3)*y1[3];
		    yt2[i] = pow(1-t,3)*y2[0] + (3*t*pow(1-t,2)*y2[1])+(3*pow(t,2)*y2[2]*pow(1-t,1))+pow(t,3)*y2[3];
		    yt3[i] = pow(1-t,3)*y3[0] + (3*t*pow(1-t,2)*y3[1])+(3*pow(t,2)*y3[2]*pow(1-t,1))+pow(t,3)*y3[3];
		    yt4[i] = pow(1-t,3)*y4[0] + (3*t*pow(1-t,2)*y4[1])+(3*pow(t,2)*y4[2]*pow(1-t,1))+pow(t,3)*y4[3];
	    }
	    glPointSize(3);
	    glColor3f(1,0.6,0.2);
	    glBegin(GL_QUAD_STRIP);
	    for(i=0;i<100;i++){
		    glVertex2d(xt[i],yt1[i]);
		    glVertex2d(xt[i],yt2[i]);
	    }
	    glEnd();

	    glColor3f(1,1,1);
	    glBegin(GL_QUAD_STRIP);
	    for(i=0;i<100;i++){
		    glVertex2d(xt[i],yt2[i]);
		    glVertex2d(xt[i],yt3[i]);
	    }
	    glEnd();

	    glColor3f(0,1,0);
	    glBegin(GL_QUAD_STRIP);
	    for(i=0;i<100;i++){
		    glVertex2d(xt[i],yt3[i]);
		    glVertex2d(xt[i],yt4[i]);
	    }
	    glEnd();

	    glColor3f(1,1,1);
	    glRecti(90,470,100,50);
    }
	glFlush();
}

void Menu(int n){
	if(n==1){
		drawFlag =1;
		animationFlag = 1;
	}
	else if(n==2)
		animationFlag = 2;
	else if(n==3)
		animationFlag = 3;
	else if(n==4)
		exit(0);
	glutPostRedisplay();
}

void MyInit(){
	glClearColor(0,0,0,1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,500,0,500);
	glMatrixMode(GL_MODELVIEW);
    
	glutCreateMenu(Menu);
	glutAddMenuEntry("Draw",1);
	glutAddMenuEntry("start",2);
	glutAddMenuEntry("Stop",3);
	glutAddMenuEntry("Exit",4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char *argv[]) {
	glutInit(&argc,argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100,100);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutCreateWindow("Animate Flag");
	MyInit();
	glutDisplayFunc(draw);
	glutIdleFunc(Animate);
	glutMainLoop();
	return 0;
}
