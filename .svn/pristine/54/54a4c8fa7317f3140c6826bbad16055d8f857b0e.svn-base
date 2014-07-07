/*
 * TPicture.cpp
 *
 *  Created on: 14/03/2012
 *      Author: gallardo
 */

#include "TPicture.h"

TPicture::TPicture() {
	widget = Core::Widget::w_pict;
	position = Point();
	width = 0;
	height = 0;
	image = "";
	idImage = 0;
	color = Color<float>(1,1,1,1);


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
	widget = Core::Widget::w_pict;
	position = p;
	width = w;
	height = h;
	image = i;
	idImage = 1;
	enable=false;
	Textura img(image, 1);
	idImage = img.getTexture();

	color = Color<float>(1,1,1,1);
	Point aux;
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

	shape = new Polygon(Point(),puntos);
	//shape = new Polygon(Point(),1);
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
			//glColor3d(1,1,1);
			color.exportOpenGL();


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
//	glPushMatrix();
//		glTranslated(position.getX()+(width/2), position.getY()+(height/2), 0);
//		DrawPolygon(*shape,Color<float>(1,0,0));
//	glPopMatrix();
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


void TPicture::setBody(World* w)
{
	BodyData *bd = new BodyData(*shape,b2_staticBody);
	Body *bod = new Body(*w,*bd);
	bod->setPosition(Point(position.getX()+(width/2),position.getY()+(height/2)));
	phisicShape = bod;
}

int TPicture::getHeight() const
{
    return height;
}

int TPicture::getIdImage() const
{
    return idImage;
}

string TPicture::getImage() const
{
    return image;
}

Point TPicture::getPosition() const
{
    return position;
}

int TPicture::getWidth() const
{
    return width;
}

void TPicture::setHeight(int height)
{
    this->height = height;
}

void TPicture::setIdImage(int idImage)
{
    this->idImage = idImage;
}

void TPicture::setImage(string image)
{
    this->image = image;
	Textura img(image, 1);
	idImage = img.getTexture();
}

void TPicture::setPosition(Point position)
{
    this->position = position;
}

void TPicture::setWidth(int width)
{
    this->width = width;
}


