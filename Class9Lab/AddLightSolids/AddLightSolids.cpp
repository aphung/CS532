#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <glut.h>

GLuint theObject;
float ORG[3] = {0,0,0}; // Origin
float XP[3] = {5,0,0}, XN[3] = {-1,0,0},
YP[3] = {0,5,0}, YN[3] = {0,-1,0},
ZP[3] = {0,0,5}, ZN[3] = {0,0,-1};


void Draw_Axes (void) {
	glLineWidth (2.0);
	glBegin (GL_LINES);
	glColor3f (1,0,0); // X axis is red.
	glVertex3fv (ORG); 	glVertex3fv (XP ); 
	glColor3f (0,1,0); // Y axis is green.
	glVertex3fv (ORG); 	glVertex3fv (YP );
	glColor3f (0,0,1); // z axis is blue.
	glVertex3fv (ORG); 	glVertex3fv (ZP ); 
	glEnd();
}


/* Draw a Solid DisplayList Object with Analytic Normals*/
// Insert code from DisplayListObjects.cpp and add Normals



/* Create display list Object and initialize state*/
static void init(void) {
	//Insert DisplayList Object code here

}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the window 

	//glCallList(theObject); // Execute the commands in the display list
	
	// Solid Objects
	glPushMatrix();
	glColor3f(0.5f, 0.7f, 1.0f); // Object Color   
	glTranslatef(3.0, 3.0, 0.0f); //  Object Position
	glutSolidCube(2.0f); // Plot Solid Objects
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5f, 0.2f, 0.5f); // Object Color   
	glTranslatef(-3.0, 2.0, 0.0f); //  Object Position
	glutSolidCube(3.0f); // Plot Solid Objects
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 0.2f, 0.1f); // Object Color   
	glTranslatef(1.0, -2.0, 0.0f); //  Object Position
	glutSolidSphere(2.0, 20, 20); // Plot Solid Objects
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(1.0f, 0.5f, 0.7f); // Object Color   
	glTranslatef(-3.0, -3.0, -2.0f); //  Object Position
	glutSolidCone(2.0, 5, 20,20); // Plot Solid Objects
	glPopMatrix();
	
	Draw_Axes (); // 
	glFlush();
}
void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat) w/(GLfloat) h, 1.0, 80.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 30, 0, 0, 0, 0, 1, 0);
}
/* Rotate about x-axis when "x" typed; rotate about y-axis when "y" typed; "i" returns torus to original view */
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'x':
	case 'X':
		glRotatef(30.,1.0,0.0,0.0);
		glutPostRedisplay();
		break;
	case 'y':
	case 'Y':
		glRotatef(30.,0.0,1.0,0.0);
		glutPostRedisplay();
		break;
	case 'z':
	case 'Z':
		glRotatef(30.,0.0,0.0,1.0);
		glutPostRedisplay();
		break;
	case 'i':
	case 'I':
		glLoadIdentity();
		gluLookAt(0, 0, 20, 0, 0, 0, 0, 1, 0);
		glutPostRedisplay();
		break;
	case 'u':
	case 'U':
		glLoadIdentity();
		gluLookAt(0, 0, 30, 0, 0, 0, 0, 1, 0);
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	}
}
int main(int argc, char **argv) {
	glutInitWindowSize(950, 700);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Solid Objects");
	//init();
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	
	
	// LIGHTING and MATERIAL Properties
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 1.0 }; // light position (x,y,z,w)
	GLfloat light[] = {0.5, 0.5, 0.0 }; // Light Color
	GLfloat lmodel_ambient[] = { 0.1, 0.5, 0.7, 1.0 }; // Ambient Light Color

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 }; //
	GLfloat mat_shininess[] = { 50.0 }; //
	
	glShadeModel (GL_SMOOTH);

	// Light
	glEnable(GL_LIGHTING); // 2) enable Phong lighting calculation
	glEnable(GL_LIGHT0); // 2) up to eight point sources ( radiating in all directions )
	glEnable(GL_DEPTH_TEST); // 2) Depth Perception
	
	// Position light
	glLightfv(GL_LIGHT0, GL_POSITION, light_position); // 2) set light position

	glEnable(GL_COLOR_MATERIAL); // 3) enable color driven materials
	
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light ); // 4) diffuse
	glLightfv(GL_LIGHT0, GL_SPECULAR, light ); // 4) specular
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient); // 4) ambient
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); // 5) set material properties 
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess); // 5) set material properties
	
	glClearColor (0.0, 0.0, 0.0, 0.0);
	

	glutMainLoop();
	return 0;
}

