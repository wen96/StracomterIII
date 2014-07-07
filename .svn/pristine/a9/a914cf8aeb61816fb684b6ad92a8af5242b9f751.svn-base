/*
 * HIDControl.cc
 *
 *  Created on: 17/11/2011
 *      Author: Chutaos Team
 */

#include "HIDControl.h"

HIDControl::HIDControl(IOControl *events_) {
	events = events_;
}

HIDControl::~HIDControl() {

}

void HIDControl::actionControl(EntityManager *entities) {
	//Prubea de teclas y color, provisional

		Entity *player = entities->getPlayer();
		if (IsPressUp()){
			player->body->addLinearVelocity(Force(0,-50));
		}
		if (IsPressDown()){
			player->body->addLinearVelocity(Force(0,50));
		}
		if (IsPressRight()){
			player->body->addLinearVelocity(Force(50,0));
		}
		if (IsPressLeft()){
			player->body->addLinearVelocity(Force(-50,0));
		}
		if (IsPressAction()){
			player->body->addAngle(1);
		}
		if((*events).IsKeyDown(Core::Key::Space)) {

			if(entities->getEntitiesbyType(Core::Entities::e_enemy2).size() < 10)
			{
				int x, y;
				int rad = 30;
				float a = rand()%100/(double)75 + 0.25;
				Color<float> c_enemy(1,0,0,a);
				x = rand()%(640- 2*rad) + rad;
				y = rand()%(480- 2*rad) + rad;

				entities->addEnemy(Point(x,y), rad, c_enemy);
			}
		}

		//Rajuste a las cordandas reales
		float x = ((*events).GetMouseX());
		float y = ((*events).GetMouseY());

		//Point c;
		bool intersecta = false;
		RayData ray;
		Color<float> c_mirilla(0.0,1.0,0.0);

		Point mouse(x,y);

		//PROLONGACIÓN DEL RAYO
		/*float ax = cos(player->getAngle()*M_PI/180);
		float ay = sin(player->getAngle()*M_PI/180);
		float px;
		if(ax != 0)
			px = player->getCenter().getX()/ax;
		else
			px = player->getCenter().getX()/0.00001;
		float py;
		if(ay != 0)
			py = player->getCenter().getX()/ay;
		else
			py = player->getCenter().getX()/0.00001;

		px = abs(px);
		py = abs(py);

		if(px > py)
		{
			mouse.setX(mouse.getX() + 2*px*cos(player->getAngle()*M_PI/180));
			mouse.setY(mouse.getY() + 2*px*sin(player->getAngle()*M_PI/180));
		}
		else
		{
			mouse.setX(mouse.getX() + 2*py*cos(player->getAngle()*M_PI/180));
			mouse.setY(mouse.getY() + 2*py*sin(player->getAngle()*M_PI/180));
		}*/
		int max = 0;
		ray = entities->getResourceManager()->getWorld()->RayBody(player->getCenter(), mouse);
		while(!ray.hit && max < 1000)
		{
			mouse.setX(mouse.getX() + cos(player->getAngle()*M_PI/180));
			mouse.setY(mouse.getY() + sin(player->getAngle()*M_PI/180));
			ray = entities->getResourceManager()->getWorld()->RayBody(player->getCenter(), mouse);
			max++;
		}

		if((*events).isMouseButtonDown(sf::Mouse::Left))
		{

			vector<Entity*> en = entities->getEntitiesbyType(Core::Entities::e_enemy2);
			ray = entities->getResourceManager()->getWorld()->RayBody(player->getCenter(), mouse);
			if(ray.hit)
			{
				for(unsigned int i = 0; i < en.size() && !intersecta; i++)
				{
					if(en[i]->body->getBody() == ray.body)
					{
						DrawLine(player->getCenter(), ray.point, Color<float>(1.0,0.0,0.0), 5);
						entities->removeEnemy(en[i]->getId());
						((Player*)player)->setHp(((Player*)player)->getHp()+1);
						intersecta = true;
					}

				}
			}


		}
		else
			ray = entities->getResourceManager()->getWorld()->RayBody(player->getCenter(), mouse);



		((Player*)player)->generateVisionRotation(Point(x,y));

		if(!ray.hit)
			DrawLine(player->getCenter(), mouse, c_mirilla);
		else
			DrawLine(player->getCenter(), ray.point, c_mirilla);

		Color<float> color(0.0,0.0,1.0);
		Point cursor(Point(x,y));
		Polygon pol(cursor, 10);
		DrawPolygon(pol, color);

}

bool HIDControl::IsPressUp() {
	return (*events).IsKeyDown(Core::Key::W);
}

bool HIDControl::IsPressDown() {
	return (*events).IsKeyDown(Core::Key::S);
}

bool HIDControl::IsPressLeft() {
	return (*events).IsKeyDown(Core::Key::A);
}

bool HIDControl::IsPressRight() {
	return (*events).IsKeyDown(Core::Key::D);
}

bool HIDControl::IsPressAction() {
	return (*events).IsKeyDown(Core::Key::E);
}

bool HIDControl::IsPressPause() {
	return (*events).IsKeyDown(Core::Key::P);
}



