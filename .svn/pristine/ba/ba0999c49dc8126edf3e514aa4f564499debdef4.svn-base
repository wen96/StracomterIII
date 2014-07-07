#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <Polygon.h>
#include <MotorGrafico.h>
#include <iostream>
#include "TWindow.h"
#include "Map.h"
#include "Pathfinder.h"

using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;

void Reshape();
void DrawTriangle(Point a, Point b, Point c, Color<float> color);

int main(int argc, char *argv[]) {
	/*TWindow window;
	window.openSFML(WIDTH, HEIGHT, false);
	window.Init();

	Color<float> color(0.0, 0.0, 1.0);
	std::vector<Point> puntos;

	Pathfinder pathF(Point(0,0), Point(800, 600), 10);

	if(argc == 2)
		pathF.setMap(argv[1]);
	else
		pathF.setMap("map_02.txt");

	Map mapa;
	if(argc == 2)
		mapa.setMap(argv[1]);
	else
		mapa.setMap("map_02.txt");

	std::vector<Point> puntosMapa = mapa.getVertex();
	std::vector<std::vector<Point> > objetosMapaExp = pathF.getExpPoints();
	std::vector<std::vector<Point> > objetosMapa = mapa.getObjects();

	std::vector<Color<float> > colores;

	//Mientras la ventana este abierta (que se cierra con Esc o con la X de cerrarla)
	while (window.isOpen()) {
		//Limpieza de color de la ventana (en este caso la limpio a blanco)
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		std::vector<Point>::iterator piter;

		color.setColor(0.0, 0.0, 0.0);
		for (piter = puntosMapa.begin(); piter != puntosMapa.end(); piter++) {
			if (piter == puntosMapa.end() - 1)
				DrawLine(*piter, *(puntosMapa.begin()), color, 2);
			else
				DrawLine(*piter, *(piter + 1), color, 2);
			DrawSolidCircle(*piter, 3.0, color);
		}
		std::vector<std::vector<Point> >::iterator vvIter;
		for(vvIter = objetosMapa.begin(); vvIter != objetosMapa.end(); vvIter++){
			for (piter = (*vvIter).begin(); piter != (*vvIter).end(); piter++) {
				if (piter == (*vvIter).end() - 1)
					DrawLine(*piter, *((*vvIter).begin()), color, 2);
				else
					DrawLine(*piter, *(piter + 1), color, 2);
				DrawSolidCircle(*piter, 3.0, color);
			}
		}

		color.setColor(0.8, 0.0, 0.1);

		for(vvIter = objetosMapaExp.begin(); vvIter != objetosMapaExp.end(); vvIter++){

			for (piter = (*vvIter).begin(); piter != (*vvIter).end(); piter++) {
				if (piter == (*vvIter).end() - 1)
					DrawLine(*piter, *((*vvIter).begin()), color, 1);
				else
					DrawLine(*piter, *(piter + 1), color, 1);
				DrawSolidCircle(*piter, 2.0, color);
			}
		}

		//Cosas de OpenGL para cuando se redimensione y tal pero no la redimensiones o no funcionara bien
		//Si lo necesitas dimelo o cambia tu la resolucion a lo ancho y algo que quieras en las constantes
		Reshape();

		//Cosas de TWindow para que funcione bien
		window.display(false);
	}

	return 0;*/
}

void Reshape() {
	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WIDTH, 0, HEIGHT, -1, 1);
	glScalef(1, -1, 1);
	glTranslatef(0, -1.0 * HEIGHT, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void DrawTriangle(Point a, Point b, Point c, Color<float> color) {
	glColor3f(color.getR(), color.getG(), color.getB());
	glBegin(GL_POLYGON); // Drawing Using Triangles
	glVertex2f(a.getX(), a.getY()); // Top
	glVertex2f(b.getX(), b.getY()); // Bottom Left
	glVertex2f(c.getX(), c.getY()); // Bottom Right
	glEnd(); // Finished Drawing The Triangle

}
