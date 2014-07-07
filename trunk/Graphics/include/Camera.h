/*
 * Camera.h
 *
 *  Created on: 05/01/2012
 *      Author: Chutaos Team
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "Element.h"
#include "Point.h"
#include "GraphicsNamespace.h"
#include <GL/gl.h>
#include <GL/glu.h>

/**\class Camera.
 * \brief Clase que representa un objeto cámara de openGL.*/
class Camera : public Element {

public:
	/**\brief Constrcutor por defecto de cámara.*/
	Camera();
	/**\brief Constrcutor sobrecargado de cámara.
	 * \param width_ Ancho de la cámara.
	 * \param height_ Alto de la cámara.
	 * \param near_ Cercanía de la pantalla.
	 * \param far_ Lejania de la pantalla.
	 * \param p Posición de la pantalla. */
	Camera(int,int,int,int,Point p = Point(0,0));
	/**\brief Constructor de Copia.
	 * \param c Objeto cámara a copiar.*/
	Camera(const Camera &);
	/**\brief Destructor de Cámara*/
	virtual ~Camera();
	/**\brief Sobrecarga del operador de asignación.
	 * \param c Objeto Cámara a copiar.
	 * \return Devuelve una copia del objeto cámara.*/
	Camera& operator=(const Camera &);

	/**\brief Accede al valor del atributo widht.
	 * \return Devuelve el ancho de la cámara.*/
	int getWidth() const;
	/**\brief Accede al valor del atributo height.
	 * \return Devuelve el alto de la cámara.*/
	int getHeight() const;
	/**\brief Accede al valor del atributo near.
	 * \return Devuelve el cercanía de la cámara.*/
	int getNear() const;
	/**\brief Accede al valor del atributo far.
	 * \return Devuelve el lejanía de la cámara.*/
	int getFar() const;
	/**\brief Accede al valor del atributo angle.
	 * \return Devuelve el ángulo de la cámara.*/
	float getAngle() const;
	/**\brief Accede al valor del atributo scale.
	 * \return Devuelve la escala de la cámara.*/
	float getScale() const;
	/**\brief Accede al tipo de proyección de la cámara.
	 * \return Devuelve el tipo de proyección.*/
	Graphics::Projection::Type getProjection() const;
	/**\brief Accede al atributo posición.
	 * \return Devuelve la posición de la cámara.*/
	Point getPosition() const;

	/**\brief Permite asginar el valor del ancho.
	 * \param width_ Nuevo valor del ancho.*/
	void setWidth(int);
	/**\brief Permite asginar el valor del alto.
	 * \param height_ Nuevo valor del alto.*/
	void setHeight(int);
	/**\brief Permite asginar el valor del cercanía.
	 * \param near_ Nuevo valor del near.*/
	void setNear(int);
	/**\brief Permite asginar el valor del lejanía.
	 * \param far_ Nuevo valor del far.*/
	void setFar(int);
	/**\brief Permite asginar el valor del ángulo.
	 * \param angle_ Nuevo valor del ángulo.*/
	void setAngle(float);
	/**\brief Permite asginar el valor de la escala.
	 * \param scale_ Nuevo valor de la escala.*/
	void setScale(float);
	/**\brief Permite asginar el valor de la posición.
	 * \param position_ Nuevo valor de la posición.*/
	void setPosition(Point);
	/**\brief Pone Ortho como modo de proyección.*/
	void setOrtho();
	/**\brief Pone Perspective como modo de proyección.*/
	void setPerspective();
	/**\brief Exporta la cámara a OpenGL.*/
	void exportOpenGL() const;

private:
	/**\brief Copia una cámara en el objeto llamante.
	 * \param c Cámara a copiar.*/
	void Copiar(const Camera &);
	/*\brief Ancho.*/
	int width;
	/*\brief Alto.*/
	int height;
	/*\brief Cercanía.*/
	int near;
	/*\brief Lejanía.*/
	int far;
	/*\brief Ángulo.*/
	float angle;
	/*\brief Escala.*/
	float scale;
	/*\brief Posición.*/
	Point position;
	/*\brief Tipo de proyección.*/
	Graphics::Projection::Type projection;
};

#endif /* CAMERA_H_ */
