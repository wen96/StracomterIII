/*
 * ResourceManager.cc
 *
 *  Created on: 15/11/2011
 *      Author: Chutaos Team
 */

#include "ResourceManager.h"
#include "EventControl.h"

ResourceManager * ResourceManager::_resources = NULL;

ResourceManager * ResourceManager::getInstance(){
	if(_resources == NULL){
		_resources = new ResourceManager();
	}
	return _resources;
}

ResourceManager * ResourceManager::getInstance(World *world_, EventControl *events_){
	if(_resources == NULL){
		_resources = new ResourceManager(world_, events_);
	}else{
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

	for(int i = 0; i < Graphics::Font::size; i++){
		fuentes.push_back(vector<fontHandler>());
	}
}

ResourceManager::ResourceManager(World *world_, EventControl *events_){
	for (int i = 0; i < Core::Entities::size; i++) {
		models2D.push_back(NULL);
		modelsPhisics.push_back(NULL);
	}
	world = world_;
	events = events_;

	texturas = vector<unsigned int>(Graphics::Texturas::t_size, 0);

	for(int i = 0; i < Graphics::Font::size; i++){
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

World* ResourceManager::getWorld() {
	return world;
}

int ResourceManager::generateWall(vector<Point> vect){

	//TODO Mirar como cambiar esta mierda.
	int id_display = glGenLists(1);
	id_display += 1000;


	double ancho;


	glNewList(id_display , GL_COMPILE);
	Textura::ActivarTextura(texturas[Graphics::Texturas::t_wall]);
	glPushMatrix();
	glColor3f(0.8,0.8,0.8);
	glBegin(GL_QUADS);
	Vector2D n(vect[0],vect[1]);
	n.perpCCW();
	n.Normalize();
	glNormal3f(n.x,n.y,0);
	if(vect[0].getX() == vect[1].getX())
		ancho = abs(vect[0].getY() - vect[1].getY());
	else
		ancho = abs(vect[0].getX() - vect[1].getX());

	ancho /= 90.0;

	glTexCoord2d(0,0);
	glVertex3d(vect[0].getX(), vect[0].getY(), vect[0].getZ());
	glTexCoord2d(ancho,0);
	glVertex3d(vect[1].getX(), vect[1].getY(), vect[1].getZ());
	glTexCoord2d(ancho,1);
	glVertex3d(vect[5].getX(), vect[5].getY(), vect[5].getZ());
	glTexCoord2d(0,1);
	glVertex3d(vect[4].getX(), vect[4].getY(), vect[4].getZ());
	glEnd();

	glBegin(GL_QUADS);

	if(vect[1].getX() == vect[2].getX())
		ancho = abs(vect[1].getY() - vect[2].getY());
	else
		ancho = abs(vect[1].getX() - vect[2].getX());

	ancho /= 90.0;

	n = Vector2D(vect[1],vect[2]);
	n.perpCCW();
	n.Normalize();
	glNormal3f(n.x,n.y,0);

	glTexCoord2d(0,0);
	glVertex3d(vect[1].getX(), vect[1].getY(), vect[1].getZ());
	glTexCoord2d(ancho, 0);
	glVertex3d(vect[2].getX(), vect[2].getY(), vect[2].getZ());
	glTexCoord2d(ancho,1);
	glVertex3d(vect[6].getX(), vect[6].getY(), vect[6].getZ());
	glTexCoord2d(0,1);
	glVertex3d(vect[5].getX(), vect[5].getY(), vect[5].getZ());

	glEnd();

	glBegin(GL_QUADS);

	if(vect[2].getX() == vect[3].getX())
		ancho = abs(vect[2].getY() - vect[3].getY());
	else
		ancho = abs(vect[2].getX() - vect[3].getX());

	ancho /= 90.0;

	n = Vector2D(vect[2],vect[3]);
	n.perpCCW();
	n.Normalize();

	glNormal3f(n.x,n.y,0);

	glTexCoord2d(0,0);
	glVertex3d(vect[2].getX(), vect[2].getY(), vect[2].getZ());
	glTexCoord2d(ancho,0);
	glVertex3d(vect[3].getX(), vect[3].getY(), vect[3].getZ());
	glTexCoord2d(ancho,1);
	glVertex3d(vect[7].getX(), vect[7].getY(), vect[7].getZ());
	glTexCoord2d(0,1);
	glVertex3d(vect[6].getX(), vect[6].getY(), vect[6].getZ());

	glEnd();

	glBegin(GL_QUADS);

	if(vect[3].getX() == vect[0].getX())
		ancho = abs(vect[3].getY() - vect[0].getY());
	else
		ancho = abs(vect[3].getX() - vect[0].getX());

	ancho /= 90.0;

	n = Vector2D(vect[3],vect[0]);
	n.perpCCW();
	n.Normalize();
	glNormal3f(n.x,n.y,0);

	glTexCoord2d(0,0);
	glVertex3d(vect[3].getX(), vect[3].getY(), vect[3].getZ());
	glTexCoord2d(ancho,0);
	glVertex3d(vect[0].getX(), vect[0].getY(), vect[0].getZ());
	glTexCoord2d(ancho,1);
	glVertex3d(vect[4].getX(), vect[4].getY(), vect[4].getZ());
	glTexCoord2d(0,1);
	glVertex3d(vect[7].getX(), vect[7].getY(), vect[7].getZ());

	glEnd();


	Textura::DesactivarTextura();
	glBegin(GL_QUADS);
	glNormal3f(0,0,1);
	glVertex3d(vect[4].getX(), vect[4].getY(), vect[4].getZ());
	glVertex3d(vect[5].getX(), vect[5].getY(), vect[5].getZ());
	glVertex3d(vect[6].getX(), vect[6].getY(), vect[6].getZ());
	glVertex3d(vect[7].getX(), vect[7].getY(), vect[7].getZ());

	glEnd();

	glPopMatrix();
	glEndList();

	return id_display;
}

int ResourceManager::generatePerimeter(vector<Point> vPerimetro){
	int id = glGenLists(1);
	id += 1000;

	vector<Point>::iterator pIter;
	vector<vector<Point> >::iterator vvIter;

	Polygon suelo(vPerimetro);
	vector<vector<Point > > triStripsFloor = suelo.getTriStrip();

	// Para hacer la expansion
	vPerimetro.push_back(vPerimetro[0]);
	vPerimetro.push_back(vPerimetro[1]);
	vector<Point> paredExpandida;

	for(pIter = vPerimetro.begin(); pIter != vPerimetro.end() - 2; pIter++){
		Point newPoint = Polygon::getNewPoint(*pIter, *(pIter+1), *(pIter+2), false, 50);
		paredExpandida.push_back(newPoint);
	}

	// Generamos el poligono de la parte de arriba de las paredes exteriores
	Polygon exterior(paredExpandida);
	exterior.makeConvexHull();
	vector<vector<Point > > triStripsWall = exterior.DiffToTriStrips(suelo);

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
	glNormal3d(0,0,1);
	for(vvIter = triStripsFloor.begin(); vvIter != triStripsFloor.end(); vvIter++){
		glBegin(GL_TRIANGLE_STRIP);
		for(pIter = (*vvIter).begin(); pIter != (*vvIter).end(); pIter++){
			glTexCoord2d((*pIter).getX()/200.0, (*pIter).getY()/200.0);
			glNormal3f(0,0,1);
			glVertex3d((*pIter).getX(), (*pIter).getY(), (*pIter).getZ());
		}
		glEnd();
	}
	Textura::DesactivarTextura();
	glFrontFace(GL_CCW);

	Textura::ActivarTextura(texturas[Graphics::Texturas::t_wallFloor]);
	////////	PARED INTERIOR	////////
	glColor3f(0.9,0.9,0.9);
	for(pIter = vPerimetro.begin(); pIter != vPerimetro.end() - 1; pIter++){
		Point 	a(*pIter),
				b(*(pIter + 1));
		a.setZ(90);
		b.setZ(90);
		Vector2D normal(a, b);
		normal.perpCCW();
		normal.Normalize();

		double ancho;
		if(a.getX() == b.getX())
			ancho = abs(a.getY() - b.getY());
		else
			ancho = abs(a.getX() - b.getX());

		ancho /= 200.0;

		glBegin(GL_QUADS);
		glNormal3f(normal.x, normal.y, 0);

		glTexCoord2d(0, 0);
		glVertex3d((*pIter).getX(), (*pIter).getY(), (*pIter).getZ());
		glTexCoord2d(ancho, 0);
		glVertex3d((*(pIter+1)).getX(), (*(pIter+1)).getY(), (*(pIter+1)).getZ());
		glTexCoord2d(ancho, 0.9);
		glVertex3d(b.getX(), b.getY(), b.getZ());
		glTexCoord2d(0, 0.9);
		glVertex3d(a.getX(), a.getY(), a.getZ());
		glEnd();
	}

	//////// PARED EXTERIOR ////////
	glColor3f(0.6,0.6,0.6);
	for(pIter = paredExpandida.begin(); pIter != paredExpandida.end() - 1; pIter++){
		Point 	a(*pIter),
				b(*(pIter + 1));
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
		glVertex3d((*(pIter+1)).getX(), (*(pIter+1)).getY(), (*(pIter+1)).getZ());

		glEnd();
	}
	Textura::DesactivarTextura();
	//////// TECHO ////////

	glFrontFace(GL_CW);

	//glColor3f(0.95, 0.92, 0.81);
	glColor3f(0.8,0.8,0.8);
	glNormal3d(0,0,1);
	for(vvIter = triStripsWall.begin(); vvIter != triStripsWall.end(); vvIter++){
		glBegin(GL_TRIANGLE_STRIP);
		for(pIter = (*vvIter).begin(); pIter != (*vvIter).end(); pIter++){
			glNormal3f(0,0,1);
			glVertex3d((*pIter).getX(), (*pIter).getY(), 90);
		}
		glEnd();
	}

	glFrontFace(GL_CCW);



	glPopMatrix();
	glEndList();

	return id;
}

void ResourceManager::loadModels() {
	string modelsroot = RESOURCESROOT;
	modelsroot += "modelos/";

	Material material;

	material.setAmbiente(Color<float>(0, 0, 0, 1));
	material.setDifusa(Color<float>(0.55,	0.55,	0.55, 1));
	material.setEspecular(Color<float>(0.70,	0.70,	0.70, 1));
	material.setBrillo(0);
	//Modelo simple
	string ruta = modelsroot + "Enemy1.3ds";
	Model aux = Model(ruta, Core::Entities::e_enemy1);
	//aux.setMaterial(material);
	aux.createDisplayList();

	ruta = modelsroot + "Enemy2.3ds";
	aux = Model(ruta, Core::Entities::e_enemy2);
	//aux.setMaterial(material);
	aux.createDisplayList();

	ruta = modelsroot + "Enemy3.3ds";
	aux = Model(ruta, Core::Entities::e_enemy3);
	//aux.setMaterial(material);
	aux.createDisplayList();

	ruta = modelsroot + "Explodemo.3ds";
	aux = Model(ruta, Core::Entities::e_explosive);
	//aux.setMaterial(material);
	aux.createDisplayList();

	ruta = modelsroot + "Especial.3ds";
	aux = Model(ruta, Core::Entities::e_especialist);
	//aux.setMaterial(material);
	aux.createDisplayList();

	ruta = modelsroot + "Captain.3ds";
	aux = Model(ruta, Core::Entities::e_captain);
	//aux.setMaterial(material);
	aux.createDisplayList();

	ruta = modelsroot + "Tecnic.3ds";
	aux = Model(ruta, Core::Entities::e_tecnic);
	//aux.setMaterial(material);
	aux.createDisplayList();


	Model2D *miniboss = getModel2DObject(Core::Entities::e_miniboss);
	if (miniboss != NULL) {
		Polygon *shape = miniboss->getShape();
		if (shape != NULL) {
			glNewList(Core::Entities::e_miniboss, GL_COMPILE);
			DrawPolygon(*shape, Color<float>(1, 0.5, 0));
			glEndList();
		}
	}

	Model2D *megaboss = getModel2DObject(Core::Entities::e_megaboss);
	if (megaboss != NULL) {
		Polygon *shape = megaboss->getShape();
		if (shape != NULL) {
			glNewList(Core::Entities::e_megaboss, GL_COMPILE);
			DrawPolygon(*shape, Color<float>(1, 0.5, 0));
			glEndList();
		}
	}

	//Falta el pointer.e_pointer
	Model2D *pointer = getModel2DObject(Core::Entities::e_pointer);
	if (pointer != NULL) {
		Polygon *shape = pointer->getShape();
		if (shape != NULL) {
			glNewList(Core::Entities::e_pointer, GL_COMPILE);
			DrawPolygon(*shape, Color<float>(1, 0.5, 0));
			glEndList();
		}
	}

}

void
ResourceManager::loadTextures() {

	string texturasroot = RESOURCESROOT;
	texturasroot += "texturas/";

	Textura textPared(texturasroot + "pared.jpg", Graphics::Texturas::t_wall+1);
	texturas[Graphics::Texturas::t_wall] = textPared.getTexture();

	Textura textSuelo(texturasroot + "sueloOficina.jpg", Graphics::Texturas::t_floor+1);
	texturas[Graphics::Texturas::t_floor] = textSuelo.getTexture();

	Textura textFloor(texturasroot + "pared.jpg", Graphics::Texturas::t_wallFloor+1);
	texturas[Graphics::Texturas::t_wallFloor] = textFloor.getTexture();

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

FTGLTextureFont * ResourceManager::getFont(Graphics::Font::Name nombre, int size){

	FTGLTextureFont *font = NULL;

	// Busco si la fuente esta creada
	vector<fontHandler>::iterator iter;
	for(iter = fuentes[(int)nombre].begin(); iter != fuentes[(int)nombre].end(); iter++){
		if((*iter).size == size){
			font = (*iter).font;
			break;
		}
	}

	if(font == NULL){
		string path = RESOURCESROOT;
		path += "fuentes/";
		switch(nombre){
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
		default:
			break;
		}

		font = new FTGLTextureFont(path.c_str());
		if(!font->Error()){
			font->FaceSize(size);
			fontHandler fH;
			fH.font = font;
			fH.size = size;
			fuentes[nombre].push_back(fH);
		}else{
			delete font;
			font = NULL;
		}
	}

	return font;
}
