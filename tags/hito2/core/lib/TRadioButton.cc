/*
 * TRadioButton.cc
 *
 *  Created on: 15/03/2012
 *      Author: gallardo
 */

#include "TRadioButton.h"

TRadioButton::TRadioButton(int num) {
	widget=Core::Widget::w_button;
	for(int i=0; i<num;i++)
	{
		buttons.push_back(TButton());
		(buttons[i].getText())->setVisible(false);
	}
	shape = new Polygon(Point(),3);
}

TRadioButton::~TRadioButton() {
	// TODO Auto-generated destructor stub
}

int TRadioButton::whoIsClicked(Point mouse) {

	int clicked = -1;

	for (unsigned int i=0; i< buttons.size(); i++){
		if (buttons[i].getPhisicShape()->TestPoint(mouse)){
			clicked = i;
			break;
		}else{
			buttons[i].setClicked(false);
			buttons[i].setOver(false);
		}
	}
	return clicked;
}


void TRadioButton::Draw() {

	for(unsigned int i=0; i<buttons.size(); i++)
	{
		buttons[i].Draw();
	}
}


void TRadioButton::setPhisicShape(Body *phisicShape)
{
    this->phisicShape = phisicShape;
    world = phisicShape->getWorld();
    Body * bod;
	BodyData *auxBody;
	Point c(0,0);
	for(unsigned int i=0; i<buttons.size();i++)
	{
		auxBody = new BodyData(*buttons[i].getShape(),b2_staticBody);
		bod = new Body(*world,*auxBody);
		bod->setPosition(c);
		buttons[i].setPhisicShape(bod);
	}
}
