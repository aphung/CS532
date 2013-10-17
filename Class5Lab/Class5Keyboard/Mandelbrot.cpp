#include <stdio.h>
#include <math.h>
#include <complex>
#include <glut.h>
using namespace std; //

const int cWinW = 500;
const int cWinH = 500;

const int depth = 100; // Iteration Depth
const int n=1000; // Number of Grid points

void init(void) {
	glClearColor (0.2f, 0.2f, 0.2f, 1.0f);
	glShadeModel (GL_FLAT);
}
int Mandelbrot(float x, float y, int k){ 
	/*--------------------------------------------------------------------------------------
	*	Insert Your Mandelbrot Algorithm here												|
	*--------------------------------------------------------------------------------------*/
	return 0;
}
void display(void) {
	glClear (GL_COLOR_BUFFER_BIT);
	glLoadIdentity (); /* clear the matrix */

	float Delta=0.003; // Grid Step
	float x0=-0.5; // X start point
	float y0=0.0; // Y start point
	//float x0=-0.77; // X start point
	//float y0=+0.25; // Y start point
	//Delta=Delta/10; // Grid Step

	float x1=x0-Delta*n/2, x2=x0+Delta*n/2; // X range
	float y1=y0-Delta*n/2, y2=y0+Delta*n/2; // Y range
	gluOrtho2D (x1, x2, y1, y2); // Set up the size of the canvas


	glBegin(GL_POINTS);

	// Loop the canvas grid
	for (float x = x1; x <= x2; x+=Delta) {
		int yc=1; // counter
		for (float y = y1; y <= y2; y+=Delta) {
			int k = 0;
			k=Mandelbrot(x,y,k); // Mandelbrot 

			// Colormapping of k to RGB
			float kr, kg, kb; 
			if (k==100) {
				kr=0.5; kg=0; kb=0; // The inside of the set
			}
			else {
				/*--------------------------------------------------------------------------------------
				*	Insert Your color mapping code here												|
				*--------------------------------------------------------------------------------------*/
			}

			glColor3f(kr, kg, kb); // Pixel Color
			glVertex2f(x, y); // Plot pixel
		}
	}


	glEnd();
	glFlush ();
}

void reshape (int w, int h) {
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glMatrixMode (GL_MODELVIEW);
}

void idle() {
	//glutPostRedisplay(); // 
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); 
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_INDEX);
	glutInitWindowSize (cWinW, cWinH);
	glutInitWindowPosition (10, 30);
	glutCreateWindow ("The Mandelbrot Set");
	init ();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//glutMouseFunc(mouseClick); // Using Mouse
	glutMainLoop();

	return 0;
}


