/*
 * Scene.cc
 *
 *  Created on: 04/11/2011
 *      Author: Chutaos Team
 */

#include "Scene.h"

Scene::Scene(EntityManager *entities_, ResourceManager *resources_, float w, float h) {
	entities = entities_;
	resources = resources_;
	widht = w;
	height = h;
	Transform tmp;
	escalado = tmp;
}

Scene::~Scene() {
	// TODO Auto-generated destructor stub
}

void Scene::Draw(){

	glEnable (GL_BLEND);
	glEnable (GL_POLYGON_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (entities != NULL && resources != NULL){
		vector<Entity*> ent = entities->getEntities();
		Polygon *pol = NULL;

		vector<Point> aux;
		Core::Entities::Type t;
		Entity *player = entities->getPlayer();
		Point p = player->getCenter();
		Point result(5, 20);
		//cout << p << endl;
		p.setY(p.getY() - 40);
		p.setX(p.getX() - 30);
		string text = "C A P T A IN";
		//DrawText(p, text, Color<float>(1.0,0.0,0.0), 5);
		for (unsigned int i = 0; i < ent.size(); i++){

			t = ent[i]->getType();
			pol = resources->getModel2DObject(t)->getShape();

			Transform tx;
			tx.loadTranslation(ent[i]->getCenter());
			tx.loadRotation(ent[i]->getAngle(), 0.0, 0.0, 1.0);

			glLoadIdentity();
			//escalado.loadOpenGL();
			tx.loadOpenGL();

			//ent[i]->setCenter(Point(ent[i]->getCenter().getX()*escalado.getSx(), ent[i]->getCenter().getY()*escalado.getSy()));
			//ent[i]->body->body->SetTransform(b2Vec2(ent[i]->body->body->GetTransform().p.x*escalado.getSx(), ent[i]->body->body->GetTransform().p.y*escalado.getSy()), ent[i]->body->body->GetTransform().q.GetAngle());
			//DrawText(ent[i]->getCenter(), text, ent[i]->getColor(), 2);

			if (pol != NULL)
				DrawSolidPolygon(*pol, ent[i]->getColor());

		}
		glLoadIdentity();
		DrawText(p, text, Color<float>(1.0,0.0,0.0), 5);
		glLoadIdentity();
		text = "P u n t u a c i o n  : ";
		string tmp = "";
		int number = ((Player*)player)->getHp()-100;
		while (number>0)
		{
			tmp+=number%10+48;
			number/=10;
		}
		if(tmp == "")
			tmp = "0";
		for(int j = tmp.length(); j >= 0; j--)
			text += tmp[j];
		DrawText(result, text, Color<float>(0.678431, 1, 0.184314), 5);
	}

	glFlush();
}

void
Scene::Reshape(float w, float h) {

	glViewport(0,0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, 0, h, -1, 1);
	/*if(widht == 0 || height == 0)
	{
		widht = w;
		height = h;
		escalado.loadIdentity();
	}
	else if(w != widht || h != height)
	{
		escalado.loadScale((float)w/(float)widht, (float)h/(float)height, 1);
	}else
	{
		escalado.loadIdentity();
	}*/

	//escalado.loadTranslation(0, -1.0*h, 0);
	//escalado.loadOpenGL();
	glScalef(1, -1, 1);
	glTranslatef(0, -1.0*h, 0);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


