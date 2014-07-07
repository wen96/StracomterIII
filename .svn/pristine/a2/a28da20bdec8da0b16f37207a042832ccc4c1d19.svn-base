/*
 * TControlMenu.cc
 *
 *  Created on: 19/01/2012
 *      Author: Chutaos Team
 */

#include "TWidget.h"

TWidget::TWidget()
{
	widget= Core::Widget::w_none;
	shape = NULL;
	phisicShape = NULL;
	enable = true;
	visible = true;
	evento = -1;
	marginUp = 0;
	marginBottom = 0;
	marginLeft = 0;
	marginRight = 0;
	world = NULL;
}



TWidget::~TWidget()
{
	if (shape!=NULL){
		delete shape;
	}

	if (phisicShape!=NULL){
		delete phisicShape;
	}

	shape = NULL;
	phisicShape = NULL;
	enable = true;
	visible = true;
	evento = -1;
}



TWidget::TWidget(const TWidget & widget_)
{
	if (widget_.shape != NULL){
		shape = new Polygon(*widget_.shape);
	}else{
		shape = NULL;
	}
	world = widget_.world;

	if (widget_.phisicShape != NULL){
		//phisicShape = new Body(world,widget_.getShape());
		phisicShape = new Body(*(widget_.phisicShape));
	}else{
		phisicShape = NULL;
	}
	enable = widget_.enable;
	visible = widget_.visible;
	evento = widget_.evento;
	color = widget_.color;
	colorOver = widget_.colorOver;
}



TWidget& TWidget::operator=(const TWidget & widget_)
{
	if (this != &widget_){
		this->~TWidget();
		if (widget_.shape != NULL){
			shape = new Polygon(*widget_.shape);
		}else{
			shape = NULL;
		}

		if (widget_.phisicShape != NULL){
			phisicShape = new Body(*widget_.phisicShape);
		}else{
			phisicShape = NULL;
		}
		color = widget_.color;
		enable = widget_.enable;
		visible = widget_.visible;
		evento = widget_.evento;
		colorOver = widget_.colorOver;
	}
	return *this;
}

bool TWidget::isInside(Point point) const
{
	bool inside = false;


	return inside;
}

Color<float> TWidget::getColor() const
{
    return color;
}

int TWidget::getEvento() const
{
    return evento;
}

Body *TWidget::getPhisicShape() const
{
    return phisicShape;
}

Polygon *TWidget::getShape() const
{
    return shape;
}

bool TWidget::isEnable() const
{
    return enable;
}

bool TWidget::isVisible() const
{
    return visible;
}

void TWidget::setColor(Color<float> color)
{
    this->color = color;
}

void TWidget::setEnable(bool enable)
{
    this->enable = enable;
}

void TWidget::setEvento(int evento)
{
    this->evento = evento;
}

void TWidget::setPhisicShape(Body *phisicShape)
{
    this->phisicShape = phisicShape;
}

void TWidget::setShape(Polygon *shape)
{
    this->shape = shape;
}

void TWidget::setVisible(bool visible)
{
    this->visible = visible;
}

int TWidget::getMarginUp() const
{
    return marginUp;
}

void TWidget::setMarginUp(int marginUp)
{
    this->marginUp = marginUp;
}

int TWidget::getMarginBottom() const
{
    return marginBottom;
}

void TWidget::addMarginUp(int size)
{
	marginUp+=size;
}

void TWidget::setMarginBottom(int marginBottom)
{
    this->marginBottom = marginBottom;
}

void TWidget::addMarginBottom(int size)
{
	marginBottom+=size;
}

void TWidget::addMarginRight(int size)
{
	marginRight+=size;
}

void TWidget::addMarginLeft(int size)
{
	marginLeft+=size;
}

bool TWidget::isClicked() const
{
    return clicked;
}

void TWidget::setClicked(bool clicked)
{
    this->clicked = clicked;
}

Core::Widget::Type TWidget::getWidget() const
{
    return widget;
}

void TWidget::setWidget(Core::Widget::Type widget)
{
    this->widget = widget;
}

int TWidget::getMarginLeft() const
{
    return marginLeft;
}

int TWidget::getMarginRight() const
{
    return marginRight;
}

void TWidget::setMarginLeft(int marginLeft)
{
    this->marginLeft = marginLeft;
}

void TWidget::setMarginRight(int marginRight)
{
    this->marginRight = marginRight;
}

bool TWidget::isOver() const
{
    return over;
}

void TWidget::setOver(bool over)
{
    this->over = over;
}

Color<float> TWidget::getColorOver() const
{
    return colorOver;
}

void TWidget::setColorOver(Color<float> colorOver)
{
    this->colorOver = colorOver;
}

Color<float> TWidget::getColorClicked() const
{
    return colorClicked;
}

void TWidget::setColorClicked(Color<float> colorClicked)
{
    this->colorClicked = colorClicked;
}












