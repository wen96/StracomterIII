/*
 * ResourceManager.h
 *
 *  Created on: 15/11/2011
 *      Author: Chutaos Team
 */

#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include <vector>
#include "Polygon.h"
#include "Model2D.h"
#include "ModelPhisic.h"
#include "CoreNamespace.h"
#include "World.h"

using namespace std;

class ResourceManager {
public:
	ResourceManager(World *world_){
		for (int i = 0; i < Core::Entities::size; i++){
			models2D.push_back(NULL);
			modelsPhisics.push_back(NULL);
		}
		world = world_;
	}
	virtual ~ResourceManager(){
		if (!models2D.empty()){
			for (int i = 0; i < Core::Entities::size; i++){
				if (models2D[i]!=NULL){
					delete models2D[i];
				}
				if (modelsPhisics[i]!=NULL){
					delete modelsPhisics[i];
				}
			}
			models2D.clear();
			modelsPhisics.clear();

		}
		if (!modelsPhisics.empty()){
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


	Model2D* getModel2DObject(Core::Entities::Type type) {
		Model2D *aux = NULL;
		if (models2D[type]==NULL){
			models2D[type] = new Model2D(type);
		}
		aux = models2D[type];


		return aux;
	}

	ModelPhisic* getModelPhisics(Core::Entities::Type type){
		ModelPhisic *aux = NULL;
		if (modelsPhisics[type]==NULL){
			modelsPhisics[type] = new ModelPhisic(type, getModel2DObject(type)->getShape());
		}
		aux = modelsPhisics[type];


		return aux;
	}

	World* getWorld(){
		return world;
	}

private:
	vector<Model2D*> models2D;
	vector<ModelPhisic*> modelsPhisics;
	//Model2D *player;
	World* world;
};



#endif /* RESOURCEMANAGER_H_ */
