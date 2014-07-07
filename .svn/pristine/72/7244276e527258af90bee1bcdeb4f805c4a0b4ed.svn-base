#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <Polygon.h>
#include <MotorGrafico.h>
#include <iostream>
#include "TWindow.h"
#include "IOControl.h"
#include "CoreNamespace.h"
#include "FSM.h"
#include "Vector2D.h"
#include <sstream>

using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;

void Reshape();
Color<float> getRandColor();
int getCuadrante(Point a, Point B);

struct TTrans{
	int input;
	int des;
	Point Ori;
	Point Des;
	Point Med;
};

struct TEstado{
	int id;
	string name;
	Color<float> color;
	Point pos;
	Point textPos;
	vector<TTrans> vTrans;
};

int main(int argc, char *argv[]) {
	if(argc == 2){
		TWindow window;
		window.setNombreVentana("Stracometer III: testFSMGrafico");
		window.openSFML(WIDTH, HEIGHT, false);
		window.Init();

		Color<float> color(0.0, 0.0, 1.0);
		vector<Point> vPoints;
		vector<Color<float> > vColors;
		vector<Color<float> >::iterator cIter;

		vector<vector<pair<Point,Point> > > vvTrans;
		vector<vector<pair<Point,Point> > >::iterator vvIter;
		vector<pair<Point,Point> >::iterator tIter;

		FSM fsm;

		if(fsm.loadData(argv[1])){

			vector<TEstado> vEstados;
			vector<TEstado>::iterator eIter;
			vector<FSMState> vFSMState;
			vector<FSMState>::iterator fsmIter;
			int eActual = fsm.getCurrentI();

			vFSMState = fsm.getStates();
			Polygon poly(vFSMState.size(), Point(400,300), 250.0, 0.0);

			vPoints = poly.getPuntos();

			vector<TTrans> vTrans;
			vector<TTrans>::iterator tIter;
			vector<pair<int,int> > iiPar;
			vector<pair<int,int> >::iterator iiIter;

			srand ( time(NULL) );
			for(fsmIter = vFSMState.begin(); fsmIter != vFSMState.end(); fsmIter++){
				vTrans.clear();

				TEstado estado;

				estado.id = (*fsmIter).getId();
				estado.color = getRandColor();
				estado.name = (*fsmIter).getName();
				estado.pos = vPoints[estado.id - 1];
				estado.textPos = Point(estado.pos.getX() + 15, estado.pos.getY() - 15);

				iiPar = (*fsmIter).getTransitions();

				for(iiIter = iiPar.begin(); iiIter != iiPar.end(); iiIter++){

					Point Ori(vPoints[estado.id - 1]);
					Point Des(vPoints[(*iiIter).second - 1]);

					Vector2D v1(Ori, Des);
					Vector2D v2(Point(0,0), Point(10,0));
					float ang = v1.Angle(v2);

					if(Ori.getY() < Des.getY()) ang = -ang;

					float oriX, oriY, desX, desY, medX, medY, h, d, alfa;

					oriX = Ori.getX() + 20 * cos(ang * (M_PI / 180));
					oriY = Ori.getY() - 20 * sin(ang * (M_PI / 180));

					desX = Des.getX() - 20 * cos(ang * (M_PI / 180));
					desY = Des.getY() + 20 * sin(ang * (M_PI / 180));

					d = Point::distance(Ori, Des);

					h = sqrt((d*d)/25 + 100);

					alfa = asin((float) 50 / d)*180/M_PI;

					medX = Ori.getX() + h * cos((ang - alfa) * (M_PI / 180));
					medY = Ori.getY() - h * sin((ang - alfa) * (M_PI / 180));

					TTrans transicion;

					transicion.input = (*iiIter).first;
					transicion.des = (*iiIter).second;
					transicion.Ori = Point(oriX, oriY);
					transicion.Des = Point(desX, desY);
					transicion.Med = Point(medX, medY);

					vTrans.push_back(transicion);

				}

				estado.vTrans = vTrans;

				vEstados.push_back(estado);
			}

			string inputText;

			//Mientras la ventana este abierta (que se cierra con Esc o con la X de cerrarla)
			while (window.isOpen()) {
				//Limpieza de color de la ventana (en este caso la limpio a blanco)
				glClearColor(1.0, 1.0, 1.0, 1.0);
				glClear(GL_COLOR_BUFFER_BIT);

				sf::Event event;
				while(window.getEvent(event)){
					if (event.Type == sf::Event::Closed){
						window.close();
					}else if (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Keyboard::Escape){
						window.close();
					}

					// In event loop...
					if (event.Type == sf::Event::TextEntered) {

						// Handle ASCII characters only
						if (event.Text.Unicode < 128) {
							inputText += static_cast<char>(event.Text.Unicode);
						}
					}

					if (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Keyboard::Return){
						//cout << inputText << endl;
						eActual = fsm.updateStates(atoi(inputText.c_str()));
						//cout << "E " << eActual << endl;
						inputText = "";
					}

				}

				eIter = vEstados.begin();
				while(eIter != vEstados.end()){

					if((*eIter).id == eActual){
						DrawSolidCircle((*eIter).pos, 20.0, (*eIter).color);
					}else{
						DrawCircle((*eIter).pos, 20.0, (*eIter).color);
					}

					DrawText((*eIter).textPos, (*eIter).name, (*eIter).color, 7);

					eIter++;
				}


				eIter = vEstados.begin();
				while(eIter != vEstados.end()){

					tIter = (*eIter).vTrans.begin();
					while(tIter != (*eIter).vTrans.end()){

						DrawLine((*tIter).Ori, (*tIter).Des, (*eIter).color, 1.0);

						tIter++;
					}

					eIter++;
				}

				eIter = vEstados.begin();
				while(eIter != vEstados.end()){

					tIter = (*eIter).vTrans.begin();
					while(tIter != (*eIter).vTrans.end()){

						DrawSolidCircle((*tIter).Des, 3, (*eIter).color);

						stringstream ss;
						ss << (*tIter).input;

						DrawText((*tIter).Med, ss.str(), (*eIter).color, 7);

						tIter++;
					}

					eIter++;
				}

				DrawText(Point(25,50), "Input: " + inputText, Color<float> (0.0,0.0,0.0), 7);
				DrawText(Point(25,70), "Estado actual: " + fsm.getCurrentS(), Color<float> (0.0,0.0,0.0), 7);

				//Si lo necesitas dimelo o cambia tu la resolucion a lo ancho y algo que quieras en las constantes
				Reshape();

				//Cosas de TWindow para que funcione bien
				window.display();
				//ControlEvents(window);
			}
		}
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

Color<float> getRandColor(){

	float R = (float) (rand()%90000) / 100000.0;
	float G = (float) (rand()%90000) / 100000.0;
	float B = (float) (rand()%90000) / 100000.0;

	return Color<float> (R, G, B);
}

int getCuadrante(Point A, Point B){
	int cuad;

	if(A.getX() > B.getX()){
		if(A.getY() > B.getY()){
			cuad = 3;
		}else{
			cuad = 0;
		}
	}else{
		if(A.getY() > B.getY()){
			cuad = 2;
		}else{
			cuad = 1;
		}
	}

	return cuad;
}
