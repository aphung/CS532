#include <Windows.h> // if you use Windows
#include <glut.h> 
#include <math.h>
#include <iostream>

// Vertices of Given Objects
float T1Vert1[] = {0.0f, 0.0f}; float T1Vert2[] = {50.0f, 0.0f}; float T1Vert3[] = {0.0f, 50.0f}; // Triangle 1 Vertices
float T2Vert1[] = {50.0f, 0.0f}; float T2Vert2[] = {50.0f, 50.0f}; float T2Vert3[] = {0.0f, 50.0f}; // Triangle 2 Vertices
float R1Vert1[] = {-50.0f, 75.0f}; float R1Vert2[] = {150.0f, 75.0f}; // Rectangle Vertices
float R1Vert3[] = {-50.0f, -75.0f}; float R1Vert4[] = {150.0f, -75.0f}; // Rectangle Vertices
int LineWidth = 1;
// Colors 
float ColorOrange[] = {255.0/255, 128.0/255, 0.0/255}; 
float ColorBlue[] = {128.0/255, 178.0/255, 255.0/255}; 
float ColorYellow[] = {255.0/255, 215.0/255, 0.0/255};
float ColorXAxis[] = {139.0/255, 126.0/255, 102.0/255};
float ColorYAxis[] = {220.0/255, 220.0/255, 220.0/255};

bool* keyStates = new bool[256]; // Create an array of boolean values of length 256 (0-255)  
bool* keySpecialStates = new bool[256]; // Create an array of boolean values of length 256 (0-255) 
bool Move = true; // Whether or not we are moving up or down  

int key_Flag=0; // to be used with the interactive controlls
float PI=3.1416; // to be used with the rotation of vertices
float angleR = 0.0;  // to be used with the rotation of vertices
float angleT1 = 0.0;
float angleT2 = 0.0;

double a, b, c, d;

float triangle1Angle = 0.0f;
/*--------------------------------------------------------------------------------------
 *	keyControl()																		|
 *-------------------------------------------------------------------------------------*/
void keyControl (void) {  
	if (keyStates['q']) { // If 'd' has been pressed move down
		if (Move) {  
			// Rotate Triange 1 CLOCKWISE
			key_Flag = 1;
			std::cout << key_Flag << "- q Pressed!\n";
		}
	}
	if (keyStates['w']) { // If 'd' has been pressed move down
		if (Move) {  
			// Rotate Triange 2 COUNTER-CLOCKWISE
			key_Flag = 2;
			std::cout << key_Flag << "- w Pressed!\n";
		}
	} 
	if (keyStates['e']) { // If 'd' has been pressed move down
		if (Move) {  
			// Rotate Rectangle CLOCKWISE
			key_Flag = 3;
			std::cout << key_Flag << "- e Pressed!\n";
		}
	}
} 

void init(void) {
	glClearColor (0.2f, 0.2f, 0.2f, 1.0f);
}

void idle() {
	glutPostRedisplay(); // If Re-display needed (FOR MOTION)
}

void Draw_Axes(void) {
	glPushMatrix ();
	glLineWidth (1.0);
	glBegin (GL_LINES);
	glColor3f (139.0/255, 126.0/255, 102.0/255); // X axis 
	glVertex2f (-250.0, 0.0); glVertex2f (250.0,0); 
	glColor3f (220.0/255, 220.0/255, 220.0/255); // Y axis 
	glVertex2f (0.0,-250.0); glVertex2f (0.0,250.0);
	glEnd();
	glPopMatrix ();
}

void DrawTriangle(float p1[], float p2[], float p3[], float color[]) {

	glBegin(GL_TRIANGLES);

	glColor3f(color[0], color[1], color[2]);
	glVertex2f(p1[0], p1[1]);
	glVertex2f(p2[0], p2[1]);
	glVertex2f(p3[0], p3[1]);
	
	glEnd();

	glDisable(GL_BLEND);
}

void DrawRectangle(float p1[], float p2[], float p3[], float p4[], float color[]) {

	glBegin(GL_LINE_LOOP);

	glColor3f(color[0], color[1], color[2]);
	glVertex2f(p1[0], p1[1]);
	glVertex2f(p2[0], p2[1]);
	glVertex2f(p3[0], p3[1]);
	glVertex2f(p4[0], p4[1]);

	glEnd();

	glDisable(GL_BLEND);
}

void RotateVertices(float angle, float *Vert) { 
	float dX = Vert[0];
	float dY = Vert[1];
	
	angle = angle * (PI/180.0);

	// Multiply Rotation Matrix of angle by Vertex
	Vert[0] = cos(angle) * dX + -sin(angle) * dY;
	Vert[1] = sin(angle) * dX + cos(angle) * dY;
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

void display(void) {
	keyControl(); // Check if a key was pressed
	glClear (GL_COLOR_BUFFER_BIT);
				
	if (Move) {
		Draw_Axes(); // Draw Axes

		switch(key_Flag) {
			case 1: // Rotate T1 clockwise for 30 degrees 
				angleT1 += 30.0;
				RotateVertices(angleT1, T1Vert1);
				RotateVertices(angleT1, T1Vert2);
				RotateVertices(angleT1, T1Vert3);
				key_Flag = 0;
				break;
			case 2: // Rotate T2 counter-clockwise for 30 degrees
				angleT2 -= 30.0;
				RotateVertices(angleT2, T2Vert1);
				RotateVertices(angleT2, T2Vert2);
				RotateVertices(angleT2, T2Vert3);
				key_Flag = 0;
				break;
			case 3: // Rotate rectangle clockwise for 45 degrees
				angleR -= 40.0;
				RotateVertices(angleR, R1Vert1);
				RotateVertices(angleR, R1Vert2);
				RotateVertices(angleR, R1Vert3);
				RotateVertices(angleR, R1Vert4);
				key_Flag = 0;
				break;
			default:
				key_Flag = 0;
				break;
		}

		DrawRectangle(R1Vert1, R1Vert2, R1Vert4, R1Vert3, ColorYellow); // Draw Rectangle
		DrawTriangle(T1Vert1, T1Vert2, T1Vert3, ColorOrange); // Draw Triangle 1
		DrawTriangle(T2Vert1, T2Vert2, T2Vert3, ColorBlue); // Draw Triangle 2

		glFlush ();
		Move = false;
	}
}

void reshape (int w, int h) {
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D(-(w/2.0), w/2.0, -(h/2.0), h/2.0);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity (); /* clear the matrix */
}

int main(int argc, char** argv) {
	for (int i = 0; i < 256; i++) {
		keyStates[i] = false; // Set the array of boolean values to False
		keySpecialStates[i] = false; // Set the array of boolean values to False
	}

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (100, 100);
	glutInitDisplayMode(GLUT_SINGLE); // Set up a basic display buffer (only single buffered for now) 
	glutCreateWindow ("Midterm Project");
	init();
	glutDisplayFunc(display);

	glutIdleFunc(idle); // Tell GLUT to use the method "display" as our idle method as well  

	glutKeyboardFunc(keyPressed); // Tell GLUT to use the method "keyPressed" for key presses  
	glutKeyboardUpFunc(keyUp); // Tell GLUT to use the method "keyUp" for key up events  
	glutSpecialFunc(keySpecialPressed); // Same for arrow keys
	glutSpecialUpFunc(keySpecialUp);

	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}

