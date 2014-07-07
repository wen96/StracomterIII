#include <iostream>
using namespace std;


#include "Box.h"
#include "Body.h"
#include "World.h"
#include "Force.h"
#include "BodyData.h"
#include "BodyData.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "MotorGrafico.h"
#include "TWindow.h"
#include "IOControl.h"
#include "Transformacion.h"

const int WIDTH = 800;
const int HEIGHT = 600;

Color<float> c1(0.8,0.7,0.2);
Color<float> c2(0.2,0.4,0.6);
void Reshape(){
	 glViewport(0,0, WIDTH, HEIGHT);
	 glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
	 glOrtho(0, WIDTH, 0, HEIGHT, -1, 1);
	 glScalef(1, -1, 1);
	 glTranslatef(0, -1.0* HEIGHT , 0);
	 glMatrixMode(GL_MODELVIEW);
	 glLoadIdentity();
}

int main() {

	IOControl *eventosTeclado = NULL;
	 TWindow window;
	 window.openSFML(WIDTH,HEIGHT,false);
	 eventosTeclado = new IOControl(&window);

	World *w = new World;

	//Polygon p1(Point(0,0), Point(5,0));
	//Polygon p2(Point(4.99,0), Point(10,0));
	vector<Point> v1;
	vector<Point> v2;

	v1.push_back(Point(10,30));
	v1.push_back(Point(10,20));
	v1.push_back(Point(40,20));
	v1.push_back(Point(40,30));

	v2.push_back(Point(20,10));
	v2.push_back(Point(30,10));
	v2.push_back(Point(30,40));
	v2.push_back(Point(20,40));
	//Polygon p1(4,v1);
	Polygon p2(v2);
	Polygon p1(4, Point(40,40), 30, 45);
	//Polygon p2(4, Point(40,40), 30, 0);

	//Polygon p1(Point(40, 20), Point(40, 120));
	//Polygon p2(Point(60, 40), Point(120, 40));

	BodyData bd1(p1 ,b2_dynamicBody);
	BodyData bd2(p2, b2_dynamicBody);

	//bd1.setSensor(true);
	//bd2.setSensor(true);

	Body *b1 = new Body(*w, bd1);
	Body *b2 = new Body(*w, bd2);

	vector<Point> sol;
	window.Init();

	while (window.isOpen()){

		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);


		sol = b1->contact(*b2);
		for(unsigned int i = 0; i < sol.size(); i++)
		{
			//cout << sol[i] << " ";
		}
		//cout << endl;
		//b1->setLinearVelocity(Force(10.0,0.0));
		//b2->setLinearVelocity(Force(-10.0,0.0));
		////cout << "P1" << b1->getPosition() << endl;
		////cout << "P2" << b2->getPosition() << endl;

		Transform tx;
		tx.addTranslation(b1->getPosition());
		//tx.loadRotation(b1->getAngle(), 0.0, 0.0, 1.0);

		glLoadIdentity();
		//escalado.loadOpenGL();
		tx.exportOpenGL();

		//ent[i]->setCenter(Point(ent[i]->getCenter().getX()*escalado.getSx(), ent[i]->getCenter().getY()*escalado.getSy()));
		//ent[i]->body->body->SetTransform(b2Vec2(ent[i]->body->body->GetTransform().p.x*escalado.getSx(), ent[i]->body->body->GetTransform().p.y*escalado.getSy()), ent[i]->body->body->GetTransform().q.GetAngle());
		//DrawText(ent[i]->getCenter(), text, ent[i]->getColor(), 2);
		DrawSolidPolygon(p1, c1);

		tx.addTranslation(b2->getPosition());
		tx.addRotationZ(b2->getAngle());

		glLoadIdentity();
		//escalado.loadOpenGL();
		tx.exportOpenGL();

		//ent[i]->setCenter(Point(ent[i]->getCenter().getX()*escalado.getSx(), ent[i]->getCenter().getY()*escalado.getSy()));
		//ent[i]->body->body->SetTransform(b2Vec2(ent[i]->body->body->GetTransform().p.x*escalado.getSx(), ent[i]->body->body->GetTransform().p.y*escalado.getSy()), ent[i]->body->body->GetTransform().q.GetAngle());
		//DrawText(ent[i]->getCenter(), text, ent[i]->getColor(), 2);
		DrawSolidPolygon(p2,c2);

		glLoadIdentity();
		//cout << "Contacto: " << b1->TestPoint(Point(80,100)) << endl;
		glPointSize(5);
		glColor3b(1,0,0);
		glBegin(GL_POINTS);
			glVertex2d(80,100);
		glEnd();
		w->UpdateWorld();
		window.display(false);
		Reshape();
	}


	return 0;
}
