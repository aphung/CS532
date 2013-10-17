#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <glut.h> // needs to be after stdlib.h


const int cWinX = 100; // Screen x positon of the window
const int cWinY = 100; // Screen y positon of the window
const int cWinW = 640; // Horizontal size of the window
const int cWinH = 480; // Vertical size of the window


void setPixel(float x, float y) {
	glBegin(GL_POINTS); // Draw Point (GL_POINTS)
		glVertex2f(x, y); // plot pixel
	glEnd();
}


void drawFern(int NumOfPts) {
	// Set the line color
	glColor3f(0.4f, 1.0f, 0.0f); // set pixel's color (RGB) Green
	
	float xn; float yn=0;
	float x; float y; float p;

	int iterations = 50;

	for (int j = 2; j <= NumOfPts; j++) {
		x = (float)(rand())/RAND_MAX; // Random number 
		y = (float)(rand())/RAND_MAX; // Random number

		for (int i = 2; i <= iterations; i++) {
			p = (float)(rand())/RAND_MAX; // Generate Random number

			/*--------------------------------------------------------------------------------------
			*	Insert Your Fren Algorithm here	to get x and y for f1, f2, f3 and f4				|
			*--------------------------------------------------------------------------------------*/


			setPixel(50*x, 50*y); // call plot pixel function
		}

	}
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// DRAWING
	int NumOfPts = 10000;
	drawFern(NumOfPts); // call draw line function with start & end points
	glutSwapBuffers(); // place the drawing from memory on the screen
}


void reshape(int width, int height) {
	// Set up orthographic projection such that each point corresponds to a pixel. 
	// The origin is set to be in the upper left corner. 
	glViewport(0, 0, width, height); // x,y,cWinW,cWinH - Set our viewport to the size of our window 
	glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed 
	glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)
	gluOrtho2D(-200, width, height, -50); // Left, Right (left and right vertical clipping planes), Bottom, Top (bottom and top horizontal clipping planes)
	glMatrixMode(GL_MODELVIEW);// Switch back to the model view matrix, so that we can start drawing shapes correctly
}


void idle() {
	//glutPostRedisplay(); // 
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowPosition(cWinX, cWinY);
	glutInitWindowSize(cWinW, cWinH);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); // 
	glutCreateWindow("Fractal Fern");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	
	// Set the background color for clearing the window
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f); //set the window background color (RGB, alpha)
	
	glutMainLoop();
	return 1;
}