/*
 * TRadioButton.h
 *
 *  Created on: 15/03/2012
 *      Author: gallardo
 */

#ifndef TRADIOBUTTON_H_
#define TRADIOBUTTON_H_

#include "TWidget.h"
#include "TButton.h"

class TRadioButton : public TWidget{
public:
	TRadioButton(int num);
	TRadioButton(Point, vector<Polygon>);
	TRadioButton(const TRadioButton &);
	TRadioButton & operator=(const TRadioButton &);
	virtual ~TRadioButton();
	/**\brief Dibuja el boton
	 */
	void Draw();
	void setPhisicShape(Body *phisicShape);
	int whoIsClicked(Point);
	void generatePolygonalButton(int, vector<int>);
private:
	vector<TButton> buttons;
	int selected;
};

#endif /* TRADIOBUTTON_H_ */
