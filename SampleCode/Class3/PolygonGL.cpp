#include <stdio.h>
#include <glut.h>
#include <math.h>


const int cWinX = 300;
const int cWinY = 200;
const int cWinW = 640;
const int cWinH = 480;


/*--------------------------------------------------------------------------------------
 *	PolygonFill()																		|
 *-------------------------------------------------------------------------------------*/
void PolygonFill() {
	// Enables anti-aliasing
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Draw the polygon
	glShadeModel(GL_SMOOTH ); // shading mode (OpenGL default)
	//glShadeModel(GL_FLAT); // Single color shading mode 
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.5f, 0.1f); // Fill color orange

	// Drawing Vertices Goes Here
	
	glEnd();

	glDisable(GL_BLEND);
}


/*--------------------------------------------------------------------------------------
 *	display()																			|
 *-------------------------------------------------------------------------------------*/
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// THIS IS WHERE WE DO OUR DRAWING
	PolygonFill();

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
	gluOrtho2D(-200, width, height, -50); // Left, Right (left and right vertical clipping planes), Bottom, Top (bottom and top horizontal clipping planes)
	glMatrixMode(GL_MODELVIEW);// Switch back to the model view matrix, so that we can start drawing shapes correctly
}


/*--------------------------------------------------------------------------------------
 *	idle()																				|
 *-------------------------------------------------------------------------------------*/
void idle() {
	//glutPostRedisplay();
}


/*--------------------------------------------------------------------------------------
 *	main()																				|
 *-------------------------------------------------------------------------------------*/
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowPosition(cWinX, cWinY);
	glutInitWindowSize(cWinW, cWinH);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Polygon GL");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // Set the background color
	
	glutMainLoop();
	return 1;
}