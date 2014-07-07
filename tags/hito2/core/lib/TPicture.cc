/*
 * TPicture.cpp
 *
 *  Created on: 14/03/2012
 *      Author: gallardo
 */

#include "TPicture.h"

TPicture::TPicture() {

	position = Point();
	width = 0;
	height = 0;
	image = "";
	idImage = 0;


	/*Point aux;
	vector<Point>puntos;
	int x=0,y=0;
	x = width/2;
	y = height/2;
	aux.setXY(x,y);
	puntos.push_back(aux);
	aux.setXY(-x,y);
	puntos.push_back(aux);
	aux.setXY(-x,-y);
	puntos.push_back(aux);
	aux.setXY(x,-y);
	puntos.push_back(aux);

	shape = new Polygon(Point(),puntos);*/
	shape = new Polygon(Point(),1);
}

TPicture::TPicture(Point p, int w, int h, string i) {

	position = p;
	width = w;
	height = h;
	image = i;
	idImage = 1;

	Textura img(image, 1);
	idImage = img.getTexture();

	/*Point aux;
	vector<Point>puntos;
	int x=0,y=0;
	x = width/2;
	y = height/2;
	aux.setXY(x,y);
	puntos.push_back(aux);
	aux.setXY(-x,y);
	puntos.push_back(aux);
	aux.setXY(-x,-y);
	puntos.push_back(aux);
	aux.setXY(x,-y);
	puntos.push_back(aux);*/

	//shape = new Polygon(Point(),puntos);
	shape = new Polygon(Point(),1);
}

TPicture::TPicture(const TPicture& p) {
	Copiar(p);
}

TPicture::~TPicture() {
	Destructor();
}

TPicture& TPicture::operator =(const TPicture& p) {

	if(this != &p)
	{
		Destructor();
		Copiar(p);
	}

	return *this;
}

void TPicture::Draw() {

	int x = position.getX();
	int y = position.getY();

	Textura::ActivarTextura(idImage);
		glBegin(GL_QUADS);
			glColor3d(1,1,1);


			glTexCoord2d(0,0);
			glVertex2d(x,y + height);

			glTexCoord2d(0,-1);
			glVertex2d(x,y);

			glTexCoord2d(1,-1);
			glVertex2d(x + width,y);

			glTexCoord2d(1,0);
			glVertex2d(x + width,y + height);

		glEnd();
	Textura::DesactivarTextura();
}

void TPicture::Destructor() {
	position = Point();
	width = 0;
	height = 0;
	image = "";
	idImage = 0;
}

void TPicture::Copiar(const TPicture& p) {
	position = p.position;
	width = p.width;
	height = p.height;
	image = p.image;
	idImage = p.idImage;

}


