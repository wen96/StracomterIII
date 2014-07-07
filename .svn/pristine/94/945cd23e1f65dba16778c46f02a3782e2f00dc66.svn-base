#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <Polygon.h>
#include <MotorGrafico.h>
#include <iostream>
#include "Triangulation.h"
#include "TWindow.h"
#include "IOControl.h"
#include "Map.h"

using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;

void Reshape();
void DrawTriangle(Point a, Point b, Point c, Color<float> color);

int main(int argc, char *argv[]) {
	IOControl *eventosTeclado = NULL;
	TWindow window;
	window.setNombreVentana("Stracometer III: Triangulacion");
	window.openSFML(WIDTH, HEIGHT, false);
	window.Init();
	eventosTeclado = new IOControl(window.getInputs());

	Color<float> color(0.0, 0.0, 1.0);
	std::vector<Point> puntos;
	std::vector<Tri *> tris;
	bool showBari = false;
	bool showIn = false;

	Triangulation triang(Point(0, 0), Point(800, 600));

	tris = triang.getTriangles();

	Map mapa;
	if(argc == 2)
		mapa.setMap(argv[1]);

	std::vector<Point> puntosMapa = mapa.getVertex();
	std::vector<std::vector<Point> > objetosMapa = mapa.getObjects();

	triang.addPoints(puntosMapa);
	vector<vector <Point> >::iterator piter2;
	for(piter2 = objetosMapa.begin(); piter2 != objetosMapa.end(); piter2++){
		triang.addPoints(*piter2);
	}

	DrawLine(tris[0]->getA(), tris[0]->getB(), color, 1);

	//tris = triang.getTriangles();

	std::vector<Color<float> > colores;

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
			if ((event.Type == sf::Event::MouseButtonPressed) && (event.MouseButton.Button == sf::Mouse::Left)){
				//Consiguiento da coordenada clicada
				double x = (*eventosTeclado).GetMouseX();
				double y = (*eventosTeclado).GetMouseY();

				Point p(x, y);
				//cout << "Pulsado boton en: " << p << endl;

				puntos.push_back(p);

				triang.addPoint(p);
			}else
			if ((event.Type == sf::Event::MouseButtonPressed) && (event.MouseButton.Button == sf::Mouse::Right)){
				triang.stepDelaunay();

				tris = triang.getTriangles();
			}else
			if (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::B){
				if (showBari)
					showBari = false;
				else
					showBari = true;
			}else
			if (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::I){
				if (showIn)
					showIn = false;
				else
					showIn = true;
			}else
			if (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::E){
				triang.continueDelaunay();
				tris = triang.getTriangles();
			}else
			if (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::F){
				tris = triang.finishedDelaunay();
			}
		}

		//Detectando el click izquierdo del boton (tambien se puede detectar el derecho haciendo sf::Mouse::Right)
		/*if ((*eventosTeclado).isMouseButtonDown(sf::Mouse::Left)) {
			//Consiguiento da coordenada clicada
			double x = (*eventosTeclado).GetMouseX();
			double y = (*eventosTeclado).GetMouseY();

			Point p(x, y);
			cout << "Pulsado boton en: " << p << endl;

			puntos.push_back(p);

			triang.addPoint(p);

			//Duermo para que no se hagan muchos click sin querer
			sleep(1);
		}

		if ((*eventosTeclado).isMouseButtonDown(sf::Mouse::Right)) {
			triang.stepDelaunay();

			tris = triang.getTriangles();

			sleep(1);
		}

		if ((*eventosTeclado).IsKeyDown(Core::Key::B)) {
			if (showBari)
				showBari = false;
			else
				showBari = true;

			sleep(1);
		}

		if ((*eventosTeclado).IsKeyDown(Core::Key::I)) {
			if (showIn)
				showIn = false;
			else
				showIn = true;

			sleep(1);
		}

		if ((*eventosTeclado).IsKeyDown(Core::Key::Space)) {
			triang.continueDelaunay();
			tris = triang.getTriangles();

			sleep(1);
		}

		if ((*eventosTeclado).IsKeyDown(Core::Key::F)) {
			tris = triang.finishedDelaunay();

			sleep(1);
		}*/

		std::vector<Tri *>::iterator iter;
		int cont = 0;
		color.setColor(0.0,0.0,1.0);
		for (iter = tris.begin(); iter != tris.end(); iter++) {

			DrawLine((*iter)->getA(), (*iter)->getB(), color, 1);
			DrawLine((*iter)->getB(), (*iter)->getC(), color, 1);
			DrawLine((*iter)->getC(), (*iter)->getA(), color, 1);

			if (showBari) {
				DrawSolidCircle((*iter)->getBaricenter(), 2.0,
						Color<float>(1.0, 0.0, 0.0));

				if ((*iter)->getAb() != NULL)
					DrawLine((*iter)->getBaricenter(),
							(*iter)->getAb()->getBaricenter(),
							Color<float>(1.0, 0.0, 0.0), 0.5);

				if ((*iter)->getBc() != NULL)
					DrawLine((*iter)->getBaricenter(),
							(*iter)->getBc()->getBaricenter(),
							Color<float>(1.0, 0.0, 0.0), 0.5);

				if ((*iter)->getCa() != NULL)
					DrawLine((*iter)->getBaricenter(),
							(*iter)->getCa()->getBaricenter(),
							Color<float>(1.0, 0.0, 0.0), 0.5);
			}

			if (showIn) {

				DrawSolidCircle((*iter)->getIncenter(), 2.0,
						Color<float>(0.0, 1.0, 0.0));

				if ((*iter)->getAb() != NULL)
					DrawLine((*iter)->getIncenter(),
							(*iter)->getAb()->getIncenter(),
							Color<float>(0.0, 1.0, 0.0), 0.5);

				if ((*iter)->getBc() != NULL)
					DrawLine((*iter)->getIncenter(),
							(*iter)->getBc()->getIncenter(),
							Color<float>(0.0, 1.0, 0.0), 0.5);

				if ((*iter)->getCa() != NULL)
					DrawLine((*iter)->getIncenter(),
							(*iter)->getCa()->getIncenter(),
							Color<float>(0.0, 1.0, 0.0), 0.5);
			}
			// DrawTriangle((*iter)->getA(), (*iter)->getB(), (*iter)->getC(), colores[cont]);
			cont++;
		}



		std::vector<Point>::iterator piter;

		color.setColor(0.0, 0.0, 1.0);
		for(piter = puntos.begin(); piter != puntos.end(); piter++){
			DrawSolidCircle(*piter, 3.0, color);
		}

		color.setColor(0.0, 0.0, 0.0);
		for (piter = puntosMapa.begin(); piter != puntosMapa.end(); piter++) {
			DrawSolidCircle(*piter, 3.0, color);
		}

		for (piter2 = objetosMapa.begin(); piter2 != objetosMapa.end(); piter2++) {
			for (piter = (*piter2).begin(); piter != (*piter2).end(); piter++) {
				DrawSolidCircle(*piter, 3.0, color);
			}
		}

		//Cosas de OpenGL para cuando se redimensione y tal pero no la redimensiones o no funcionara bien
		//Si lo necesitas dimelo o cambia tu la resolucion a lo ancho y algo que quieras en las constantes
		Reshape();

		//Cosas de TWindow para que funcione bien
		window.display();
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
