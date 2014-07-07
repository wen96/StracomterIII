/*
 * Text.cc
 *
 *  Created on: Feb 9, 2012
 *      Author: Chutaos Team
 */

#include "Text.h"

Text::Text() {
	font = NULL;
	fontColor = Color<float>();
	fontName = Graphics::Font::Monospace;
	fontSize = 0.0;
	cadena = "";
	element = Core::Element::e_text;
}

Text::~Text() {
	font = NULL;
	fontColor = Color<float>();
	fontName = Graphics::Font::Monospace;
	fontSize = 0.0;
	cadena = "";
	element = Core::Element::e_none;
}

Text::Text(const Text &text) {
	font = text.font;
	fontName = text.fontName;
	fontColor = text.fontColor;
	fontSize = text.fontSize;
	cadena = text.cadena;
	element = text.element;
}

Text &
Text::operator=(const Text &text) {
	if (this != &text) {
		font = text.font;
		fontColor = text.fontColor;
		fontName = text.fontName;
		fontSize = text.fontSize;
		cadena = text.cadena;
		element = text.element;
	}
	return *this;
}

Text::Text(Graphics::Font::Name fuente, Point pos, Color<float> color, double size, string texto){
	font = ResourceManager::getInstance()->getFont(fuente, size);
	fontName = fuente;
	fontColor = color;
	cadena = texto;
	posicion = pos;
	fontSize = size;
	element = Core::Element::e_text;
}

bool Text::setFont(FTGLTextureFont *fuente) {
	font = fuente;
	return font != NULL;
}

bool Text::setFont(Graphics::Font::Name fuente){
	fontName = fuente;
	font = ResourceManager::getInstance()->getFont(fuente, fontSize);
	return font != NULL;
}

void Text::setText(string texto) {
	cadena = texto;
}

bool Text::setSize(double size) {
	if (size <= 0)
		return false;

	fontSize = size;
	font = ResourceManager::getInstance()->getFont(fontName, fontSize);
	return true;
}

void Text::setColor(Color<float> color_) {
	fontColor = color_;
}

void Text::renderText(string cadena, Point pos, float size,
		Color<float> color) {

	if (font != NULL) {

		//TODO por algun motivo, la escena esta bocaabajo
		glPushMatrix();
			glScalef(1.0, -1.0, 1.0);

			glTranslatef(pos.getX(), pos.getY() * -1, pos.getZ());
			glColor4f(color.getR(), color.getG(), color.getB(), color.getAlpha());

			font->Render(cadena.c_str());
		glPopMatrix();
	}
}

void Text::renderText(string cadena, Point pos) {
	if (font != NULL) {
		glPushMatrix();
			glScalef(1.0, -1.0, 1.0);

			glTranslatef(pos.getX(), pos.getY() *-1, pos.getZ());
			glColor4f(fontColor.getR(), fontColor.getG(), fontColor.getB(), fontColor.getAlpha());

			font->Render(cadena.c_str());
		glPopMatrix();
	}
}

void Text::renderText(string cadena) {
	if (font != NULL) {

		//TODO por algun motivo, la escena esta bocaabajo
		glPushMatrix();
		//glScalef(1.0,-1.0,1.0);

		glColor4f(fontColor.getR(), fontColor.getG(), fontColor.getB(),
				fontColor.getAlpha());
		font->Render(cadena.c_str());
		glPopMatrix();
	}
}

void Text::exportOpenGL(){
	if(font != NULL){
		glPushMatrix();

			glTranslatef(posicion.getX(), posicion.getY(), posicion.getZ());
			glColor4f(fontColor.getR(), fontColor.getG(), fontColor.getB(), fontColor.getAlpha());

			glScalef(1,-1,1);

			font->Render(cadena.c_str());
		glPopMatrix();
	}
}

FTGLTextureFont *Text::getFont() const {
	return font;
}

Color<float> Text::getColor() const {
	return fontColor;
}

double Text::getSize() const {
	return fontSize;
}

string Text::getText() const{
	return cadena;
}
