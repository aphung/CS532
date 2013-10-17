#include <stdio.h>
#include <glut.h>
#include <math.h>


const int cWinX = 300;
const int cWinY = 200;
const int cWinW = 1024;
const int cWinH = 768;


/*--------------------------------------------------------------------------------------
 *	drawLineGL()																		|
 *-------------------------------------------------------------------------------------*/
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

// Ellipse
void drawEllipse(int x, int y, double radius, double b) {
	double theta = 0.0;
	double delta_theta = 6.28/1000; // Angle increment
	int y1 = y;

	int x1 = x + radius;
	
	while (theta <= 6.28) {
		double base = pow((b * cos(theta)), 2.0) + pow((radius * sin(theta)), 2.0);
		double r = radius * b / pow(base, 0.5);

		int x2 = (x + r * cos(theta));
		int y2 = (x + r * sin(theta));

		drawLineGL(x1, y1, x2, y2, 1);

		theta = theta + delta_theta;
		x1 = x2;
		y1 = y2;
	}
}

// Problem 1: (x^2 + y^2 +2ax)^2 = 4a^2(x^2 + y^2)
void drawProblemOne(int x, int y, int radius, double dTheta) {
	double theta = 0.0;
	int y1 = y;
	int x1 = x;
	
	while (theta <= 6.28) {
		// r = 2a - 2a cos (theta)
		double r = 2 * radius - (2 * radius * cos(theta));

		int x2 = (x + r * cos(theta));
		int y2 = (x + r * sin(theta));

		drawLineGL(x1, y1, x2, y2, 1);

		theta = theta + dTheta;
		x1 = x2;
		y1 = y2;
	}
}

// Problem 2: x^4 + 2x^2y^2 + y^4 - x^3 + 3xy^2 = 0
void drawProblemTwo(int x, int y, int radius, double dTheta) {
	double theta = 0.0;
	int y1 = y;
	int x1 = x + radius;
	
	while (theta <= 6.28) {
		// r = cos(3 * theta) * radius
		double r = cos(3 * theta) * radius;

		int x2 = (x + r * cos(theta));
		int y2 = (x + r * sin(theta));

		drawLineGL(x1, y1, x2, y2, 1, 0.0f, 1.0f, 0.0f);

		theta = theta + dTheta;
		x1 = x2;
		y1 = y2;
	}
}

// Problem 3: x^4 + 2x^2y^2 + y^4 - x^3 + 3xy^2 = 0
void drawProblemThree(int x, int y, int radius, double dTheta) {
	double theta = 0.0;
	int y1 = y;
	int x1 = x;
	
	while (theta <= 6.28) {
		// r = sqrt(a * theta)
		double r = sqrt(radius * theta);

		int x2 = x + r * (sqrt(radius * theta) * cos(theta));
		int y2 = x + r * (sqrt(radius * theta) * sin(theta));

		drawLineGL(x1, y1, x2, y2, 1, 0.0f, 0.0f, 1.0f);

		theta = theta + dTheta;
		x1 = x2;
		y1 = y2;
	}
}

/*--------------------------------------------------------------------------------------
 *	display()																			|
 *-------------------------------------------------------------------------------------*/
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Draw Axis
	drawLineGL(0, -1000, 0, 1000, 1, 1.0f, 1.0f, 1.0f);
	drawLineGL(-1000, 0, 1000, 0, 1, 1.0f, 1.0f, 1.0f);

	// THIS IS WHERE WE DO OUR DRAWING
	drawProblemOne(0, 0, 100, (6.28/1000.0));
	drawProblemTwo(0, 0, 100, (6.28/1000.0));
	drawProblemThree(0, 0, 100, (6.28/1000.0));

	glutSwapBuffers();
}


/*--------------------------------------------------------------------------------------
 *	reshape()																			|
 *-------------------------------------------------------------------------------------*/
void reshape(int width, int height) {
	// Set up orthographic projection such that each point corresponds to a pixel. 
	// The origin is set to be in the upper left corner. 
	glViewport(0, 0, width, height); // x,y,cWinW,cWinH - Set our viewport to the size of our window 
	glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed 
	glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)
	gluOrtho2D(-(width/2.0), width/2.0, -(height/2.0), height/2.0);
	glMatrixMode(GL_MODELVIEW);// Switch back to the model view matrix, so that we can start drawing shapes correctly
}


/*--------------------------------------------------------------------------------------
 *	idle()																				|
 *-------------------------------------------------------------------------------------*/
void idle() {
	glutPostRedisplay();
}


/*--------------------------------------------------------------------------------------
 *	main()																				|
 *-------------------------------------------------------------------------------------*/
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowPosition(cWinX, cWinY);
	glutInitWindowSize(cWinW, cWinH);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Homework 2 - Adam Phung");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // Set the background color
	
	glutMainLoop();
	return 1;
}