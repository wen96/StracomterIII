#ifndef _TRANSFORMACION_H_
#define _TRANSFORMACION_H_

#include "Matrix.h"
#include "Point.h"
#include "Element.h"
#include "GraphicsNamespace.h"
#include "GL/gl.h"


/**class Transform.
 * Clase Transformación que emula las tranformaciones de OpenGL. Hereda de Element*/
class Transform : public Element {
	/**\brief Operador de salida.
	 * \param os ostream de salida.
	 * \param t Transformación a mostrar.*/
	friend ostream& operator<<(ostream &os, const Transform &t);
public:
	/**\brief Constructor.*/
	Transform();
	/**\brief Constructor sobrecargado
	 * \param mode_ Indica a que matriz está afectando.*/
	Transform(Graphics::MatrixMode::Type);
	/**\brief Constructor de Copia.
	 * \param t Objeto a copiar.*/
	Transform(const Transform &t);
	/**\brief Destructor.*/
	~Transform();

	/**\brief Sobrecarga del operación de asignación.
	 * \param t Objeto a copiar.
	 * \return Devuelve la copia del objeto.*/
	Transform& operator=(const Transform &t);

	/**\brief Sobrecarga del operador suma.
	 * \param t Objeto a sumar.
	 * \return Devuelve la suma de las dos trasnformaciones.*/
	Transform operator+(const Transform &t) const;

	/**\brief Añade una rotación.
	 * \param rx_ Cantidad de giro en X.*/
	void addRotationX(double rx_);
	/**\brief Añade una rotación.
	 * \param rx_ Cantidad de giro en Y.*/
	void addRotationY(double ry_);
	/**\brief Añade una rotación.
	 * \param rx_ Cantidad de giro en Z.*/
	void addRotationZ(double rz_);
	/**\brief Añade una Translación.
	 * \param tx_ Translación en X.
	 * \param ty_ Translación en Y.
	 * \param tz_ Translación en Z.*/
	void addTranslation(double tx_, double ty_, double tz_);
	/**\brief Añade un Escalado.
	 * \param sx_ Escalado en X.
	 * \param sy_ Escalado en Y.
	 * \param sz_ Escalado en Z.*/
	void addScale(double sx_, double sy_, double sz_);
	/**\brief Añade Translación.
	 * \param p Point donde se translada.*/
	void addTranslation(Point);

	/**\brief Carga la identidad.*/
	void setIdentity();

	/**\brief Carga la transformación a OpenGL*/
	void exportOpenGL() const;

	/**\brief Añade la transformación a OpenGL*/
	void addOpenGL() const;

	/**\brief Importa la transformación de OpenGL*/
	void importOpenGL();

	/**\brief Devuelve el modo de matriz
	 * \return El Type del modo.*/
    Graphics::MatrixMode::Type getMode() const;
    /**\brief Devuelve la matriz
	 * \return Un puntero a Matriz.*/
    Matrix<double> *getTransform() const;
    /**\brief Cambia el modo de la matriz
	 * \param mode_ modo de la matriz.*/
    void setMode(Graphics::MatrixMode::Type mode_);
    /**\brief Carga la matriz
	 * \param transform_ Matriz nueva.*/
    void setTransform(Matrix<double> *transform_);
    /**\brief Selecciona modo Modelview*/
    void setModelView();
    /**\brief Selecciona modo Projection*/
    void setProjection();
    /**\brief Selecciona modo Texture*/
	void setTexture();



private:
	/**\brief Matriz que contiene las transformaciones acumuladas.*/
	Matrix<double> *transform;
	Graphics::MatrixMode::Type mode;
};

#endif
