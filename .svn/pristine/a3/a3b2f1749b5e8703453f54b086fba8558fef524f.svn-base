#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <Polygon.h>
#include <MotorGrafico.h>
#include <iostream>
#include "Triangulation.h"
#include "TWindow.h"
#include "IOControl.h"
#include "Map.h"
#include "Pathfinder.h"
#include "NavGraph.h"

using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;

void Reshape();
void DrawTriangle(Point a, Point b, Point c, Color<float> color);

int main(int argc, char *argv[]) {
	IOControl *eventosTeclado = NULL;
	TWindow window;
	window.setNombreVentana("Stracometer III: testPathfinder");
	window.openSFML(WIDTH, HEIGHT, false);
	window.Init();
	eventosTeclado = new IOControl(window.getInputs());

	Color<float> color(0.0, 0.0, 1.0);
	std::vector<Point> puntos;
	std::vector<Tri *> tris;

	Pathfinder pathF(Point(0,0), Point(800, 600), 10);
	if(argc == 2)
		pathF.setMap(argv[1]);
	else
		pathF.setMap("map_01.txt");

	tris = pathF.getTriangulation();


	Map mapa;
	if(argc == 2)
		mapa.setMap(argv[1]);
	else
		mapa.setMap("map_01.txt");

	NavGraph dualGraph;

	std::vector<Point> puntosMapa = mapa.getVertex();
	std::vector<std::vector<Point> > objetosMapa = mapa.getObjects();

	std::vector<std::vector<Point> > objetosMapaExp = pathF.getExpPoints();
	std::vector<Tri *>::iterator triter3;

	std::vector<Color<float> > colores;
	int space = 0;

	//Mientras la ventana este abierta (que se cierra con Esc o con la X de cerrarla)
	while (window.isOpen()) {
		//Limpieza de color de la ventana (en este caso la limpio a blanco)
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		sf::Event event;
		while(window.getEvent(event)){
			if (event.Type == sf::Event::Closed){
				window.close();
			}else
			if (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Escape){
				window.close();
			}else
			if (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::F){
				pathF.generateTriangulation();
				pathF.flattenTriangulation();
				pathF.removeNonNavigableTris();
				tris = pathF.getTriangulation();
				dualGraph = pathF.getDualGraph();

			}else
			if ((event.Type == sf::Event::MouseButtonPressed) && (event.MouseButton.Button == sf::Mouse::Left)){
				switch(space){
				case 0:
					pathF.generateTriangulation();
					tris = pathF.getTriangulation();
					space++;
					break;
				case 1:
					pathF.flattenTriangulation();
					tris = pathF.getTriangulation();
					space++;
					break;
				case 2:
					pathF.removeNonNavigableTris();
					tris = pathF.getTriangulation();
					dualGraph = pathF.getDualGraph();
					space++;


					break;

				}
			}


		}

		std::vector<Tri *>::iterator iter;
		color.setColor(0.0,0.0,1.0);
		for (iter = tris.begin(); iter != tris.end(); iter++) {

			DrawLine((*iter)->getA(), (*iter)->getB(), color, 1);
			DrawLine((*iter)->getB(), (*iter)->getC(), color, 1);
			DrawLine((*iter)->getC(), (*iter)->getA(), color, 1);

		}

		// DualGraph

		color.setColor(0.5, 0.5, 0.0);
		std::vector<ASNode>::iterator niter;
		for(niter = dualGraph.nodes.begin(); niter != dualGraph.nodes.end(); niter++){
			DrawSolidCircle((*niter).getPosition(), 2.0, color);

			std::vector<ASNode>::iterator asiter;
			std::vector<ASNode> vASNodes = dualGraph.getAdyacence((*niter).getId());
			for(asiter = vASNodes.begin(); asiter != vASNodes.end(); asiter++){
				//DrawLine((*niter)->getPosition(), (*asiter).getPosition(), color, 1);
				DrawLine((*niter).getPosition(), (*asiter).getPosition(), color, 0.5);
			}
		}

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
		window.display();
		//ControlEvents(window);
	}

	return 0;
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
