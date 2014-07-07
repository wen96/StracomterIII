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
#include "TRadioButton.h"
#include "TLabel.h"
#include "Matrix.h"
#include "ResourceManager.h"
#include "TPicture.h"

using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;
const float GROSOR = 10;

class TEditorWall{
public:
	TEditorWall(){
		selected = false;
		color = Color<float>(1,0,0);
		colorSelect = Color<float>(1,0,1);
	}
	vector<Point> puntos;
	Point a;
	Point b;
	Color<float> color;
	Color<float> colorSelect;
	bool selected;
	// CALCULOS DE LOS PUNTOS DE PARED /////
	void generatePoints(){
		Point c = a;
		c.setX(b.getX());
		Point d = b;
		d.setX(a.getX());

		Vector2D v1(a,c);
		Vector2D v2(a,d);

		puntos.clear();
		if (v1.crossProduct(v2)<0){
			puntos.push_back(a);
			puntos.push_back(c);
			puntos.push_back(b);
			puntos.push_back(d);
		}else{
			puntos.push_back(a);
			puntos.push_back(d);
			puntos.push_back(b);
			puntos.push_back(c);
		}




	}
	bool isInside(Point p){
		bool inside = false;
		if ( (p.getX() >= a.getX() && p.getY() >= a.getY()) &&
				(p.getX() <= b.getX() && p.getY() <= b.getY()) ){
			inside = true;
		}else if ( (p.getX() <= a.getX() && p.getY() <= a.getY()) &&
				(p.getX() >= b.getX() && p.getY() >= b.getY()) ){
			inside = true;
		}else if ( (p.getX() <= a.getX() && p.getY() >= a.getY()) &&
				(p.getX() >= b.getX() && p.getY() <= b.getY()) ){
			inside = true;
		}else if ( (p.getX() >= a.getX() && p.getY() <= a.getY()) &&
				(p.getX() <= b.getX() && p.getY() >= b.getY()) ){
			inside = true;
		}
		return inside;
	}
};

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
		typeEnt = Core::Entities::e_captain;
		modeWall = false;
		modeSave = false;
		drawPointA = true;
		iterSelecPared = paredes.end();
		currLine = "";
	}

	//Camaras
	Camera c_panel;
	Camera c_canvas;

	//Utiles de acceso
	TForm panel;
	TWindow *window;
	IOControl *eventosTeclado;
	TLabel *modeLabel;
	TLabel *typeEnemyLabel;
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
	bool modeSave;

	//Variables de redisposicion
	int despX;
	int despY;
	float zoom;

	//Linea de nombre del fichero
	string currLine;
	TLabel* lSave;
	//objetos

	//Typo para saber el tipo de entidad que se quiere dibujar
	Core::Entities::Type typeEnt;

	//Perimetro
	Polygon perimetre;
	vector<Point> perimetrePoints;

	Point jugador;

	vector<Point> mesas;
	vector<Point> columnas;

	//paredes
	vector<TEditorWall> paredes;
	TEditorWall paredSelec;
	vector<TEditorWall>::iterator iterSelecPared;

	vector<Point> enemy1;
	vector<Point> enemy2;
	vector<Point> enemy3;
	vector<Point> miniboss;
	Point megaboss;
	GLfloat mv[16];

};

//Cosas de opengl para camaras y tal
void Reshape(int, TOptions &op);
//Control de eventos
void ControlEvents(TOptions &op);
//Dibujo del canvas donde esta el mapa
void DrawCanvas(TOptions &op);
//Funcion util para borrar un punto de la lista
bool removePoint(vector<Point> &puntos, Point p, int radio);
//Funcion para saber si un poligono es convexo o no
bool isConvex(vector<Point> pol);
//funcion para guardar el mapa en un fichero
void saveMap(string nomFile, TOptions &op);
//funcion auxiliar para borrar paredes
void removeSelected(TOptions &op);
//funcion del evento de guardado
void eventSave(TOptions&,sf::Event&);

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

	op.panel = TForm(200, 600, Point(100,300));

	TLabel *modeLabel = new TLabel(150,16,"Bloquear movimiento: B",12);
	modeLabel->setMarginUp(12);
	op.panel.addWidget(modeLabel);

	modeLabel = new TLabel(150,18,"Loqued",14);
	modeLabel->setColorText(Color<float>(1,0,0));
	op.panel.addWidget(modeLabel);
	op.lockLabel = modeLabel;

	op.panel.addWidget(new TLabel(150,16,"Cambiar modo: Space",12));
	modeLabel = new TLabel(150,16,"Perimetro",12);
	op.panel.addWidget(modeLabel);
	op.modeLabel = modeLabel;
	op.panel.addWidget(new TLabel(150,16,"Mostra-Ocultar eje: E",12));
	op.panel.addWidget(new TLabel(150,16,"<= => (direction keys)",12));
	op.panel.addWidget(new TLabel(150,16,"Zoom: Z:- | A:+",12));
	op.panel.addWidget(new TLabel(150,16,"Restaurar vista: R",12));
	op.panel.addWidget(new TLabel(150,16,"Delete: Right click",12));

	TButton *b = new TButton("Pared");
	b->setMarginUp(20);
	b->setMarginLeft(10);
	b->setEnable(false);
	op.panel.addWidget(b);

	b = new TButton("Player");
	b->setMarginUp(20);
	b->setMarginLeft(10);
	b->setEnable(false);
	b->setClicked(true);
	op.panel.addWidget(b);

	b = new TButton("Enemy");
	b->setMarginUp(20);
	b->setMarginBottom(10);
	b->setMarginLeft(10);
	b->setEnable(false);
	op.panel.addWidget(b);
	modeLabel = new TLabel(175,12,"Change type: Num1,Num2,Num3",10);
	modeLabel->setMarginUp(20);
	modeLabel->setMarginBottom(20);
	op.panel.addWidget(modeLabel);
	op.typeEnemyLabel = modeLabel;

	b = new TButton("Mesa");
	b->setMarginUp(20);
	b->setMarginLeft(10);
	b->setEnable(false);
	op.panel.addWidget(b);

	b = new TButton("Columna");
	b->setMarginUp(20);
	b->setMarginLeft(10);
	b->setEnable(false);
	op.panel.addWidget(b);

	b = new TButton("Delete Wall");
	b->setMarginUp(50);
	b->setMarginLeft(10);
	b->setEnable(false);
	op.panel.addWidget(b);

	b = new TButton("Save Map");
	b->setMarginUp(50);
	b->setMarginLeft(10);
	b->setEnable(false);
	op.panel.addWidget(b);
	op.lSave = new TLabel(150,18,"Mapa sin guardar",12);
	op.lSave->setColorText(Color<float>(1,0,0));
	op.panel.addWidget(op.lSave);

	glEnable (GL_BLEND);
	glEnable (GL_POLYGON_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Mientras la ventana este abierta (que se cierra con Esc o con la X de cerrarla)
	while (window->isOpen()) {

		//Limpieza de color de la ventana (en este caso la limpio a blanco)
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);




		//Aqui el Canvas
		Reshape(0,op);
		DrawCanvas(op);

		float x = (*eventosTeclado).GetMouseX();
		float y = (*eventosTeclado).GetMouseY();
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

		ControlEvents(op);

		//Aqui el HUD
		Reshape(1,op);
		op.panel.Draw();
		DrawPolygon(op.puntero,Color<float>(0,1,0));


		//Actualizador de los botones (por el mundo y por poner a false los isOver)
		op.panel.Update(window->getFrameTime());

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
	map.setPerimeter(op.perimetrePoints);
	map.addObject(op.jugador,Core::Entities::e_captain);
	vector<Point>::iterator iterPoints;
	//Mesas
	for (iterPoints = op.mesas.begin(); iterPoints != op.mesas.end(); iterPoints++){
		map.addObject(*iterPoints,Core::Entities::e_table);
	}
	//Columnas
	for (iterPoints = op.columnas.begin(); iterPoints != op.columnas.end(); iterPoints++){
		map.addObject(*iterPoints,Core::Entities::e_columne);
	}
	//enemy 1
	for (iterPoints = op.enemy1.begin(); iterPoints != op.enemy1.end(); iterPoints++){
		map.addObject(*iterPoints,Core::Entities::e_enemy1);
	}
	//enemy 2
	for (iterPoints = op.enemy2.begin(); iterPoints != op.enemy2.end(); iterPoints++){
		map.addObject(*iterPoints,Core::Entities::e_enemy2);
	}
	//enemy 3
	for (iterPoints = op.enemy3.begin(); iterPoints != op.enemy3.end(); iterPoints++){
		map.addObject(*iterPoints,Core::Entities::e_enemy3);
	}

	vector<TEditorWall>::iterator iterWalls;
	for (iterWalls = op.paredes.begin(); iterWalls != op.paredes.end(); iterWalls++){
		map.addWall(iterWalls->puntos);
	}

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
	wid = op.panel.whoIsClicked(op.mouse);
	if (wid != NULL){
		wid->setOver(true);
	}
	Point mouseRect;

	int errorMargen = 0;

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


	////############################# EVENTOS GENERALES ############################################////

	vector<TWidget*> widgets = op.panel.getWidgets();
	sf::Event event;
	while (op.window->getEvent(event)) {

		//Guardado de partida
		if(op.modeSave)
		{
			eventSave(op,event);
		}else{

		//Eventos de control
		if (event.Type == sf::Event::Closed) {//control de cerrado de ventana
			op.window->close();
		} else if (event.Type == sf::Event::KeyPressed
				&& event.Key.Code == sf::Keyboard::Escape) {//control de cerrado de ventana
			op.window->close();
		}else if (event.Type == sf::Event::KeyPressed
				&& event.Key.Code == sf::Keyboard::Space){
			//CAMBIO DE MODO PERIMETRO A MODO DIBUJO
			op.modePerimetre = !op.modePerimetre;
			if (op.modePerimetre){
				op.modeLabel->setCaption("Modo perimetro");
			}else{
				op.modeLabel->setCaption("Modo objetos");
			}
			//enableamos los botones
			vector<TWidget*>::iterator iter;
			for (iter = widgets.begin(); iter != widgets.end(); iter++){
				(*iter)->setEnable(!op.modePerimetre);
			}


		}else if (event.Type == sf::Event::KeyPressed
				&& event.Key.Code == sf::Keyboard::R){
			op.despY = 0;
			op.despX = 0;
			op.zoom = 1;
		}else if (event.Type == sf::Event::KeyPressed
				&& event.Key.Code == sf::Keyboard::B){

			op.bloquearMov = !op.bloquearMov;
			if (op.bloquearMov){
				op.lockLabel->setCaption("Locked");
			}else{
				op.lockLabel->setCaption("");
			}
		}else if (event.Type == sf::Event::KeyPressed
				&& event.Key.Code == sf::Keyboard::E){
			op.showEdge = !op.showEdge;
		}else if (event.Type == sf::Event::KeyPressed
				&& event.Key.Code == sf::Keyboard::Z){
			if (op.zoom>=0)
				op.zoom-=0.1;
		}else if (event.Type == sf::Event::KeyPressed
				&& event.Key.Code == sf::Keyboard::A){
			op.zoom+=0.1;
		}else if (event.Type == sf::Event::KeyPressed
				&& event.Key.Code == sf::Keyboard::Left){
			op.despX+=3;
		}else if (event.Type == sf::Event::KeyPressed
				&& event.Key.Code == sf::Keyboard::Right){
			op.despX-=3;
		}else if (event.Type == sf::Event::KeyPressed
				&& event.Key.Code == sf::Keyboard::Up){
			op.despY+=3;
		}else if (event.Type == sf::Event::KeyPressed
				&& event.Key.Code == sf::Keyboard::Num1){
			op.typeEnemyLabel->setCaption("Enemy1");
			op.typeEnt = Core::Entities::e_enemy1;
		}else if (event.Type == sf::Event::KeyPressed
				&& event.Key.Code == sf::Keyboard::Num2){
			op.typeEnemyLabel->setCaption("Enemy2");
			op.typeEnt = Core::Entities::e_enemy2;
		}else if (event.Type == sf::Event::KeyPressed
				&& event.Key.Code == sf::Keyboard::Num3){
			op.typeEnemyLabel->setCaption("Enemy3");
			op.typeEnt = Core::Entities::e_enemy3;
		}else if (event.Type == sf::Event::KeyPressed
				&& event.Key.Code == sf::Keyboard::Down){
			op.despY-=3;
		}else if ((event.Type == sf::Event::MouseButtonPressed)
				&& (event.MouseButton.Button == sf::Mouse::Left)){
			//CONTROL DE PULSADO DE BOTONES
			if (wid!=NULL){
				vector<TWidget*>::iterator iter;
				for (iter = widgets.begin(); iter != widgets.end(); iter++){
					(*iter)->setClicked(false);
				}
				wid->setClicked(true);

				string textButon = "";

				if(wid->getWidget() == Core::Widget::w_button)
					textButon = ((TButton*)wid)->getCaption();

				if (textButon == "Mesa"){
					op.typeEnt = Core::Entities::e_table;
					op.modeWall = false;
				}else if (textButon == "Pared"){
					op.typeEnt = Core::Entities::e_wall;
					op.modeWall = true;
				}else if (textButon == "Player"){
					op.typeEnt = Core::Entities::e_captain;
					op.modeWall = false;
				}else if (textButon == "Columna"){
					op.typeEnt = Core::Entities::e_columne;
					op.modeWall = false;
				}else if (textButon == "Save Map"){
					op.lSave->setCaption("");
					op.lSave->setColorText(Color<float>(0,0,0));
					op.modeSave = true;
				}else if (textButon == "Delete Wall"){
					removeSelected(op);

				}else if (textButon == "Enemy"){
					string typeEn = op.typeEnemyLabel->getCaption();
					if (typeEn == "Enemy1"){
						op.typeEnt = Core::Entities::e_enemy1;
					}else if (typeEn == "Enemy2"){
						op.typeEnt = Core::Entities::e_enemy2;
					}else if (typeEn == "Enemy3"){
						op.typeEnt = Core::Entities::e_enemy3;
					}else{
						cerr << "Tipo de enemigo no seleccionado\n";
					}

				}else if (textButon == "<"){
					//TODO
				}else if (textButon == "^"){
					//TODO
				}else if (textButon == "V"){
					//TODO
				}else if (textButon == "Rotar"){
					//TODO
				}
			}
		}else if (event.Type == sf::Event::MouseMoved){//control de raton
			op.puntero = Polygon(op.mouse,3);
		}else
			//CUIDADO, aqui no puede ir codigo este espacio es para que se vea mas claro
			//----------------------------------//


			if (op.modeWall && !op.modePerimetre){//Si vamos a dibujar una pared WALL###########################
				if ((event.Type == sf::Event::MouseButtonReleased)//Click izquierdo
						&& (event.MouseButton.Button == sf::Mouse::Left)){
					if (wid == NULL){//si no se ha pulsado ningun boton
						if (op.drawPointA){
							op.paredSelec.a = op.desplacedMouse;
							op.drawPointA = false;
						}else{
							op.paredSelec.b = op.desplacedMouse;
							op.paredSelec.generatePoints();
							op.paredes.push_back(op.paredSelec);
							op.iterSelecPared =  op.paredes.end();
							op.drawPointA = true;
						}
					}

				}else if ((event.Type == sf::Event::MouseButtonReleased)//click derecho
						&& (event.MouseButton.Button == sf::Mouse::Right)){
					//Miramos a ver en que pared hemos pulsado
					bool soloUna = false;//booleano para seleccionar solo una pared
					vector< TEditorWall >::iterator iterPared;
					for (iterPared = op.paredes.begin(); iterPared != op.paredes.end(); iterPared++){
						if (iterPared->isInside(op.desplacedMouse) && !soloUna){
							iterPared->selected = true;
							op.iterSelecPared = iterPared;
							soloUna = true;
						}else{
							iterPared->selected = false;
						}
					}
				}


			}else{//Si no hacemos un control normal
				if ((event.Type == sf::Event::MouseButtonReleased)
						&& (event.MouseButton.Button == sf::Mouse::Left)){//clicks izquierdos


					if (op.modePerimetre){//si estamos en modo perimetro ponemos puntos al perimetro
						op.perimetrePoints.push_back(op.desplacedMouse);
						op.perimetre = Polygon(op.perimetrePoints);

					}else{//si no estamos en modo perimetro dibujamos el elemento adecuado
						if (wid==NULL){
							switch (op.typeEnt){
							case Core::Entities::e_table:
								op.mesas.push_back(op.desplacedMouse);
								break;
							case Core::Entities::e_captain:
								op.jugador = op.desplacedMouse;
								break;
							case Core::Entities::e_columne:
								op.columnas.push_back(op.desplacedMouse);
								break;
							case Core::Entities::e_enemy1:
								op.enemy1.push_back(op.desplacedMouse);
								break;
							case Core::Entities::e_enemy2:
								op.enemy2.push_back(op.desplacedMouse);
								break;
							case Core::Entities::e_enemy3:
								op.enemy3.push_back(op.desplacedMouse);
								break;
							default:
								break;
							}
						}
					}
				}else if ((event.Type == sf::Event::MouseButtonPressed)
						&& (event.MouseButton.Button == sf::Mouse::Right)){//click derecho (habitualmente para borrar)
					if (op.modePerimetre){//si estamos en modo perimetro borramos puntos
						if (removePoint(op.perimetrePoints,op.desplacedMouse,8)){//si se borra un punto que esta en un radio de 8 del punto
							op.perimetre = Polygon(op.perimetrePoints);//recargamos el poligono del perimetro con los nuevos puntos
						}
					}else{//si estamos en modo objetos

						if (wid==NULL){//si no se ha pulsado ningun boton

							switch (op.typeEnt){
							case Core::Entities::e_table:
								removePoint(op.mesas,op.desplacedMouse,60);
								break;
							case Core::Entities::e_columne:
								removePoint(op.columnas,op.desplacedMouse,50);
								break;
							default:

								break;
							}
						}
					}
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
		//Bibujo del perimetro
		DrawPolygon(op.perimetre,Color<float>(0.4,0.4,0.4));

		//Dibujo de las mesas
		vector<Point>::iterator iterPoints;
		for (iterPoints = op.mesas.begin(); iterPoints != op.mesas.end(); iterPoints++){
			auxPol = Polygon(5,*iterPoints,60,45);
			DrawSolidPolygon(auxPol, Color<float>(0.4,0.1,0.8));
		}

		//Dibujo del player
		auxPol = Polygon(8,op.jugador,30,45);
		DrawSolidPolygon(auxPol,Color<float>(0.5,0.7,0.3));

		//Dibujo de colunas
		for (iterPoints = op.columnas.begin(); iterPoints != op.columnas.end(); iterPoints++){
			DrawSolidCircle(*iterPoints, 50, Color<float>(0.6,0.1,0.3));
		}
		//Dibujo de colunas
		for (iterPoints = op.enemy1.begin(); iterPoints != op.enemy1.end(); iterPoints++){
			auxPol = Polygon(8,*iterPoints,30,45);
			DrawSolidPolygon(auxPol,Color<float>(0.8,0.4,0.3));
		}
		//Dibujo de colunas
		for (iterPoints = op.enemy2.begin(); iterPoints != op.enemy2.end(); iterPoints++){
			auxPol = Polygon(8,*iterPoints,30,45);
			DrawSolidPolygon(auxPol,Color<float>(0.8,0.6,0.3));
		}
		//Dibujo de colunas
		for (iterPoints = op.enemy3.begin(); iterPoints != op.enemy3.end(); iterPoints++){
			auxPol = Polygon(8,*iterPoints,30,45);
			DrawSolidPolygon(auxPol,Color<float>(0.8,0.4,0.6));
		}

		//Dibujo paredes

		//detalles para editar pared
		if (!op.drawPointA){//si se va a dibujar el punto b
			//Dibujamos una cajita de sugerencia
			TEditorWall auxWall;
			auxWall.a = op.paredSelec.a;
			auxWall.b = op.desplacedMouse;
			auxWall.generatePoints();
			Polygon pol = Polygon(auxWall.puntos);
			DrawPolygon(pol,Color<float>(1,0,1));
		}
		vector< TEditorWall >::iterator iterPared;
		for (iterPared = op.paredes.begin(); iterPared != op.paredes.end(); iterPared++){
			Polygon pol = Polygon((*iterPared).puntos);
			if (iterPared->selected){
				DrawPolygon(pol,iterPared->colorSelect);
			}else{
				DrawPolygon(pol,iterPared->color);
			}

		}

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
	/*
	given p[k], p[k+1], p[k+2] each with coordinates x, y:
	dx1 = x[k+1]-x[k]
	dy1 = y[k+1]-y[k]
	dx2 = x[k+2]-x[k+1]
	dy2 = y[k+2]-y[k+1]
	dotproduct = dx1*dx2 + dy1*dy2

	si esto recorriendo todo el poligono da siempre positivo es convexo si no concavo (o al reves, no lo se)
	 */
	return true;
}

void removeSelected(TOptions &op){
	vector< TEditorWall >::iterator iterPared;
	for (iterPared = op.paredes.begin(); iterPared != op.paredes.end(); iterPared++){
		if (iterPared->selected){
			op.paredes.erase(iterPared);
			break;
		}
	}
}

void eventSave(TOptions &op,sf::Event &event)
{
	if (event.Type == sf::Event::TextEntered) {
		if(event.Text.Unicode == 8){	// Pulsado Backspace
			if(op.currLine.size() > 0){
				op.currLine.erase(op.currLine.size() - 1, 1);
				op.lSave->setCaption(op.currLine);
			}

		}else if(event.Text.Unicode == 13){	// Pulsado Enter

			saveMap(op.currLine,op);
			op.currLine = "";
			op.lSave->setCaption("Guardado");
			op.lSave->setColorText(Color<float>(0,1,0));
			op.modeSave = false;

		}else if (event.Text.Unicode < 128) {

			op.currLine += static_cast<char>(event.Text.Unicode);
			op.lSave->setCaption(op.currLine);
		}
	}

}
