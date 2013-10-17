#include <stdio.h>
#include <glut.h>
#include <math.h>

const int cWinX = 300;
const int cWinY = 200;
const int cWinW = 640;
const int cWinH = 480;

void drawLineGL(int p1X, int p1Y, int p2X, int p2Y, int width, float red, float green, float blue) {
	glDisable(GL_TEXTURE_2D);

	// Enables anti-aliasing
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glColor3f(red, green, blue); // Line Color

	// Draw Line
	glLineWidth(width);
	glBegin(GL_LINES);
	glVertex2i(p1X, p1Y);
	glVertex2i(p2X, p2Y);
	glEnd();

	glDisable(GL_BLEND);
}

// Basic drawLineGL with default color (red)
void drawLineGL(int p1X, int p1Y, int p2X, int p2Y, int width) {
	drawLineGL(p1X, p1Y, p2X, p2Y, width, 1.0f, 0.0f, 0.0f);
}

void drawShape(double *x, double *y, int count, int width) {
	// Enable anti-aliasing
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	

	// Draw
	glLineWidth(width); // Line Width

	glBegin(GL_LINE_LOOP); // Draw Line (GL_LINE_LOOP)
	glColor3f(0.0f, 1.0f, 0.0f);
	for (int i = 0; i < count; i++) {
		glVertex2i(x[i], y[i]);
	}
	glEnd();

	glDisable(GL_BLEND);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw axis
	drawLineGL(0, -1000, 0, 1000, 1, 1.0f, 1.0f, 0.0f);
	drawLineGL(-1000, 0, 1000, 0, 1, 1.0f, 1.0f, 0.0f);

	double shapeX[8] = {-50, 25, 25, 50, 25, 25, -50, -40};
	double shapeY[8] = {15, 15, 30, 0, -30, -15, -15, 0}; // y vertices coordinates
	double Xn[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	double Yn[8] = {0, 0, 0, 0, 0, 0, 0, 0};

	// Draw Arrow
	//drawShape(shapeX, shapeY, 8, 3);

	double a = 1.0;
	double b = 0.0;
	double c = 0.0;
	double d = 1.0;
	int tx = 0;
	int ty = 0;
	
	/// Problem b: translate your figure along y axis for 1,5 times the figure's y size.
	int size = 100;
	ty = size;
	for (int i = 0; i < 8; i++) {
		Xn[i] = a*shapeX[i] + b*shapeY[i]+tx;
		Yn[i] = c*shapeX[i] + d*shapeY[i]+ty;
	}
	//drawShape(Xn, Yn, 8, 3);


	/// Problem c: rotate your figure clockwise for 30 degrees.
	double angle = -0.3f;
	a = cos(angle);
	b = -sin(angle);
	c = sin(angle);
	d = cos(angle);
	tx = 0;
	ty = 0;

	for (int i = 0; i < 8; i++) {
		Xn[i] = a*shapeX[i] + b*shapeY[i]+tx;
		Yn[i] = c*shapeX[i] + d*shapeY[i]+ty;
	}
	//drawShape(Xn, Yn, 8, 3);


	/// Problem d: scale the y dimension of your figure for 0.75. 
	angle = 0.0f;
	double scale = 0.75;
	a = cos(angle);
	b = -sin(angle);
	c = sin(angle);
	d = cos(angle) + scale;
	tx = 0;
	ty = 0;

	for (int i = 0; i < 8; i++) {
		Xn[i] = a*shapeX[i] + b*shapeY[i]+tx;
		Yn[i] = c*shapeX[i] + d*shapeY[i]+ty;
	}
	drawShape(Xn, Yn, 8, 3);


	/// Problem e: shear your figure along y by a factor of 1.1
	double sheerFactor = 1.1;
	a = 1;
	b = sheerFactor;
	c = 0;
	d = 1;
	tx = 0;
	ty = 0;

	for (int i = 0; i < 8; i++) {
		Xn[i] = a*shapeX[i] + b*shapeY[i]+tx;
		Yn[i] = c*shapeX[i] + d*shapeY[i]+ty;
	}
	//drawShape(Xn, Yn, 8, 3);

	glFlush();
	glutSwapBuffers();
}

void reshape(int width, int height) {
	// Set up orthographic projection such that each point corresponds to a pixel. 
	// The origin is set to be in the upper left corner. 
	glViewport(0, 0, width, height); // x,y,cWinW,cWinH - Set our viewport to the size of our window 
	glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed 
	glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)
	gluOrtho2D(-(width/2.0), width/2.0, -(height/2.0), height/2.0);
	glMatrixMode(GL_MODELVIEW);// Switch back to the model view matrix, so that we can start drawing shapes correctly
}

void idle() {
	glutPostRedisplay(); // If Re-display needed (FOR MOTION)
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitWindowPosition(cWinX, cWinY);
	glutInitWindowSize(cWinW, cWinH);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow ("Homework 3 - Adam Phung"); // Set the title for the window  

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // Set the background color

	glutMainLoop(); // Enter GLUT's main loop  
	return 1;
}