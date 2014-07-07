#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <stdlib.h>
#include <string.h>

#include "MotorGrafico.h"
#include "Transformacion.h"

const float TAB = 0.8;
const float X_SIZE = 500;
const float Y_SIZE = 500; 
const float ESPAI = 0.05;
const float TEXT = 0.94;
void display(void);
void init(void);
void idle(void);

const string nombre = "Test motorGrafico 2D";
//Control de eventos
void KeyPressed(unsigned char, int, int);
void KeyUp(unsigned char, int, int);
void MoveMouse(int, int);
void PassiveMoveMouse(int, int);
void MouseButton(int , int, int, int);
void mostra_text(string, float, float);

bool solid = false;

Color<float> cS(1.0,1.0,1.0);
Color<float> cP(1.0,0.0,0.0);
Color<float> cD(0.0,1.0,0.0);

//Como se instala OpenGL:
/*
freeglut3
freeglut3-dev
libglew1.5
libglew1.5-dev
libglu1-mesa
libglu1-mesa-dev
libgl1-mesa-glx
libgl1-mesa-dev
*/
//g++ -lglut -lGL -lGLU -lGLEW example.cpp -o example

/**
 * g++ lib/MotorGrafico.cc -c -Iinclude
 * g++ lib/Color.cc -c -Iinclude
 * g++ src/test.cc -c -Iinclude -lglut -lGL -lGLU -lGLEW
 * g++ -o test test.o MotorGrafico.o Color.o -lglut -lGL -lGLU -lGLEW
 */
int main(int argc, char *argv[]) {
	

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(20,20);
	glutInitWindowSize(X_SIZE, Y_SIZE);
	glutCreateWindow("Test motorGrafico 2D");
	//glutFullScreen();
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(KeyPressed);
	glutKeyboardUpFunc(KeyUp);
	glutPassiveMotionFunc(PassiveMoveMouse);
	glutMotionFunc(MoveMouse);
	glutMouseFunc(MouseButton);
	glutIdleFunc(idle);
	glutMainLoop();
	
	return 0;
}

//Inicia el estado global.
void init(void) {
	glClearColor(0.0,0.0,0.0,0.0);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}
//Pinta en la plantalla
void display(void) 
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	Point p(-0.55,0.5);
	glColor3f(1.0,1.0,0.0);
	if(solid)
		DrawSolidCircle(p,0.4,300, Color<float>(0.25,0.5,0.75));
	else
		DrawCircle(p,0.4,300, Color<float>(0.25,0.5,0.75));

	glColor3f(1.0,0.5,0.0);
	vector<Point> ver;
	ver.push_back(Point(0,0));
	ver.push_back(Point(0.8,0.0));
	ver.push_back(Point(0.8,0.6));
	ver.push_back(Point(0.4,0.3));
	ver.push_back(Point(0.2,0.6));
	ver.push_back(Point(0.0,0.2));
	Polygon p2(Point(0,0), ver);

	if(solid)
		DrawSolidPolygon(p2, Color<float>(1.0,0.5,0.0));
	else
		DrawPolygon(p2, Color<float>(1.0,0.5,0.0));

	Point centro(-0.5, -0.5);
	//Polygon(double n, Point center, double radius, double ang);
	Polygon pol(6,centro, 0.3, 0.0);
	//Polygon pol(centro, 0.3);

	if(solid)
		DrawSolidPolygon(pol, Color<float>(1.0,1.0,0.0));
	else
		DrawPolygon(pol, Color<float>(1.0,1.0,0.0));

	glColor3f(0.5,0.5,1.0);
	Point a(0.95, 0.5);
	Point b(0.8, -0.5);
	DrawLine(a,b, Color<float>(1.0,0.5,1.0));

	Color<float> colorP(0.75,0.5,0.3);
	Point ini(0,-0.3);
	DrawPoint(ini, colorP, 4);

	Point t(-0.94,0.94);
	DrawText(t, nombre, colorP);

	glFlush();
	glutSwapBuffers();		
}
//Control de las teclas pulsadas.
void KeyPressed(unsigned char key, int x, int y) {

	switch(key)
	{
	case 'w':
		solid = !solid;
		break;
	}
	glutPostRedisplay();
}
//Control de las teclas no pulsadas.
void KeyUp(unsigned char key, int x, int y) {

	glutPostRedisplay(); //Repinta si se cambian las variables del dibujo.
}

//Mover el ratón.
void MoveMouse(int x, int y)
{
	glutPostRedisplay(); //Repinta si se cambian las variables del dibujo.
}

void PassiveMoveMouse(int x, int y)
{
	glutPostRedisplay(); //Repinta si se cambian las variables del dibujo.
}

void MouseButton(int button, int state, int x, int y)
{
}
//Modifica el estado del dibujo.
void idle(void)
{
	glutPostRedisplay();
}

void mostra_text(string cadena, float x, float y) {
    unsigned int tmp;
    for(tmp=0; tmp < cadena.length(); tmp++) {         
		glRasterPos2f( x + tmp*ESPAI, y );
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,(int)cadena[tmp]);
    }
}
