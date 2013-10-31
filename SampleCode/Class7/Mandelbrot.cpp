#include <stdio.h>
#include <math.h>
#include <complex>
#include <glut.h>
using namespace std; //

const int cWinW = 500;
const int cWinH = 500;

const int depth = 100; // Iteration Depth
const int n=1000; // Number of Grid points
int xc=255, yc=255;


void init(void)
{
	glClearColor (0.2f, 0.2f, 0.2f, 1.0f);
	glShadeModel (GL_FLAT);
}
int Mandelbrot(float x, float y, int k){
	complex <float> z0 (x,y);
	complex <float> z (0,0);
	while ((abs(z) < 2) && (k < depth)) {
		z = z*z+z0;
		k = k + 1;
	}    
	return k;
}
int SineMandelbrot(float x, float y, int k){
	complex <float> z0 (x,y);
	complex <float> z = z0;
	while ((abs(z) < 2*3.14) && (k < depth)) {
		z = z0*sin(z);
		k = k + 1;
	}    
	return k;
}
void display(void) {
	glClear (GL_COLOR_BUFFER_BIT);
	glLoadIdentity (); /* clear the matrix */

	// Mandelbrot
	float Delta=0.003; // Grid Step
	float x0=-0.5; // X start point
	float y0=0.0; // Y start point
	//float x0=-0.77; // X start point
	//float y0=+0.25; // Y start point
	//Delta=Delta/10; // Grid Step

	// Sine Mandelbrot
	//float Delta=0.003; // Grid Step
	//float x0=0.0; // X start point
	//float y0=0.0; // Y start point

	float x1=x0-Delta*n/2, x2=x0+Delta*n/2; // X range
	float y1=y0-Delta*n/2, y2=y0+Delta*n/2; // Y range
	gluOrtho2D (x1, x2, y1, y2); // Set up the size of the canvas

	float x0_new = x1-(cWinW/(xc+1)*(x2-x1));

	//GLint viewport[4];
	//GLdouble modelview[16];
	//GLdouble projection[16];
	//GLfloat winX, winY, winZ;
	//GLdouble posX, posY, posZ;
	//glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	//glGetDoublev( GL_PROJECTION_MATRIX, projection );
	//glGetIntegerv( GL_VIEWPORT, viewport );
 //
 //   winX = (float)xc;
 //   winY = (float)viewport[3] - (float)yc;
 //  // lReadPixels( xc, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

	//float b=projection[1], c=projection[2];


	glBegin(GL_POINTS);

	// Loop the canvas grid
	for (float x = x1; x <= x2; x+=Delta) {
		int yc=1; // counter
		for (float y = y1; y <= y2; y+=Delta) {
			int k = 0;
			k=Mandelbrot(x,y,k); // Mandelbrot 
			k=SineMandelbrot(x,y,k); // Sine Mandelbrot 

			// Colormapping of k to RGB
			float kr, kg, kb; 
			if (k==100) {
				kr=0.5; kg=0; kb=0; // The inside of the set
			}
			else {
				/*--------------------------------------------------------------------------------------
				*	Insert Your color mapping code here												|
				*--------------------------------------------------------------------------------------*/
				//kr=; // linear 
				//kg=; // increasing
				//kb=; // decreasing
			}

			glColor3f(kr, kg, kb); // Pixel Color
			glVertex2f(x, y); // Plot pixel
		}
	}
	
	glEnd();
	glFlush ();
}
void reshape (int w, int h) {
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	//glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	glMatrixMode (GL_MODELVIEW);


}
void mouseClick(int button, int state, int xc, int yc) {

	switch(button) {
	case GLUT_LEFT_BUTTON:
		printf(" LEFT ");
		if (state == GLUT_DOWN) {
			printf("DOWN\n");
			printf("(%d, %d)\n", xc, yc);
		}
		else 
			if (state == GLUT_UP) {
				printf("UP\n");
			}
			break;

	default:
		break;
	}
	fflush(stdout);  // Force output to stdout

}
void idle() {
	//glutPostRedisplay(); // 
}

//CVector3 GetOGLPos(int x, int y) {
//    GLint viewport[4];
//    GLdouble modelview[16];
//    GLdouble projection[16];
//    GLfloat winX, winY, winZ;
//    GLdouble posX, posY, posZ;
// 
//    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
//    glGetDoublev( GL_PROJECTION_MATRIX, projection );
//    glGetIntegerv( GL_VIEWPORT, viewport );
// 
//    winX = (float)x;
//    winY = (float)viewport[3] - (float)y;
//    glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
// 
//    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
// 
//    return CVector3(posX, posY, posZ);
//}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); 
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_INDEX);
	glutInitWindowSize (cWinW, cWinH);
	glutInitWindowPosition (10, 30);
	glutCreateWindow ("The Mandelbrot Set");
	init ();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouseClick);
	glutMainLoop();

	return 0;
}


