#include <stdio.h>
#include <glut.h>


const int cWinX = 300;
const int cWinY = 200;
const int cWinW = 640;
const int cWinH = 480; // Specify Window Size


void setPixel(int x, int y) {
	glColor3f(0.4f, 1.0f, 0.0f); // set pixel's color (RGB)
	glBegin(GL_POINTS); // Draw Line (GL_POINTS)
		glVertex2i(x, y); // plot pixel
	glEnd();
}



void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// THIS IS WHERE WE DO OUR DRAWING
	setPixel(10,30); // Call plot pixel function
	glutSwapBuffers(); // place the drawing from memory on the screen
}


void reshape(int width, int height) {
	// Set up orthographic projection such that each point corresponds to a pixel. 
	// The origin is set to be in the upper left corner. 
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, height, 0);
	glMatrixMode(GL_MODELVIEW);
}


void idle() {
	glutPostRedisplay(); // 
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