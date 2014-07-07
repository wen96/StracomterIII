/*
 * Shape.h
 *
 *  Created on: 11/02/2012
 *      Author: Chutaos Team
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include "Element.h"
#include "Color.h"
#include "Point.h"
#include "Polygon.h"
#include "MotorGrafico.h"
#include "CoreNamespace.h"
#include "Textura.h"
#include "ResourceManager.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

class SceneManager;

/**\class Shape
 * \brief Clase que implementa una forma polígonal.*/
class Shape : public Element{
public:
	/**\brief Constructor por defecto.*/
	Shape();
	/**\brief Constructor sobrecargado,
	 * \param color_ Color del shape.*/
	Shape(Color<float>);
	/**\brief Constructor sobrecargado,
	 * \param shape_ Forma del shape.
	 * \param color_ Color del shape.*/
	Shape(Polygon, Color<float>);
	/**\brief Constructor sobrecargado.
	 * \param shape_ Forma del shape.
	 * \param color_ Color del shape.
	 * \param relleno_ Relleno o no.*/
	Shape(Polygon, Color<float>, bool);
	/**\brief Constructor sobrecargado.
	 * \param shape_ Forma del shape.*/
	Shape(Polygon);
	/**\brief Constructor sobrecargado.
	 * \param shape_ Forma del shape.*/
	Shape(Point, float, Textura*);
	Shape(vector<Point> vP);
	/**\brief Constructor de Copia.
	 * \param s Objeto a copiar.*/
	Shape(const Shape&);
	/**\brief Destructor.*/
	~Shape();
	/**\brief Sobrecarga del operador de asignación.
	 * \param s Objeto a copiar.
	 * \return Devuelve una copia del objeto.*/
	Shape & operator=(const Shape&);
	/**\brief Accede al atributo privado Color.
	 * \return Devuelve el color del Shape.*/
    Color<float> getColor() const;
    /**\brief Accede al atributo privado Shape.
	 * \return Devuelve la forma del Shape.*/
    Polygon getShape() const;
    /**\brief Permite cambiar atributo privado Tamano.
	 * \param tamano el tamaño de la línea.*/
    void setTamano(int tamano);
    /**\brief Accede al atributo privado Tamano.
	 * \return Devuelve el tamaño de la línea.*/
    int getTamano();
    /**\brief Permite cambiar atributo privado Color.
	 * \param color_ el color del shape.*/
    void setColor(Color<float> color_);
    /**\brief Permite cambiar atributo privado shape.
	 * \param shape_ la forma del shape.*/
    void setShape(Polygon shape_);

    void setShape(vector<Point> vPoint);
    /**\brief Exporta la forma a OpenGL*/
    void exportOpenGL();
    /**\brief Indica si la forma es rellena o no.
     * \return true si es relleno, false en caso contrario.*/
    bool isRelleno() const;
    /**\brief Permite cambiar atributo privado relleno.
   	 * \param relleno_ relleno o no del shape.*/
    void setRelleno(bool relleno_);
private:
    /**\brief Forma del shape.*/
	Polygon shape;
	/**\brief Color del shape.*/
	Color<float> color;
	/**\brief Tamaño de la línea.*/
	int tamano;
	/**\brief Indica si está relleno o no.*/
	bool relleno;

	bool cadena;
	bool conTextura;
	Textura *textura;
};

#endif /* SHAPE_H_ */
