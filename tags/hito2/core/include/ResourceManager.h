/*
 * ResourceManager.h
 *
 *  Created on: 15/11/2011
 *      Author: Chutaos Team
 */

#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include <vector>
#include <map>
#include "Polygon.h"
#include "Model2D.h"
#include "ModelPhisic.h"
#include "CoreNamespace.h"
#include "GraphicsNamespace.h"
#include "World.h"
#include <GL/gl.h>
#include <FTGL/ftgl.h>
#include "MotorGrafico.h"
#include "Textura.h"
#include "Color.h"
#include "Model.h"

class EventControl;

using namespace std;

struct fontHandler{
	FTGLTextureFont *font;
	int size;
};

class ResourceManager {
public:
	static ResourceManager * getInstance();
	static ResourceManager * getInstance(World *world_, EventControl *events_);

	virtual ~ResourceManager();

	Model2D* getModel2DObject(Core::Entities::Type type);

	ModelPhisic* getModelPhisics(Core::Entities::Type type);

	World* getWorld();

	void loadModels();
	void loadTextures();
    EventControl *getEvents() const;
    void setEvents(EventControl *events);
    void setWorld(World *world);

    FTGLTextureFont * getFont(Graphics::Font::Name fuente, int size);

    int generateWall(vector<Point> vect);

    int generatePerimeter(vector<Point> vect);

private:
    ResourceManager();
	ResourceManager(World *world_, EventControl *events_);
	static ResourceManager *_resources;

	vector<Model2D*> models2D;
	vector<ModelPhisic*> modelsPhisics;
	//Model2D *player;
	World* world;
	EventControl *events;
	vector<unsigned int>texturas;

	//Fuentes
	vector<vector<fontHandler> > fuentes;
};



#endif /* RESOURCEMANAGER_H_ */
