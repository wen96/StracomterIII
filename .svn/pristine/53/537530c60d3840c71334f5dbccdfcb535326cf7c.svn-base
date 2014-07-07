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
	marginLeft = 0;
	color = Color<float>(0.8,0.8,0.8);
	colorOver = Color<float>(0.8,0.8,0.99);
	colorClicked = Color<float>(0.6,0.6,1);
	text->getFont().setColor(Color<float>(0,0,0));
	text->getFont().setFont(Graphics::Font::tf2);
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
	marginLeft = 0;
	color = Color<float>(0.8,0.8,0.8);
	colorOver = Color<float>(0.8,0.8,0.99);
	colorClicked = Color<float>(0.6,0.6,1);
	text->getFont().setColor(Color<float>(0,0,0));
	text->getFont().setFont(Graphics::Font::tf2);
	text->getFont().setSize(14);

	clicked = false;
	over = false;
}

TButton::TButton(Point p,World* w)
{
	widget=Core::Widget::w_button;
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
	marginUp = marginBottom = 	marginRight = marginLeft = 0;
	color = Color<float>(0.8,0.8,0.8);
	colorOver = Color<float>(0.8,0.8,0.99);
	colorClicked = Color<float>(0.6,0.6,1);
	text = NULL;
	shape = new Polygon(Point(),puntos);
	BodyData *bd = new BodyData(*shape,b2_staticBody);
	Body *bod = new Body(*w,*bd);
	bod->setPosition(p);
	phisicShape = bod;

	clicked = false;
	over = false;
}

TButton::TButton(Point p, int width_, int height_, string caption_){
	widget=Core::Widget::w_button;
	text = new TLabel(width_,height_,caption_);
	width = width_;
	height = height_;
	vector<Point>puntos;
	Point aux = p;
	puntos.push_back(aux);
	aux.setX(aux.getX()+width);
	puntos.push_back(aux);
	aux.setY(aux.getY()+height);
	puntos.push_back(aux);
	aux.setX(aux.getX()-width);
	puntos.push_back(aux);
	shape = new Polygon(puntos);
	text->setShape(new Polygon(puntos));
	marginUp = height/2;
	marginBottom = height/2;
	marginRight = 0;
	marginLeft = 0;
	color = Color<float>(0.8,0.8,0.8);
	colorOver = Color<float>(0.8,0.8,0.99);
	text->getFont().setColor(Color<float>(0,0,0));
	text->getFont().setFont(Graphics::Font::tf2);
	text->getFont().setSize(14);

	clicked = false;
	over = false;
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
	marginLeft = 0;
	color = Color<float>(0.8,0.8,0.8);
	colorOver = Color<float>(0.8,0.8,0.99);
	text->getFont().setColor(Color<float>(0,0,0));
	text->getFont().setFont(Graphics::Font::tf2);
	text->getFont().setSize(14);

	clicked = false;
	over = false;
}

TButton::~TButton()
{
	widget=Core::Widget::w_none;

	if(text != NULL)
	{
		delete text;
		text = NULL;
	}
	//text->~TLabel();
}

void TButton::Draw()
{
	if (isVisible()){
		//Polygon *p = new Polygon(phisicShape->getPosition(),phisicShape->getBodydata()->getPoligon().getPuntos());
		//Polygon *p = new Polygon(phisicShape->getPosition(),shape->getPuntos());
		if (isEnable()){
			if (!isClicked()){
				if (isOver()){
					//DrawSolidPolygon(*p,colorOver);
					DrawSolidPolygon(*shape,colorOver);

				}else{
					//DrawSolidPolygon(*p,color);
					DrawSolidPolygon(*shape,color);
				}
			}else{
				//DrawSolidPolygon(*p,auxColor);
				DrawSolidPolygon(*shape,colorClicked);
			}
		}else{
			//DrawSolidPolygon(*p,color);
			DrawSolidPolygon(*shape,color);
		}
		DrawPolygon(*shape,Color<float>(0,0,0));

		if(text != NULL)
			text->Draw();

		//delete p;
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

	if(text != NULL)
		text->setShape(shape);
}


void TButton::setPhisicShape(Body *phisicShape)
{
	this->phisicShape = phisicShape;
	if(text != NULL)
		text->setPhisicShape(phisicShape);
}

TLabel *TButton::getText() const
{
	return text;
}

TButton::TButton(const TButton & b)
{
	Copiar(b);
}

TButton & TButton::operator =(const TButton & b)
{
	if(this != &b)
	{
		Destructor();
		Copiar(b);
	}

	return *this;
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

void TButton::Destructor()
{
	if(text != NULL)
	{
		delete text;
		text = NULL;
	}
}



void TButton::Copiar(const TButton & b)
{
	widget=Core::Widget::w_button;
	text = new TLabel(*b.text);
	width = b.width;
	height = b.height;
	shape = new Polygon(*b.shape);
	marginUp = b.marginUp;
	marginBottom = b.marginBottom;
	marginRight = b.marginRight;
	marginLeft = b.marginLeft;
	color = b.color;
	colorOver = b.colorOver;
}




