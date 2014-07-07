/*
 * MotorGrafico.cc
 *
 *  Created on: 04/11/2011
 *      Author: Chtaos Team.
 */

#include "MotorGrafico.h"


//============ CIRCULO ===================//

void DrawCircle(Point centro, float radio, Color<float> color) {

	float x, y;
	float x0, y0;

	x0 = centro.getX();
	y0 = centro.getY();

	color.exportOpenGL();
	glBegin(GL_LINE_LOOP);

		for(float angulo = 0.0; angulo <= GRADOS; angulo += (GRADOS/TXC))
		{
			x = x0 + (cos(angulo*M_PI/180) * radio);
			y = y0 + (sin(angulo*M_PI/180) * radio);
			glVertex2f(x,y);
		}
	glEnd();
}

void DrawCircle(Point centro, float radio, int lados, Color<float> color) {

	float x, y;
	float x0, y0;

	x0 = centro.getX();
	y0 = centro.getY();

	if(lados >= 3)
	{
		color.exportOpenGL();
		glBegin(GL_LINE_LOOP);

			for(float angulo = 0.0; angulo <= GRADOS; angulo += (GRADOS/lados))
			{
				x = x0 + (cos(angulo*M_PI/180) * radio);
				y = y0 + (sin(angulo*M_PI/180) * radio);
				glVertex2f(x,y);
			}
		glEnd();
	}
}

void DrawSolidCircle(Point centro, float radio, Color<float> color) {

	float x, y;
	float x0, y0;

	float angulo = ((float)GRADOS/(float)TXC);
	x0 = centro.getX();
	y0 = centro.getY();

	color.exportOpenGL();
	glBegin(GL_POLYGON);

		/*for(float angulo = 0.0; angulo <= GRADOS; angulo += (GRADOS/TXC))
		{*/
		for(int i = 0; i <= TXC; i++)
		{
			x = x0 + (cos(angulo*M_PI/180*i) * radio);
			y = y0 + (sin(angulo*M_PI/180*i) * radio);
			glVertex2f(x,y);
		}
	glEnd();
}

void DrawSolidCircle(Point centro, float radio, int lados, Color<float> color) {

	float x, y;
	float x0, y0;

	x0 = centro.getX();
	y0 = centro.getY();

	if(lados >= 3)
	{
		color.exportOpenGL();
		glBegin(GL_POLYGON);

			for(float angulo = 0.0; angulo <= GRADOS; angulo += (GRADOS/lados))
			{
				x = x0 + (cos(angulo*M_PI/180) * radio);
				y = y0 + (sin(angulo*M_PI/180) * radio);
				glVertex2f(x,y);
			}
		glEnd();
	}
}

// ================= POLÍGONOS ===================//
void DrawPolygon(const Polygon &pol, Color<float> color) {

	color.exportOpenGL();
	int n_vertex = pol.getNVertices();
	vector<Point> vertices = pol.getPuntos();

	if(pol.getType() == POL_EDGE)
	{

		glLineWidth(1.0);
		glBegin(GL_LINES);
			glNormal3d(0,0,-1);
			glVertex3f(vertices[0].getX(), vertices[0].getY(), vertices[0].getZ());
			glVertex3f(vertices[1].getX(), vertices[1].getY(), vertices[1].getZ());
		glEnd();
	}
	else if(pol.getType() != POL_NONE)
	{
		glBegin(GL_LINE_LOOP);
			for(int i = 0; i < n_vertex; i++)
			{
				glNormal3d(0,0,-1);
				glVertex3f(vertices[i].getX(),vertices[i].getY(), vertices[i].getZ());
			}
		glEnd();
	}
}

void DrawSolidPolygon(const Polygon &pol, Color<float> color) {

	color.exportOpenGL();
	int n_vertex = pol.getNVertices();
	vector<Point> vertices = pol.getPuntos();

	if(pol.getType() == POL_EDGE)
	{

		glLineWidth(1.0);
		glBegin(GL_LINES);
			glNormal3d(0,0,-1);
			glVertex3f(vertices[0].getX(), vertices[0].getY(), vertices[0].getZ());
			glVertex3f(vertices[1].getX(), vertices[1].getY(), vertices[1].getZ());
		glEnd();
	}
	else if(pol.getType() == POL_CHAIN)
	{
		glBegin(GL_LINE_LOOP);
			for(int i = 0; i < n_vertex; i++)
			{
				glNormal3d(0,0,-1);
				glVertex3f(vertices[i].getX(),vertices[i].getY(), vertices[i].getZ());
			}
		glEnd();
	}else if(pol.getType() != POL_NONE)
	{
		glBegin(GL_POLYGON);
			for(int i = 0; i < n_vertex; i++)
			{
				glNormal3d(0,0,-1);
				glVertex3f(vertices[i].getX(),vertices[i].getY(), vertices[i].getZ());
			}
		glEnd();
	}
}

//======================= LINEA ==========================//
void DrawLine(Point a, Point b, Color<float> color, float grosor) {

	glLineWidth(grosor);
	color.exportOpenGL();
	glBegin(GL_LINES);
		glVertex3f(a.getX(), a.getY(), a.getZ());
		glVertex3f(b.getX(), b.getY(), b.getZ());
	glEnd();
	glLineWidth(1);
}

void DrawPoint(Point p, float grosor) {

	glPointSize(grosor);
	glBegin(GL_POINTS);
		glVertex3f(p.getX(), p.getY(), p.getZ());
	glEnd();
	glPointSize(1);
}

void DrawPoint(Point p, Color<float> color, float grosor) {

	glPointSize(grosor);
	color.exportOpenGL();
	glBegin(GL_POINTS);
		glVertex3f(p.getX(), p.getY(), p.getZ());
	glEnd();
	glPointSize(1);
}

void DrawText(Point centro, string cadena, Color<float> color, float TAM) {

	float x = centro.getX();
	float y = centro.getY();

	color.exportOpenGL();
	    for(unsigned int tmp = 0; tmp < cadena.length(); tmp++) {
			glRasterPos2f( x + tmp*TAM, y );
	        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,(int)cadena[tmp]);
	    }
}

void DrawText(Point centro, string cadena, int size, Color<float> color) {

	GLfloat font_scale = 100;
	int grosor = size/10;
	float x = centro.getX();
	float y = centro.getY();

	color.exportOpenGL();
	for(int i=0; i<grosor;i++)
	{
		for(int j=0; j<grosor;j++)
		{
			glPushMatrix();
			glTranslatef(x+i, y+j, 0.0);
			glScalef(size/font_scale, -size/font_scale, size/font_scale);
				for (unsigned int tmp = 0; tmp < cadena.length(); tmp++) {
				glutStrokeCharacter(GLUT_STROKE_ROMAN, (int) cadena[tmp]);
			}
			glPopMatrix();
		}
	}
}

void DrawTriangle(Point a, Point b, Point c, Color<float> color) {
	color.exportOpenGL();
	glBegin(GL_POLYGON); // Drawing Using Triangles
	glVertex2f(a.getX(), a.getY()); // Top
	glVertex2f(b.getX(), b.getY()); // Bottom Left
	glVertex2f(c.getX(), c.getY()); // Bottom Right
	glEnd(); // Finished Drawing The Triangle
}
