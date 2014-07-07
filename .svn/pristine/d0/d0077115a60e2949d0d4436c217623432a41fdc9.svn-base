/*
 * TControlMenu.cc
 *
 *  Created on: 19/01/2012
 *      Author: Chutaos Team
 */

#include "TForm.h"

//FUNCIONES DE FORM//
TForm::TForm() {
	panel = NULL;
	world = new World();
	widgets.clear();
	center=true;
	width = 200;
	height = 400;

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
	color = Color<float>(0.3,0.3,0.3,0.9);
	panel = new Polygon(Point(),puntos);
	element = Core::Element::e_form;

}

TForm::TForm(int width_, int height_, Point center_) {
	panel = NULL;
	world = new World();
	widgets.clear();
	center=true;
	width = width_;
	height = height_;

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
	color = Color<float>(0.3,0.3,0.3,0.9);
	panel = new Polygon(center_,puntos);

	element = Core::Element::e_form;
}


TForm::~TForm() {
	if (panel != NULL)
	{
		delete panel;
		panel = NULL;
	}

	world = NULL;
	/*if (world != NULL)
	{
		delete world;
		world = NULL;
	}
	for (unsigned int i = 0; i < widgets.size(); i++) {
		delete widgets[i];
		widgets[i] = NULL;
	}*/
	widgets.clear();
}

TForm::TForm(const TForm & form) {
	if (form.panel != NULL){
		panel = new Polygon(*form.panel);
	} else {
		panel = NULL;
	}
	if (form.world != NULL){
		world = form.world;
	} else {
		world = NULL;
	}
	width = form.width;
	height = form.height;
	center=form.center;
	color = form.color;

	for (unsigned int i = 0; i < form.widgets.size(); i++) {
		if (form.widgets[i] != NULL)
		{
			/*TButton *tmp = NULL;
			Body *bodyAux = NULL;*/
			switch(form.widgets[i]->getWidget())
			{
			case Core::Widget::w_button:
				widgets.push_back(new TButton(*((TButton*)form.widgets[i])));
				break;
			case 			Core::Widget::w_label:
				widgets.push_back(new TLabel(*((TLabel*)form.widgets[i])));
				break;
			default:
				cerr<<"Warning: Widget con tipo none no copiado"<<endl;
				break;
			}
		}
	}

	element = Core::Element::e_form;
}

TForm& TForm::operator =(const TForm & form) {
	if(this!=&form)
	{
		this->~TForm();
		if (form.panel != NULL){
			panel = new Polygon(*form.panel);
		} else {
			panel = NULL;
		}
		if (form.world != NULL){
			world = form.world;
		} else {
			world = NULL;
		}
		width = form.width;
		height = form.height;
		center=form.center;
		color = form.color;

		for (unsigned int i = 0; i < form.widgets.size(); i++) {
			if (form.widgets[i] != NULL)
			{
				switch(form.widgets[i]->getWidget())
				{
				case Core::Widget::w_button:
					widgets.push_back(new TButton(*((TButton*)form.widgets[i])));
					break;
				case Core::Widget::w_label:
					widgets.push_back(new TLabel(*((TLabel*)form.widgets[i])));
					break;
				default:
					cerr<<"Warning: Widget con tipo none no copiado"<<endl;
					break;
				}
			}
		}

		element = Core::Element::e_form;
	}
	return *this;
}

void TForm::addWidget(TWidget* widget_)
{
	Polygon* pol = NULL;
	Body *bod = NULL;
	Point cent;
	if (widgets.empty()){
		if(center)
		{
			cent.setX(panel->getCentro().getX());
		}else
		{
			cent.setX((panel->getCentro().getX()-width/2)+widget_->getMarginLeft());
		}
		cent.setY(( panel->getCentro().getY()-(height/2) )+widget_->getMarginUp());
		pol = new Polygon(cent,widget_->getShape()->getPuntos());

	}else{
		TWidget *ultimo = widgets.back();
		int ultY = ultimo->getShape()->getCentro().getY();
		int ultX = ultimo->getShape()->getCentro().getX();
		int ultMarg = ultimo->getMarginBottom();
		cent.setY((ultY + ultMarg)+widget_->getMarginUp());
		cent.setX(ultX);
		pol = new Polygon(cent,widget_->getShape()->getPuntos());
	}
	//Fisica
			Point c(0,0);
			//c.setY(-c.getY());
			BodyData *auxBody = new BodyData(*pol,b2_staticBody);
			bod = new Body(*world,*auxBody);
			bod->setPosition(c);
			widget_->setPhisicShape(bod);

	widget_->setShape(pol);
	widgets.push_back(widget_);
}

void TForm::Draw()
{
	DrawSolidPolygon(*panel, color);
	vector<TWidget*>::iterator iter;
	for (iter = widgets.begin(); iter != widgets.end(); iter++){
		(*iter)->Draw();
	}
}

TWidget *TForm::whoIsClicked(Point point)
{
	TWidget *clicked = NULL;
	vector<TWidget*>::iterator iter;
	for (iter = widgets.begin(); iter != widgets.end(); iter++){
		if ((*iter)->getPhisicShape()->TestPoint(point)){
			clicked = (*iter);
			break;
		}else{
			(*iter)->setClicked(false);
			(*iter)->setOver(false);
		}
	}
	return clicked;
}

Color<float> TForm::getColor() const
{
    return color;
}

Polygon *TForm::getPanel() const
{
    return panel;
}

vector<TWidget*> TForm::getWidgets() const
{
    return widgets;
}

World *TForm::getWorld() const
{
    return world;
}

void TForm::setColor(Color<float> color)
{
    this->color = color;
}

void TForm::setPanel(Polygon *panel)
{
    this->panel = panel;
}

void TForm::setWidgets(vector<TWidget*> widgets)
{
    this->widgets = widgets;
}

void TForm::setWorld(World *world)
{
    this->world = world;
}

void TForm::Update(int frameTime)
{
	world->setFrame(frameTime);
	world->UpdateWorld();
	vector<TWidget*>::iterator iter;
	for (iter = widgets.begin(); iter != widgets.end(); iter++){
		if ((*iter)->isOver()){
			(*iter)->setOver(false);
		}
	}

}

int TForm::getHeight() const
{
    return height;
}

int TForm::getWidth() const
{
    return width;
}

bool TForm::isCenter() const
{
    return center;
}

void TForm::centerForm(bool center_)
{
	center=center_;
}

void TForm::setHeight(int height)
{
    this->height = height;
}

void TForm::setWidth(int width)
{
    this->width = width;
}

void TForm::removeWorld()
{
	if (world!=NULL){
		delete world;
	}
}
