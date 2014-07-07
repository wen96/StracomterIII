#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <stdlib.h>
#include <string.h>

#include "MotorGrafico.h"
#include "Transformacion.h"
#include "Point.h"
#include "Polygon.h"

const float TAB = 0.8;
const float X_SIZE = 800;
const float Y_SIZE = 600;
const float ESPAI = 0.05;
const float TEXT = 0.94;
void display(void);
void reshape ( int w, int h);
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
Transform t;

Color<float> cS(1.0,1.0,1.0);
Color<float> cP(1.0,0.0,0.0);
Color<float> cD(0.0,1.0,0.0);

float  w = X_SIZE;
float h = Y_SIZE;
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
	glutInitWindowSize(w, h);
	glutCreateWindow("Test motorGrafico 2D");
	//glutFullScreen();
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
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
}
//Pinta en la plantalla
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT); // borro la pantalla.
	glMatrixMode(GL_MODELVIEW); // modo matriz de transformacion

	t.loadOpenGL();
	DrawPolygon(Polygon(4, Point(0,0), 10, 45), cD);

	glutSwapBuffers(); //Cambio los buffers

}

void reshape ( int w, int h)
{
	glViewport(0,0,w,h); // coloque el viewport al tamano de la ventana
	glMatrixMode(GL_PROJECTION); // modo matriz de proyeccion
		glLoadIdentity(); // inicialize la matriz
		glOrtho(0, w, 0, h, -1, 1); // tranformacion directa a pantalla
		//glScalef(1, 1, 1); // invierta Y para que vaya para abajo
		//glTranslatef(0, -h, 0); // corra el origen a la parte superior izq.

	glMatrixMode(GL_MODELVIEW); // modo matriz de transformacion
		glLoadIdentity(); // inicialize la matriz

}


//Control de las teclas pulsadas.
void KeyPressed(unsigned char key, int x, int y) {

	switch(key) {

	case 'w':
		t.addTranslation(0,-5,0);
		break;
	case 's':
		t.addTranslation(0,5,0);
		break;
	case 'a':
		t.addTranslation(-5,0,0);
		break;
	case 'd':
		t.addTranslation(5,0,0);
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
