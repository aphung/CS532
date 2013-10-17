#include <stdio.h>
#include <glut.h>
#include <math.h>


const int cWinX = 300;
const int cWinY = 200;
const int cWinW = 640;
const int cWinH = 480;


/*--------------------------------------------------------------------------------------
 *	DrawLineLoopGL()																		|
 *-------------------------------------------------------------------------------------*/
//void DrawLineLoopGL(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int width) {
void DrawLineLoopGL(double *x, double *y, int width) {
	//glDisable(GL_TEXTURE_2D);

	// Enables anti-aliasing
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Draw the line
	glLineWidth(width); // Line Width
	glBegin(GL_LINE_LOOP); // Draw Line (GL_LINE_LOOP)
	glVertex2i(x[0], y[0]); glVertex2i(x[1], y[1]); glVertex2i(x[2], y[2]); glVertex2i(x[3], y[3]); 
	
	glEnd(); // Done Drawing

	// Draw the Square
	//glLineWidth(width); // Line Width
	//glBegin(GL_QUADS); // Draw Square
	//glVertex2i(x[0], y[0]); glVertex2i(x[1], y[1]); glVertex2i(x[2], y[2]); glVertex2i(x[3], y[3]); 
	//glEnd(); // Done Drawing

	glDisable(GL_BLEND);
	//glEnable(GL_TEXTURE_2D);
}

 
/*--------------------------------------------------------------------------------------
 *	display()																			|
 *-------------------------------------------------------------------------------------*/
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//GLshort X [4] = {200, 300, 300, 200}; // x vertices coordinates
	double X [4] = {200, 300, 300, 200}; // x vertices coordinates
	double Y [4] = {200, 200, 300, 300}; // y vertices coordinates

	// THIS IS WHERE WE DO OUR DRAWING
	glColor3f(1.0f, 0.5f, 0.1f); // Line color (Orange)
	DrawLineLoopGL(X, Y, 5);

	// 2D Transformation Parameters
	double a=0.71; // (rot/scale/reflection)
	double b=-0.71; // (rot/shear)
	double c=0.71; //(rot/scale/reflection)
	double d=0.71; // (rot/shear)
	double tx=100; // X-Translation
	double ty=50; // Y-Translation


	double Xn[4] = {0, 0, 0, 0}; // x vertices coordinates
	double Yn[4] = {0, 0, 0, 0}; // x vertices coordinates

	for (int i = 0; i <= 3; i++) {
		Xn[i] = a*X[i]+b*Y[i]+tx; // x' = ax+by+tx
		Yn[i] = c*X[i]+d*Y[i]+ty;;// y' = cx+dy+ty
	}
	glColor3f(0.5f, 1.0f, 0.1f); // Line color (Green)
	DrawLineLoopGL(Xn, Yn, 5);
	
	glutSwapBuffers();
}


/*--------------------------------------------------------------------------------------
 *	reshape()																			|
 *-------------------------------------------------------------------------------------*/
void reshape(int width, int height) {
	
	// Set up orthographic projection such that each point corresponds to a pixel. 
	// The origin is set to be in the upper left corner. 
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, height, 0);
	glMatrixMode(GL_MODELVIEW);
}

/*--------------------------------------------------------------------------------------
 *	idle()																				|
 *-------------------------------------------------------------------------------------*/
void idle() {
	glutPostRedisplay();
}

//void MultiplyMatrix(float * M, float * v, float * w) {
//	double[][] M = new double[r][c];
//	double[] v = new double[c];
//	double w = new double[r];
//	for (int i = 0; i < r; i++) {
//		w[i] = 0;
//		for (int j = 0; j < c; j++) {
//			w[i] = w[i] + M[i][j] * v[j];
//		}
//	}
//}

/*--------------------------------------------------------------------------------------
 *	main()																				|
 *-------------------------------------------------------------------------------------*/
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowPosition(cWinX, cWinY);
	glutInitWindowSize(cWinW, cWinH);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("My Window");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);// Set the background color
	
	glutMainLoop();
	return 1;
}