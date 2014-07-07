/*
 * TControlMenu.cc
 *
 *  Created on: 19/01/2012
 *      Author: Chutaos Team
 */

#include "TLabel.h"

TLabel::TLabel()
{
	widget=Core::Widget::w_label;
	caption = "label";
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
	marginUp = height/2;
	marginBottom = height/2;
	marginRight = width/2;
	marginLeft = 0;
	colorBorder = Color<float>(0,0,0,0);
	font.setColor(Color<float>(0,0,0,1));
	font.setFont(Graphics::Font::tf2);
	font.setSize(18);
}



TLabel::TLabel(string caption_,int size_)
{

	widget=Core::Widget::w_label;
	caption = caption_;
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
	marginUp = height/2;
	marginBottom = height/2;
	marginRight = width/2;
	marginLeft = 0;
	colorBorder = Color<float>(0,0,0,0);
	font.setColor(Color<float>(0,0,0,1));
	font.setFont(Graphics::Font::tf2);
	font.setSize(size_);
}



TLabel::TLabel(int width_, int height_, string caption_, int _size)
{
	widget = Core::Widget::w_button;
	caption = caption_;
	width = width_;
	height = height_;
	Point aux;
	vector<Point> puntos;
	int x = 0, y = 0;
	x = width / 2;
	y = height / 2;
	aux.setXY(x, y);
	puntos.push_back(aux);
	aux.setXY(-x, y);
	puntos.push_back(aux);
	aux.setXY(-x, -y);
	puntos.push_back(aux);
	aux.setXY(x, -y);
	puntos.push_back(aux);
	shape = new Polygon(Point(), puntos);
	marginUp = height / 2;
	marginBottom = height / 2;
	marginRight = width / 2;
	marginLeft = 0;
	colorBorder = Color<float>(0,0,0,0);
	font.setColor(Color<float>(0,0,0,1));
	font.setFont(Graphics::Font::tf2);
	font.setSize(_size);
}



TLabel::~TLabel()
{
	widget=Core::Widget::w_none;
	caption = "";
}



void TLabel::Draw()
{
	if (isVisible()) {
		float x = shape->getCentro().getX();
		float y = shape->getCentro().getY();
		//colorBorder = Color<float>(1,0,0);//Color rojo, para hacer pruebas y localizar los LABELS
		//DrawPolygon(*shape, colorBorder);
		//font.renderText(caption,Point(x-(caption.size()*font.getSize())/2,y+font.getSize()/2));
		font.renderText(caption,Point(x-(width/2),y+(font.getSize()/2)));
		//DrawText(Point(x-(caption.size()*font.getFontSize())/2,y+font.getFontSize()/2), caption, font.getFontSize(), font.getFontColor());
	}
}

string TLabel::getCaption() const
{
    //return caption;
    return "Poleo";
}

Color<float> TLabel::getColorBorder() const
{
    return colorBorder;
}

int TLabel::getHeight() const
{
    return height;
}

int TLabel::getSize() const
{
    return font.getSize();
}

int TLabel::getWidth() const
{
    return width;
}

void TLabel::setCaption(string caption)
{
    this->caption = caption;
}

void TLabel::setColorBorder(Color<float> colorBorder)
{
    this->colorBorder = colorBorder;
}

void TLabel::setHeight(int height)
{
    this->height = height;
}

void TLabel::setSize(int size)
{
    this->font.setSize(size);
}

Color<float> TLabel::getColorText() const
{
	return font.getColor();
}

void TLabel::setColorText(Color<float> colorText)
{
	font.setColor(colorText);
}

void TLabel::setWidth(int width)
{
    this->width = width;
}

Text TLabel::getFont() const
{
    return font;
}

TLabel::TLabel(const TLabel & l)
{
	Copiar(l);
}

TLabel & TLabel::operator =(const TLabel & l)
{
	if(this != &l)
	{
		Destructor();
		Copiar(l);
	}
	return *this;
}

void TLabel::setFont(Text font)
{
    this->font = font;
}

void TLabel::Destructor()
{
}



void TLabel::setFontText(Graphics::Font::Name name)
{
	font.setFont(name);
}

void TLabel::Copiar(const TLabel & l)
{
	widget = Core::Widget::w_button;
	caption = l.caption;
	width = l.width;
	height = l.height;
	shape = new Polygon(*l.shape);
	marginUp = l.marginUp;
	marginBottom = l.marginBottom;
	marginRight = l.marginRight;
	marginLeft = l.marginLeft;
	colorBorder = l.colorBorder;
	font.setColor(l.font.getColor());
	font.setFont(l.font.getFont());
	font.setSize(l.font.getSize());
}




