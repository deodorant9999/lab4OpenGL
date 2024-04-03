#include "glos.h"

#include "gl.h"
#include "glu.h"
#include "glaux.h"

GLUnurbsObj* theNurb;

void myInit()
{
	glShadeModel(GL_FLAT);
	theNurb = gluNewNurbsRenderer(); // obiectul de tip GLUnurbsObj este creat dinamic prin apelul functiei gluNewNurbsRenderer()
	gluNurbsProperty(theNurb, GLU_SAMPLING_TOLERANCE, 10.0); // eroarea de esantionare a curbei la redare
}

void CALLBACK display()
{	
	glLoadIdentity();

	// 4 puncte de control
	GLfloat ctlpoints[16][3] = {
		{1, 0.5, 0.0},
		{0.5, 0.25, 0.0},
		{0.0, 0.25, 0.0},
		{-0.5, 0.5, 0.0},
		{-0.85, 1.0, 0.0},
		{-0.85, 1.5, 0.0},
		{-0.5, 2.0, 0.0},
		{0.0, 2.25, 0.0},
		{0.5, 2.25, 0.0},
		{1.0, 2.0, 0.0},
		{1.25, 1.90, 0.0},
		{1.25, 1.35, 0.0},
		{1.0, 1.25, 0.0},
		{0.85, 1.0, 0.0},
		{0.15, 1.0, 0.0},
		{0.0, 1.25, 0.0}
	};

	// 8 noduri
	GLfloat knots[20] = { 0.0, 0.0, 0.0, 0.0, 1.0, 2.0, 3.0, 4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0,13.0,13.0,13.0 };
	//   GLfloat knots[8] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0};
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0); // culoarea curenta de desenare
	// incepe corpul de redare al curbei Spline
	gluBeginCurve(theNurb);
	gluNurbsCurve(theNurb,	// pointer obiect NURBS
		20, knots,			// numar noduri, tablou noduri
		sizeof(ctlpoints[0]) / sizeof(GLfloat), // intervalul de valori dintre doua puncte de control consecutive
		&ctlpoints[0][0],	// vector puncte de control
		4,					// ordinul curbei 
		GL_MAP1_VERTEX_3);	// tip evaluator
	gluEndCurve(theNurb);

	glFlush();
}

void CALLBACK myReshape(GLsizei w, GLsizei h)
{
	if (!h) return;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		gluOrtho2D(-5.0, 5.0, -5.0 * (GLfloat)h / (GLfloat)w, 5.0 * (GLfloat)h / (GLfloat)w);
	}
	else {
		gluOrtho2D(-5.0 * (GLfloat)w / (GLfloat)h, 5.0 * (GLfloat)w / (GLfloat)h, -5.0, 5.0);
	}
	glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char** argv)
{
	auxInitDisplayMode(AUX_SINGLE | AUX_RGB);
	auxInitPosition(0, 0, 500, 500);
	auxInitWindow("Curba B-spline");
	myInit();
	auxReshapeFunc(myReshape);
	auxMainLoop(display);
	return 0;
}
