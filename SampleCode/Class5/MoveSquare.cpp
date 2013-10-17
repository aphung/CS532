#include <stdio.h>
#include <glut.h>
#include <math.h>


const int cWinX = 300;
const int cWinY = 200;
const int cWinW = 640;
const int cWinH = 480;

bool* keyStates = new bool[256]; // Create an array of boolean values of length 256 (0-255)  
bool* keySpecialStates = new bool[256]; // Create an array of boolean values of length 256 (0-255) 
  
bool Move = true; // Whether or not we are moving up or down  
float yLocation = 0.0f; // Keep track of our position on the y axis.  
float xLocation = 0.0f; // Keep track of our position on the X axis.

float zRotationAngle = 0.0f; // The angle of rotation for our object  

/*--------------------------------------------------------------------------------------
 *	keyControl()																		|
 *-------------------------------------------------------------------------------------*/
void keyControl (void) {  
	if (keyStates['d'] || keySpecialStates[GLUT_KEY_DOWN]) { // If 'd' has been pressed move down
		if (Move) {  
			yLocation -= 0.1f; // Move down along the yLocation  
		}
	}  
	if (keyStates['u'] || keySpecialStates[GLUT_KEY_UP]) { // If 'u' has been pressed move up
		if (Move) {
			yLocation += 0.1f; // Move up along the yLocation  
		}
	}  
	if (keyStates['l'] || keySpecialStates[GLUT_KEY_LEFT]) { // If 'l' has been pressed move left
		if (Move) {  
			xLocation -= 0.1f; // Move left along the xLocation  
		}
	}  
	if (keyStates['r'] || keySpecialStates[GLUT_KEY_RIGHT]) { // If 'r' has been pressed move right
		if (Move) { 
			xLocation += 0.1f; // Move right along the xLocation  
		}
	}  

	if (keyStates['t']) { // If 't' has been pressed rotate clockwise
		if (Move) {  
			zRotationAngle += 0.2f; // Increment rotation value  
		}
	}  
	if (keyStates['y']) { // If 't' has been pressed rotate counter clockwise 
		if (Move) {  
			zRotationAngle -= 0.2f; // Increment rotation value  
		}
	}  
}  

/*--------------------------------------------------------------------------------------
 *	keyPress()																			|
 *-------------------------------------------------------------------------------------*/
void keyPressed (unsigned char key, int x, int y) {  
	keyStates[key] = true; // Set the state of the current key to pressed  
	Move = true;
}
  
void keyUp (unsigned char key, int x, int y) {  
	keyStates[key] = false; // Set the state of the current key to not pressed
}  

void keySpecialPressed(int key, int x, int y) {
	keySpecialStates[key] = true; // Set the state of the current key to pressed  
	Move = true;
}

void keySpecialUp(int key, int x, int y) {
	keySpecialStates[key] = false; // Set the state of the current key to not pressed
}

/*--------------------------------------------------------------------------------------
 *	DrawLineLoopGL()																	|
 *-------------------------------------------------------------------------------------*/
void DrawLineLoopGL(double *x, double *y, int width) {
	// Enables anti-aliasing
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Draw the Square with line segments
	glLineWidth(width); // Line Width
	glBegin(GL_LINE_LOOP); // Draw Line (GL_LINE_LOOP)
	glVertex2i(x[0], y[0]); glVertex2i(x[1], y[1]); glVertex2i(x[2], y[2]); glVertex2i(x[3], y[3]); 
	
	glEnd(); // Done Drawing

	// Draw the Square as Quad
	//glLineWidth(width); // Line Width
	//glBegin(GL_QUADS); // Draw Square
	//glVertex2i(x[0], y[0]); glVertex2i(x[1], y[1]); glVertex2i(x[2], y[2]); glVertex2i(x[3], y[3]); 
	//glEnd(); // Done Drawing

	glDisable(GL_BLEND);

}

 
/*--------------------------------------------------------------------------------------
 *	display()																			|
 *-------------------------------------------------------------------------------------*/
void display() {
	keyControl(); // Check if a key was pressed
	
	double X [4] = {200, 300, 300, 200}; // x vertices coordinates
	double Y [4] = {200, 200, 300, 300}; // y vertices coordinates	



	if (Move) {
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // Set the background color
		glColor3f(1.0f, 0.5f, 0.1f); // Line color (Orange)
		glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer 
		
		/*--------------------------------------------------------------------------------------
		*	Enter your transformation code here													|
		*	Use DrawLineLoopGL(X, Y, 5); to Render the primitive								|
		*--------------------------------------------------------------------------------------*/
		// 



		glFlush(); // Flush the OpenGL buffers to the window s
		Move = false;
	}
}


/*--------------------------------------------------------------------------------------
 *	reshape()																			|
 *-------------------------------------------------------------------------------------*/
void reshape(int width, int height) {
	glViewport(0, 0, (GLsizei)width, (GLsizei)height); // x,y,cWinW,cWinH - Set our viewport to the size of our window   
	glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed  
	glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)  
	gluOrtho2D(0, width, height, 0); // Set the origin in the upper left corner.  
	glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly  
}

/*--------------------------------------------------------------------------------------
 *	idle()																				|
 *-------------------------------------------------------------------------------------*/
void idle() {
	glutPostRedisplay(); // If Re-display needed (FOR MOTION)
}


/*--------------------------------------------------------------------------------------
 *	main()																				|
 *-------------------------------------------------------------------------------------*/
int main(int argc, char **argv) {
	for (int i = 0; i < 256; i++) {
		keyStates[i] = false; // Set the array of boolean values to False
		keySpecialStates[i] = false; // Set the array of boolean values to False
	}

	glutInit(&argc, argv); // Initialize GLUT  
	glutInitWindowSize(cWinW, cWinH); // Set the width and height of the window  
	glutInitWindowPosition(cWinX, cWinY); // Set the position of the window  
	glutInitDisplayMode(GLUT_SINGLE); // Set up a basic display buffer (only single buffered for now) 
	glutCreateWindow ("Move the Square"); // Set the title for the window  

	glutDisplayFunc(display); // Tell GLUT to use the method "display" for rendering  
	glutIdleFunc(idle); // Tell GLUT to use the method "display" as our idle method as well  
	glutReshapeFunc(reshape); // Tell GLUT to use the method "reshape" for reshaping  

	glutKeyboardFunc(keyPressed); // Tell GLUT to use the method "keyPressed" for key presses  
	glutKeyboardUpFunc(keyUp); // Tell GLUT to use the method "keyUp" for key up events  
	glutSpecialFunc(keySpecialPressed); // Same for arrow keys
	glutSpecialUpFunc(keySpecialUp);

	glutMainLoop(); // Enter GLUT's main loop  

}