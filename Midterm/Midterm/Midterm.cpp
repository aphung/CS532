#include <Windows.h> // if you use Windows
#include <glut.h> 
#include <math.h>

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
float angle;  // to be used with the rotation of vertices

double a, b, c, d;

float triangle1Angle = 0.0f;
/*--------------------------------------------------------------------------------------
 *	keyControl()																		|
 *-------------------------------------------------------------------------------------*/
void keyControl (void) {  
	if (keyStates['q'] || keySpecialStates[GLUT_KEY_DOWN]) { // If 'd' has been pressed move down
		if (Move) {  
			// Rotate Triange 1 CLOCKWISE
			key_Flag = 1;
		}
	}
	if (keyStates['w'] || keySpecialStates[GLUT_KEY_DOWN]) { // If 'd' has been pressed move down
		if (Move) {  
			// Rotate Triange 2 COUNTER-CLOCKWISE
			key_Flag = 2;
		}
	} 
	if (keyStates['e'] || keySpecialStates[GLUT_KEY_DOWN]) { // If 'd' has been pressed move down
		if (Move) {  
			// Rotate Rectangle CLOCKWISE
			key_Flag = 3;
		}
	}
} 

void init(void) {
	glClearColor (0.2f, 0.2f, 0.2f, 1.0f);
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

float RotateVertices(float angle, float *Vert) { 
	// Multiply Rotation Matrix of angle by Vertex
	return 0.0f;
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

	Draw_Axes(); // Draw Axes

	// Set rectangle and triangle as array
	float rectangleX [4] = { R1Vert1[0], R1Vert2[0], R1Vert4[0], R1Vert3[0] };
	float rectangleY [4] = { R1Vert1[1], R1Vert2[1], R1Vert4[1], R1Vert3[1] };
	float triangle1X [3] = { T1Vert1[0], T1Vert2[0], T1Vert3[0] };
	float triangle1Y [3] = { T1Vert1[1], T1Vert2[1], T1Vert3[1] };
	float triangle2X [3] = { T2Vert1[0], T2Vert2[0], T2Vert3[0] };
	float triangle2Y [3] = { T2Vert1[1], T2Vert2[1], T2Vert3[1] };

	// Transformation Arrays
	float dRectangleX [4] = { 0, 0, 0, 0 };
	float dRectangleY [4] = { 0, 0, 0, 0 };

	float dTriangle1X [3] = { 0, 0, 0 };
	float dTriangle1Y [3] = { 0, 0, 0 };

	float dTriangle2X [3] = { 0, 0, 0 };
	float dTriangle2Y [3] = { 0, 0, 0 };

	// if (key_Flag==3) Rotate rectangle clockwise for 45 degrees
	// if (key_Flag==1) Rotate T1 clockwise for 30 degrees
	// if (key_Flag==2) Rotate T2 counter-clockwise for 30 degrees
	switch(key_Flag) {
		case 1: // Rotate T1 clockwise for 30 degrees
			triangle1Angle -= 30.0;
			a = cos(triangle1Angle);
			b = -sin(triangle1Angle);
			c = sin(triangle1Angle);
			d = cos(triangle1Angle);
			for (int i = 0; i < 3; i++) {
				dTriangle1X[i] = a*triangle1X[i]+b*triangle1Y[i];
				dTriangle1Y[i] = c*dTriangle1X[i]+d*dTriangle1Y[i];
			}
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
	}


	DrawRectangle(R1Vert1, R1Vert2, R1Vert4, R1Vert3, ColorYellow); // Draw Rectangle

	float p1[] = { dTriangle1X[0], dTriangle1Y[0] };
	float p2[] = { dTriangle1X[1], dTriangle1Y[1] };
	float p3[] = { dTriangle1X[2], dTriangle1Y[2] };
	DrawTriangle(p1, p2, p3, ColorOrange); // Draw Triangle 1

	DrawTriangle(T2Vert1, T2Vert2, T2Vert3, ColorBlue); // Draw Triangle 2

	glFlush ();
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
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Midterm Project");
	init ();
	glutDisplayFunc(display);

	glutKeyboardFunc(keyPressed); // Tell GLUT to use the method "keyPressed" for key presses  
	glutKeyboardUpFunc(keyUp); // Tell GLUT to use the method "keyUp" for key up events  
	glutSpecialFunc(keySpecialPressed); // Same for arrow keys
	glutSpecialUpFunc(keySpecialUp);

	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}

