#include <Polygon.h>
#include <MotorGrafico.h>
#include <iostream>
#include "TWindow.h"
#include "IOControl.h"
#include "Tri.h"
#include "Map.h"
#include "CoreNamespace.h"
#include "Camera.h"
#include <GL/gl.h>
#include "TForm.h"
#include "TWidget.h"
#include "TButton.h"
#include "TLabel.h"
#include "Matrix.h"
#include "ResourceManager.h"
#include "TPicture.h"
#include "Scene.h"

using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;
const float GROSOR = 10;

/** Clase TOptions contenedor de variables para pasarlo de funcion en función y evitar variables globales.
 * Si se necesita cambiar el nombre porque hay algun conflicto que se cambie, esta clase solo se utiliza por este fichero.
 */
class TOptions{
public:
	TOptions(){
		modePerimetre=true;
		showEdge=true;
		modeLabel = NULL;
		despX = 0;
		despY = 0;
		zoom = 1;
		bloquearMov = true;
		modeWall = false;
		drawPointA = true;
		resManager = ResourceManager::getInstance(new World(), NULL);
		manager = new EntityManager(resManager);
		scene = new Scene(manager, resManager, WIDTH, HEIGHT);
		panel = new TForm(200,600,Point(100,300));
		panel->setColor(Color<float>(0.4,0.4,0.4,0.7));
		//TODO manager->addBot(Point(300,300),0.0,Core::Entities::e_captain);
	}

	//Camaras
	Camera c_panel;
	Camera c_canvas;

	//Utiles de acceso
	TForm* panel;
	TWindow *window;
	IOControl *eventosTeclado;
	TLabel *modeLabel;
	TLabel *lockLabel;

	//Mouse
	Point mouse;
	Point desplacedMouse;
	Polygon puntero;

	//Auxiliares para sugerencias
	Point auxSugerLine;

	//Booleanos de control
	bool modePerimetre;
	bool showEdge;
	bool bloquearMov;
	bool foundSuger;

	bool modeWall;
	bool drawPointA;

	//Variables de redisposicion
	int despX;
	int despY;
	float zoom;

	//Perimetro para modificar y toquetear
	Polygon perimetre;
	vector<Point> perimetrePoints;

	EntityManager *manager;
	ResourceManager *resManager;
	Scene *scene;

	GLfloat mv[16];

};

//Cosas de opengl para camaras y tal
void Reshape(int, TOptions &op);
//Control de eventos
void ControlEvents(TOptions &op);
//Recalcula raton
void RecalculoRaton(TOptions &op, int x, int y);
//Dibujo del canvas donde esta el mapa
void DrawCanvas(TOptions &op);
//Funcion util para borrar un punto de la lista
bool removePoint(vector<Point> &puntos, Point p, int radio);
//Funcion para saber si un poligono es convexo o no
bool isConvex(vector<Point> pol);
//funcion para guardar el mapa en un fichero
void saveMap(string nomFile, TOptions &op);
//Funcion para controlas los eventos con perimetro
void controlPerimetre(TOptions &, sf::Event event);
//Funcion para controlas los eventos con objetos
void controlObjetos(TOptions &, sf::Event event);

int main(int argc, char *argv[]) {
	IOControl *eventosTeclado = NULL;
	TWindow *window = new TWindow;

	window->setNombreVentana("Stracometer III: Pruebas de menu");
	window->openSFML(WIDTH, HEIGHT, false);
	window->Init();
	eventosTeclado = new IOControl(window);

	TOptions op;

	op.c_panel= Camera(WIDTH,HEIGHT,-1,1);
	op.c_canvas= Camera(WIDTH,HEIGHT,-1,1);
	op.c_panel.setOrtho();
	op.c_canvas.setOrtho();
	op.c_panel.setScale(400);
	op.c_canvas.setScale(400);


	op.window = window;
	op.eventosTeclado = eventosTeclado;
	op.puntero = Polygon(Point(),4);



	TLabel *label = new TLabel(200,100,"Pause");
	label->setMarginUp(100);
	label->setColorBorder(Color<float>(1,0,0));
	label->setColorText(Color<float>(0.1,0.1,0.4));
	label->setSize(50);
	op.panel->addWidget(label);
	TButton *continuar = new TButton(150,50,"Continuar");
	continuar->setMarginUp(200);
	continuar->setEvento(1);//lo enlazo al evento 1 para decir que se debe continuar
	op.panel->addWidget(continuar);
	continuar = new TButton(150,50,"Salir");
	continuar->setMarginUp(50);
	continuar->setEvento(0);//lo enlazo al evento 0 para decir que se debe salir
	op.panel->addWidget(continuar);
	/*op.panel = new TForm(200, 600, Point(100,300));
	op.panel->setColor(Color<float>(0.4,0.4,0.4,0.7));

	TLabel *modeLabel = NULL;

	modeLabel = new TLabel(200,30,"Bloquear movimiento: B");
	modeLabel->setColorText(Color<float>(0.1,0.1,0.4));
	op.panel->addWidget(modeLabel);

	modeLabel = new TLabel(200,30,"Loqued");
	modeLabel->setColorText(Color<float>(0.1,0.1,0.4));
	op.panel->addWidget(modeLabel);

	op.lockLabel = modeLabel;

	modeLabel = new TLabel(200,30,"Cambiar modo: Space");
	modeLabel->setColorText(Color<float>(0.1,0.1,0.4));
	op.panel->addWidget(modeLabel);

	modeLabel = new TLabel(200,30,"Perimetro");
	modeLabel->setColorText(Color<float>(0.1,0.1,0.4));
	op.panel->addWidget(modeLabel);

	op.modeLabel = modeLabel;
	op.panel->addWidget(new TLabel(200,30,"Mostra-Ocultar eje: E"));
	op.panel->addWidget(new TLabel(200,30,"<= => (direction keys)"));
	op.panel->addWidget(new TLabel(200,30,"Zoom: Z:- | A:+"));
	op.panel->addWidget(new TLabel(200,30,"Restaurar vista: R"));
	op.panel->addWidget(new TLabel(200,30,"Delete: Right click"));

	TButton *b = new TButton("Pared");
	b->setMarginUp(20);
	b->setMarginLeft(10);
	b->setEnable(false);
	op.panel->addWidget(b);

	b = new TButton("Player");
	b->setMarginUp(20);
	b->setMarginLeft(10);
	b->setEnable(false);
	b->setClicked(true);
	op.panel->addWidget(b);

	b = new TButton("Mesa");
	b->setMarginUp(20);
	b->setMarginLeft(10);
	b->setEnable(false);
	op.panel->addWidget(b);

	b = new TButton("Columna");
	b->setMarginUp(20);
	b->setMarginLeft(10);
	b->setEnable(false);
	op.panel->addWidget(b);

	b = new TButton("Delete Wall");
	b->setMarginUp(50);
	b->setMarginLeft(10);
	b->setEnable(false);
	op.panel->addWidget(b);

	b = new TButton("<");
	b->setMarginUp(20);
	b->setMarginLeft(10);
	b->setEnable(false);
	op.panel->addWidget(b);
	b = new TButton(">");
	b->setMarginUp(20);
	b->setMarginLeft(10);
	b->setEnable(false);
	op.panel->addWidget(b);
	b = new TButton("^");
	b->setMarginUp(20);
	b->setMarginLeft(10);
	b->setEnable(false);
	op.panel->addWidget(b);
	b = new TButton("V");
	b->setMarginUp(20);
	b->setMarginLeft(10);
	b->setEnable(false);
	op.panel->addWidget(b);*/

	glEnable (GL_BLEND);
	glEnable (GL_POLYGON_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Mientras la ventana este abierta (que se cierra con Esc o con la X de cerrarla)
	while (window->isOpen()) {

		//Limpieza de color de la ventana (en este caso la limpio a blanco)
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		//DIBUJADO  ///////////////////////////////

		//Aqui el Canvas
		Reshape(0,op);
		DrawCanvas(op);

		//EVENTOS /////////
		//Recalculo del raton ////////
		RecalculoRaton(op,eventosTeclado->GetMouseX(),eventosTeclado->GetMouseY());

		ControlEvents(op);

		//Aqui el HUD
		Reshape(1,op);

		//Dibujamos el panel
		op.panel->Draw();
		//Dibujamos el puntero en el hud
		DrawPolygon(op.puntero,Color<float>(0,1,0));


		//Actualizador de los botones (por el mundo y por poner a false los isOver)
		op.panel->Update(window->getFrameTime());

		//Cosas de TWindow para que funcione bien
		window->display();
	}

	if (window!=NULL){
		delete window;
	}

	saveMap("editorMap.xml", op);
	return 0;

}

void saveMap(string nomFile, TOptions &op){
	Map map;

	map.writeFile(nomFile);
}

void Reshape(int mode, TOptions &op) {

	switch(mode)
	{
	case 0:
		op.c_canvas.exportOpenGL();

		glScalef(op.zoom, -op.zoom, 1.0);
		glTranslatef(-1.0 * WIDTH/2, -1.0 * HEIGHT/2, 0.0);
		glTranslatef(op.despX,op.despY,0);

		glGetFloatv(GL_MODELVIEW_MATRIX,op.mv);
		break;
	case 1:
		op.c_panel.exportOpenGL();
		glScalef(1, -1, 1);
		glTranslatef(-1.0 * WIDTH/2, -1.0 * HEIGHT/2, 0.0);
		break;
	}
}

void ControlEvents(TOptions &op){

	//puntero para guardar botones pulsados
	TWidget* wid = NULL;


	//Pillamos el boton seleccionado
	wid = op.panel->whoIsClicked(op.mouse);
	if (wid != NULL){
		wid->setOver(true);
	}
	Point mouseRect;

	int errorMargen = 0;


		///############################ DETALLES Y SUGERENCIAS ################################################//

	//Si modo perimetro esta enmarcha hacemos
	if (op.modePerimetre){


		//Sugerencia de linas rectas
		if (op.eventosTeclado->IsKeyDown(Core::Key::LShift)){
			errorMargen = 10;//margen de error para la sugerencia de misma altura
			//Calculo de angulos rectos al pulsar mayusculas
			if (op.eventosTeclado->IsKeyDown(Core::Key::LShift)){
				if (op.modePerimetre){
					if (!op.perimetrePoints.empty()){
						int orX = abs((int)op.perimetrePoints.back().getX());
						int orY = abs((int)op.perimetrePoints.back().getY());
						int mX = abs((int)op.desplacedMouse.getX());
						int mY = abs((int)op.desplacedMouse.getY());
						if (abs(orX-mX) < abs(orY-mY)){
							op.desplacedMouse.setX(op.perimetrePoints.back().getX());
						}else{
							op.desplacedMouse.setY(op.perimetrePoints.back().getY());
						}
					}
				}
			}
		}

		// Sugerencia de lineas a la misma altura
		vector<Point>::iterator iterPerim;
		for (iterPerim = op.perimetrePoints.begin(); iterPerim != op.perimetrePoints.end(); iterPerim++){
			if (*iterPerim != op.perimetrePoints.back()){//si no es el ultimo
				int auxX1 = iterPerim->getX()+errorMargen;
				int auxX2 = iterPerim->getX()-errorMargen;

				int auxY1 = iterPerim->getY()+errorMargen;
				int auxY2 = iterPerim->getY()-errorMargen;


				if (auxX1 >= op.desplacedMouse.getX() && auxX2 <= op.desplacedMouse.getX()){
					op.foundSuger = true;
					op.auxSugerLine = *iterPerim;
					if (errorMargen != 0){
						op.desplacedMouse.setX(iterPerim->getX());
					}
					break;
				}else if (auxY1 >= op.desplacedMouse.getY() && auxY2 <= op.desplacedMouse.getY()){
					op.foundSuger = true;
					op.auxSugerLine = *iterPerim;
					if (errorMargen != 0){
						op.desplacedMouse.setY(iterPerim->getY());
					}
					break;
				}
			}
		}
	}

	//Desplazamiento automatico al acercarse al final
	if (!op.bloquearMov){
		if (WIDTH-op.mouse.getX() < 10){
			op.despX -= 5;
		}else if (WIDTH-op.mouse.getX() >(WIDTH-10)){
			op.despX += 5;
		}
		if (HEIGHT-op.mouse.getY() < 10){
			op.despY -= 5;
		}else if (HEIGHT-op.mouse.getY() >(HEIGHT-10)){
			op.despY += 5;
		}
	}


	////############################# EVENTOS GENERALES ############################################////

	vector<TWidget*> widgets = op.panel->getWidgets();
	sf::Event event;
	while (op.window->getEvent(event)) {
		//Eventos de control
		if (event.Type == sf::Event::Closed) {//control de cerrado de ventana
			op.window->close();
		} else if (event.Type == sf::Event::KeyPressed){

			if (event.Key.Code == sf::Keyboard::Escape) {//control de cerrado de ventana
				op.window->close();
			}else if (event.Key.Code == sf::Keyboard::Space){//cambio modo permitro
				//si es convexo el poligono
				if (isConvex(op.perimetrePoints)){
					op.modePerimetre = !op.modePerimetre;//cambiamos la variable de control
					op.modeLabel->setColorText(Color<float>());
					if (op.modePerimetre){//cambiamos el texto del label indicador
						op.modeLabel->setCaption("Perimetro");
					}else{
						op.modeLabel->setCaption("Objetos");
					}
				}else{//advertimos si no es convexo
					op.modeLabel->setCaption("El perimetro debe ser convexo");
					op.modeLabel->setColorText(Color<float>(1,0,0));
				}
			}else if (event.Key.Code == sf::Keyboard::R){//restaurar valores de desplazamiento y zoom
				op.despY = 0;
				op.despX = 0;
				op.zoom = 1;
			}else if (event.Key.Code == sf::Keyboard::B){//cambio del bloquedo de desplazamiento con raton
				op.bloquearMov = !op.bloquearMov;
				if (op.bloquearMov){
					op.manager->removeType(Core::Entities::e_floor,0);
					op.lockLabel->setCaption("Locked");
					op.lockLabel->setColorText(Color<float>(1,0,0));
				}else{
					op.manager->addFloor(op.perimetrePoints,0,Color<float>(0.5,0.5,0.5));
					op.lockLabel->setCaption("Unlock");
					op.lockLabel->setColorText(Color<float>(0,1,0));
				}
			}else if (event.Key.Code == sf::Keyboard::E){//mostrar/ocultar eje
				op.showEdge = !op.showEdge;
			}else if (event.Key.Code == sf::Keyboard::Z){//disminuir zoom
				if (op.zoom>=0)
					op.zoom-=0.1;
			}else if (event.Key.Code == sf::Keyboard::A){//aumentar zoom
				op.zoom+=0.1;
			}else if (event.Key.Code == sf::Keyboard::Left){
				op.despX+=3;
			}else if (event.Key.Code == sf::Keyboard::Right){
				op.despX-=3;
			}else if (event.Key.Code == sf::Keyboard::Up){
				op.despY+=3;
			}else if (event.Key.Code == sf::Keyboard::Down){
				op.despY-=3;
			}
		}else if (event.Type == sf::Event::MouseMoved){//control de raton
			op.puntero = Polygon(op.mouse,3);
		}

		if (op.modePerimetre){
			controlPerimetre(op,event);
		}else{
			controlObjetos(op,event);
		}

	}

}

void DrawCanvas(TOptions &op){
	Polygon auxPol;
	if (op.showEdge){
		//Dibujo el eje

		//Flecha horizontal
		DrawTriangle(Point(380,300),Point(385,302),Point(385,298),Color<float>(0,0,1.0,1.0));
		DrawTriangle(Point(420,300),Point(415,302),Point(415,298),Color<float>(0,0,1.0,1.0));
		DrawLine(Point(380,300),Point(420,300),Color<float>(0,0,1.0,1.0),1);

		//Flecha vertical
		DrawTriangle(Point(400,320),Point(402,315),Point(398,315),Color<float>(0,1,0));
		DrawTriangle(Point(400,280),Point(402,285),Point(398,285),Color<float>(0,1,0));
		DrawLine(Point(400,280),Point(400,320),Color<float>(0,1,0),1);

		//Punto rojo centro
		DrawSolidCircle(Point(400,300),3,Color<float>(0.7,0,0,0.5));
	}
	if (op.modePerimetre){
		if (!op.perimetrePoints.empty()){

			vector<Point>::iterator iterPerim;
			for (iterPerim = op.perimetrePoints.begin(); iterPerim != op.perimetrePoints.end(); iterPerim++){
				DrawPoint(*iterPerim, Color<float>(0.3,0.4,0.8), 5);
			}
			//op.perimetre.setType(0);
			DrawSolidPolygon(op.perimetre,Color<float>(0.0,0.4,0.6,0.8));

			//Linea de destino
			DrawLine(op.perimetrePoints.back(),op.desplacedMouse,Color<float>(0,1,0),2);

			//Linea de sugerencia
			if (op.foundSuger){
				DrawLine(op.auxSugerLine,op.desplacedMouse,Color<float>(0.9,0,0,0.8),1);
				op.foundSuger = false;
			}
		}
	}else{
		//TODO: Dibujar el canvas con la escena

		op.scene->DrawModeEditor();
		glLoadIdentity();
	}
}

bool removePoint(vector<Point> &puntos, Point p, int radio){
	bool borrado = false;
	vector<Point>::iterator iterPerim;
	for (iterPerim = puntos.begin(); iterPerim != puntos.end(); iterPerim++){
		if ((*iterPerim).isInRadius(p,radio)){
			puntos.erase(iterPerim);
			borrado = true;
			break;
		}
	}
	return borrado;
}

bool isConvex(vector<Point> pol){
	Polygon poly(pol);
	if(poly.isClockwise()){
		//cout << "Sentido horario" << endl;
	}else{
		//cout << "Sentido anti-horario" << endl;
	}

	return poly.isConvex();
}

void controlPerimetre(TOptions &op, sf::Event event){
	if (event.Type == sf::Event::MouseButtonReleased
			&& event.MouseButton.Button == sf::Mouse::Left){
		op.perimetrePoints.push_back(op.desplacedMouse);
		op.perimetre = Polygon(op.perimetrePoints);
	}else if ((event.Type == sf::Event::MouseButtonPressed)
			&& (event.MouseButton.Button == sf::Mouse::Right)){//click derecho para borrar
		if (removePoint(op.perimetrePoints,op.desplacedMouse,8)){//si se borra un punto que esta en un radio de 8 del punto
			op.perimetre = Polygon(op.perimetrePoints);//recargamos el poligono del perimetro con los nuevos puntos
		}
	}
}

void controlObjetos(TOptions &, sf::Event event){
//TODO
}

void RecalculoRaton(TOptions &op, int x, int y){
	op.mouse.setXY(x,y);
	GLdouble model[16];
	GLdouble project[16];
	glGetDoublev(GL_MODELVIEW_MATRIX,model);
	glGetDoublev(GL_PROJECTION_MATRIX ,project);
	double *auxX = new double;
	double *auxY = new double;
	double *auxZ = new double;
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	y = 600 - y;
	gluUnProject(x,y,0, model, project, viewport, auxX, auxY, auxZ);
	x = *auxX;
	y = *auxY;

	op.desplacedMouse.setXY(x,y);
}


