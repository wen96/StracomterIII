/*
 * TRadioButton.cc
 *
 *  Created on: 15/03/2012
 *      Author: Chutaos Team
 */

#include "TRadioButton.h"
#include <math.h>

TRadioButton::TRadioButton(int num, Point p, World* w) {
	widget=Core::Widget::w_radio;
	position = p;
	selected = -1;
	for(int i= 0; i<num; i++)
	{
		TButton *b = new TButton(p,w);
		buttons.push_back(b);
	}

	vector<Point>puntos;
	puntos.push_back(Point(120,120));
	puntos.push_back(Point(-120,120));
	puntos.push_back(Point(-120,-120));
	puntos.push_back(Point(120,-120));

	shape = new Polygon(8,Point(),120,22.5);

	BodyData *bd = new BodyData(*shape,b2_staticBody);
	Body *bod = new Body(*w,*bd);
	bod->setPosition(p);
	phisicShape = bod;
}

TRadioButton::~TRadioButton() {
	// TODO Auto-generated destructor stub
}

int TRadioButton::whoIsClicked(Point mouse) {
	int clicked = 0;

	for (unsigned int i=0; i< buttons.size(); i++){
		if (buttons[i]->getPhisicShape()->TestPoint(mouse)){
			clicked = i;
			//cout<<"MARCO BOTON: "<<i<<endl;
			//buttons[i]->setOver(true);
		}else{
			//cout<<"NO MARCO BOTON: "<<i<<endl;
			buttons[i]->setClicked(false);
			buttons[i]->setOver(false);
		}
	}
	return clicked;
}


void TRadioButton::Draw() {
	for (unsigned int i=0; i< buttons.size(); i++)
	{
		////cout<<"CLICADO: "<<selected<<endl;
		if(selected>-1)
			buttons[selected]->setClicked(true);
		buttons[i]->Draw();
	}
}

vector<TButton*> TRadioButton::getButtons() const
{
    return buttons;
}

int TRadioButton::getHeight() const
{
    return height;
}

Point TRadioButton::getPosition() const
{
    return position;
}

int TRadioButton::getSelected() const
{
    return selected;
}

int TRadioButton::getWidth() const
{
    return width;
}

void TRadioButton::setButtons(vector<TButton*> buttons)
{
    this->buttons = buttons;
}

void TRadioButton::setHeight(int height)
{
    this->height = height;
}

void TRadioButton::setPosition(Point position)
{
    this->position = position;
}

void TRadioButton::setSelected(int selected)
{
    this->selected = selected;
}

void TRadioButton::setWidth(int width)
{
    this->width = width;
}

void TRadioButton::Octogonal(int s0, int s1,int s2)
{

	Polygon pol;
	vector<Point> vP;
	int x0 = position.getX();
	int y0 = position.getY();
	int x,y;
	int radio = 120;
	double angle = 360.0/8.0 * M_PI / 180.0;
	int partes = 0;
	World *w = ((Body*)buttons[0]->getPhisicShape())->getWorld();

	vP.push_back(Point(x0,y0));
	for(int i = 0; i <= s0; i++)
	{

		x = x0 + cos(angle*partes)*radio;
		y = y0 + sin(angle*partes)*radio;

		vP.push_back(Point(x,y));
		partes++;
	}
	//cout << "PRUEBA" << endl;
	Polygon * poly = new Polygon(Point(), vP);
	buttons[0]->setShape(poly);
	//cout << *poly << endl << *buttons[0]->getShape() << endl << "FIN PRUEBA" << endl;
	BodyData *bd = new BodyData(*buttons[0]->getShape(),b2_staticBody);
	//buttons[0]->getPhisicShape()->setBodydata(bd);
	buttons[0]->setPhisicShape(new Body(*w,*bd));
	//cout << *buttons[0]->getShape() << endl;

	buttons[0]->setColor(Color<float>(0.6,0,0));
	buttons[0]->setColorOver(Color<float>(0.8,0,0));
	buttons[0]->setColorClicked(Color<float>(1,0,0));
	vP.clear();

	partes--;
	vP.push_back(Point(x0,y0));
	for(int i = 0; i <= s1; i++)
	{

		x = x0 + cos(angle*partes)*radio;
		y = y0 + sin(angle*partes)*radio;

		vP.push_back(Point(x,y));
		partes++;
	}

	buttons[1]->setShape(new Polygon(Point(), vP));
	bd = new BodyData(*buttons[1]->getShape(),b2_staticBody);
	buttons[1]->setPhisicShape(new Body(*w,*bd));
	//cout << *buttons[1]->getShape() << endl;
	//buttons[1]->getPhisicShape()->setBodydata(bd);
	buttons[1]->setColor(Color<float>(0.6,0.6,0));
	buttons[1]->setColorOver(Color<float>(0.8,0.8,0));
	buttons[1]->setColorClicked(Color<float>(1,1,0));

	vP.clear();
	partes--;

	vP.push_back(Point(x0,y0));
	for(int i = 0; i <= s2; i++)
	{

		if(partes == 8)
		{
			x = x0 + radio;
			y = y0;
		}
		else
		{
			x = x0 + cos(angle*partes)*radio;
			y = y0 + sin(angle*partes)*radio;
		}

		vP.push_back(Point(x,y));
		partes++;
	}

	buttons[2]->setShape(new Polygon(Point(), vP));
	bd = new BodyData(*buttons[2]->getShape(),b2_staticBody);
	//buttons[2]->getPhisicShape()->setBodydata(bd);
	buttons[2]->setPhisicShape(new Body(*w,*bd));
	//cout << *buttons[2]->getShape() << endl;

	buttons[2]->setColor(Color<float>(0,0.6,0));
	buttons[2]->setColorOver(Color<float>(0,0.8,0));
	buttons[2]->setColorClicked(Color<float>(0,1,0));
	vP.clear();
	//ASIGNAMOS LOS EVENTOS
	buttons[0]->setEvento(s0);
	buttons[1]->setEvento(s1);
	buttons[2]->setEvento(s2);
}


void TRadioButton::Octogonal()
{
	//Estos 3 enteros seran calculados con random
	srand(time(NULL));
	int s0 = (rand()%4)+3;
	int s1 = (8-s0)/2;
	int s2 = 8-s0-s1;
	Octogonal(s0,s1,s2);
}

