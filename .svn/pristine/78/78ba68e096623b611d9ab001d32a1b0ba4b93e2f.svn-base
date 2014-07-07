#include <iostream>
#include <GL/gl.h>
#include <SFML/Window.hpp>

#include "Polygon.h"
#include "Color.h"
#include "TForm.h"
#include "SceneManager.h"
#include "Map.h"
using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;
const float GROSOR = 10;

class TContenedor {
public:
	SceneManager *sm;
	GameMenu *menuGame;
	TWindow *window;
	IOControl *eventosIO;
	TForm* menuPrincipal;
	HIDControl *hid;
	EntityManager *manager;
	ResourceManager *resManager;

	//Variables de redisposicion
	int despX;
	int despY;
	float zoom;

	Point mouse;
	Point desplacedMouse;
};

void UpdateScene(TContenedor &op);
void RecalculoRaton(TContenedor &op, int x, int y);
void ControlEvents(TContenedor &op);

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
	ResourceManager *resources = ResourceManager::getInstance(world, NULL);
	EntityManager *entMan = new EntityManager(resources);
	CharacterFeature *features = CharacterFeature::getInstance();
	features->loadData("testFiles/features/f1.xml");

	TContenedor op;
	op.zoom = 1;
	op.despX = 0;
	op.despY = 0;
	op.window = window;
	op.sm = sm;
	op.eventosIO = eventosTeclado;
	op.manager = entMan;
	op.menuGame = menuGame;
	op.hid = hid;

	/* ------- */
	//Segun Gallardo esto hace falta para poder pillar las texturas y los modelos
	resources->loadModels();
	resources->loadTextures();
	//Creo un arbol en modo editor que tiene un menu y una scena
	sm->makeEditorTree();

	//Prueba de poner forma en el arbol
	Shape* prueba = new Shape(Polygon(Point(0,-10),30.0),Color<float>(1,0,0));
	op.sm->addElement((Element*)prueba,op.sm->getNode(Graphics::DirectNodes::t_escena));


	//Mientras la ventana este abierta (que se cierra con Esc o con la X de cerrarla)
	while (window->isOpen()) {

		ControlEvents(op);//Control de ventos

		UpdateScene(op);//Reshape

		sm->DrawScene();//Draw del arbol

		//Tambien se puede dibujar a mano
		Polygon pol(Point(100,100),20.0);
		DrawPolygon(pol,Color<float>(0,1,0));

		window->display();//Swap buffers y temporizacion


	}

	return 0;

}

void ControlEvents(TContenedor &op){
	sf::Event event;
	while (op.window->getEvent(event)) {
		if (event.Type == sf::Event::Closed) {//control de cerrado de ventana
			op.window->close();
		} else if (event.Type == sf::Event::KeyPressed){

			if (event.Key.Code == sf::Keyboard::Escape) {//control de cerrado de ventana
				op.window->close();
			}
		}
	}

	/* ------------------ACTUALIZACION RATON --------------------------*/
	Entity *ent = op.manager->getPointer();
	if (ent != NULL){
		float x = ((*op.eventosIO).GetMouseX());
		float y = ((*op.eventosIO).GetMouseY());
		RecalculoRaton(op, x, y);//En op.mouse se guarda la posicion real y en op.desplacedMouse devuelve la relativa
		((Pointer*)ent)->setCenter(op.desplacedMouse);
	}
}

void UpdateScene(TContenedor &op){

	op.manager->Update();
	GraphicNode *gn = op.sm->getNode(Graphics::DirectNodesEditor::t_escena);

	Element *escenario = gn->getItem();

	((Transform*) escenario)->setIdentity();
	((Transform*) escenario)->addScale(op.zoom,op.zoom,op.zoom);
	((Transform*) escenario)->addTranslation(-1.0 * op.despX, op.despY, -100);


}

void RecalculoRaton(TContenedor &op, int x, int y){

	glPushMatrix();
	glLoadIdentity();
	((Transform*)op.sm->getNode(Graphics::DirectNodesEditor::t_escena)->getItem())->exportOpenGL();
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
	//x -= 400;
	gluUnProject(x,y,0, model, project, viewport, auxX, auxY, auxZ);
	//cout << "X: " << x << " aX: " << *auxX << " Y: " << y << " aY: " << *auxY << endl;
	x = *auxX;
	y = *auxY;

	op.desplacedMouse.setXY(x,y);
	glPopMatrix();
}


