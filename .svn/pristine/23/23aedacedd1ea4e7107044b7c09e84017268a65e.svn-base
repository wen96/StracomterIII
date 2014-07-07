/*
 * TCheckBox.cc
 *
 *  Created on: 19/04/2012
 *      Author: Chutaos Team
 */

#include "TCheckBox.h"

TCheckBox::TCheckBox() {
	position = Point();
	checked = false;
	text = "";
	shapeCheck = Polygon();
	shapeCheckInside = Polygon();
	font.setFont(Graphics::Font::tf2);
}

TCheckBox::TCheckBox(Point p, string text_){
	position = p;
	text = text_;
	width = 100;
	height = 20;
	checked = false;

	int x=width/2,y=height/2;
	vector<Point> vect;
	Point aux;
	aux.setXY(x,y);
	vect.push_back(aux);
	aux.setXY(-x,y);
	vect.push_back(aux);
	aux.setXY(-x,-y);
	vect.push_back(aux);
	aux.setXY(x,-y);
	vect.push_back(aux);

	this->shape = new Polygon(Point(),vect);

	marginUp = height/2;
	marginBottom = height/2;
	marginRight = width/2;
	marginLeft = width/2;

	color = Color<float>(0.8,0.8,1);
	colorOver = Color<float>(0.8,0.8,1);
	colorClicked = Color<float>(0.6,0.6,1);


	vect.clear();
	aux = p;
	aux.setXY(aux.getX()+17,aux.getY()+15);
	aux.setX(aux.getX()-5);
	vect.push_back(aux);
	aux.setX(aux.getX()-10);
	vect.push_back(aux);
	aux.setY(aux.getY()-10);
	vect.push_back(aux);
	aux.setX(aux.getX()+10);
	vect.push_back(aux);
	shapeCheck = Polygon(Point(),vect);
	vect.clear();
	aux = p;
	aux.setXY(aux.getX()+17,aux.getY()+15);
	aux.setY(aux.getY()-2);
	aux.setX(aux.getX()-7);
	vect.push_back(aux);
	aux.setX(aux.getX()-6);
	vect.push_back(aux);
	aux.setY(aux.getY()-6);
	vect.push_back(aux);
	aux.setX(aux.getX()+6);
	vect.push_back(aux);
	shapeCheckInside = Polygon(Point(),vect);
	font.setColor(Color<float>(0,0,0,1));
	font.setFont(Graphics::Font::tf2);
	font.setSize(15);
	widget = Core::Widget::w_checkBox;
}

void TCheckBox::setBody(World *w){
	BodyData *bd = new BodyData(*shape,b2_staticBody);
	Body *bod = new Body(*w,*bd);
	bod->setPosition(Point(position.getX()+(width/2),position.getY()+(height/2)));
	phisicShape = bod;
}

void TCheckBox::Draw(){
	Point aux = position;
	if (isVisible()) {
		aux.setXY(aux.getX()+20,aux.getY()+15);
		font.renderText(text,aux);
		DrawSolidPolygon(shapeCheck,Color<float>(1,1,1));
		if (this->checked){

			DrawSolidPolygon(shapeCheckInside,Color<float>(0,0,0));
		}
	}
//	glPushMatrix();
//		glTranslated(position.getX()+(width/2), position.getY()+(height/2), 0);
//		DrawPolygon(*shape,Color<float>(1,0,0));
//	glPopMatrix();
}

TCheckBox::~TCheckBox() {
	position = Point();
	checked = false;
	text = "";
	shapeCheck = Polygon();
	shapeCheckInside = Polygon();
}

Point TCheckBox::getPosition() const
{
    return position;
}

Polygon TCheckBox::getShapeCheck() const
{
    return shapeCheck;
}

Polygon TCheckBox::getShapeCheckInside() const
{
    return shapeCheckInside;
}

string TCheckBox::getText() const
{
    return text;
}

bool TCheckBox::isChecked() const
{
    return checked;
}

void TCheckBox::setChecked(bool checked_)
{
    this->checked = checked_;
}

void TCheckBox::setPosition(Point position)
{
    this->position = position;
}

void TCheckBox::setShapeCheck(Polygon shapeCheck)
{
    this->shapeCheck = shapeCheck;
}

void TCheckBox::setShapeCheckInside(Polygon shapeCheckInside)
{
    this->shapeCheckInside = shapeCheckInside;
}

void TCheckBox::switchCheck()
{
	if (enable){
		checked = !checked;
	}
}

void TCheckBox::setText(string text)
{
    this->text = text;
}



