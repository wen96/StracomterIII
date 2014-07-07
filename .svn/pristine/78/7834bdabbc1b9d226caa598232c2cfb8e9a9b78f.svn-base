#include <iostream>
#include <GL/gl.h>
#include <SFML/Window.hpp>

#include "Polygon.h"
#include "Color.h"
#include "TForm.h"
#include "SceneManager.h"
#include "Map.h"
#include "Animation.h"
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

	float rotacion;

	Point mouse;
	Point desplacedMouse;
};

void UpdateScene(TContenedor &op);
void RecalculoRaton(TContenedor &op, int x, int y);
void ControlEvents(TContenedor &op);

void animationThr(Animation *anim){
	anim->play();
}

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
	op.rotacion = 0;

	/* ------- */
	//Segun Gallardo esto hace falta para poder pillar las texturas y los modelos
	resources->loadModels();
	resources->loadTextures();
	//Creo un arbol en modo editor que tiene un menu y una scena
	sm->makeEditorTree();

	Polygon pol(Point(100,100),20.0);

	sm->addElement(menuGame, sm->getNode(Graphics::DirectNodesEditor::t_menu));
	TForm *mainMenu = new TForm(400, 600, Point(200, 300));
	mainMenu->setColor(Color<float>(0.7, 0.7, 0.7, 0.7));
	TLabel *label = new TLabel(200, 300, "Las animaciones molan");
	label->setMarginUp(10);
	label->setColorText(Color<float>(0.1, 0.1, 0.4));
	label->setSize(20);
	mainMenu->addWidget(label);
	op.menuGame->addMenu(Graphics::Menus::m_inicio, mainMenu);
	menuGame->setVisible(Graphics::Menus::m_none);

	Animation *animMenu = new Animation((Transform*)sm->getNode(Graphics::DirectNodesEditor::t_menu)->getItem());
	animMenu->init();
	vector<vector<float> > vAux;
	vector<float>v3(3,0);
//	v3[0]=50;
//	v3[1]=50;
//	v3[2]=220;
//	vAux.push_back(v3);
//	v3[0]=0;
//	v3[1]=0;
//	v3[2]=0;
//	vAux.push_back(v3);
//	animMenu->createRotationTransform(vAux);
	vector<Point>vectMen;
	vectMen.push_back(Point(200,0));
	vectMen.push_back(Point(0,200));
	vectMen.push_back(Point(0,-200));
	vectMen.push_back(Point(-200,0));
	animMenu->createTranslationTransform(vectMen);
	animMenu->setTimeAnimation(4000);

	//Creo un player para animarlo
	entMan->addPlayer(Point(),0.0);

	//ANIMACION CON TRANSFORM
//	Animation *anim = new Animation((Transform*)entMan->getPlayer()->getPadre()->getItem());
//	anim->setEntity(entMan->getPlayer());
//	anim->init();
//	vAux.clear();
//	v3[0]=50;
//	v3[1]=50;
//	v3[2]=220;
//	vAux.push_back(v3);
//	v3[0]=300;
//	v3[1]=340;
//	v3[2]=10;
//	vAux.push_back(v3);
//	v3[0]=0;
//	v3[1]=0;
//	v3[2]=0;
//	vAux.push_back(v3);
//	anim->createRotationTransform(vAux);


	//ANIMACION CON ENTITY
	Animation *anim = new Animation((Transform*)entMan->getPlayer()->getPadre()->getItem());//Le paso el player a la animacion
	anim->init();
	vector<Point>vect;
	vect.push_back(Point(100,100,0));
	vect.push_back(Point(-100,-100,0));
	anim->createTranslationTransform(vect);
//	vector<float>vectF;
//	vectF.push_back(0);
//	vectF.push_back(360);
//	vectF.push_back(0);
//	vectF.push_back(90);
//	vectF.push_back(0);
//	vectF.push_back(-90);
//	vectF.push_back(0);
//	anim->createRotation(vectF);
//
//	vector<Color<float> >vectC;
//	vectC.push_back(Color<float>(0.1,0.5,0.1,1));
//	vectC.push_back(Color<float>(1,1,0,0.3));
//	vectC.push_back(Color<float>(0.6,0.1,0.8,0.8));
//	vectC.push_back(Color<float>(0.1,0.5,0.6,0.01));
//	vectC.push_back(Color<float>(0.1,0.5,0.1,1));
//	anim->createFade(vectC);

	anim->setTimeAnimation(10000);

	cout << "PROBANDO THREAD, POR ESO EL SEGMENTATION" << endl;
	sf::Thread thr(&animationThr,anim);
	thr.Launch();


	//Mientras la ventana este abierta (que se cierra con Esc o con la X de cerrarla)
	while (window->isOpen()) {

		ControlEvents(op);//Control de ventos



		UpdateScene(op);//Reshape

		//if (anim->step()){
			//cout << "Reiniciamos" << endl;
			//anim->init();
		//}

//		if (animMenu->step()){
//			animMenu->init();
//		}

		op.rotacion += 0.1;
//		((Transform*)entMan->getPlayer()->getPadre()->getItem())->addRotationX(op.rotacion);
//		((Transform*)entMan->getPlayer()->getPadre()->getItem())->addRotationY(op.rotacion);

		pol = Polygon(Point(eventosTeclado->GetMouseX(),eventosTeclado->GetMouseY()),30);
		//cout << Point(eventosTeclado->GetMouseX(),eventosTeclado->GetMouseY()) << endl;

		sm->DrawScene();//Draw del arbol
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
		}else if (event.Type == sf::Event::MouseWheelMoved){//Control de rueda raton para zoom
			if (event.MouseWheel.Delta > 0){
				op.zoom+=0.01;
			}else{
				op.zoom-=0.01;
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

	//op.manager->Update();
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


