/*
 * ResourceManager.cc
 *
 *  Created on: 15/11/2011
 *      Author: Chutaos Team
 */

#include "ResourceManager.h"
#include "EventControl.h"

ResourceManager * ResourceManager::_resources = NULL;

ResourceManager * ResourceManager::getInstance() {
	if (_resources == NULL) {
		_resources = new ResourceManager();
	}
	return _resources;
}

ResourceManager * ResourceManager::getInstance(World *world_,
		EventControl *events_) {
	if (_resources == NULL) {
		_resources = new ResourceManager(world_, events_);
	} else {
		_resources->world = world_;
		_resources->events = events_;
	}
	return _resources;
}

ResourceManager::ResourceManager() {
	//glGenLists(1000);
	for (int i = 0; i < Core::Entities::size; i++) {
		models2D.push_back(NULL);
		modelsPhisics.push_back(NULL);
	}

	world = NULL;
	events = NULL;

	texturas = vector<unsigned int>(Graphics::Texturas::t_size, 0);

	for (int i = 0; i < Graphics::Font::size; i++) {
		fuentes.push_back(vector<fontHandler>());
	}

	loadShaders();
}

void ResourceManager::loadShaders() {

	string shaderroot = RESOURCESROOT;
	shaderroot += "shaders/";

	sf::Shader *cellShad = new sf::Shader();
	if(cellShad->LoadFromFile(shaderroot + "CellShading.vert", shaderroot + "CellShading.frag")){
		shaderV.push_back(cellShad);
	}else{
		shaderV.push_back(NULL);
	}

	cellShad = new sf::Shader();
	if(cellShad->LoadFromFile(shaderroot + "Phong.vert", shaderroot + "Phong.frag")){
		shaderV.push_back(cellShad);
	}else{
		shaderV.push_back(NULL);
	}

	cellShad = new sf::Shader();
	if(cellShad->LoadFromFile(shaderroot + "Pruebas.vert", shaderroot + "Pruebas.frag")){
		shaderV.push_back(cellShad);
	}else{
		shaderV.push_back(NULL);
	}
}

void ResourceManager::activateShader(Graphics::Shader::Name sh) {
	if(shaderV.size() > (int) sh && shaderV[sh] != NULL){
		shaderV[sh]->Bind();
	}
}

void ResourceManager::deactivateShader(Graphics::Shader::Name sh) {
	if(shaderV.size() > (int) sh && shaderV[sh] != NULL){
		shaderV[sh]->Unbind();
	}
}

ResourceManager::ResourceManager(World *world_, EventControl *events_) {
	for (int i = 0; i < Core::Entities::size; i++) {
		models2D.push_back(NULL);
		modelsPhisics.push_back(NULL);
	}
	world = world_;
	events = events_;

	texturas = vector<unsigned int>(Graphics::Texturas::t_size, 0);

	for (int i = 0; i < Graphics::Font::size; i++) {
		fuentes.push_back(vector<fontHandler>());
	}
}
ResourceManager::~ResourceManager() {
	if (!models2D.empty()) {
		for (int i = 0; i < Core::Entities::size; i++) {
			if (models2D[i] != NULL) {
				delete models2D[i];
			}
			if (modelsPhisics[i] != NULL) {
				delete modelsPhisics[i];
			}
		}
		models2D.clear();
		modelsPhisics.clear();

	}
	if (!modelsPhisics.empty()) {
		ModelPhisic *forDelete = NULL;
		vector<ModelPhisic*>::iterator iter;
		iter = modelsPhisics.begin();
		while (iter < modelsPhisics.end()) {
			forDelete = (*iter);
			modelsPhisics.erase(iter);
			if (forDelete != NULL)
				delete forDelete;
		}

	}
	world = NULL;
}

Model2D* ResourceManager::getModel2DObject(Core::Entities::Type type) {
	Model2D *aux = NULL;
	if (models2D[type] == NULL) {
		models2D[type] = new Model2D(type);
	}
	aux = models2D[type];

	return aux;
}

ModelPhisic* ResourceManager::getModelPhisics(Core::Entities::Type type) {
	ModelPhisic *aux = NULL;
	if (modelsPhisics[type] == NULL) {
		modelsPhisics[type] = new ModelPhisic(type,
				getModel2DObject(type)->getShape());
	}
	aux = modelsPhisics[type];

	return aux;
}

ModelPhisic ResourceManager::getObstacle(Core::Obstacles::Type type,
		Polygon p) {
	ModelPhisic aux = ModelPhisic(type, p);
	return aux;
}

World* ResourceManager::getWorld() {
	return world;
}

int ResourceManager::generateWall(vector<Point> vect, int id) {

	int id_display;
	if(id < 0){
		id_display = glGenLists(1);
		id_display += 1500;
	}else{
		id_display = id;
	}

	double ancho;

	glNewList(id_display, GL_COMPILE);
	Textura::ActivarTextura(texturas[Graphics::Texturas::t_wall]);

	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_QUADS);

	// Calculamos la Normal
	Vector2D n(vect[0], vect[1]);
	ancho = n.Length();
	n.Normalize();
	n.perpCCW();
	glNormal3f(n.x, n.y, 0);

	ancho /= 90.0;

	glTexCoord2d(0, 0);
	glVertex3d(vect[0].getX(), vect[0].getY(), 0);
	glTexCoord2d(ancho, 0);
	glVertex3d(vect[1].getX(), vect[1].getY(), 0);
	glTexCoord2d(ancho, 1);
	glVertex3d(vect[1].getX(), vect[1].getY(), 90);
	glTexCoord2d(0, 1);
	glVertex3d(vect[0].getX(), vect[0].getY(), 90);
	glEnd();

	glBegin(GL_QUADS);

	n = Vector2D(vect[1], vect[2]);
	ancho = n.Length();
	n.Normalize();
	n.perpCCW();
	glNormal3f(n.x, n.y, 0);

	ancho /= 90.0;

	glTexCoord2d(0, 0);
	glVertex3d(vect[1].getX(), vect[1].getY(), 0);
	glTexCoord2d(ancho, 0);
	glVertex3d(vect[2].getX(), vect[2].getY(), 0);
	glTexCoord2d(ancho, 1);
	glVertex3d(vect[2].getX(), vect[2].getY(), 90);
	glTexCoord2d(0, 1);
	glVertex3d(vect[1].getX(), vect[1].getY(), 90);

	glEnd();

	glBegin(GL_QUADS);

	n = Vector2D(vect[2], vect[3]);
	ancho = n.Length();
	n.Normalize();
	n.perpCCW();
	glNormal3f(n.x, n.y, 0);

	ancho /= 90.0;

	glTexCoord2d(0, 0);
	glVertex3d(vect[2].getX(), vect[2].getY(), 0);
	glTexCoord2d(ancho, 0);
	glVertex3d(vect[3].getX(), vect[3].getY(), 0);
	glTexCoord2d(ancho, 1);
	glVertex3d(vect[3].getX(), vect[3].getY(), 90);
	glTexCoord2d(0, 1);
	glVertex3d(vect[2].getX(), vect[2].getY(), 90);

	glEnd();

	glBegin(GL_QUADS);

	n = Vector2D(vect[3], vect[0]);
	ancho = n.Length();
	n.Normalize();
	n.perpCCW();
	glNormal3f(n.x, n.y, 0);

	ancho /= 90.0;

	glTexCoord2d(0, 0);
	glVertex3d(vect[3].getX(), vect[3].getY(), 0);
	glTexCoord2d(ancho, 0);
	glVertex3d(vect[0].getX(), vect[0].getY(), 0);
	glTexCoord2d(ancho, 1);
	glVertex3d(vect[0].getX(), vect[0].getY(), 90);
	glTexCoord2d(0, 1);
	glVertex3d(vect[3].getX(), vect[3].getY(), 90);

	glEnd();

	Textura::DesactivarTextura();


	Textura::ActivarTextura(texturas[Graphics::Texturas::t_wallCeil]);

	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glTexCoord2d(vect[0].getX() / 200.0, vect[0].getY() / 200.0);
	glVertex3d(vect[0].getX(), vect[0].getY(), 90);
	glTexCoord2d(vect[1].getX() / 200.0, vect[1].getY() / 200.0);
	glVertex3d(vect[1].getX(), vect[1].getY(), 90);
	glTexCoord2d(vect[2].getX() / 200.0, vect[2].getY() / 200.0);
	glVertex3d(vect[2].getX(), vect[2].getY(), 90);
	glTexCoord2d(vect[3].getX() / 200.0, vect[3].getY() / 200.0);
	glVertex3d(vect[3].getX(), vect[3].getY(), 90);
	glEnd();
	glPopMatrix();
	glEndList();
	Textura::DesactivarTextura();
	return id_display;
}

int ResourceManager::generateDoor(vector<Point> vect, int id){

	int id_display;
	if(id < 0){
		id_display = glGenLists(1);
		id_display += 1500;
	}else{
		id_display = id;
	}

	int cortoVertical;
	int cortoHorizontal;

	Vector2D long1(vect[0], vect[1]);
	Vector2D long2(vect[1], vect[2]);

	if(long1.Length() < long2.Length())
	{
		//O-1 es lado corto
		cortoVertical = 10;
		cortoHorizontal = 0;
	}
	else
	{
		//0-1 es lado largo
		cortoVertical = 0;
		cortoHorizontal = 10;
	}

	glNewList(id_display, GL_COMPILE);
	Textura::ActivarTextura(texturas[Graphics::Texturas::t_door]);

	glPushMatrix();
	//glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_QUADS);

	// Calculamos la Normal
	Vector2D n(vect[0], vect[1]);
	n.Normalize();
	n.perpCCW();
	glNormal3f(n.x, n.y, 0);

	glTexCoord2d(0, 0);
	glVertex3d(vect[0].getX()+cortoHorizontal, vect[0].getY()+cortoVertical, 0);
	glTexCoord2d(1, 0);
	glVertex3d(vect[1].getX()+cortoHorizontal, vect[1].getY()-cortoVertical, 0);
	glTexCoord2d(1, 1);
	glVertex3d(vect[1].getX()+cortoHorizontal, vect[1].getY()-cortoVertical, 90);
	glTexCoord2d(0, 1);
	glVertex3d(vect[0].getX()+cortoHorizontal, vect[0].getY()+cortoVertical, 90);
	glEnd();

	glBegin(GL_QUADS);

	n = Vector2D(vect[1], vect[2]);
	n.Normalize();
	n.perpCCW();
	glNormal3f(n.x, n.y, 0);


	glTexCoord2d(0, 0);
	glVertex3d(vect[1].getX()+cortoHorizontal, vect[1].getY()-cortoVertical, 0);
	glTexCoord2d(1, 0);
	glVertex3d(vect[2].getX()-cortoHorizontal, vect[2].getY()-cortoVertical, 0);
	glTexCoord2d(1, 1);
	glVertex3d(vect[2].getX()-cortoHorizontal, vect[2].getY()-cortoVertical, 90);
	glTexCoord2d(0, 1);
	glVertex3d(vect[1].getX()+cortoHorizontal, vect[1].getY()-cortoVertical, 90);

	glEnd();

	glBegin(GL_QUADS);

	n = Vector2D(vect[2], vect[3]);
	n.Normalize();
	n.perpCCW();
	glNormal3f(n.x, n.y, 0);


	glTexCoord2d(0, 0);
	glVertex3d(vect[2].getX()-cortoHorizontal, vect[2].getY()-cortoVertical, 0);
	glTexCoord2d(1, 0);
	glVertex3d(vect[3].getX()-cortoHorizontal, vect[3].getY()+cortoVertical, 0);
	glTexCoord2d(1, 1);
	glVertex3d(vect[3].getX()-cortoHorizontal, vect[3].getY()+cortoVertical, 90);
	glTexCoord2d(0, 1);
	glVertex3d(vect[2].getX()-cortoHorizontal, vect[2].getY()-cortoVertical, 90);

	glEnd();

	glBegin(GL_QUADS);

	n = Vector2D(vect[3], vect[0]);
	n.Normalize();
	n.perpCCW();
	glNormal3f(n.x, n.y, 0);

	glTexCoord2d(0, 0);
	glVertex3d(vect[3].getX()-cortoHorizontal, vect[3].getY()+cortoVertical, 0);
	glTexCoord2d(1, 0);
	glVertex3d(vect[0].getX()+cortoHorizontal, vect[0].getY()+cortoVertical, 0);
	glTexCoord2d(1, 1);
	glVertex3d(vect[0].getX()+cortoHorizontal, vect[0].getY()+cortoVertical, 90);
	glTexCoord2d(0, 1);
	glVertex3d(vect[3].getX()-cortoHorizontal, vect[3].getY()+cortoVertical, 90);

	glEnd();

	Textura::DesactivarTextura();
	Textura::ActivarTextura(texturas[Graphics::Texturas::t_doorCeil]);
	glBegin(GL_QUADS);

	glNormal3f(0.3, 0.3, 0.3);
	glTexCoord2d(0, 0);
	glVertex3d(vect[0].getX()+cortoHorizontal, vect[0].getY()+cortoVertical, 90);
	glTexCoord2d(1, 0);
	glVertex3d(vect[1].getX()+cortoHorizontal, vect[1].getY()-cortoVertical, 90);
	glTexCoord2d(1, 1);
	glVertex3d(vect[2].getX()-cortoHorizontal, vect[2].getY()-cortoVertical, 90);
	glTexCoord2d(0, 1);
	glVertex3d(vect[3].getX()-cortoHorizontal, vect[3].getY()+cortoVertical, 90);
	glEnd();
	Textura::DesactivarTextura();
	glPopMatrix();
	glEndList();


	return id_display;
}

int ResourceManager::generatePerimeter(vector<Point> vPerimetro) {
	int id = glGenLists(1);
	id += 1500;

	vector<Point>::iterator pIter;
	vector<vector<Point> >::iterator vvIter;

	Polygon suelo(vPerimetro);
	vector<vector<Point> > triStripsFloor = suelo.getTriStrip();

	// Para hacer la expansion
	vPerimetro.push_back(vPerimetro[0]);
	vPerimetro.push_back(vPerimetro[1]);
	vector<Point> paredExpandida;

	for (pIter = vPerimetro.begin(); pIter != vPerimetro.end() - 2; pIter++) {
		Point newPoint = Polygon::getNewPoint(*pIter, *(pIter + 1),
				*(pIter + 2), false, 50);
		paredExpandida.push_back(newPoint);
	}

	// Generamos el poligono de la parte de arriba de las paredes exteriores
	Polygon exterior(paredExpandida);
	exterior.makeConvexHull();
	vector<vector<Point> > triStripsWall = exterior.DiffToTriStrips(suelo);

	// Para pintar las paredes solo nos hace falta un punto auxiliar
	paredExpandida = exterior.getPuntos();
	paredExpandida.push_back(paredExpandida[0]);
	vPerimetro.pop_back();

	glNewList(id, GL_COMPILE);
	glPushMatrix();
	//glColor3f(1, 0.97, 0.86);

	////////	SUELO	////////
	glColor3f(1.0, 1.0, 1.0);
	glFrontFace(GL_CW);
	Textura::ActivarTextura(texturas[Graphics::Texturas::t_floor]);
	glNormal3d(0, 0, 1);
	for (vvIter = triStripsFloor.begin(); vvIter != triStripsFloor.end();
			vvIter++) {
		glBegin(GL_TRIANGLE_STRIP);
		for (pIter = (*vvIter).begin(); pIter != (*vvIter).end(); pIter++) {
			glTexCoord2d((*pIter).getX() / 200.0, (*pIter).getY() / 200.0);
			glNormal3f(0, 0, 1);
			glVertex3d((*pIter).getX(), (*pIter).getY(), (*pIter).getZ());
		}
		glEnd();
	}
	Textura::DesactivarTextura();
	glFrontFace(GL_CCW);

	Textura::ActivarTextura(texturas[Graphics::Texturas::t_wallFloor]);
	////////	PARED INTERIOR	////////
	glColor3f(0.9, 0.9, 0.9);
	for (pIter = vPerimetro.begin(); pIter != vPerimetro.end() - 1; pIter++) {
		Point a(*pIter), b(*(pIter + 1));
		a.setZ(90);
		b.setZ(90);
		Vector2D normal(a, b);
		double ancho = normal.Length();
		normal.perpCCW();
		normal.Normalize();

		ancho /= 200.0;

		glBegin(GL_QUADS);
		glNormal3f(normal.x, normal.y, 0);

		glTexCoord2d(0, 0);
		glVertex3d((*pIter).getX(), (*pIter).getY(), (*pIter).getZ());
		glTexCoord2d(ancho, 0);
		glVertex3d((*(pIter + 1)).getX(), (*(pIter + 1)).getY(),
				(*(pIter + 1)).getZ());
		glTexCoord2d(ancho, 0.9);
		glVertex3d(b.getX(), b.getY(), b.getZ());
		glTexCoord2d(0, 0.9);
		glVertex3d(a.getX(), a.getY(), a.getZ());
		glEnd();
	}

	//////// PARED EXTERIOR ////////
	glColor3f(0.6, 0.6, 0.6);
	for (pIter = paredExpandida.begin(); pIter != paredExpandida.end() - 1;
			pIter++) {
		Point a(*pIter), b(*(pIter + 1));
		a.setZ(90);
		b.setZ(90);
		Vector2D normal(a, b);
		normal.perpCW();
		normal.Normalize();

		glBegin(GL_QUADS);
		glNormal3f(normal.x, normal.y, 0);

		glVertex3d((*pIter).getX(), (*pIter).getY(), (*pIter).getZ());
		glVertex3d(a.getX(), a.getY(), a.getZ());
		glVertex3d(b.getX(), b.getY(), b.getZ());
		glVertex3d((*(pIter + 1)).getX(), (*(pIter + 1)).getY(),
				(*(pIter + 1)).getZ());

		glEnd();
	}
	Textura::DesactivarTextura();
	//////// TECHO ////////

	glFrontFace(GL_CW);
	Textura::ActivarTextura(texturas[Graphics::Texturas::t_wallCeil]);
	//glColor3f(0.95, 0.92, 0.81);
	glColor3f(0.8, 0.8, 0.8);
	glNormal3d(0, 0, 1);
	for (vvIter = triStripsWall.begin(); vvIter != triStripsWall.end();
			vvIter++) {
		glBegin(GL_TRIANGLE_STRIP);
		for (pIter = (*vvIter).begin(); pIter != (*vvIter).end(); pIter++) {
			glNormal3f(0, 0, 1);
			glTexCoord2d((*pIter).getX() / 200.0, (*pIter).getY() / 200.0);
			glVertex3d((*pIter).getX(), (*pIter).getY(), 90);
		}
		glEnd();
	}
	Textura::DesactivarTextura();
	glFrontFace(GL_CCW);

	glPopMatrix();
	glEndList();

	return id;
}

void ResourceManager::loadModels() {
	string modelsroot = RESOURCESROOT;
	modelsroot += "modelos/";

	string texturesroot = RESOURCESROOT;
	texturesroot += "texturas/";

	/*Material material;

	material.setAmbiente(Color<float>(0, 0, 0, 1));
	material.setDifusa(Color<float>(0.55, 0.55, 0.55, 1));
	material.setEspecular(Color<float>(0.70, 0.70, 0.70, 1));
	material.setBrillo(0);*/

	//Modelo simple
	string ruta;
	string text;

	//Enemy 1
	text = texturesroot + "pyro_flat.tga";
	ruta = modelsroot + "p1.3ds";
	Model aux = Model(ruta, Core::Entities::e_enemy1*5 + 0, Textura(text,1));
	aux.createDisplayList();

	ruta = modelsroot + "p2.3ds";
	aux = Model(ruta, Core::Entities::e_enemy1*5 + 1, Textura(text,1));
	aux.createDisplayList();

	ruta = modelsroot + "p3.3ds";
	aux = Model(ruta, Core::Entities::e_enemy1*5 + 2, Textura(text,1));
	aux.createDisplayList();

	ruta = modelsroot + "p4.3ds";
	aux = Model(ruta, Core::Entities::e_enemy1*5 + 3, Textura(text,1));
	aux.createDisplayList();

	ruta = modelsroot + "p5.3ds";
	aux = Model(ruta, Core::Entities::e_enemy1*5 + 4, Textura(text,1));
	aux.createDisplayList();


	//Enemy 2
	text = texturesroot + "sniper_flat.tga";
	ruta = modelsroot + "sn1.3ds"; //"Enemy2.3ds";
	aux = Model(ruta, Core::Entities::e_enemy2*5 + 0, Textura(text,1));
	aux.createDisplayList();

	ruta = modelsroot + "sn2.3ds"; //"Enemy2.3ds";
	aux = Model(ruta, Core::Entities::e_enemy2*5 + 1, Textura(text,1));
	aux.createDisplayList();

	ruta = modelsroot + "sn3.3ds"; //"Enemy2.3ds";
	aux = Model(ruta, Core::Entities::e_enemy2*5 + 2, Textura(text,1));
	aux.createDisplayList();

	ruta = modelsroot + "sn4.3ds"; //"Enemy2.3ds";
	aux = Model(ruta, Core::Entities::e_enemy2*5 + 3, Textura(text,1));
	aux.createDisplayList();

	ruta = modelsroot + "sn5.3ds"; //"Enemy2.3ds";
	aux = Model(ruta, Core::Entities::e_enemy2*5 + 4, Textura(text,1));
	aux.createDisplayList();


	//Enemy 3
	text = texturesroot + "engi_flat.tga";
	ruta = modelsroot + "e1.3ds"; //"Enemy3.3ds";
	aux = Model(ruta, Core::Entities::e_enemy3*5 + 0, Textura(text,1));
	aux.createDisplayList();

	ruta = modelsroot + "e2.3ds"; //"Enemy3.3ds";
	aux = Model(ruta, Core::Entities::e_enemy3*5 + 1, Textura(text,1));
	aux.createDisplayList();

	ruta = modelsroot + "e3.3ds"; //"Enemy3.3ds";
	aux = Model(ruta, Core::Entities::e_enemy3*5 + 2, Textura(text,1));
	aux.createDisplayList();

	ruta = modelsroot + "e4.3ds"; //"Enemy3.3ds";
	aux = Model(ruta, Core::Entities::e_enemy3*5 + 3, Textura(text,1));
	aux.createDisplayList();

	ruta = modelsroot + "e5.3ds"; //"Enemy3.3ds";
	aux = Model(ruta, Core::Entities::e_enemy3*5 + 4, Textura(text,1));
	aux.createDisplayList();

	//Explodemo
	text = texturesroot + "demo_flat.tga";
	ruta = modelsroot + "d1.3ds"; //"Explodemo.3ds";
	aux = Model(ruta, Core::Entities::e_explosive*5 + 0, Textura(text,1));
	aux.createDisplayList();

	ruta = modelsroot + "d2.3ds"; //"Explodemo.3ds";
	aux = Model(ruta, Core::Entities::e_explosive*5 + 1, Textura(text,1));
	aux.createDisplayList();


	ruta = modelsroot + "d3.3ds"; //"Explodemo.3ds";
	aux = Model(ruta, Core::Entities::e_explosive*5 + 2, Textura(text,1));
	aux.createDisplayList();

	ruta = modelsroot + "d4.3ds"; //"Explodemo.3ds";
	aux = Model(ruta, Core::Entities::e_explosive*5 + 3, Textura(text,1));
	aux.createDisplayList();

	ruta = modelsroot + "d5.3ds"; //"Explodemo.3ds";
	aux = Model(ruta, Core::Entities::e_explosive*5 + 4, Textura(text,1));
	aux.createDisplayList();


	//Especial
	text = texturesroot + "heavy_flat.tga";
	ruta = modelsroot + "h1.3ds"; //"Especial.3ds";
	aux = Model(ruta, Core::Entities::e_especialist*5 + 0, Textura(text,1));
	aux.createDisplayList();

	ruta = modelsroot + "h2.3ds"; //"Especial.3ds";
	aux = Model(ruta, Core::Entities::e_especialist*5 + 1, Textura(text,1));
	aux.createDisplayList();


	ruta = modelsroot + "h3.3ds"; //"Especial.3ds";
	aux = Model(ruta, Core::Entities::e_especialist*5 + 2, Textura(text,1));
	aux.createDisplayList();


	ruta = modelsroot + "h4.3ds"; //"Especial.3ds";
	aux = Model(ruta, Core::Entities::e_especialist*5 + 3, Textura(text,1));
	aux.createDisplayList();

	ruta = modelsroot + "h5.3ds"; //"Especial.3ds";
	aux = Model(ruta, Core::Entities::e_especialist*5 + 4, Textura(text,1));
	aux.createDisplayList();



	//Tecnic
	text = texturesroot + "scout_flat.tga";
	ruta = modelsroot + "s1.3ds";
	aux = Model(ruta, Core::Entities::e_tecnic*5 + 0, Textura(text,1));
	aux.createDisplayList();

	ruta = modelsroot + "s2.3ds";
	aux = Model(ruta, Core::Entities::e_tecnic*5 + 1, Textura(text,1));
	aux.createDisplayList();

	ruta = modelsroot + "s3.3ds";
	aux = Model(ruta, Core::Entities::e_tecnic*5 + 2, Textura(text,1));
	aux.createDisplayList();

	ruta = modelsroot + "s4.3ds";
	aux = Model(ruta, Core::Entities::e_tecnic*5 + 3, Textura(text,1));
	aux.createDisplayList();

	ruta = modelsroot + "s5.3ds";
	aux = Model(ruta, Core::Entities::e_tecnic*5 + 4, Textura(text,1));
	aux.createDisplayList();


	//Captain


	text = texturesroot + "soldier_flat.tga";
	ruta = modelsroot + "c1.3ds";
	aux = Model(ruta, Core::Entities::e_captain*5 + 0, Textura(text,1));
	aux.createDisplayList();

	text = texturesroot + "soldier_flat.tga";
	ruta = modelsroot + "c2.3ds";
	aux = Model(ruta, Core::Entities::e_captain*5 + 1, Textura(text,1));
	aux.createDisplayList();


	ruta = modelsroot + "c3.3ds";
	aux = Model(ruta, Core::Entities::e_captain*5 + 2, Textura(text,1));
	aux.createDisplayList();


	ruta = modelsroot + "c4.3ds";
	aux = Model(ruta, Core::Entities::e_captain*5 + 3, Textura(text,1));
	aux.createDisplayList();


	ruta = modelsroot + "c5.3ds";
	aux = Model(ruta, Core::Entities::e_captain*5 + 4, Textura(text,1));
	aux.createDisplayList();


	//MiniBoss
	text = texturesroot + "spy_flat.tga";

	ruta = modelsroot + "sp1.3ds";
	aux = Model(ruta, Core::Entities::e_miniboss*5 + 0, Textura(text,1));
	aux.createDisplayList();

	ruta = modelsroot + "sp2.3ds";
	aux = Model(ruta, Core::Entities::e_miniboss*5 + 1, Textura(text,1));
	aux.createDisplayList();

	ruta = modelsroot + "sp3.3ds";
	aux = Model(ruta, Core::Entities::e_miniboss*5 + 2, Textura(text,1));
	aux.createDisplayList();

	ruta = modelsroot + "sp4.3ds";
	aux = Model(ruta, Core::Entities::e_miniboss*5 + 3, Textura(text,1));
	aux.createDisplayList();

	ruta = modelsroot + "sp5.3ds";
	aux = Model(ruta, Core::Entities::e_miniboss*5 + 4, Textura(text,1));
	aux.createDisplayList();

	//MegaBoss
	text = texturesroot + "medic_flat.tga";
	ruta = modelsroot + "m1.3ds";
	aux = Model(ruta, Core::Entities::e_megaboss*5 + 0, Textura(text,1));
	aux.createDisplayList();

	ruta = modelsroot + "m2.3ds";
	aux = Model(ruta, Core::Entities::e_megaboss*5 + 1, Textura(text,1));
	aux.createDisplayList();

	ruta = modelsroot + "m3.3ds";
	aux = Model(ruta, Core::Entities::e_megaboss*5 + 2, Textura(text,1));
	aux.createDisplayList();

	ruta = modelsroot + "m4.3ds";
	aux = Model(ruta, Core::Entities::e_megaboss*5 + 3, Textura(text,1));
	aux.createDisplayList();

	ruta = modelsroot + "m5.3ds";
	aux = Model(ruta, Core::Entities::e_megaboss*5 + 4, Textura(text,1));
	aux.createDisplayList();


	//Obstáculos

	ruta = modelsroot + "mesa.3ds";
	text = texturesroot + "mesa.png";
	aux = Model(ruta, Core::Obstacles::obs_table + 1000, Textura(text,1));
	aux.createDisplayList();

	ruta = modelsroot + "desk.3ds";
	text = texturesroot + "desk.png";
	aux = Model(ruta, Core::Obstacles::obs_desk + 1000, Textura(text,1));
	aux.createDisplayList();

	ruta = modelsroot + "sillon.3ds";
	text = texturesroot + "sAzul.png";
	aux = Model(ruta, Core::Obstacles::obs_couch + 1000, Textura(text,1));
	aux.createDisplayList();

	ruta = modelsroot + "sofa.3ds";
	text = texturesroot + "sAzul.png";
	aux = Model(ruta, Core::Obstacles::obs_sofa + 1000, Textura(text,1));
	aux.createDisplayList();

	ruta = modelsroot + "plant.3ds";
	text = texturesroot + "plant.png";
	aux = Model(ruta, Core::Obstacles::obs_plantPot + 1000, Textura(text,1));
	aux.createDisplayList();

	ruta = modelsroot + "estanteria.3ds";
	text = texturesroot + "estanteria.png";
	aux = Model(ruta, Core::Obstacles::obs_shelf + 1000, Textura(text,1));
	aux.createDisplayList();

	ruta = modelsroot + "sillaEspera.3ds";
	text = texturesroot + "silla.png";
	aux = Model(ruta, Core::Obstacles::obs_chair + 1000, Textura(text,1));
	aux.createDisplayList();

	ruta = modelsroot + "mesaSillas.3ds";
	text = texturesroot + "mesaSillas.png";
	aux = Model(ruta, Core::Obstacles::obs_mesaConSillas + 1000, Textura(text,1));
	aux.createDisplayList();

	//Recompensas

	text = texturesroot + "hpack.png";
	ruta = modelsroot + "hpack.3ds";
	aux = Model(ruta, Core::Objects::health_pack_1 + 500, Textura(text, 1));
	aux.createDisplayList();

	ruta = modelsroot + "hpack.3ds";
	aux = Model(ruta, Core::Objects::health_pack_2 + 500, Textura(text, 1));
	aux.createDisplayList();

	ruta = modelsroot + "hpack.3ds";
	aux = Model(ruta, Core::Objects::health_pack_3 + 500, Textura(text, 1));
	aux.createDisplayList();

	text = texturesroot + "ammo_pack.png";
	ruta = modelsroot + "ammo_pack.3ds";
	aux = Model(ruta, Core::Objects::ammo_pack_1 + 500, Textura(text, 1));
	aux.createDisplayList();

	aux = Model(ruta, Core::Objects::ammo_pack_2 + 500, Textura(text, 1));
	aux.createDisplayList();

	aux = Model(ruta, Core::Objects::ammo_pack_3 + 500, Textura(text, 1));
	aux.createDisplayList();

	//Falta el pointer.e_pointer
	Model2D *pointer = getModel2DObject(Core::Entities::e_pointer);
	if (pointer != NULL) {
		Polygon *shape = pointer->getShape();
		if (shape != NULL) {
			glNewList(Core::Entities::e_pointer*5, GL_COMPILE);
			DrawPolygon(*shape, Color<float>(1, 0.5, 0));
			glEndList();
		}
	}

}

void ResourceManager::loadTextures() {

	string texturasroot = RESOURCESROOT;
	texturasroot += "texturas/";

	Textura textPared(texturasroot + "pared.jpg",
			Graphics::Texturas::t_wall + 1);
	texturas[Graphics::Texturas::t_wall] = textPared.getTexture();

	Textura textSuelo(texturasroot + "sueloOficina.jpg",
			Graphics::Texturas::t_floor + 1);
	texturas[Graphics::Texturas::t_floor] = textSuelo.getTexture();

	Textura textFloor(texturasroot + "pared.jpg",
			Graphics::Texturas::t_wallFloor + 1);
	texturas[Graphics::Texturas::t_wallFloor] = textFloor.getTexture();

	Textura textDoor(texturasroot + "tp3.png",
			Graphics::Texturas::t_door + 1);
	texturas[Graphics::Texturas::t_door] = textDoor.getTexture();

	Textura textParedTecho(texturasroot + "techoPared.png",
			Graphics::Texturas::t_wallCeil + 1);
	texturas[Graphics::Texturas::t_wallCeil] = textParedTecho.getTexture();

	Textura textDoorTecho(texturasroot + "techoPuerta.png",
			Graphics::Texturas::t_doorCeil + 1);
	texturas[Graphics::Texturas::t_doorCeil] = textDoorTecho.getTexture();

	Textura texturaExplosion(texturasroot + "exploMala.png",
			Graphics::Texturas::t_explosion + 1);
	texturas[Graphics::Texturas::t_explosion] = texturaExplosion.getTexture();

}
EventControl *ResourceManager::getEvents() const {
	return events;
}

void ResourceManager::setEvents(EventControl *events) {
	this->events = events;
}

void ResourceManager::setWorld(World *world) {
	this->world = world;
}

//// FUENTES ////

FTGLTextureFont * ResourceManager::getFont(Graphics::Font::Name nombre,
		int size) {

	FTGLTextureFont *font = NULL;

	// Busco si la fuente esta creada
	vector<fontHandler>::iterator iter;
	for (iter = fuentes[(int) nombre].begin();
			iter != fuentes[(int) nombre].end(); iter++) {
		if ((*iter).size == size) {
			font = (*iter).font;
			break;
		}
	}

	if (font == NULL) {
		string path = RESOURCESROOT;
		path += "fuentes/";
		switch (nombre) {
		case Graphics::Font::Monospace:
			path += "Monospace.ttf";
			break;
		case Graphics::Font::Serif:
			path += "Serif.ttf";
			break;
		case Graphics::Font::SansSerif:
			path += "Sans.ttf";
			break;
		case Graphics::Font::BebasNeue:
			path += "BebasNeue.ttf";
			break;
		case Graphics::Font::Coolvetica:
			path += "Coolvetica.ttf";
			break;
		case Graphics::Font::Absender:
			path += "Absender.ttf";
			break;
		case Graphics::Font::tf2:
			path += "TF2.ttf";
			break;
		case Graphics::Font::tf2Build:
			path += "tf2build.ttf";
			break;
		default:
			break;
		}

		font = new FTGLTextureFont(path.c_str());
		if (!font->Error()) {
			font->FaceSize(size);
			fontHandler fH;
			fH.font = font;
			fH.size = size;
			fuentes[nombre].push_back(fH);
		} else {
			delete font;
			font = NULL;
		}
	}

	return font;
}
