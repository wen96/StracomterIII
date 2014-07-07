/*
 * TControlMenu.cc
 *
 *  Created on: 19/01/2012
 *      Author: Chutaos Team
 */

#include "TButton.h"

TButton::TButton()
{
	widget=Core::Widget::w_button;
	text = new TLabel(0,0,"");
	width = 150;
	height = 30;
	Point aux;
	vector<Point> puntos;
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
	text->setShape(new Polygon(Point(),puntos));
	marginUp = height/2;
	marginBottom = height/2;
	marginRight = width/2;
	marginLeft = width/2;
	color = Color<float>(0.8,0.8,0.8);
	colorOver = Color<float>(0.8,0.8,0.99);
	text->getFont().setColor(Color<float>(0,0,0));
	text->getFont().setFont(Graphics::Font::Monospace);
	text->getFont().setSize(14);
}

TButton::TButton(string caption_)
{
	widget=Core::Widget::w_button;
	text = new TLabel(150,30,caption_);
	width = 150;
	height = 30;
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
	text->setShape(new Polygon(Point(),puntos));
	marginUp = height/2;
	marginBottom = height/2;
	marginRight = width/2;
	marginLeft = width/2;
	color = Color<float>(0.8,0.8,0.8);
	colorOver = Color<float>(0.8,0.8,0.99);
	text->getFont().setColor(Color<float>(0,0,0));
	text->getFont().setFont(Graphics::Font::Monospace);
	text->getFont().setSize(14);
}

TButton::TButton(int width_, int height_, string caption_)
{
	widget=Core::Widget::w_button;
	text = new TLabel(width_,height_,caption_);
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
	shape = new Polygon(Point(),puntos);
	text->setShape(new Polygon(Point(),puntos));
	marginUp = height/2;
	marginBottom = height/2;
	marginRight = width/2;
	marginLeft = width/2;
	color = Color<float>(0.8,0.8,0.8);
	colorOver = Color<float>(0.8,0.8,0.99);
	text->getFont().setColor(Color<float>(0,0,0));
	text->getFont().setFont(Graphics::Font::Monospace);
	text->getFont().setSize(14);
}

TButton::~TButton()
{
	widget=Core::Widget::w_none;
	text->~TLabel();
}

void TButton::Draw()
{
	if (isVisible()){
		Polygon *p = new Polygon(phisicShape->getPosition(),shape->getPuntos());
		if (isEnable()){
			if (!isClicked()){
				if (isOver()){
					DrawSolidPolygon(*p,colorOver);
					//DrawSolidPolygon(*shape,Color<float>(1.0,1.0,0.0));
				}else{
					DrawSolidPolygon(*p,color);
					//DrawSolidPolygon(*shape,color);
				}
			}else{
				//Rojo intenso
				Color<float>auxColor = color;
				auxColor.setR(auxColor.getR()+0.2);
				DrawSolidPolygon(*p,auxColor);
			}
		}else{
			DrawSolidPolygon(*p,color);
		}
		text->Draw();

		delete p;
	}
}


string TButton::getCaption() const
{
    return text->getCaption();
}

int TButton::getHeight() const
{
    return height;
}

int TButton::getWidth() const
{
    return width;
}

void TButton::setCaption(string caption)
{
    text->setCaption(caption);
}

void TButton::setHeight(int height)
{
    this->height = height;
}

void TButton::setWidth(int width)
{
    this->width = width;
}

Text TButton::getFont() const
{
    return text->getFont();
}

void TButton::setFont(Text font)
{
    text->setFont(font);
}

Color<float> TButton::getColorText() const
{
	return text->getFont().getColor();
}

void TButton::setColorText(Color<float> colorText)
{
	text->getFont().setColor(colorText);
}


void TButton::setWlabel(int wLabel)
{
	text->setWidth(wLabel);
}

int TButton::getWlabel()
{
	return text->getWidth();
}

void TButton::setHlabel(int hLabel)
{
	text->setWidth(hLabel);
}

int TButton::getHlabel()
{
	return text->getHeight();
}

void TButton::setShape(Polygon *shape)
{
    this->shape = shape;
    text->setShape(shape);
}


void TButton::setPhisicShape(Body *phisicShape)
{
    this->phisicShape = phisicShape;
    text->setPhisicShape(phisicShape);
}

TLabel *TButton::getText() const
{
    return text;
}

void TButton::setText(TLabel *text)
{
    this->text = text;
}



Color<float> TButton::getColorBorder() const
{
	return text->getColorBorder();
}

void TButton::setColorBorder(Color<float> colorText)
{
	text->setColorBorder(colorText);
}


