/*
 * TRadioButton.h
 *
 *  Created on: 15/03/2012
 *      Author: Chutaos Team
 */

#ifndef TRADIOBUTTON_H_
#define TRADIOBUTTON_H_

#include "TWidget.h"
#include "TButton.h"

class TRadioButton : public TWidget{
public:
	TRadioButton(int num, Point p,World *w);
	TRadioButton(const TRadioButton &);
	TRadioButton & operator=(const TRadioButton &);
	virtual ~TRadioButton();
	/**\brief Dibuja el boton
	 */
	void Draw();
//	void setPhisicShape(Body *phisicShape);
//	void setShape(Polygon *shape);
	int whoIsClicked(Point);
	void generatePolygonalButton(int, vector<int>);
    vector<TButton*> getButtons() const;
    int getHeight() const;
    Point getPosition() const;
    int getSelected() const;
    int getWidth() const;
    void setButtons(vector<TButton*> buttons);
    void setHeight(int height);
    void setPosition(Point position);
    void setSelected(int selected);
    void setWidth(int width);
    void Octogonal();
    void Octogonal(int s0,int s1,int s2);
private:
    vector<TButton*> buttons;
    int selected;
    /**\brief Posición del.*/
    Point position;
    /**\brief Anchura del boton*/
    int width;
    /**\brief Altura del boton*/
    int height;
};

#endif /* TRADIOBUTTON_H_ */
