/*
 * Scene.cc
 *
 *  Created on: 04/11/2011
 *      Author: Chutaos Team
 */

#include "Scene.h"

Scene::Scene(EntityManager *entities_, ResourceManager *resources_, float w,
		float h) {
	entities = entities_;
	resources = resources_;
	widht = w;
	height = h;
	Transform tmp;
	escalado = tmp;
	hud = Camera(w, h, -1, 2000);
	hud.setScale(w / 2);
	hud.setOrtho();
	game = Camera(w, h, -1, 2000);
	game.setScale(w / 2);
	game.setOrtho();
	//resources->loadModels();

	mapa = Camera(200, 150, -1, 2000, Point(600, 450));
	mapa.setScale(100);
	mapa.setOrtho();

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

Scene::~Scene() {
	// TODO Auto-generated destructor stub
}

void Scene::Init(AI *ia_){

	ia = ia_;
	resources->loadModels();

	/*glEnable(GL_BLEND);
	glEnable(GL_POLYGON_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);*/
	//glEnable(GL_DEPTH_TEST);

}


void Scene::Draw() {


	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	Entity *aux = entities->getPlayer();
	Point p_player;
	if (aux != NULL){
		lastPositionPlayer = p_player = aux->getCenter();
	}else{
		p_player = lastPositionPlayer;
	}
	Reshape(p_player, 0);

	for (int reshape = 0; reshape < 3; reshape++) {
		Reshape(p_player, reshape);
		////cout << "Llamo a CallList" << Core::Entities::e_enemy1 << endl;
		//glLoadName(0);
		//glCallList(1);
		//glLoadName(Core::Entities::e_enemy1);
		/*glBegin(GL_POLYGON);
					//DrawPolygon(*aux->getShape(), Color<float>(1,0,0));
				glVertex2d(50,50);
				glVertex2d(50,100);
				glVertex2d(100,100);
				glVertex2d(100, 50);
		glEnd();*/

		if (entities != NULL && resources != NULL) {
			vector<Entity*> ent = entities->getEntities();
			Polygon *pol = NULL;

			vector<Point> aux;
			Core::Entities::Type t;
			Entity *player = entities->getPlayer();
			Point p;
			if (player != NULL) {
				lastPositionPlayer = p = player->getCenter();
				p.setY(p.getY() - 40);
				p.setX(p.getX() - 30);
			}else{
				p = lastPositionPlayer;
				p.setY(p.getY() - 40);
				p.setX(p.getX() - 30);
			}
			Point result(5, 20);
			////cout << p << endl;

			string text = "C A P T A IN";
			//DrawText(p, text, Color<float>(1.0,0.0,0.0), 5);


			//Reshape(p_player, reshape);
			if (reshape != 1) {

				// Pintamos cosas de debuging (la triangulacion)
				if(debugOn){

					NavGraph *dualGraph = ia->getTriangulation();
					Color<float> color(0,0.7,1);
					std::vector<ASNode>::iterator niter;
					for (niter = dualGraph->nodes.begin(); niter != dualGraph->nodes.end();niter++) {
						DrawPoint((*niter).getPosition(), color, 1.0);

						std::vector<ASNode>::iterator asiter;
						std::vector<ASNode> vASNodes = dualGraph->getAdyacence((*niter).getId());
						for (asiter = vASNodes.begin(); asiter != vASNodes.end();asiter++) {

							//DrawLine((*niter)->getPosition(), (*asiter).getPosition(), color, 1);
							DrawLine((*niter).getPosition(), (*asiter).getPosition(), color,1);
						}

					}
				}

				for (unsigned int i = 0; i < ent.size(); i++) {

					t = ent[i]->getType();

					if (reshape == 0) {
						//Si es un bot
						if ((t == Core::Entities::e_enemy1
								|| t == Core::Entities::e_enemy2
								|| t == Core::Entities::e_especialist
								|| t == Core::Entities::e_tecnic
								|| t == Core::Entities::e_explosive
								|| t == Core::Entities::e_captain
								|| t == Core::Entities::e_enemy3
								|| t == Core::Entities::e_miniboss
								|| t == Core::Entities::e_megaboss) &&
								t != entities->playerType) {
							glLoadIdentity();
							Point forlife = ((Character*) ent[i])->getCenter();
							forlife.setY(forlife.getY() - 40);
							char vida[10];
							sprintf(vida, "%d", ((Character*) ent[i])->getHp());
							DrawText(forlife, vida, Color<float>(1.0, 0.0, 0.0),
									5);
							forlife.setY(forlife.getY() + 80);
							char id[10];
							sprintf(id, "%d", ((Character*) ent[i])->getId());
							DrawText(forlife, id, Color<float>(1.0, 0.0, 0.0),
									5);
							DrawLine(((Character*) ent[i])->getCenter(),
									((Character*) ent[i])->laser.point,
									Color<float>(0.7, 0.0, 0.0, 0.3), 3);
							if (((Character*) ent[i])->isShooting()) {
								((Character*) ent[i])->setShooting(false);
								DrawLine(((Character*) ent[i])->getCenter(),
										((Character*) ent[i])->laser.point,
										Color<float>(0.7, 0.7, 0.0, 0.8), 3);
							}

							Tri v = ((Bot *) ent[i])->getVision();
							Color<float> colorCono(0,1,0,.1);
								if(!((Bot *) ent[i])->isBlind()){
									DrawTriangle(v.getA(), v.getB(), v.getC(), colorCono);
								}else{
									DrawLine(v.getA(), v.getB(), colorCono);
									DrawLine(v.getB(), v.getC(), colorCono);
									DrawLine(v.getC(), v.getA(), colorCono);
								}
								vector<Point> path = ((Bot *) ent[i])->getPath();
								colorCono =  Color<float>(1,0.4,0,1);
								if (path.size()>1){
									vector<Point>::iterator iterPath;
									////cout << "Size: " << path.size() << endl;
									for (iterPath = (path.begin()+1); iterPath != path.end(); iterPath++){
										////cout << "Dibujo: " << (*(iterPath-1)) << " | " <<  (*iterPath) << endl;
										DrawLine((*(iterPath-1)), (*iterPath),colorCono, 3);
									}
								}
						}
					}

					if(t == Core::Entities::e_wall){
						vector<Point> vaux = ((Wall *)ent[i])->getPoints();
						for(int i = 0; i < 4; i++) vaux.pop_back();
						pol = new Polygon(vaux);
					}else if(t == Core::Entities::e_floor){
						pol = new Polygon(((Floor *)ent[i])->getPoints());
					}else{
						pol = resources->getModel2DObject(t)->getShape();
					}

					Transform tx;
					tx.addTranslation(ent[i]->getCenter());
					tx.addRotationZ(ent[i]->getAngle());



					glLoadIdentity();
					//escalado.loadOpenGL();
					tx.exportOpenGL();

					//ent[i]->setCenter(Point(ent[i]->getCenter().getX()*escalado.getSx(), ent[i]->getCenter().getY()*escalado.getSy()));
					//ent[i]->body->body->SetTransform(b2Vec2(ent[i]->body->body->GetTransform().p.x*escalado.getSx(), ent[i]->body->body->GetTransform().p.y*escalado.getSy()), ent[i]->body->body->GetTransform().q.GetAngle());
					//DrawText(ent[i]->getCenter(), text, ent[i]->getColor(), 2);

					/*if(t == Core::Entities::e_enemy1
						|| t == Core::Entities::e_enemy2
						|| t == Core::Entities::e_enemy3)
					{
						glCallList(t);
					}
					else if (t != Core::Entities::e_pointer && pol != NULL)
						DrawSolidPolygon(*pol, ent[i]->getColor());
					else if (pol != NULL && reshape == 0){
						DrawPolygon(*pol, ent[i]->getColor());
					}*/
					if(t == Core::Entities::e_wall || t == Core::Entities::e_floor)
					{
						if (pol != NULL && reshape != 1)
								DrawPolygon(*pol, ent[i]->getColor());
					}else
					{
						if(t != Core::Entities::e_pointer || reshape == 0){
							DrawPolygon(*resources->getModel2DObject(t)->getShape(), ent[i]->getColor());

							ent[i]->getColor().exportOpenGL();
							glCallList(t);
						}
					}

				}

				if (reshape == 0) {
					if (player != NULL) {
						glLoadIdentity();
						DrawText(p, text, Color<float>(1.0, 0.0, 0.0), 5);
						DrawLine(player->getCenter(),
								((Player*) player)->laser.point,
								Color<float>(0.7, 0.0, 0.0, 0.3), 3);
						if (((Character*) player)->isShooting()) {
							((Character*) player)->setShooting(false);
							DrawLine(player->getCenter(),
									((Player*) player)->laser.point,
									Color<float>(0.7, 0.7, 0.0, 0.8), 3);
						}
					}
				}
			}
			if (reshape == 1) {
				//HUD

				//glFlush();
				//Reshape(p_player,1);
				glLoadIdentity();

				text = "P U N T U A C IO N : ";
				string tmp = "";
				int number;
				if (player != NULL)
					number = ((Player*) player)->getScore();
				while (number > 0) {
					tmp += number % 10 + 48;
					number /= 10;
				}
				if (tmp == "")
					tmp = "0";
				for (int j = tmp.length(); j >= 0; j--)
					text += tmp[j];
				DrawText(result, text, Color<float>(0.678431, 1, 0.184314), 5);

				text = "H P : ";
				tmp = "";
				if (player != NULL)
					number = ((Player*) player)->getHp();
				while (number > 0) {
					tmp += number % 10 + 48;
					number /= 10;
				}
				if (tmp == "")
					tmp = "0";
				for (int j = tmp.length(); j >= 0; j--)
					text += tmp[j];
				DrawText(Point(5, 40), text,
						Color<float>(0.678431, 1, 0.184314), 5);

				//Reshape(player->getCenter(),0);
				//glLoadIdentity();

				//HUD

			}
		}
	}
	Reshape(p_player, 0);
	glFlush();
	Reshape(p_player, 0);
}

void Scene::DrawModeEditor(){

	if (entities != NULL && resources != NULL) {
		vector<Entity*> ent = entities->getEntities();
		Polygon *pol = NULL;

		vector<Point> aux;
		Core::Entities::Type t;

		for (unsigned int i = 0; i < ent.size(); i++) {


			t = ent[i]->getType();


			if(t == Core::Entities::e_wall){
				vector<Point> vaux = ((Wall *)ent[i])->getPoints();
				for(int i = 0; i < 4; i++) vaux.pop_back();
				pol = new Polygon(vaux);
			}else if(t == Core::Entities::e_floor){
				pol = new Polygon(((Floor *)ent[i])->getPoints());
			}else{
				pol = resources->getModel2DObject(t)->getShape();
			}

			Transform tx;
			tx.addTranslation(ent[i]->getCenter());
			tx.addRotationZ(ent[i]->getAngle());
			tx.exportOpenGL();

			if (t != Core::Entities::e_pointer && pol != NULL){
				DrawSolidPolygon(*pol, ent[i]->getColor());
			}
		}
	}
}

void Scene::DrawMenu(TForm *menu) {

	Entity *aux = entities->getPlayer();
	Point p_player;
	if (aux != NULL){
		lastPositionPlayer = p_player = aux->getCenter();
	}else{
		p_player = lastPositionPlayer;
	}

	Reshape(p_player, 1);

	menu->Draw();

	Reshape(p_player, 0);
	Entity* ent = entities->getPointer();
	Polygon *pol = resources->getModel2DObject(Core::Entities::e_pointer)->getShape();
	if (ent!=NULL){
		Transform tx;
		tx.addTranslation(ent->getCenter());
		tx.addRotationZ(ent->getAngle());
		glLoadIdentity();
		tx.exportOpenGL();

		if (pol != NULL){
			DrawPolygon(*pol, ent->getColor());
		}
	}

}

void Scene::Reshape(Point player, int modo) {

	Transform t;
	t.setProjection();
	int x = player.getX();
	int y = player.getY();

	switch (modo) {
	case 0:
		game.exportOpenGL();

		t.addTranslation(-x + widht / 2, y - height / 2, -10);
		t.addScale(1, -1, 1);
		t.addTranslation(-1.0 * widht / 2, -1.0 * height / 2, 0);
		//t.addRotationX(-30);
		t.addOpenGL();
		break;
	case 1:
		hud.exportOpenGL();
		t.addScale(1, -1, 1);
		t.addTranslation(-1.0 * widht / 2, -1.0 * height / 2, 0);
		t.addOpenGL();

		glColor3d(0.1, 0.1, 0.1);
		glBegin(GL_POLYGON);
		glVertex2d(800, 150);
		glVertex2d(800, 0);
		glVertex2d(599, 0);
		glVertex2d(599, 150);
		glEnd();

		glColor3d(1, 1, 1);
		glBegin(GL_LINE_LOOP);
		glVertex2d(800, 150);
		glVertex2d(800, 0);
		glVertex2d(599, 0);
		glVertex2d(599, 150);
		glEnd();
		break;
	case 2:
		mapa.exportOpenGL();
		t.addTranslation((-x + widht / 2) * 0.15, (y - height / 2) * 0.15, 0);
		t.addScale(1, -1, 1);
		t.addScale(0.15, 0.15, 0.15);
		t.addTranslation(-widht / 2, -1.0 * height / 2, 0);

		t.addOpenGL();
		break;
	}

	////cout << x << " " << y << endl;
	/*glViewport(0,0, widht, height);
	 glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
	 glOrtho(0, widht, 0, height, -1, 1);*/

	/*glTranslated(-x+widht/2,y-height/2,0);
	 glTranslated(-x,y,0);
	 glScalef(1, -1, 1);
	 glTranslatef(-1.0*widht/2, -1.0*height/2, 0);*/

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
}


bool Scene::isDebugOn() const {
	return debugOn;
}

void Scene::setDebugOn(bool debugOn) {
	this->debugOn = debugOn;
}



