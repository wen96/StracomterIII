/*
 * SceneManager.cc
 *
 *  Created on: 10/02/2012
 *      Author: Chutaos Team
 */

#include "SceneManager.h"

SceneManager * SceneManager::_sm = NULL;

SceneManager* SceneManager::getInstance() {
	if(_sm == NULL){
		_sm = new SceneManager();
	}
	return _sm;

}

SceneManager* SceneManager::getInstance(GraphicTree* scene) {
	if(_sm == NULL){
		_sm = new SceneManager(scene);
	}
	return _sm;
}

SceneManager::SceneManager(GraphicTree* _scene) {
	zbuffer = true;
	culling = true;
	smooth = true;
	luzAmbiente = Color<float> (0.1,0.1,0.1,1);
	mode = Graphics::ModeRender::m_polygon;
	scene = _scene;
}

SceneManager::SceneManager() {
	zbuffer = true;
	culling = true;
	smooth = true;
	luzAmbiente = Color<float> (0.1,0.1,0.1,1);
	mode = Graphics::ModeRender::m_polygon;
	scene = new GraphicTree();
	/*
	for(int i = 0; i < Graphics::DirectNodes::size; i++)
	{
		directNodes.push_back(NULL);
	}*/
	//makeStracomterTree();

}

SceneManager::~SceneManager() {
	zbuffer = false;
	culling = false;
	smooth = false;
	mode = Graphics::ModeRender::m_point;
	removeStracomterTree();
	if(scene != NULL)
	{
		delete scene;
		scene = NULL;
	}
}

GraphicTree* SceneManager::getScene() const {
	return scene;
}

void SceneManager::setScene(GraphicTree* scene) {
	this->scene = scene;
}

Graphics::ModeRender::Mode SceneManager::getMode() const {
	return mode;
}

bool SceneManager::isCulling() const {
	return culling;
}

bool SceneManager::isSmooth() const {
	return smooth;
}

bool SceneManager::isZbuffer() const {
	return zbuffer;
}

bool SceneManager::isLighting() const {
	return lighting;
}

void SceneManager::setCulling(bool culling) {
	this->culling = culling;
	if (culling) {
		glEnable(GL_CULL_FACE);
	} else {
		glDisable(GL_CULL_FACE);
	}
}

void SceneManager::setMode(Graphics::ModeRender::Mode mode) {
	this->mode = mode;
	switch (mode) {
	case Graphics::ModeRender::m_point:
		glShadeModel(GL_POINT);
		break;
	case Graphics::ModeRender::m_line:
		glBegin(GL_LINE_LOOP);
		break;
	case Graphics::ModeRender::m_polygon:
		glBegin(GL_POLYGON);
		break;
	}
}

void SceneManager::setSmooth(bool smooth) {
	this->smooth = smooth;
	if (smooth) {
		glShadeModel(GL_SMOOTH);
	} else {
		glShadeModel(GL_FLAT);
	}
}

void SceneManager::setLighting(bool l) {
	this->lighting = l;
	if (lighting) {
		glEnable(GL_LIGHTING);
	} else {
		glDisable(GL_LIGHTING);
	}
}

void SceneManager::setZbuffer(bool zbuffer) {
	this->zbuffer = zbuffer;
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);
	if (zbuffer) {
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
	} else {
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
	}
}

void SceneManager::DrawScene() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GraphicNode *nodo;

	if(tree == Graphics::StracomerTrees::gameAction)
	{
		setZbuffer(true);
		setLighting(true);
		setCulling(false);

		nodo = getNode(Graphics::DirectNodes::c_escena);
		if(nodo != NULL)
		{
			if(nodo->getVisible())
			{
				nodo->Render();
			nodo = getNode(Graphics::DirectNodes::t_escena);
			if(nodo != NULL)
				nodo->Render();
			}
		}

		setLighting(false);
		setZbuffer(false);
		setCulling(false);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		nodo = getNode(Graphics::DirectNodes::c_hud);
		if(nodo != NULL)
		{
			if(nodo->getVisible())
			{
				nodo->Render();
			nodo = getNode(Graphics::DirectNodes::t_screen);
			if(nodo != NULL)
				nodo->Render();
			}
		}
		glDisable(GL_BLEND);

		nodo = getNode(Graphics::DirectNodes::c_mapa);
		if(nodo != NULL)
		{
			if(nodo->getVisible())
			{
				nodo->Render();
			nodo = getNode(Graphics::DirectNodes::t_mapa);
			if(nodo != NULL)
				nodo->Render();
			}
		}
	}
	else if (tree == Graphics::StracomerTrees::gameMenu)
	{
		setLighting(false);
		setZbuffer(false);
		setCulling(false);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		nodo = getNode(Graphics::DirectNodesMenu::c_menu);
		if(nodo != NULL)
		{
			if(nodo->getVisible())
			{
				nodo->Render();
			nodo = getNode(Graphics::DirectNodesMenu::t_menu);
			if(nodo != NULL)
				nodo->Render();
			}
		}
		glDisable(GL_BLEND);
	}
}

void SceneManager::InitializeScene() {

	glClearIndex((GLfloat) 0);
	glClearDepth(1000.0);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (culling) {
		glEnable(GL_CULL_FACE);
	}

	if (zbuffer) {
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
	}

	if (smooth) {
		glShadeModel(GL_SMOOTH);
	} else {
		glShadeModel(GL_FLAT);
	}

	switch (mode) {
	case Graphics::ModeRender::m_point:
		//glShadeModel(GL_POINT);
		glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );
		break;
	case Graphics::ModeRender::m_line:
		//glBegin(GL_LINE_LOOP);
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		break;
	case Graphics::ModeRender::m_polygon:
		//glBegin(GL_POLYGON);
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		break;
	}

	GLfloat amb[4];
	amb[0] = luzAmbiente.getR();
	amb[1] = luzAmbiente.getG();
	amb[2] = luzAmbiente.getB();
	amb[3] = luzAmbiente.getAlpha();
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
}

Color<float> SceneManager::getLuzAmbiente() const
{
    return luzAmbiente;
}

void SceneManager::setLuzAmbiente(Color<float> luzAmbiente)
{
    this->luzAmbiente = luzAmbiente;
}

void SceneManager::loadTree(EntityManager *em, Element* raiz)
{
	vector<Entity*> entities = em->getEntities();
	Element *aux = getNode(Graphics::DirectNodes::t_escena)->getItem();

	for(unsigned int  i = 0; i < entities.size(); i++)
	{
		addElement(entities[i],aux);
	}
}

void SceneManager::addElement(vector<Element*> vec, Element* raiz)
{

}

void SceneManager::addElement(Element *elem, Element* raiz)
{
	Shape *pol;
	GraphicNode* nodo = NULL;
	GraphicNode *padre = NULL;

	nodo = scene->Insertar(elem,raiz);

	if(elem != NULL)
	{
		elem->setNodo(nodo);
		elem->setPadre(padre);

		if(elem->getElementType() == Core::Element::e_entity)
		{
			if(((Entity*)elem)->getType() == Core::Entities::e_wall)
			{
				vector<Point> points = ((Wall*)elem)->getPoints();
				for(int i = 0; i < 4; i++) points.pop_back();
				pol = new Shape(Polygon(Point(), points));
				scene->Insertar(pol, getNode(Graphics::DirectNodes::t_mapa));
			}
			if(((Entity*)elem)->getType() == Core::Entities::e_floor)
			{
				vector<Point> points = ((Floor*)elem)->getPerimetro();
				pol = new Shape(Polygon(points));
				scene->Insertar(pol, getNode(Graphics::DirectNodes::t_mapa));
			}
		}
	}

}

void SceneManager::addCharacter(Element *elem, Element* raiz)
{
	//GraphicNode *padre = scene->getPadre(nodo);
	GraphicNode* nodo = NULL;
	GraphicNode* Raynodo = NULL;
	Transform *aux = new Transform();
	Shape *ray = new Shape();
	GraphicNode *padre = scene->Insertar(aux, raiz);

	nodo = scene->Insertar(elem,aux);

	if(elem != NULL)
	{
		elem->setNodo(nodo);
		elem->setPadre(padre);
		Raynodo = scene->Insertar(ray,nodo);
		((Character*)elem)->setRay(Raynodo);
	}

}

void SceneManager::addCharacter(Element *elem, GraphicNode* raiz)
{
	//GraphicNode *padre = scene->getPadre(nodo);
	GraphicNode* nodo = NULL;
	GraphicNode* Raynodo = NULL;
	GraphicNode* nodo2D = NULL;
	Transform *aux = new Transform();
	Transform *aux2 = new Transform();
	GraphicNode *padre = scene->Insertar(aux, raiz);
	Core::Entities::Type t;
	t = ((Character*)elem)->getType();
	Polygon *pol = ((Character*)elem)->getResource()->getModel2DObject(t)->getShape();
	Color<float> color = ((Character*)elem)->getColor();
	Shape *mapa = new Shape(*pol, color);
	nodo = scene->Insertar(elem,aux);
	Shape *ray = NULL;

	if(elem != NULL)
	{
		elem->setNodo(nodo);
		elem->setPadre(padre);
		if(((Character*)elem)->isGoodPerson())
		{
			ray = new Shape(Color<float>(1,0,0));
			Raynodo = scene->Insertar(ray,getNode(Graphics::DirectNodes::t_ray));
		}

		((Character*)elem)->setRay(Raynodo);
		nodo2D = scene->Insertar(aux2,getNode(Graphics::DirectNodes::t_mapa));
		scene->Insertar(mapa,aux2);
		((Entity*)elem)->set2DNode(nodo2D);
	}

}

void SceneManager::addElement(Element *elem, GraphicNode* raiz)
{
	//GraphicNode *padre = scene->getPadre(nodo);
	/*GraphicNode* nodo = NULL;
	Transform *aux = new Transform();
	GraphicNode *padre = scene->Insertar(aux, raiz);
	Shape *pol;

	//if(padre != NULL)
	//{
		nodo = scene->Insertar(elem,aux);
	//}
	if(elem != NULL)
	{
		elem->setNodo(nodo);
		elem->setPadre(padre);
	}
	*/

	Shape *pol;
	GraphicNode* nodo = NULL;
	GraphicNode *padre = NULL;

	nodo = scene->Insertar(elem,raiz);

	if(elem != NULL)
	{
		elem->setNodo(nodo);
		elem->setPadre(padre);

		if(elem->getElementType() == Core::Element::e_entity)
		{
			if(((Entity*)elem)->getType() == Core::Entities::e_wall)
			{
				vector<Point> points = ((Wall*)elem)->getPoints();
				for(int i = 0; i < 4; i++) points.pop_back();
				pol = new Shape(Polygon(Point(), points));
				scene->Insertar(pol, getNode(Graphics::DirectNodes::t_mapa));
			}
			if(((Entity*)elem)->getType() == Core::Entities::e_floor)
			{
				vector<Point> points = ((Floor*)elem)->getPerimetro();
				pol = new Shape(Polygon(points));
				scene->Insertar(pol, getNode(Graphics::DirectNodes::t_mapa));
			}
		}
	}
}

void SceneManager::removeElement(Element *elem)
{
	GraphicNode *padre;

	padre = elem->getPadre();

	if(padre != NULL)
	{
		//abuelo = padre->getItem()->getPadre();
		scene->BorrarElemento(padre->getItem());

		//delete padre;
		//padre = NULL;

		/*if(abuelo != NULL)
		{
			vector<GraphicTree *> hijos = abuelo->getHijos();
			vector<GraphicTree*>::iterator it;
			for(it = hijos.begin(); it != hijos.end() && !borrado; it++)
			{
				hijo = *it;

				if(hijo != NULL)
				{
					if(hijo->getRaiz() == padre)
					{
						abuelo->getHijos().erase(it);

						if(hijo != NULL)
						{
							//delete hijo;
							hijo = NULL;
						}
						borrado = true;
					}
				}
			}
		}*/

	}

}

void SceneManager::removeCharacter(Element *elem)
{
	GraphicNode *padre;
	GraphicNode *laser;
	GraphicNode *nodo2d;

	padre = elem->getPadre();
	laser = ((Character*)elem)->getRay();
	nodo2d = ((Entity*)elem)->get2DNode();

	if(padre != NULL)
	{
		scene->BorrarElemento(padre->getItem());
		//scene->BorrarRama(padre);
	}

	if(laser != NULL)
	{
		scene->BorrarElemento(laser->getItem());
		//scene->BorrarRama(laser);
	}

	if(nodo2d != NULL)
	{
		scene->BorrarElemento(nodo2d->getItem());
		//scene->BorrarRama(nodo2d);
	}

}
void
SceneManager::initTree(Element *elem) {

	if(scene != NULL)
	{
		delete scene;
		scene = NULL;
	}

	scene = new GraphicTree();
	scene->Insertar(elem);
}

vector<GraphicNode*> SceneManager::getDirectNodes() const
{
    return directNodes;
}

void SceneManager::setDirectNodes(vector<GraphicNode*> directNodes)
{
    this->directNodes = directNodes;
}



void SceneManager::addDirectNodes(GraphicNode* node)
{
    this->directNodes.push_back(node);
}

void
SceneManager::makeStracomterTree() {

	if(scene != NULL)
	{
		delete scene;
		scene = NULL;
	}


	scene = new GraphicTree();

	directNodes = vector<GraphicNode*>(Graphics::DirectNodes::size,NULL);

	//Cámara de la escena
	Camera *c_escena = new Camera(800, 600, 1, 20000, Point());
	c_escena->setAngle(45);
	c_escena->setPerspective();

	Camera *c_mapa = new Camera(200, 150, 1, 2000, Point(600,450));
	c_mapa->setScale(1000);
	c_mapa->setOrtho();

	Camera *c_hud = new Camera(800, 600, 0.0001, 20000, Point());
	c_hud->setScale(400);
	c_hud->setOrtho();

	Color<float> amb(0.1, 0.1, 0.1, 1.0);
	Color<float> dif(0.7, 0.7, 0.7, 1.0);
	Color<float> esp(0.9, 0.9, 0.9, 1.0);

	Point pos0(0, 0, 150); //Y ==> N/S; Z ==> A/B; X ==> I/D;
	Point pos1(0, 0, 150);
	Point pos2(0, 0, 150);

	Light *l0 = new Light(amb,dif,esp,pos0,0);
	Light *l1 = new Light(amb,dif,esp,pos1,1);
	Light *l2 = new Light(amb,dif,esp,pos2,2);

	vector<Point> puntos;
	puntos.push_back(Point(600,0));
	puntos.push_back(Point(800,0));
	puntos.push_back(Point(800,150));
	puntos.push_back(Point(600,150));

//	puntos.push_back(Point(0,600));
//	puntos.push_back(Point(200,600));
//	puntos.push_back(Point(200,450));
//	puntos.push_back(Point(0,450));

	Shape *cajaMapa = new Shape(Polygon(Point(), puntos), Color<float>(0.2,0.2,0.2, 0.7));
	Shape *marcoMapa = new Shape(Polygon(puntos), Color<float>(1,1,1));


	Transform *t_escena = new Transform();
	Transform *t_hud = new Transform();
	Transform *t_console = new Transform();
	Transform *t_menu = new Transform();
	Transform *pnull = new Transform();
	Transform *ray = new Transform();
	Transform *t_mapa = new Transform();
	Transform *t_screen = new Transform();

	// Marco con la informacion
	vector<Point> puntosInfo;
	puntosInfo.push_back(Point(800,600));
	puntosInfo.push_back(Point(800,450));
	puntosInfo.push_back(Point(650,450));
	puntosInfo.push_back(Point(650,600));

	Text *puntuacion = new Text(Graphics::Font::Absender, Point(40,30), Color<float>(1,1,1), 30, "");
	Text *enemigos = new Text(Graphics::Font::Absender, Point(128,30), Color<float>(1,1,1), 30, "");
	Text *fps = new Text(Graphics::Font::Absender, Point(188,30), Color<float>(1,1,1), 30, "");

	Text *time = new Text(Graphics::Font::Absender, Point(380,30), Color<float>(1,1,1), 30, "");

	Text *hp = new Text(Graphics::Font::Absender, Point(660,590), Color<float>(1,1,1), 30, "");
	Text *balas = new Text(Graphics::Font::Absender, Point(748,590), Color<float>(1,1,1), 30, "");

	string texturesroot = RESOURCESROOT;
	texturesroot += "texturas/";

	TForm *timeFrame = new TForm(140,40,Point(400,20));
	timeFrame->addWidget(new TPicture(Point(344,4), 32, 32, texturesroot + "clock.png"));

	TForm *topLeftHUD = new TForm(180,40,Point(90,20));
	topLeftHUD->addWidget(new TPicture(Point(90,4), 32, 32, texturesroot + "skull.png"));
	topLeftHUD->addWidget(new TPicture(Point(4,4), 32, 32, texturesroot + "points.png"));
	topLeftHUD->setColor(Color<float>(0.2,0.2,0.2,0.7));

	TForm *downBottomHUD = new TForm(180,40, Point(710,580));
	downBottomHUD->addWidget(new TPicture(Point(624,564), 32, 32, texturesroot + "vida.png"));
	downBottomHUD->addWidget(new TPicture(Point(710,564), 32, 32, texturesroot + "ammo.png"));
	downBottomHUD->setColor(Color<float>(0.2,0.2,0.2,0.7));

	t_hud->addScale(1, -1, 1);
	t_hud->addTranslation(-1.0 * 800 / 2, -1.0 * 600 / 2, -1);
	*t_menu = *t_hud;
	*t_console = *t_hud;

	addElement(pnull);

	addElement(c_mapa,pnull);
	addElement(c_escena,pnull);
	addElement(c_hud,pnull);

	addElement(t_escena,pnull);
	addElement(t_mapa,pnull);
	//addElement(t_hud,pnull);
	addElement(t_screen,pnull);
	addElement(t_hud,t_screen);

	addElement(timeFrame, t_hud);
	addElement(downBottomHUD, t_hud);
	addElement(topLeftHUD, t_hud);

	addElement(cajaMapa,t_hud);
	addElement(marcoMapa,t_hud);

	addElement(t_console,t_screen);
	addElement(t_menu,t_screen);
	addElement(puntuacion,t_hud);
	addElement(enemigos,t_hud);
	addElement(fps,t_hud);
	addElement(time,t_hud);
	addElement(hp,t_hud);
	addElement(balas,t_hud);

	addElement(l0,t_escena);
	addElement(l1,t_escena);
	addElement(l2,t_escena);
	addElement(ray,t_escena);

	directNodes[Graphics::DirectNodes::c_escena] = c_escena->getNodo();
	directNodes[Graphics::DirectNodes::c_hud] = c_hud->getNodo();
	directNodes[Graphics::DirectNodes::c_mapa] = c_mapa->getNodo();
	directNodes[Graphics::DirectNodes::t_escena] = t_escena->getNodo();
	directNodes[Graphics::DirectNodes::t_hud] = t_hud->getNodo();
	directNodes[Graphics::DirectNodes::t_console] = t_console->getNodo();
	directNodes[Graphics::DirectNodes::t_menu] = t_menu->getNodo();
	directNodes[Graphics::DirectNodes::t_puntuacion] = puntuacion->getNodo();
	directNodes[Graphics::DirectNodes::t_hp] = hp->getNodo();
	directNodes[Graphics::DirectNodes::t_ray] = ray->getNodo();
	directNodes[Graphics::DirectNodes::t_light0] = l0->getNodo();
	directNodes[Graphics::DirectNodes::t_light1] = l1->getNodo();
	directNodes[Graphics::DirectNodes::t_light2] = l2->getNodo();
	directNodes[Graphics::DirectNodes::t_mapa] = t_mapa->getNodo();
	directNodes[Graphics::DirectNodes::t_enemigos] = enemigos->getNodo();
	directNodes[Graphics::DirectNodes::t_fps] = fps->getNodo();
	directNodes[Graphics::DirectNodes::t_time] = time->getNodo();
	directNodes[Graphics::DirectNodes::t_balas] = balas->getNodo();
	directNodes[Graphics::DirectNodes::t_screen] = t_screen->getNodo();
	t_console->getNodo()->setVisible(false);

	GLfloat luzAmbiente[]   = {0.1, 0.1, 0.1, 1.0};
	GLfloat luzDifusa[]     = {0.7, 0.7, 0.7, 1.0};
	GLfloat luzEspecular[]  = {0.9, 0.9, 0.9, 1.0};
	GLfloat luzExponente[]  = {64.0, 64.0, 64.0, 1.0};

	//TODO esto no va aquí.
	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT, GL_AMBIENT, luzAmbiente);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, luzDifusa);
	glMaterialfv(GL_FRONT, GL_SPECULAR, luzEspecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, luzExponente);

	mode = Graphics::ModeRender::m_polygon;
	culling = smooth = zbuffer = true;

	tree = Graphics::StracomerTrees::gameAction;

}

void
SceneManager::removeStracomterTree() {

	GraphicNode *tmp;
	Element* elem;
	while(!directNodes.empty())
	{
		tmp  = directNodes[0];
		directNodes.erase(directNodes.begin());

		if(tmp != NULL)
		{
			elem = tmp->getItem();
			if(elem != NULL)
			{
				delete elem;
				elem = NULL;
			}
		}
	}

	if(scene != NULL)
	{
		delete scene;
		scene = NULL;
	}
}

GraphicNode*
SceneManager::getNode(Graphics::DirectNodes::Index index) {

	GraphicNode *nodo = NULL;

	////cout << "SIZE: " << endl;
	////cout << "SIZE: " << directNodes.size() << endl;
	if(index < directNodes.size())
		nodo =  directNodes[index];

	return nodo;
}

GraphicNode*
SceneManager::getNode(Graphics::DirectNodesMenu::Index index) {

	GraphicNode *nodo = NULL;

	////cout << "SIZE: " << endl;
	////cout << "SIZE: " << directNodes.size() << endl;
	if(index < directNodes.size())
		nodo =  directNodes[index];

	return nodo;
}

void
SceneManager::makeMenuTree() {

	if(scene != NULL)
	{
		delete scene;
		scene = NULL;
	}


	scene = new GraphicTree();

	directNodes = vector<GraphicNode*>(Graphics::DirectNodesMenu::size,NULL);

	//Cámara de la escena

	Camera *c_menu = new Camera(800, 600, 0.0001, 20000, Point());
	c_menu->setScale(400);
	c_menu->setOrtho();

	Transform *t_menu = new Transform();
	t_menu->addScale(1, -1, 1);
	t_menu->addTranslation(-1.0 * 800 / 2, -1.0 * 600 / 2, -1);


	Transform *pnull = new Transform();

	addElement(pnull);

	addElement(c_menu,pnull);
	addElement(t_menu,pnull);

	directNodes[Graphics::DirectNodesMenu::c_menu] = c_menu->getNodo();
	directNodes[Graphics::DirectNodesMenu::t_menu] = t_menu->getNodo();

	GLfloat luzAmbiente[]   = {0.1, 0.1, 0.1, 1.0};
	GLfloat luzDifusa[]     = {0.7, 0.7, 0.7, 1.0};
	GLfloat luzEspecular[]  = {0.9, 0.9, 0.9, 1.0};
	GLfloat luzExponente[]  = {64.0, 64.0, 64.0, 1.0};

	//TODO esto no va aquí.
	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT, GL_AMBIENT, luzAmbiente);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, luzDifusa);
	glMaterialfv(GL_FRONT, GL_SPECULAR, luzEspecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, luzExponente);

	mode = Graphics::ModeRender::m_polygon;
	culling = smooth = zbuffer = true;

	tree = Graphics::StracomerTrees::gameMenu;
}

void
SceneManager::removeMenuTree() {

	GraphicNode *tmp;
	Element* elem;
	while(!directNodes.empty())
	{
		tmp  = directNodes[0];
		directNodes.erase(directNodes.begin());

		if(tmp != NULL)
		{
			elem = tmp->getItem();
			if(elem != NULL)
			{
				delete elem;
				elem = NULL;
			}
		}
	}

	if(scene != NULL)
	{
		delete scene;
		scene = NULL;
	}

}


