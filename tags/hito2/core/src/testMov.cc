#include <iostream>
#include "MovementComp.h"
#include <SFML/Graphics.hpp>
#include <MotorGrafico.h>
#include "TWindow.h"
#include "IOControl.h"
using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;

int main(int argc, char * argv[]){

	IOControl *eventosTeclado = NULL;
	TWindow window;
	window.setNombreVentana("Stracometer III: A Star");
	window.openSFML(WIDTH, HEIGHT, false);
	window.Init();
	eventosTeclado = new IOControl(&window);

	int n;
	MovementComp *ent = new MovementComp();
	ent->setHeading(Vector2D(1,0));
	ent->setVelocity(Vector2D());
	ent->setPos(Point(100,100));

	if(argc == 4){
		ent->setMass(atoi(argv[1]));
		ent->setMaxSpeed(atoi(argv[2]));
		ent->setMaxForce(atoi(argv[3]));
	}else{
		ent->setMass(1);
		ent->setMaxSpeed(100);
		ent->setMaxForce(4);
	}

	MovementComp *seg1 = new MovementComp(*ent);
	MovementComp *seg2 = new MovementComp(*ent);
	MovementComp *seg3 = new MovementComp(*ent);
	MovementComp *seg4 = new MovementComp(*ent);
	seg1->setLeader(ent);
	seg1->setOffset(Vector2D(50, -10));
	seg2->setLeader(ent);
	seg2->setOffset(Vector2D(30, -30));
	seg3->setLeader(ent);
	seg3->setOffset(Vector2D(-50, -10));
	seg4->setLeader(ent);
	seg4->setOffset(Vector2D(-30, -30));

	vector<Point> recorrido;

	Point p0(100,100);
	Point p1(50,300);
	Point p2(150,500);
	Point p3(350,500);
	Point p4(250,200);
	Point p5(500,300);
	Point p6(600,60);

	vector<Point> camino;
	camino.push_back(p0);
	camino.push_back(p1);
	camino.push_back(p2);
	camino.push_back(p3);
	camino.push_back(p4);
	camino.push_back(p5);
	camino.push_back(p6);

	ent->setPath(camino, false);

	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WIDTH, 0, HEIGHT, -1, 1);
	glScalef(1, -1, 1);
	glTranslatef(0, -1.0 * HEIGHT, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Color<float> negro(0,0,0);
	Color<float> rojo(1,0,0);
	Color<float> verde(0,1,0);
	Color<float> azul(0,0,1);
	Color<float> amarillo(1,1,0);
	Color<float> gris1(0.5, 0.5, 0.5);
	Color<float> gris2(0.2, 0.2, 0.2);

	Vector2D force;

	while (window.isOpen()) {

		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		ent->Update();
		seg1->Update();
		seg2->Update();
		seg3->Update();
		seg4->Update();

		DrawLine(p0,p1, gris2, 1);
		DrawLine(p1,p2, gris2, 1);
		DrawLine(p2,p3, gris2, 1);
		DrawLine(p3,p4, gris2, 1);
		DrawLine(p4,p5, gris2, 1);
		DrawLine(p5,p6, gris2, 1);

		force = ent->getVelocity() + ent->getPos();
		DrawLine(ent->getPosP(), Point(force.x, force.y), negro);
		DrawSolidCircle(ent->getPosP(),5, negro);

		force = seg1->getVelocity() + seg1->getPos();
		DrawLine(seg1->getPosP(), Point(force.x, force.y), rojo);
		DrawSolidCircle(seg1->getPosP(),5, rojo);

		force = seg2->getVelocity() + seg2->getPos();
		DrawLine(seg2->getPosP(), Point(force.x, force.y), verde);
		DrawSolidCircle(seg2->getPosP(),5, verde);

		force = seg3->getVelocity() + seg3->getPos();
		DrawLine(seg3->getPosP(), Point(force.x, force.y), azul);
		DrawSolidCircle(seg3->getPosP(),5, azul);

		force = seg4->getVelocity() + seg4->getPos();
		DrawLine(seg4->getPosP(), Point(force.x, force.y), amarillo);
		DrawSolidCircle(seg4->getPosP(),5, amarillo);

		window.display(true);
	}

	return 0;
}
