#include<stdio.h>
#include<GL/glut.h>
int x1, p, x2, y2;
void myInit(){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200.0, 0.0, 200.0);
}
void drawPixel(int x, int y){
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}
void drawLine(int x1, int x2, int p, int y2) {
	int x, y, dy, dx, i, e, inc1, inc2;
	int incx = 1, incy = 1;
	dx = x2 - x1;
	dy = y2 - p;
	x=x1;
	y=p;
	if(dx < 0)
		dx = -dx;
	if(dy < 0)
		dy = -dy;
	if(x2 < x1)
		incx = -1;
	if(y2 < p)
		incy = -1;
	if (dx > dy) {
		drawPixel(x,y);
		e = 2*dy-dx;
		inc1 = 2*(dy-dx);
		inc2 = 2*dy;
		for (i=0; i<dx; i++) {
			if (e >= 0) {
				y+=incy;
				e+=inc1;
			} else {
				e+=inc2;
			}
			x+=incx;
			drawPixel(x,y);
		}
	} else {
		drawPixel(x,y);
		e = 2*dx-dy;
		inc1 = 2*(dx-dy);
		inc2 = 2*dx;
		for (i=0; i<dy; i++) {
			if (e>=0) {
				x+=incx;
				e+=inc1;
			} else {
				e+=inc2;
			}
			y+=incy;
			drawPixel(x, y);
		}
	}
}
void myDisplay() {
	drawLine(x1, x2, p, y2);
	glFlush();
}
void main(int argc, char* argv[]){
	printf("Enter the starting coordinates: ");
	scanf("%d%d", &x1, &p);
	printf("Enter the ending coordinates: ");
	scanf("%d%d", &x2, &y2);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(400,400);
	glutCreateWindow("4MT19CS154_P1_[m=infinite]");	
	myInit();
	glutDisplayFunc(myDisplay);
	glutMainLoop();	
}
