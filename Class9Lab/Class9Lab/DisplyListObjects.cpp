#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <glut.h>


float PI=3.1415926535897932384626433832795; // 
float ZOOM = 30;
GLuint theObject;

/* Draw Display List Object */
static void Object(int numU, int numV, float r, int R) {
	int i, j, k;
	double s, t, x, y, z, twopi, V, U;
	twopi = 2 * PI;
	for (i = 0; i < numU; i++) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe
		glBegin(GL_QUAD_STRIP); // Quads
		//glBegin(GL_TRIANGLE_STRIP); // Triangles
		for (j = 0; j <= numV; j++) {
			for (k = 1; k >= 0; k--) {
				s = (i + k) % numU + 0.5;
				t = j % numV;
				V=s*twopi/numU; // Phi
				U=t*twopi/numV; // Theta
				
				//// Object Parametric Coordinates Here
				// Insert Parametric x(U,V)
				// Insert Parametric y(U,V)
				// Insert Parametric z(U,V)

				// Sphere
				//x = R * sin(V) * cos(U);
				//y = R * sin(V) * sin(U);
				//z = R * cos(V);

				// Cylinder
				//x = r * cos(V);
				//y = r * sin(V);
				//z = U;

				// Torus
				//x = (R + r * cos(U)) * cos(V);
				//y = (R + r * cos(U)) * sin(V);
				//z = r * sin(U);

				// Double Funnel
				x = R * pow(cos(U), 3) * pow(cos(V), 2);
				y = R * pow(cos(U), 3) * pow(sin(V-1), 2);
				z = R * pow(sin(U), 2);


				glVertex3f(x, y, z);
			}
		}
		glEnd();
	}
}
/* Create display list with Torus and initialize state*/
static void init(void) {
	theObject = glGenLists (1); //creates a display list
	glNewList(theObject, GL_COMPILE); // Define the display list

	// Draw Display List Objects 
	Object(50.0, 50.0, 9.0, 9.0); // Draw display list Objec

	glEndList();  // Define the display list (End)

	glShadeModel(GL_SMOOTH);
	glClearColor(0.0, 0.0, 0.0, 0.0);
}
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT); // Clear the window 
	glColor3f (0.5f, 0.7f, 1.0f);  // Draw color
	glCallList(theObject); // Execute the commands in the display list
	glFlush();
}
void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat) w/(GLfloat) h, 1.0, 80.0);
	//glFrustum (-40.0, 40.0, -40.0, 40.0, -20.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, ZOOM, 0, 0, 0, 0, 1, 0);
}

/* Rotate about x-axis when "x" typed; rotate about y-axis when "y" typed; "i" returns object to original view */
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'x':
	case 'X':
		glRotatef(15.0,1.0,0.0,0.0);
		glutPostRedisplay();
		break;
		// Insert Rotation along y & z axis here
	case 'y':
	case 'Y':
		glRotatef(15.0, 0.0, 1.0, 0.0);
		glutPostRedisplay();
		break;
	case 'z':
	case 'Z':
		glRotatef(15.0, 0.0, 0.0, 1.0);
		glutPostRedisplay();
		break;
	// Insert zoom in/out code here
	case '_':
	case '-':
		ZOOM -= 1;
		glLoadIdentity();
		gluLookAt(0, 0, ZOOM, 0, 0, 0, 0, 1, 0);
		glutPostRedisplay();
		break;
	case '=':
	case '+':
		ZOOM += 1;
		glLoadIdentity();
		gluLookAt(0, 0, ZOOM, 0, 0, 0, 0, 1, 0);
		glutPostRedisplay();
		break;

	// Return to Normal
	case 'i':
	case 'I':
		glLoadIdentity();
		ZOOM = 30;
		gluLookAt(0, 0, 30, 0, 0, 0, 0, 1, 0);
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	}
}

int main(int argc, char **argv) {
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(200, 200);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Wireframe Surfaces");
	init();
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}