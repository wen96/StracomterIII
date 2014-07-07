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
#include <SFML/Graphics.hpp>
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

/**\brief Clase de gestion de recursos
  * Se encargar de gestionar los recursos necesarios para el juego y devolverlos cuando son necesarios.
  */
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

    int generateWall(vector<Point> vect, int id = -1);

    int generateDoor(vector<Point> vect,  int id = -1);

    int generatePerimeter(vector<Point> vect);
    ModelPhisic getObstacle(Core::Obstacles::Type type, Polygon);

    void loadShaders();
    void activateShader(Graphics::Shader::Name sh);
    void deactivateShader(Graphics::Shader::Name sh);
    vector<unsigned int> getTexturas()
	{
    	return texturas;
	}
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

	//Shaders
	vector<sf::Shader *> shaderV;
};



#endif /* RESOURCEMANAGER_H_ */
