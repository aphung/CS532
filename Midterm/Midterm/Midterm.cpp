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

int key_Flag=0; // to be used with the interactive controlls
float PI=3.1416; // to be used with the rotation of vertices
float angle;  // to be used with the rotation of vertices

void init(void)
{
	glClearColor (0.2f, 0.2f, 0.2f, 1.0f);
}

void Draw_Axes (void) {
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

void DrawTriangle() {

}

void DrawRectangle() {

}

float RotateVertices(float angle, float *Vert) { 
	// Multiply Rotation Matrix of angle by Vertex
	return 0.0f;
}

void display(void) {
	glClear (GL_COLOR_BUFFER_BIT);

	Draw_Axes (); // 

	// if (key_Flag==3) Rotate rectangle clockwise for 45 degrees
	// if (key_Flag==1) Rotate T1 clockwise for 30 degrees
	// if (key_Flag==2) Rotate T2 counter-clockwise for 30 degrees


	DrawRectangle(); // Draw Rectangle
	DrawTriangle(); // Draw Triangle 1
	DrawTriangle(); // Draw Triangle 2

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

	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}

