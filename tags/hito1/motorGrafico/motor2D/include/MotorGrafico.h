/*
 * MotorGrafico.h
 *
 *  Created on: 04/11/2011
 *      Author: Chutaos Team
 */

#ifndef MOTORGRAFICO_H_
#define MOTORGRAFICO_H_

#include "Color.h"
#include "Point.h"
#include "Polygon.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

const int TXC = 200;
const int GRADOS = 360;

void DrawCircle(Point centro, float radio, Color<float> color = Color<float>(0.0,0.0,0.0));
void DrawCircle(Point centro, float radio, int lado = 3, Color<float> color = Color<float>(0.0,0.0,0.0));

void DrawSolidCircle(Point centro, float radio, Color<float> color = Color<float>(0.0,0.0,0.0));
void DrawSolidCircle(Point centro, float radio, int lado = 3, Color<float> color = Color<float>(0.0,0.0,0.0));

void DrawPolygon(const Polygon &, Color<float> color = Color<float>(0.0,0.0,0.0));
void DrawSolidPolygon(const Polygon &, Color<float> color = Color<float>(0.0,0.0,0.0));

void DrawLine(Point, Point, Color<float> color = Color<float>(0.0,0.0,0.0), float grosor = 1.0);

void DrawPoint(Point, Color<float>, float grosor = 1.0);

void DrawText(Point, string, Color<float> color = Color<float>(0.0,0.0,0.0), float TAM = 0.05);

#endif /* MOTORGRAFICO_H_ */
