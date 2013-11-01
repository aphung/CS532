#include <stdio.h>
#include <glut.h>
#include <math.h>

const int cWinX = 300;
const int cWinY = 200;
//const int cWinW = 640;
//const int cWinH = 480;
const int cWinW = 500; // 
const int cWinH = 500;

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
	glColor3f(0.5f, 0.7f, 1.0f); // Line color
	/* 1) viewing transformation */
	//gluLookAt (0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); //(eyeX, eyeY, eyeZ, atX, atY, atZ, upX, upY, upZ)
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); //Zoom out to see more

	/* 2) modeling transformation */
	// Compare 3 ways of implementing modeling transformations 
	int Method=2; // Chose Which Method

	switch (Method) {
	case 0:
		// 1)...3D Transform by using OGL Functions
		// Transformation code here
		glTranslatef(0.0, 0.0, 0.5);
		glTranslatef(0.0, 0.0, 1.0);
		break;
	case 1:
		// 2)...3D Transform by using matrix multiplication with OpenGL glMultMatrix. 
		// Transformation code here
		float TM[16];
		TM[0] = 1; TM[4] = 0; TM[8] = 0; TM[12] = 0;
		TM[1] = 0; TM[5] = 1; TM[9] = 0; TM[13] = 0;
		TM[2] = 0; TM[6] = 0; TM[10] = 1; TM[14] = 0.5;// <--- z-axis change here
		TM[3] = 0; TM[7] = 0; TM[11] = 0; TM[15] = 1;
		glMultMatrixf(TM); glMultMatrixf(TM); glMultMatrixf(TM); // Call multiple times (matrix stack)

		//TM[0] = 1; TM[4] = 0; TM[8] = 0; TM[12] = 0;
		//TM[1] = 0; TM[5] = 1; TM[9] = 0; TM[13] = 0;
		//TM[2] = 0; TM[6] = 0; TM[10] = 1; TM[14] = 1;// <--- z-axis change here
		//TM[3] = 0; TM[7] = 0; TM[11] = 0; TM[15] = 1;
		//glMultMatrixf(TM);
		break;
	case 2:
		// Add modifications to transform only one object here
		glPushMatrix();
		glColor3f(1.0f, 0.2f, 0.1f); // object color
		glRotatef(45.0, 0.0, 0.0, 1.0);
		glTranslatef(-3.0, 0.0, 0.0f); // Object position
		glutWireTeapot(1.0);
		glPopMatrix();

		glPushMatrix();
		glColor3f(2.0f, 1.2f, 0.1f); // object color
		glRotatef(25.0, 0.0, 0.0, 1.0);
		glTranslatef(-3.0, 0.0, 0.0f); // Object position
		glutWireTeapot(2.0);
		glPopMatrix();
		break;
	}

	// Render the primitive
	//glutWireCube(1.0);
	glColor3f(0.5f, 0.7f, 1.0f);
	glutWireTeapot(1.0);

	Draw_Axes (); // Draw xyz

	glFlush(); // Flush the OpenGL buffers to the window  


}


/*--------------------------------------------------------------------------------------
*	reshape()																			|
*-------------------------------------------------------------------------------------*/
void reshape(int width, int height) {
	/* 4) viewport transformation */
	glViewport(0, 0, (GLsizei)width, (GLsizei)height); // x,y,cWinW,cWinH - Set our viewport to the size of our window   
	//glViewport(-250, -250, (GLsizei)width*2.0, (GLsizei)height*2.0); // x,y,cWinW,cWinH - Set our viewport to the size of our window   
	glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed  
	glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)
	/* 3) projection transformation */
	glFrustum (-1.0, 1.0, -1.0, 1.0, 1.0, 10.0);  // (left, right, bottom, top, near, far)
	glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly  
}


/*--------------------------------------------------------------------------------------
*	main()																				|
*-------------------------------------------------------------------------------------*/
int main(int argc, char** argv) {
	glutInit(&argc, argv); // Initialize GLUT  
	glutInitWindowSize(cWinW, cWinH); // Set the width and height of the window  
	glutInitWindowPosition(cWinX, cWinY); // Set the position of the window  
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set up a basic display buffer (only single buffered for now) 
	glutCreateWindow ("3D Transformation"); // Set the title for the window  

	glutDisplayFunc(display); // Tell GLUT to use the method "display" for rendering  
	glutReshapeFunc(reshape); // Tell GLUT to use the method "reshape" for reshaping  

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // Set the background color

	glutMainLoop(); // Enter GLUT's main loop  

	return 1;
}