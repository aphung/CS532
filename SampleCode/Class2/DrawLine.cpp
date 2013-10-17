#include <stdio.h>
#include <glut.h>


const int cWinX = 300;
const int cWinY = 200;
const int cWinW = 640;
const int cWinH = 480;


void setPixel(int x, int y) {
	glBegin(GL_POINTS); // Draw Line (GL_POINTS)
		glVertex2i(x, y); // plot pixel
	glEnd();
}


void drawLine(int x0, int y0, int x1, int y1) {
	
	// Set the line color
	glColor3f(0.4f, 1.0f, 0.0f); // set pixel's color (RGB)
	
	float y;
	float m = (float)(y1 - y0) / (x1 - x0);
	
	for (int x = x0; x <= x1; x++) {
		y = m * (x - x0) + y0;
		//y = x*x -20*x - 100;
		setPixel(x, y); // call plot pixel function
	}
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// THIS IS WHERE WE DO OUR DRAWING
	drawLine(10, 10, 300, 240); // call draw line function with start & end points
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
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); // THIS FIXED IT!!!
	glutCreateWindow("My Window");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	
	// Set the background color for clearing the window
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f); //set the window background color (RGB alpha)
	
	glutMainLoop();
	return 1;
}