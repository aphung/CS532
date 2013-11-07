#include <Windows.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <glut.h>

GLuint theObject1, theObject2;
float ORG[3] = {0,0,0}; // Origin
float XP[3] = {5,0,0}, XN[3] = {-1,0,0},
YP[3] = {0,5,0}, YN[3] = {0,-1,0},
ZP[3] = {0,0,5}, ZN[3] = {0,0,-1};


void Draw_Axes (void) {
	glLineWidth (3.0);
	glBegin (GL_LINES);
	glColor3f (1,0,0); // X axis is red.
	glVertex3fv (ORG); 	glVertex3fv (XP ); 
	glColor3f (0,1,0); // Y axis is green.
	glVertex3fv (ORG); 	glVertex3fv (YP );
	glColor3f (0,0,1); // z axis is blue.
	glVertex3fv (ORG); 	glVertex3fv (ZP ); 
	glEnd();
}

/* Draw a Sphere with Calculated Normals*/
static void Sphere(int numU, int numV, float r) {
	int i, j, k, cc=1, pp=1;
	double s, t, x, y, z, twopi, V, U;
	double pi = 3.1415926535897932384626433832795; twopi = 2 * pi;

	double rx1=0, ry1=0, rz1=0, rx2=0, ry2=0, rz2=0;
	double x1, x2, x3, x4, y1, y2, y3, y4, z1, z2, z3, z4;
	double x0=0.0, y0=0.0, z0=0.0; // Sphere Position 
	double nX=0, nY=0, nZ=0, d1, d2;
	double dn=1;

	glColor3f (1.0f, 0.2f, 0.1f); // Draw color
	for (i = 0; i <= numU; i++) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Fill Color
		glBegin(GL_QUAD_STRIP); // Quads
		for (j = 0; j <= numV; j++) {
			for (k = 1; k >= 0; k--,cc++, pp++) { // Zig-Zag the vertices
				s = (i + k) % numU + 0.5;
				t = j % numV;
				V=s*pi/numU; // Theta [0 pi]
				U=t*twopi/numV; // Phi [0 2*pi]

				x = x0+r*sin(V)*cos(U); // Sphere 
				y = y0+r*sin(V)*sin(U);
				z = z0+r*cos(V);



				// Calculate Normals as Cross product of vertices

				// 1) Add code to accumulate the coordinates of 4 vertices (i.e. x1=x,x2=x,x3=x,x4=x )
				switch (pp) {
				case 1:
					x1=x; y1=y; z1=z;
					break;
				case 2:
					x2=x; y2=y; z2=z;
					break;
				case 3:
					x3=x; y3=y; z3=z;
					break;
				case 4:
					x4=x; y4=y; z4=z;
					break;
				}

				glNormal3f(nX/dn, nY/dn, nZ/dn);

				// 2) Add code to analyze lattice vectors and find cross product
				if (pp==4) {
					rx1=x3-x1; ry1=y3-y1; rz1=z3-z1;  // r1 Latice Vector
					rx2=x2-x1; ry2=y2-y1; rz2=z2-z1; // r2 Latice Vector
					nX = ry1*rz2 - rz1*ry2; // Cross Product
					nY = rz1*rx2 - rx1*rz2;
					nZ = rx1*ry2 - ry1*rx2;
					dn=sqrt(pow(nX,2)+pow(nY,2)+pow(nZ,2));
					pp=0;
				}
				glVertex3f(x, y, z);
			}
		}
		glEnd();
	}
}

/* Draw a Sphere with Analytic Normals*/
static void SphereA(int numU, int numV, float r) {
	int i, j, k, cc=1, pp=1;
	double s, t, x, y, z, twopi, V, U;
	double pi = 3.1415926535897932384626433832795; twopi = 2 * pi;
	double x0=0.0, y0=0.0, z0=0.0;
	double nX=0, nY=0, nZ=0, d1, d2;
	double dn=1;

	glColor3f (1.0f, 0.2f, 0.1f); // Draw color
	for (i = 0; i <= numU; i++) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Fill Color
		glBegin(GL_QUAD_STRIP); // Quads
		for (j = 0; j <= numV; j++) {
			for (k = 1; k >= 0; k--,cc++, pp++) { // Zig-Zag the vertices
				s = (i + k) % numU + 0.5;
				t = j % numV;
				V=s*pi/numU; // Theta [0 pi]
				U=t*twopi/numV; // Phi [0 2*pi]
				
				// Enter Sphere equations here  
				//x = 
				//y = 
				//z = 

				// Enter Analytically calculated normals here
				//nX =  
				//nY = 
				//nZ = 
				//dn = sqrt(pow(nX,2)+pow(nY,2)+pow(nZ,2));

				glNormal3f(nX/dn, nY/dn, nZ/dn);
				glVertex3f(x, y, z);
			}
		}
		glEnd();
	}
}

/* Create display list with 2 objects and initialize state*/
static void init(void) {
	theObject1 = glGenLists (1); //creates a display list
	glNewList(theObject1, GL_COMPILE); // Define the display list
	Sphere(50, 50, 3); // 1) Draw a Sphere calculated normals
	glEndList();  // Define the display list (End)

	theObject2 = glGenLists (2); //creates a display list
	glNewList(theObject2, GL_COMPILE); // Define the display list
	SphereA(50, 50, 3); // 1) Draw a Analytic normals
	glEndList();  // Define the display list (End)

}
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the window 
	
	glPushMatrix();
	glTranslatef(-3.5, 0.0, 0.0f); //  Object 1 Position
	glCallList(theObject1); // Execute the commands in the display list
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.5, 0.0, 0.0f); //  Object 2 Position
	glCallList(theObject2); // Execute the commands in the display list
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
		glRotatef(-15,1.0,0.0,0.0);
		glutPostRedisplay();
		//PlaySound(TEXT("C:\\Users\\...\\30341__junggle__waterdrop24.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case 'y':
	case 'Y':
		glRotatef(15,0.0,1.0,0.0);
		glutPostRedisplay();
		break;
	case 'z':
	case 'Z':
		glRotatef(15,0.0,0.0,1.0);
		glutPostRedisplay();
		break;
	case 'i':
	case 'I':
		glLoadIdentity();
		gluLookAt(0, 0, 20, 0, 0, 0, 0, 1, 0);
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
	glutCreateWindow("Adding Normals to Solid Objects");
	//glutCreateWindow(argv[0]);
	init();
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	
	
	// LIGHTING and MATERIAL Properties
	GLfloat light_position[] = { 0.0, 0.0, 10.0, 1.0 }; // light position (x,y,z,w)
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
	//
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light ); // 4) diffuse
	glLightfv(GL_LIGHT0, GL_SPECULAR, light ); // 4) specular
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient); // 4) ambient
	//
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); // 5) set material properties 
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess); // 5) set material properties
	
	glClearColor (0.0, 0.0, 0.0, 0.0);
	


	glutMainLoop();
	return 0;
}

