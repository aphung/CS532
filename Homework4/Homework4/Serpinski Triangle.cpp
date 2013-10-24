#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <glut.h>



const int cWinX = 100; // Screen x positon of the window
const int cWinY = 100; // Screen y positon of the window
const int cWinW = 640; // Horizontal size of the window
const int cWinH = 480; // Vertical size of the window


void setPixel(float x, float y) {
	glBegin(GL_POINTS); // Draw point (GL_POINTS)
		glVertex2f(x, y); // plot pixel
	glEnd();
}


void drawSerpinski(int n) {
	// Set the line color
	glColor3f(0.4f, 1.0f, 0.0f); // set pixel's color (RGB) Green
	//glColor3f(0.98f, 0.625f, 0.12f); // set pixel's color (RGB) Orange
	
	int randNum;
	float x_old=0; float y_old=0;
	float x; float y;

	for (int a = 2; a <= n; a++) {
		randNum = rand() % 3; // Random number between 0 and 2
		
		/*--------------------------------------------------------------------------------------
		*	Enter your Serpinski Algorithm Code here (use switch/case)							|
		*--------------------------------------------------------------------------------------*/
		switch (randNum) {
		case 0:
			x = 0.5 * x_old;
			y = 0.5 * y_old;
			break;
		case 1:
			x = 0.5 * x_old + 0.25;
			y = 0.5 * y_old + sqrt(3.0)/4;
			break;
		case 2:
			x = 0.5 * x_old + 0.5;
			y = 0.5 * y_old;
			break;
		}

		setPixel(200*x, 200*y); // call plot pixel function
		x_old=x; y_old=y;
	}
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// DRAWING
	int n = 10000;
	drawSerpinski(n); // call draw line function with start & end points
	glutSwapBuffers(); // place the drawing from memory on the screen
}


void reshape(int width, int height) {
	// Set up orthographic projection such that each point corresponds to a pixel. 
	// The origin is set to be in the upper left corner. 
	glViewport(0, 0, width, height); // x,y,cWinW,cWinH - Set our viewport to the size of our window 
	glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed 
	glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)
	gluOrtho2D(-100, width, height, -100); // Left, Right (left and right vertical clipping planes), Bottom, Top (bottom and top horizontal clipping planes)
	glMatrixMode(GL_MODELVIEW);// Switch back to the model view matrix, so that we can start drawing shapes correctly
}


void idle() {
	// glutPostRedisplay(); // 
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowPosition(cWinX, cWinY);
	glutInitWindowSize(cWinW, cWinH);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); // 
	glutCreateWindow("My Window");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	
	// Set the background color for clearing the window
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f); //set the window background color (RGB, alpha)
	
	glutMainLoop();
	return 1;
}