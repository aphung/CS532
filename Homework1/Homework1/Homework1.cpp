#include <stdio.h>
#include <math.h>
#include <iostream>
#include "glut.h"

const int cWinX = 300;
const int cWinY = 300;
const int cWinW = 800;
const int cWinH = 600; // Specify Window Size


void setPixel(int x, int y, float r, float g, float b) {
	glColor3f(r, g, b); // set pixel's color (RGB)
	glBegin(GL_POINTS); // Draw Line (GL_POINTS)
	glVertex2i(x, y); // plot pixel
	glEnd();
}

void setPixel(int x, int y) {
	setPixel(x, y, 0.4f, 1.0f, 0.0f);
}

void swapInt(int &num1, int &num2) {
	int temp = num1;
	num1 = num2;
	num2 = temp;
}


void bresenhamLine(int x1, int y1, int x2, int y2, float r, float g, float b) {

	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	double slope = abs((double)deltaY / (double)deltaX);
	double inverseSlope = abs((double)deltaX / (double)deltaY);
	double error = 0.0;
	int x, y, xStep, yStep;

	if (slope >= 1) {
		if (x1 <= x2)
			xStep = 1;
		else
			xStep = -1;

		x = x1;
		if (y1 <= y2) {
			for (int y = y1; y <= y2; y++) {
				setPixel(x, y, r, g, b);
				error += inverseSlope;
				if (error >= 0.5) {
					x += xStep;
					error--;
				}
			}
		}
		else {
			for (int y = y1; y >= y2; y--) {
				setPixel(x, y, r, g, b);
				error += inverseSlope;
				if (error >= 0.5) {
					x += xStep;
					error--;
				}
			}
		}
	}
	else {
		if (y1 <= y2)
			yStep = 1;
		else
			yStep = -1;
		
		y = y1;
		if (x1 <= x2) {
			for (int x = x1; x <= x2; x++) {
				setPixel(x, y, r, g, b);
				error += slope;
				if (error >= 0.5) {
					y += yStep;
					error--;
				}
			}
		}
		else {
			for (int x = x1; x >= x2; x--) {
				setPixel(x, y, r, g, b);
				error += slope;
				if (error >= 0.5) {
					y += yStep;
					error--;
				}
			}
		}
	}
}

void bresenhamLine(int x1, int y1, int x2, int y2) {
	bresenhamLine(x1, y1, x2, y2, 0.4f, 1.0f, 0.0f);
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Draw Axis
	bresenhamLine(0, -1000, 0, 1000, 1.0f, 1.0f, 1.0f);
	bresenhamLine(-1000, 0, 1000, 0, 1.0f, 1.0f, 1.0f);

	// THIS IS WHERE WE DO OUR DRAWING
	
	// From the Slide
	bresenhamLine(0, 0, 100, -100);
	bresenhamLine(50, -20, 80, -40);
	bresenhamLine(30, -60, 60, -40);
	bresenhamLine(10, -70, 85, 10);

	/* Sample lines from Won to test all directions */
	// x-axis
	bresenhamLine(-316, 0, 316, 0, 1.0f, 1.0f, 0.0f);

	// y-axis
	bresenhamLine(0, -316, 0, 316, 1.0f, 1.0f, 0.0f);

	// 1st octant
	bresenhamLine(0, 0, 100, 300, 1.0f, 1.0f, 0.0f);
	bresenhamLine(0, 0, 230, 230, 1.0f, 1.0f, 0.0f);
	bresenhamLine(0, 0, 300, 100, 1.0f, 1.0f, 0.0f);

	// 2nd octant
	bresenhamLine(0, 0, -100, 300, 1.0f, 1.0f, 0.0f);
	bresenhamLine(0, 0, -230, 230, 1.0f, 1.0f, 0.0f);
	bresenhamLine(0, 0, -300, 100, 1.0f, 1.0f, 0.0f);

	// 3rd octant
	bresenhamLine(0, 0, -100, -300, 1.0f, 1.0f, 0.0f);
	bresenhamLine(0, 0, -230, -230, 1.0f, 1.0f, 0.0f);
	bresenhamLine(0, 0, -300, -100, 1.0f, 1.0f, 0.0f);

	// 4th octant
	bresenhamLine(0, 0, 100, -300, 1.0f, 1.0f, 0.0f);
	bresenhamLine(0, 0, 230, -230, 1.0f, 1.0f, 0.0f);
	bresenhamLine(0, 0, 300, -100, 1.0f, 1.0f, 0.0f);

	glutSwapBuffers();
}


void reshape(int width, int height) {
	// Set up orthographic projection such that each point corresponds to a pixel. 
	// The origin is set to be in the upper left corner. 
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(0, width, height, 0);
	gluOrtho2D(-(width/2.0), width/2.0, -(height/2.0), height/2.0);
	glMatrixMode(GL_MODELVIEW);
}


void idle() {
	glutPostRedisplay();
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowPosition(cWinX, cWinY);
	glutInitWindowSize(cWinW, cWinH);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); // 
	glutCreateWindow("My Window"); // Window title
	glutDisplayFunc(display); // Call Display 
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	
	// Set the background color for clearing the window
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f); //set the window background color (RGB alpha)
	
	glutMainLoop();
	return 1;
}