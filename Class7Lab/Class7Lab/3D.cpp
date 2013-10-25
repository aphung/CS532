#include <stdio.h>
#include <glut.h>
#include <math.h>

const int cWinX = 300;
const int cWinY = 200;
const int cWinW = 640;
const int cWinH = 480;

float ORG[3] = {0,0,0}; // Origin
float XP[3] = {1,0,0}, XN[3] = {-1,0,0},
YP[3] = {0,1,0}, YN[3] = {0,-1,0},
ZP[3] = {0,0,1}, ZN[3] = {0,0,-1};

/*--------------------------------------------------------------------------------------
 *	Draw xyz Axes																			|
 *-------------------------------------------------------------------------------------*/
void Draw_Axes (void) {
	//glPushMatrix ();
	glLineWidth (2.0);
	
	glBegin (GL_LINES);
	glColor3f (1,0,0); // X axis is red.
	glVertex3fv (ORG); 	glVertex3fv (XP ); 
	glColor3f (0,1,0); // Y axis is green.
	glVertex3fv (ORG); 	glVertex3fv (YP );
	glColor3f (0,0,1); // z axis is blue.
	glVertex3fv (ORG); 	glVertex3fv (ZP ); 
	glEnd();
	
	//glPopMatrix ();
} 

/*--------------------------------------------------------------------------------------
 *	display()																			|
 *-------------------------------------------------------------------------------------*/
void display(void) {
	glClear (GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations  
	//gluLookAt(0, 0, -20, 0, 0, -1, 0, 1, 0);
	//glTranslatef(0.0f, 0.0f, -2.5f);
	glColor3f(0.5f, 0.7f, 1.0f); // Line color

	// Look
	gluLookAt(10, 6, 15, 0, 0, 0, 0, 1, 0);
	
	// Enter the primitive code here
	glutWireCube(1.5f);

	Draw_Axes (); // Draw xyz
	glFlush(); // Flush the OpenGL buffers to the window  
}


/*--------------------------------------------------------------------------------------
 *	reshape()																			|
 *-------------------------------------------------------------------------------------*/
void reshape(int width, int height) {
	// Set up orthographic projection such that each point corresponds to a pixel. 
	glViewport(0, 0, (GLsizei)width, (GLsizei)height); // x,y,cWinW,cWinH - Set our viewport to the size of our window  

	glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed  
	glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)
	//glOrtho(-2.0,2.0,-2.0,2.0,-2.0,2.0); // left, right, bottom, top, nearVal, farVal
	gluPerspective(20.0, (GLfloat)width / (GLfloat)height, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly  
	
	//glFrustum(-1.0, 1.0, -1.0, 2.0, 1.5, 20.0);
	//glFrustum(-2.0, 2.0, -2.0, 2.0, 1.5, 20.0);	
}


/*--------------------------------------------------------------------------------------
 *	main()																				|
 *-------------------------------------------------------------------------------------*/
int main(int argc, char** argv) {
	glutInit(&argc, argv); // Initialize GLUT  
	glutInitWindowSize(cWinW, cWinH); // Set the width and height of the window  
	glutInitWindowPosition(cWinX, cWinY); // Set the position of the window  
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set up a basic display buffer (only single buffered for now) 
	glutCreateWindow ("Draw 3D Square"); // Set the title for the window  

	glutDisplayFunc(display); // Tell GLUT to use the method "display" for rendering  
	glutReshapeFunc(reshape); // Tell GLUT to use the method "reshape" for reshaping  
	
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // Set the background color

	glutMainLoop(); // Enter GLUT's main loop  

	return 1;
}