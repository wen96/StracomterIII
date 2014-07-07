#include <SFML/Audio.hpp>
 #include <SFML/Graphics.hpp>
#include <Polygon.h>
#include <MotorGrafico.h>
#include <iostream>
#include "Triangulation.h"
#include "TWindow.h"
#include "IOControl.h"

using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;

void Resape();
void DrawTriangle(Point a, Point b, Point c, Color<float> color);

 int main()
 {
	 Point a = Point(300,300);
	 Point b = Point(350,350);
	 Point c = Point(300,350);
	 Tri triangle(c,b,a);
	 vector<Tri>triangles;
	 //triangles.push_back(triangle);
	 //triangles.push_back(Tri(Point(100,150),Point(160,230),Point(400,120)));
	 triangle=Tri(Point(100,150),Point(160,230),Point(400,120));
	 triangle.makeCounterClockwise();

	 IOControl *eventosTeclado = NULL;
	 TWindow window;
	 window.openSFML(WIDTH,HEIGHT,false);
	 eventosTeclado = new IOControl(window.getInputs());
	 Color<float> color = Color<float>(1.0,1.0,1.0);


	 //Mientras la ventana este abierta (que se cierra con Esc o con la X de cerrarla)
	 while (window.isOpen()){
		 //Limpieza de color de la ventana (en este caso la limpio a blanco)
		 glClearColor(0.0, 0.0, 0.0, 0.0);
		 glClear(GL_COLOR_BUFFER_BIT);

		 //Detectando el click izquierdo del boton (tambien se puede detectar el derecho haciendo sf::Mouse::Right)
		 if ((*eventosTeclado).isMouseButtonDown(sf::Mouse::Left)){
			 //Consiguiento da coordenada clicada

			 float x = (*eventosTeclado).GetMouseX();
			 float y = (*eventosTeclado).GetMouseY();
			 cout << "Pulsado boton en: " << x << "x - " << y << "y" << endl;

			 //Mis comprobaciones para isInside()
			 if (triangle.isInside(Point(x,y)) == 1){
				 color = Color<float>(0.0,1.0,0.0);
				 cout << "DENTRO!" << endl;

			 }else if (triangle.isInside(Point(x,y))== -1){
				 color = Color<float>(1.0,0.0,0.0);
				 cout << "FUERA!" << endl;

			 }else if (triangle.isInside(Point(x,y)) == 0){
				 color = Color<float>(0.0,0.0,1.0);
				 cout << "LINEA!" << endl;

			 }

			 //Duerto para que no se hagan muchos click sin querer
			 sleep(1);
		 }
		 //Dibujar un triangulo, le pasas 3 puntos (en orden antiohorario, si no no estoy seguro de que lo dibuje bien)
		 //Y un color en formato float RGB
		 DrawTriangle(triangle.getA(),triangle.getB(),triangle.getC(),color);

		 //Cosas de OpenGL para cuando se redimensione y tal pero no la redimensiones o no funcionara bien
		 //Si lo necesitas dimelo o cambia tu la resolucion a lo ancho y algo que quieras en las constantes
		 Resape();

		 //Cosas de TWindow para que funcione bien
		 window.display(false);
	 }


	 return 0;
 }



 void Resape(){
	 glViewport(0,0, WIDTH, HEIGHT);
	 glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
	 glOrtho(0, WIDTH, 0, HEIGHT, -1, 1);
	 glScalef(1, -1, 1);
	 glTranslatef(0, -1.0* HEIGHT , 0);
	 glMatrixMode(GL_MODELVIEW);
	 glLoadIdentity();
 }

 void DrawTriangle(Point a, Point b, Point c, Color<float> color){
	 glColor3f(color.getR(), color.getG(), color.getB());
	 glBegin(GL_POLYGON);                      // Drawing Using Triangles
	     glVertex2f( a.getX(), a.getY());              // Top
	     glVertex2f( b.getX(), b.getY());              // Bottom Left
	     glVertex2f( c.getX(), c.getY());              // Bottom Right
	 glEnd();                            // Finished Drawing The Triangle

 }
