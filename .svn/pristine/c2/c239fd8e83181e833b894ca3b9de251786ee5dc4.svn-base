#include <iostream>
#include <GL/gl.h>
#include <SFML/Window.hpp>

#include "Polygon.h"
#include "Color.h"
#include "TForm.h"
#include "SceneManager.h"
#include "Map.h"
#include "Scene.h"
using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;
const float GROSOR = 10;

/** Clase TOptions contenedor de variables para pasarlo de funcion en función y evitar variables globales.
 * Si se necesita cambiar el nombre porque hay algun conflicto que se cambie, esta clase solo se utiliza por este fichero.
 */
class TOptionsMenu {
public:
	TOptionsMenu() {
		modePerimetre = true;
		modeObjects = false;
		showEdge = true;
		modeLabel = NULL;
		despX = 0;
		despY = 0;
		zoom = 1;
		bloquearMov = true;
		modeWall = false;
		drawPointA = true;
		resManager = NULL;
		manager = NULL;
		sugerPerim = NULL;
		mode = none;
		currentEntity = NULL;
		c_canvas = Camera(WIDTH, HEIGHT, -1, 1);
		c_canvas.setOrtho();
		c_canvas.setScale(400);
		mapa = NULL;
		currentEntity = NULL;
		saveLine = "";
		lSave = NULL;
	}
	enum ObjectMode {
		none, player, newWall, newDoor, table, desk, couch, sofa, chair, shelf, plantPot, mesaConSillam, hp1, hp2, hp3, ammo1, ammo2, ammo3,  save, objectSelected, size
	};
	ObjectMode mode;

	SceneManager *sm;
	GameMenu *menuGame;
	TWindow *window;
	IOControl *eventosIO;
	TForm* menuPrincipal;
	HIDControl *hid;
	Scene *scene;

	//Formas
	Shape *perimProvisional;
	Shape *sugerPerim;

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
	bool modeObjects;
	bool showEdge;
	bool bloquearMov;
	bool foundSuger;
	bool wikiScene;

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

	GLfloat mv[16];
	Camera c_canvas;

	// Colocacion de objetos
	Entity * currentEntity;

	Map * mapa;
	NavGraph * navgraph;

	string saveLine;
	TLabel* lSave;
};

void UpdateScene(TOptionsMenu &op);

//Control de eventos
void ControlEvents(TOptionsMenu &op);
//Recalcula raton
void RecalculoRaton(TOptionsMenu &op, int x, int y);
//Funcion util para borrar un punto de la lista
bool removePoint(vector<Point> &puntos, Point p, int radio);
//Funcion para controlas los eventos con perimetro
void controlPerimetre(TOptionsMenu &, sf::Event event);
//Funcion para controlas los eventos con objetos
void controlObjetos(TOptionsMenu &, sf::Event event);

void moveWall(TOptionsMenu &op, sf::Event event);
void moveDoor(TOptionsMenu &op, sf::Event event);
void moveObstacle(TOptionsMenu &op, sf::Event event);

void createMenus(TOptionsMenu &op);

Map * dumpMap(TOptionsMenu op);

void saveMap(TOptionsMenu op, string name);

Entity * pickObject(TOptionsMenu &op, Point p);

int main(int argc, char *argv[]) {
	/* INICION */
	IOControl *eventosTeclado = NULL;
	TWindow *window = new TWindow;
	World *world = new World();

	window->setNombreVentana("Stracometer III: Editor de Mapas");
	window->openSFML(WIDTH, HEIGHT, false);
	window->Init();
	eventosTeclado = new IOControl(window);

	HIDControl *hid = new HIDControl(eventosTeclado);
	GameMenu *menuGame = new GameMenu(hid);
	SceneManager *sm = SceneManager::getInstance();
	sm->setMyClippin(false);
	ResourceManager *resources = ResourceManager::getInstance(world, NULL);
	EntityManager *entMan = new EntityManager(resources);
	CharacterFeature *features = CharacterFeature::getInstance();
	features->loadData("testFiles/features/f1.xml");

	Scene *scene = new Scene(entMan, resources, 800.0, 600.0);

	TOptionsMenu op;
	op.zoom = 1;
	op.despX = 0;
	op.despY = 0;
	op.window = window;
	op.sm = sm;
	op.eventosIO = eventosTeclado;
	op.manager = entMan;
	op.menuGame = menuGame;
	op.perimProvisional = NULL;
	op.hid = hid;
	op.scene = scene;
	op.wikiScene = false;
	/* ------- */
	resources->loadModels();
	resources->loadTextures();
	sm->makeEditorTree();

	op.sugerPerim = new Shape(Polygon(), Color<float>(1, 0, 0));
	op.sm->addElement((Element*) op.sugerPerim, op.sm->getNode(Graphics::DirectNodes::t_escena));
	op.sugerPerim->getNodo()->setVisible(false);

	menuGame->setVisible(Graphics::Menus::m_inicio);

	if(argc == 2){
		op.mapa = new Map();
		op.mapa->setManager(op.manager);
		op.mapa->setMap(argv[1]);
		op.mapa->loadData();

		op.perimetrePoints = op.mapa->getPerimeter();
		op.perimetre = Polygon(op.perimetrePoints);
		op.perimProvisional = new Shape(op.perimetre, Color<float>(1, 1, 1));
		op.sm->addElement((Element*) op.perimProvisional, op.sm->getNode(Graphics::DirectNodes::t_escena));

		op.modePerimetre = false;

		op.menuGame->setVisible(Graphics::Menus::m_pause);
		op.perimProvisional->getNodo()->setVisible(false);
		op.sugerPerim->getNodo()->setVisible(false);


	}

	//Esto funciona por los pelos TODO
	entMan->addPlayer(Point(), 0.0);
	entMan->setAllCharacterFeatures(features);
	entMan->addPointer();

	sm->addElement(menuGame, sm->getNode(Graphics::DirectNodesEditor::t_menu));

	createMenus(op);

	sm->InitializeScene();

	//Mientras la ventana este abierta (que se cierra con Esc o con la X de cerrarla)
	while (window->isOpen()) {

		UpdateScene(op);

		if (op.wikiScene) {
			op.scene->Draw();
		} else {
			sm->DrawScene();
		}

		ControlEvents(op);
		world->UpdateWorld(60);
		window->display();

	}

	saveMap(op, "editorMap.xml");

	return 0;
}

void createMenus(TOptionsMenu &op) {
	TForm *mainMenu = new TForm(200, 600, Point(100, 300));
	mainMenu->setColor(Color<float>(0.3, 0.3, 0.3, 0.7));
	TLabel *label = new TLabel(200, 300, "Perimetro");
	label->setMarginUp(10);
	label->setColorText(Color<float>(0.1, 0.1, 0.4));
	label->setSize(20);
	op.modeLabel = label;
	mainMenu->addWidget(label);

	//ESTO NO DEBE ESTAR AQUI

	///---------------------

	op.menuGame->addMenu(Graphics::Menus::m_inicio, mainMenu);

	TForm *menuObjects = new TForm(200, 600, Point(100, 300));
	menuObjects->setColor(Color<float>(0.6, 0.7, 0.6, 0.4));
	label = new TLabel(200, 100, "Objetos");
	label->setMarginUp(10);
	label->setColorText(Color<float>(0.5, 0.5, 0.9));
	label->setSize(20);
	menuObjects->addWidget(label);

	int nEvento = 1;

	TButton *b = new TButton("Player");
	b->setEnable(false);
	b->setEvento(nEvento++);
	b->setColorOver(Color<float>(0.4, 0.4, 0.6));
	b->setEnable(true);
	menuObjects->addWidget(b);

	b = new TButton("Pared");
	b->setEnable(false);
	b->setEvento(nEvento++);
	b->setColorOver(Color<float>(0.4, 0.4, 0.6));
	b->setEnable(true);
	menuObjects->addWidget(b);

	b = new TButton("Puerta");
	b->setEnable(false);
	b->setEvento(nEvento++);
	b->setColorOver(Color<float>(0.4, 0.4, 0.6));
	b->setEnable(true);
	menuObjects->addWidget(b);

	b = new TButton("Mesa");
	b->setEnable(false);
	b->setEvento(nEvento++);
	b->setColorOver(Color<float>(0.4, 0.4, 0.6));
	b->setEnable(true);
	menuObjects->addWidget(b);

	b = new TButton("Escritorio");
	b->setEnable(false);
	b->setEvento(nEvento++);
	b->setColorOver(Color<float>(0.4, 0.4, 0.6));
	b->setEnable(true);
	menuObjects->addWidget(b);

	b = new TButton("Sillon");
	b->setEnable(false);
	b->setEvento(nEvento++);
	b->setColorOver(Color<float>(0.4, 0.4, 0.6));
	b->setEnable(true);
	menuObjects->addWidget(b);

	b = new TButton("Sofa");
	b->setEnable(false);
	b->setEvento(nEvento++);
	b->setColorOver(Color<float>(0.4, 0.4, 0.6));
	b->setEnable(true);
	menuObjects->addWidget(b);

	b = new TButton("Silla");
	b->setEnable(false);
	b->setEvento(nEvento++);
	b->setColorOver(Color<float>(0.4, 0.4, 0.6));
	b->setEnable(true);
	menuObjects->addWidget(b);

	b = new TButton("Estanteria");
	b->setEnable(false);
	b->setEvento(nEvento++);
	b->setColorOver(Color<float>(0.4, 0.4, 0.6));
	b->setEnable(true);
	menuObjects->addWidget(b);

	b = new TButton("Maceta");
	b->setEnable(false);
	b->setEvento(nEvento++);
	b->setColorOver(Color<float>(0.4, 0.4, 0.6));
	b->setEnable(true);
	menuObjects->addWidget(b);

	b = new TButton("Mesa con Sillas");
	b->setEnable(false);
	b->setEvento(nEvento++);
	b->setColorOver(Color<float>(0.4, 0.4, 0.6));
	b->setEnable(true);
	menuObjects->addWidget(b);

	b = new TButton("Botiquín 1");
	b->setEnable(false);
	b->setEvento(nEvento++);
	b->setColorOver(Color<float>(0.4, 0.4, 0.6));
	b->setEnable(true);
	menuObjects->addWidget(b);

	b = new TButton("Botiquín 2");
	b->setEnable(false);
	b->setEvento(nEvento++);
	b->setColorOver(Color<float>(0.4, 0.4, 0.6));
	b->setEnable(true);
	menuObjects->addWidget(b);

	b = new TButton("Botiquín 3");
	b->setEnable(false);
	b->setEvento(nEvento++);
	b->setColorOver(Color<float>(0.4, 0.4, 0.6));
	b->setEnable(true);
	menuObjects->addWidget(b);

	b = new TButton("Munición 1");
	b->setEnable(false);
	b->setEvento(nEvento++);
	b->setColorOver(Color<float>(0.4, 0.4, 0.6));
	b->setEnable(true);
	menuObjects->addWidget(b);

	b = new TButton("Munición 2");
	b->setEnable(false);
	b->setEvento(nEvento++);
	b->setColorOver(Color<float>(0.4, 0.4, 0.6));
	b->setEnable(true);
	menuObjects->addWidget(b);

	b = new TButton("Munición 3");
	b->setEnable(false);
	b->setEvento(nEvento++);
	b->setColorOver(Color<float>(0.4, 0.4, 0.6));
	b->setEnable(true);
	menuObjects->addWidget(b);

	/*b = new TButton("Guardar");
	b->setEnable(false);
	b->setEvento(nEvento++);
	b->setColorOver(Color<float>(0.4, 0.4, 0.6));
	b->setEnable(true);
	menuObjects->addWidget(b);*/

	op.lSave = new TLabel(150,18,"Mapa sin guardar",12);
	op.lSave->setColorText(Color<float>(1,0,0));
	menuObjects->addWidget(op.lSave);

	op.menuGame->addMenu(Graphics::Menus::m_pause, menuObjects);
}

void UpdateScene(TOptionsMenu &op) {

	op.manager->Update();

	if (op.wikiScene) {
		op.c_canvas.exportOpenGL();
		glScalef(op.zoom, -op.zoom, 1.0);
		glTranslatef(-1.0 * WIDTH / 2, -1.0 * HEIGHT / 2, 0.0);
		glTranslatef(op.despX, op.despY, 0);

		glGetFloatv(GL_MODELVIEW_MATRIX, op.mv);
	} else {
		GraphicNode *gn = op.sm->getNode(Graphics::DirectNodesEditor::t_escena);

		Element *escenario = gn->getItem();

		((Transform*) escenario)->setIdentity();

		((Transform*) escenario)->addScale(1, -1, 1);
		((Transform*) escenario)->addScale(op.zoom, op.zoom, op.zoom);
		((Transform*) escenario)->addTranslation(-1.0 * op.despX, op.despY, -100);
	}
}

void ControlEvents(TOptionsMenu &op) {

	Point mouseRect;

	int errorMargen = 0;

	//Desplazamiento automatico al acercarse al final
	if (!op.bloquearMov) {
		if (WIDTH - op.mouse.getX() < 10) {
			op.despX -= 5;
		} else if (WIDTH - op.mouse.getX() > (WIDTH - 10)) {
			op.despX += 5;
		}
		if (HEIGHT - op.mouse.getY() < 10) {
			op.despY -= 5;
		} else if (HEIGHT - op.mouse.getY() > (HEIGHT - 10)) {
			op.despY += 5;
		}
	}

	////############################# EVENTOS GENERALES ############################################////

	//vector<TWidget*> widgets = op.panel->getWidgets();
	sf::Event event;
	while (op.window->getEvent(event)) {
		//Eventos de control
		if (event.Type == sf::Event::Closed) { //control de cerrado de ventana
			op.window->close();
		} else if (event.Type == sf::Event::KeyPressed) {

			if (event.Key.Code == sf::Keyboard::Escape) { //control de cerrado de ventana
				op.window->close();
			} else if (event.Key.Code == sf::Keyboard::Space && !op.modeObjects) { //cambio modo permitro
				op.modePerimetre = !op.modePerimetre; //cam biamos la variable de control
				if (op.modePerimetre) { //Si se activa el modo perimetro
					op.menuGame->setVisible(Graphics::Menus::m_inicio);
					op.modeLabel->setCaption("Perimetre");
					op.manager->removeFloors();
					op.perimProvisional->getNodo()->setVisible(true);
					op.sugerPerim->getNodo()->setVisible(true);
				} else { //Si se activa el modo objetos
					op.menuGame->setVisible(Graphics::Menus::m_pause);

					op.perimProvisional->getNodo()->setVisible(false);
					op.sugerPerim->getNodo()->setVisible(false);

					//Si no esta en sentido horario le doy la vuelta
					if (!op.perimetre.isClockwise()) {
						op.perimetre.Reverse();
						op.perimetrePoints = op.perimetre.getPuntos();

					}

					op.manager->addFloor(op.perimetrePoints, 0, Color<float>(1, 1, 1));
				}
			} else if (event.Key.Code == sf::Keyboard::R) { //restaurar valores de desplazamiento y zoom
				op.despY = 0;
				op.despX = 0;
				op.zoom = 1;
			} else if (event.Key.Code == sf::Keyboard::B) { //cambio del bloquedo de desplazamiento con raton
				op.bloquearMov = !op.bloquearMov;
			} else if (event.Key.Code == sf::Keyboard::E) { //mostrar/ocultar eje
				op.showEdge = !op.showEdge;
			} else if (event.Key.Code == sf::Keyboard::Z) { //disminuir zoom
				op.zoom -= 0.01;
			} else if (event.Key.Code == sf::Keyboard::A) { //aumentar zoom
				op.zoom += 0.01;
			} else if (event.Key.Code == sf::Keyboard::Left) {
				op.despX -= 3;
			} else if (event.Key.Code == sf::Keyboard::Right) {
				op.despX += 3;
			} else if (event.Key.Code == sf::Keyboard::Up) {
				op.despY += 3;
			} else if (event.Key.Code == sf::Keyboard::Down) {
				op.despY -= 3;
			} else if (event.Key.Code == sf::Keyboard::F5) {
				op.wikiScene = !op.wikiScene;
			}else if (event.Key.Code == sf::Keyboard::F2) {
				saveMap(op, "editorMap.xml");
			}
		} else if (event.Type == sf::Event::MouseWheelMoved) { //Control de rueda raton para zoom
			if (event.MouseWheel.Delta > 0) {
				op.zoom += 0.01;
			} else {
				op.zoom -= 0.01;
			}
		}

		if (op.modePerimetre) {
			controlPerimetre(op, event);
		} else {
			controlObjetos(op, event);
		}

	}

	/* ------------------ACTUALIZACION RATON --------------------------*/
	Entity *ent = op.manager->getPointer();
	if (ent != NULL) {
		float x = ((*op.eventosIO).GetMouseX());
		float y = ((*op.eventosIO).GetMouseY());
		RecalculoRaton(op, x, y); //En op.mouse se guarda la posicion real y en op.desplacedMouse devuelve la relativa
		((Pointer*) ent)->setCenter(op.desplacedMouse);
		////cout << op.desplacedMouse << endl;
	}

	///############################ DETALLES Y SUGERENCIAS ################################################//

	//Si modo perimetro esta en marcha hacemos
	if (op.modePerimetre) {
		//Sugerencia de linas rectas
		if (op.eventosIO->IsKeyDown(Core::Key::LShift)) {
			errorMargen = 10; //margen de error para la sugerencia de misma altura
			//Calculo de angulos rectos al pulsar mayusculas
			if (op.eventosIO->IsKeyDown(Core::Key::LShift)) {
				if (op.modePerimetre) {
					if (!op.perimetrePoints.empty()) {
						int orX = abs((int) op.perimetrePoints.back().getX());
						int orY = abs((int) op.perimetrePoints.back().getY());
						int mX = abs((int) op.desplacedMouse.getX());
						int mY = abs((int) op.desplacedMouse.getY());
						if (abs(orX - mX) < abs(orY - mY)) {
							op.desplacedMouse.setX(op.perimetrePoints.back().getX());
						} else {
							op.desplacedMouse.setY(op.perimetrePoints.back().getY());
						}
					}
				}
			}
		}

		// Sugerencia de lineas a la misma altura
		vector<Point>::iterator iterPerim;
		for (iterPerim = op.perimetrePoints.begin(); iterPerim != op.perimetrePoints.end(); iterPerim++) {
			if (*iterPerim != op.perimetrePoints.back()) { //si no es el ultimo
				int auxX1 = iterPerim->getX() + errorMargen;
				int auxX2 = iterPerim->getX() - errorMargen;

				int auxY1 = iterPerim->getY() + errorMargen;
				int auxY2 = iterPerim->getY() - errorMargen;

				if (auxX1 >= op.desplacedMouse.getX() && auxX2 <= op.desplacedMouse.getX()) {
					++op.foundSuger = true;
					op.auxSugerLine = *iterPerim;
					if (errorMargen != 0) {
						op.desplacedMouse.setX(iterPerim->getX());
					}
					break;
				} else if (auxY1 >= op.desplacedMouse.getY() && auxY2 <= op.desplacedMouse.getY()) {
					op.foundSuger = true;
					op.auxSugerLine = *iterPerim;
					if (errorMargen != 0) {
						op.desplacedMouse.setY(iterPerim->getY());
					}
					break;
				}
			}
		}
	}

	//Actualizacion Linea roja
	if (op.sugerPerim != NULL) {
		if (op.perimetrePoints.size() > 0) {
			if (op.foundSuger) { //Si va a sugerir una linea
				vector<Point> pAuxSug;
				pAuxSug.push_back(op.perimetrePoints.back());
				pAuxSug.push_back(op.desplacedMouse);
				pAuxSug.push_back(op.auxSugerLine);
				op.sugerPerim->setShape(pAuxSug);
				op.foundSuger = false;
			} else { //Si no solo pinta la principal
				op.sugerPerim->setShape(Polygon(op.perimetrePoints.back(), op.desplacedMouse));
			}
		}
	}

}

bool removePoint(vector<Point> &puntos, Point p, int radio) {
	bool borrado = false;
	vector<Point>::iterator iterPerim;
	for (iterPerim = puntos.begin(); iterPerim != puntos.end(); iterPerim++) {
		if ((*iterPerim).isInRadius(p, radio)) {
			puntos.erase(iterPerim);
			borrado = true;
			break;
		}
	}
	return borrado;
}

/* -------------------------------EVENTOS DE MODO PERIMETRO ---------------------------------*/
void controlPerimetre(TOptionsMenu &op, sf::Event event) {
	bool ocurreAlgo = false;
	if (event.Type == sf::Event::MouseButtonReleased && event.MouseButton.Button == sf::Mouse::Left) {
		op.perimetrePoints.push_back(op.desplacedMouse);
		op.perimetre = Polygon(op.perimetrePoints);
		ocurreAlgo = true;
	} else if ((event.Type == sf::Event::MouseButtonPressed) && (event.MouseButton.Button == sf::Mouse::Right)) { //click derecho para borrar
		if (removePoint(op.perimetrePoints, op.desplacedMouse, 8)) { //si se borra un punto que esta en un radio de 8 del punto
			op.perimetre = Polygon(op.perimetrePoints); //recargamos el poligono del perimetro con los nuevos puntos
			ocurreAlgo = true;
		}
	}
	//Actualizacion en el arbol
	if (ocurreAlgo) {
		if (op.perimProvisional == NULL) {
			op.perimProvisional = new Shape(op.perimetre, Color<float>(1, 1, 1));
			op.sm->addElement((Element*) op.perimProvisional, op.sm->getNode(Graphics::DirectNodes::t_escena));
		} else {
			op.perimProvisional->setShape(op.perimetre);
		}
		if (op.perimetrePoints.size() == 1) {
			if (op.sugerPerim != NULL) {
				op.sugerPerim->getNodo()->setVisible(true);
			}

		} else if (op.perimetrePoints.size() == 0) {
			if (op.sugerPerim != NULL) {
				op.sugerPerim->getNodo()->setVisible(false);
			}
		}
	}
}

void controlObjetos(TOptionsMenu &op, sf::Event event) {
	int evento = op.hid->formMenuControlEditor(op.menuGame->getActive(), event);
	if (evento != -1) { //Si le damos a algun boton
		op.mode = (TOptionsMenu::ObjectMode) evento;
	} else { //Si no le damos a un boton
		switch (op.mode) {
		case TOptionsMenu::player:

			if (event.Type == sf::Event::MouseButtonPressed && event.MouseButton.Button == sf::Mouse::Left) {
				Entity*ent = op.manager->getPlayer();
				if (ent != NULL) {
					ent->setCenter(op.desplacedMouse);
				}
			}
			break;

		case TOptionsMenu::newWall:

			if (event.Type == sf::Event::MouseButtonPressed && event.MouseButton.Button == sf::Mouse::Left) {

				double nx = floor(op.desplacedMouse.getX() / 25) * 25 + 12.5;
				double ny = floor(op.desplacedMouse.getY() / 25) * 25 + 12.5;

				// Creo los puntos de la pared, que es un cuadrado de 25*25
				Point a(nx - 12.5, ny - 12.5);
				Point b(nx - 12.5, ny + 12.5);
				Point c(nx + 12.5, ny + 12.5);
				Point d(nx + 12.5, ny - 12.5);

				vector<Point> paredV;
				paredV.push_back(a);
				paredV.push_back(b);
				paredV.push_back(c);
				paredV.push_back(d);

				op.currentEntity = op.manager->addWall(paredV, 0.0, Color<float>(1, 1, 1));
				op.mode = TOptionsMenu::objectSelected;
			}

			break;

		case TOptionsMenu::newDoor:

			if (event.Type == sf::Event::MouseButtonPressed && event.MouseButton.Button == sf::Mouse::Left) {

				double nx = floor(op.desplacedMouse.getX() / 25) * 25 + 12.5;
				double ny = floor(op.desplacedMouse.getY() / 25) * 25 + 12.5;

				// Creo los puntos de la puerta, que es un rectangulo de 25*50
				Point a(nx - 50, ny - 12.5);
				Point b(nx - 50, ny + 12.5);
				Point c(nx + 50, ny + 12.5);
				Point d(nx + 50, ny - 12.5);

				vector<Point> doorV;
				doorV.push_back(a);
				doorV.push_back(b);
				doorV.push_back(c);
				doorV.push_back(d);

				op.currentEntity = op.manager->addDoor(Point(), doorV);
				op.mode = TOptionsMenu::objectSelected;
			}

			break;

		case TOptionsMenu::table:
		case TOptionsMenu::desk:
		case TOptionsMenu::couch:
		case TOptionsMenu::sofa:
		case TOptionsMenu::chair:
		case TOptionsMenu::shelf:
		case TOptionsMenu::plantPot:
		case TOptionsMenu::mesaConSillam:


			if (event.Type == sf::Event::MouseButtonPressed && event.MouseButton.Button == sf::Mouse::Left) {

				int type = op.mode - (int) TOptionsMenu::table;
				cout << "Core: " << Core::Obstacles::obs_couch << " Editor: " << type << endl;
				op.currentEntity = op.manager->addObstacle((Core::Obstacles::Type) type, op.desplacedMouse, 0.0);
				op.mode = TOptionsMenu::objectSelected;
			}

			break;

		case TOptionsMenu::hp1:
		case TOptionsMenu::hp2:
		case TOptionsMenu::hp3:
		case TOptionsMenu::ammo1:
		case TOptionsMenu::ammo2:
		case TOptionsMenu::ammo3:

			if (event.Type == sf::Event::MouseButtonPressed && event.MouseButton.Button == sf::Mouse::Left) {

				int type = op.mode - (int) TOptionsMenu::hp1;

				//cout << "Que mierda sucede?" << endl;
				op.currentEntity = op.manager->addObject((Core::Objects::Class)type, op.desplacedMouse, 0.0);
				//cout << "Número: " << op.manager->getEntitiesbyType(Core::Entities::e_objects).size() << endl;
				op.mode = TOptionsMenu::objectSelected;
			}

			break;

		case TOptionsMenu::objectSelected:

			if (op.currentEntity != NULL) {

				switch (op.currentEntity->getType()) {
				case Core::Entities::e_wall:
					moveWall(op, event);
					break;

				case Core::Entities::e_door:
					moveDoor(op, event);
					break;

				case Core::Entities::e_obstacle:
					moveObstacle(op, event);
					break;
				case Core::Entities::e_objects:
					moveObstacle(op, event);
					break;
				default:
					break;
				}

			} else {
				op.mode = TOptionsMenu::none;
			}
			break;

		case TOptionsMenu::none:
			if (event.Type == sf::Event::MouseButtonPressed) {

				Entity * ent = pickObject(op, op.desplacedMouse);

				if (ent != NULL) {
					if (event.MouseButton.Button == sf::Mouse::Left) {
						op.currentEntity = ent;
						op.mode = TOptionsMenu::objectSelected;
					} else if (event.MouseButton.Button == sf::Mouse::Right) {
						op.manager->removeEntity(ent->getId());
					}
				}
			}

			break;

		case TOptionsMenu::save:

			if (event.Type == sf::Event::TextEntered) {
				if (event.Text.Unicode == 8) { // Pulsado Backspace
					if (op.saveLine.size() > 0) {
						op.saveLine.erase(op.saveLine.size() - 1, 1);
						op.lSave->setCaption(op.saveLine);
					}

				} else if (event.Text.Unicode == 13) { // Pulsado Enter

					saveMap(op, op.saveLine);
					op.saveLine = "";
					op.lSave->setCaption("Guardado");
					op.lSave->setColorText(Color<float>(0, 1, 0));
					op.mode = op.TOptionsMenu::none;

				} else if (event.Text.Unicode < 128) {

					op.saveLine += static_cast<char>(event.Text.Unicode);
					op.lSave->setCaption(op.saveLine);
				}
			}

			break;

		default:
			break;
		}
	}
}

Entity * pickObject(TOptionsMenu &op, Point p) {

	World *mundo = new World();
	vector<Entity *> entidades;
	vector<Entity *>::iterator iter;

	entidades = op.manager->getEntitiesbyType(Core::Entities::e_wall);
	for (iter = entidades.begin(); iter != entidades.end(); iter++) {

		Polygon poly(((Wall *) (*iter))->getPoints());
		BodyData data(poly);
		Body *cuerpo = new Body(*mundo, data);
		cuerpo->getAngle();
		if (mundo->CutOffPoints(p, Point(-99999, -99999)).size() % 2 == 1) {
			return *iter;
		} else {
			//cout << p << " no esta dentro de " << poly << endl;
		}
	}

	entidades = op.manager->getEntitiesbyType(Core::Entities::e_door);
	for (iter = entidades.begin(); iter != entidades.end(); iter++) {

		Polygon poly(((Door *) (*iter))->getPoints());
		BodyData data(poly);
		Body *cuerpo = new Body(*mundo, data);
		cuerpo->getAngle();
		if (mundo->CutOffPoints(p, Point(-99999, -99999)).size() % 2 == 1) {
			return *iter;
		}
	}

	entidades = op.manager->getEntitiesbyType(Core::Entities::e_obstacle);
	for (iter = entidades.begin(); iter != entidades.end(); iter++) {
		//cout << "Paso" << endl;
		if (((Obstacle *) (*iter))->isInside(p)) {
			//cout << "Entro" << endl;
			return *iter;
		}
	}

	entidades = op.manager->getEntitiesbyType(Core::Entities::e_objects);
	//cout << "En el click" << op.manager->getEntitiesbyType(Core::Entities::e_objects).size() << endl;
	for (iter = entidades.begin(); iter != entidades.end(); iter++) {
		//cout << "Paso" << endl;
		if (((Object *) (*iter))->isInside(p)) {
			//cout << "Entro" << endl;
			return *iter;
		}
	}
	//TODO Coger los obstaculos
	return NULL;
}

void moveWall(TOptionsMenu &op, sf::Event event) {

	if (event.Type == sf::Event::MouseButtonPressed) {

		Entity * ent = pickObject(op, op.desplacedMouse);
		if (ent != NULL) {
			if (event.MouseButton.Button == sf::Mouse::Left) {
				op.currentEntity = ent;
				op.mode = TOptionsMenu::objectSelected;
			} else if (event.MouseButton.Button == sf::Mouse::Right) {
				op.manager->removeEntity(ent->getId());
			}
		} else if (event.MouseButton.Button == sf::Mouse::Left) {
			op.currentEntity = NULL;
			op.mode = TOptionsMenu::none;
		}

	} else if (op.eventosIO->isMouseButtonDown(Core::Mouse::Left)) {

		double x = op.desplacedMouse.getX(), y = op.desplacedMouse.getY();

		y = floor(y / 25) * 25;
		if (((int) ((Wall *) op.currentEntity)->Height() / 25) % 2 == 1) {
			y += 12.5;
		}

		x = floor(x / 25) * 25;
		if (((int) ((Wall *) op.currentEntity)->Width() / 25) % 2 == 1) {
			x += 12.5;
		}

		((Wall *) op.currentEntity)->Move(Point(x, y));
	} else if (op.eventosIO->isKeyPressed(event, Core::Key::Left)) {
		((Wall *) op.currentEntity)->Expand(-25);
		op.despX += 3;
	} else if (op.eventosIO->isKeyPressed(event, Core::Key::Right)) {
		((Wall *) op.currentEntity)->Expand(25);
		op.despX -= 3;
	} else if (op.eventosIO->isKeyPressed(event, Core::Key::Up)) {
		((Wall *) op.currentEntity)->Rotate(90);
		op.despY -= 3;
	} else if (op.eventosIO->isKeyPressed(event, Core::Key::Down)) {
		((Wall *) op.currentEntity)->Rotate(-90);
		op.despY += 3;
	}
}

void moveDoor(TOptionsMenu &op, sf::Event event) {
	if (event.Type == sf::Event::MouseButtonPressed) {

		Entity * ent = pickObject(op, op.desplacedMouse);
		if (ent != NULL) {
			if (event.MouseButton.Button == sf::Mouse::Left) {
				op.currentEntity = ent;
				op.mode = TOptionsMenu::objectSelected;
			} else if (event.MouseButton.Button == sf::Mouse::Right) {
				op.manager->removeEntity(ent->getId());
			}
		} else if (event.MouseButton.Button == sf::Mouse::Left) {
			op.currentEntity = NULL;
			op.mode = TOptionsMenu::none;
		}

	} else if (op.eventosIO->isMouseButtonDown(Core::Mouse::Left)) {

		double x = op.desplacedMouse.getX(), y = op.desplacedMouse.getY();

		y = floor(y / 25) * 25;
		if (((int) ((Door *) op.currentEntity)->Height() / 25) % 2 == 1) {
			y += 12.5;
		}

		x = floor(x / 25) * 25;
		if (((int) ((Door *) op.currentEntity)->Width() / 25) % 2 == 1) {
			x += 12.5;
		}

		((Door *) op.currentEntity)->Move(Point(x, y));
	} else if (op.eventosIO->isKeyPressed(event, Core::Key::Up)) {
		((Door *) op.currentEntity)->Rotate(90);
		op.despY -= 3;
	} else if (op.eventosIO->isKeyPressed(event, Core::Key::Down)) {
		((Door *) op.currentEntity)->Rotate(-90);
		op.despY += 3;
	}

}

void moveObstacle(TOptionsMenu &op, sf::Event event) {

	if (event.Type == sf::Event::MouseButtonPressed) {

		Entity * ent = pickObject(op, op.desplacedMouse);
		if (ent != NULL) {
			if (event.MouseButton.Button == sf::Mouse::Left) {
				op.currentEntity = ent;
				op.mode = TOptionsMenu::objectSelected;
			} else if (event.MouseButton.Button == sf::Mouse::Right) {
				op.manager->removeEntity(ent->getId());
			}
		} else if (event.MouseButton.Button == sf::Mouse::Left) {
			op.currentEntity = NULL;
			op.mode = TOptionsMenu::none;
		}

	} else if (op.eventosIO->isMouseButtonDown(Core::Mouse::Left)) {

		op.currentEntity->setCenter(op.desplacedMouse);
	} else if (op.eventosIO->isKeyPressed(event, Core::Key::Up)) {
		op.currentEntity->setAngle(-1 * op.currentEntity->getAngle() + 1);
		op.despY -= 3;
	} else if (op.eventosIO->isKeyPressed(event, Core::Key::Down)) {
		op.currentEntity->setAngle(-1 * op.currentEntity->getAngle() - 1);
		op.despY += 3;
	}

}

Map * dumpMap(TOptionsMenu op) {
	Map * mapa = new Map();

	mapa->setPerimeter(((Floor *) op.manager->getEntitiesbyType(Core::Entities::e_floor)[0])->getPoints());

	vector<Entity *> paredes = op.manager->getEntitiesbyType(Core::Entities::e_wall);

	vector<Entity *>::iterator eIter;
	for (eIter = paredes.begin(); eIter != paredes.end(); eIter++) {
		mapa->addWall(((Wall *) *eIter)->getPoints());
	}

	vector<Entity *> puertas = op.manager->getEntitiesbyType(Core::Entities::e_door);

	for (eIter = puertas.begin(); eIter != puertas.end(); eIter++) {
		mapa->addDoor(((Door *) *eIter)->getPoints());
	}

	mapa->setPlayerPos(op.manager->getPlayer()->getCenter());

	vector<Entity *> obstaculos = op.manager->getEntitiesbyType(Core::Entities::e_obstacle);
	for (eIter = obstaculos.begin(); eIter != obstaculos.end(); eIter++) {
		mapa->addObstacle(((Obstacle *) (*eIter))->getObstacle(), (*eIter)->getCenter(), (*eIter)->getAngle());
	}

	vector<Entity *> objects = op.manager->getEntitiesbyType(Core::Entities::e_objects);
	for (eIter = objects.begin(); eIter != objects.end(); eIter++) {
		mapa->addObject(((Object *) (*eIter))->getObjectClass(), (*eIter)->getCenter(), (*eIter)->getAngle());
	}

	return mapa;
}

void saveMap(TOptionsMenu op, string name) {
	op.mapa = dumpMap(op);

//	op.mapa->generateTriangulation();
//	op.navgraph = Pathfinder::makeDualGraph(op.mapa->getTriangulation());

	op.mapa->writeFile(name);
	//if (op.navgraph != NULL)
	//op.navgraph->writeFile(name + ".nav");
}

void RecalculoRaton(TOptionsMenu &op, int x, int y) {

	glPushMatrix();
	glLoadIdentity();
	((Transform*) op.sm->getNode(Graphics::DirectNodesEditor::t_escena)->getItem())->exportOpenGL();
	op.mouse.setXY(x, y);
	GLdouble model[16];
	GLdouble project[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, model);
	glGetDoublev(GL_PROJECTION_MATRIX, project);
	double *auxX = new double;
	double *auxY = new double;
	double *auxZ = new double;
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	y = 600 - y;
	gluUnProject(x, y, 0, model, project, viewport, auxX, auxY, auxZ);
	x = *auxX;
	y = *auxY;

	op.desplacedMouse.setXY(x, y);

	glPopMatrix();
}

