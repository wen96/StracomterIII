#ifndef _TRANSFORMACION_H_
#define _TRANSFORMACION_H_

#include "Matrix.h"
#include "Point.h"
#include "GL/gl.h"

/**class Transform
 * Clase Transformación que emula las tranformaciones de OpenGL.*/
class Transform {
	/**\brief Operador de salida.
	 * \param os ostream de salida.
	 * \param t Transformación a mostrar.*/
	friend ostream& operator<<(ostream &os, const Transform &t);
public:
	/**\brief Constructor.*/
	Transform();
	/**\brief Constructor de Copia.
	 * \param t Objeto a copiar.*/
	Transform(const Transform &t);
	/**\brief Destructor.*/
	~Transform();

	/**\brief Sobrecarga del operación de asignación.
	 * \param t Objeto a copiar.
	 * \return Devuelve la copia del objeto.*/
	Transform& operator=(const Transform &t);
	/**\brief Sobrecarga del operación de suma.
	 * \param t Objeto a sumar.
	 * \return Devuelve la suma del objeto con el llamador.*/
	Transform operator+(const Transform &t);

	/**\brief Añade una rotación.
	 * \param angle_ Ángulo de giro.
	 * \param rx_ Cantidad de giro en X.
	 * \param ry_ Cantidad de giro en Y.
	 * \param rz_ Cantidad de giro en Z.*/
	void addRotation(double angle_, double rx_, double ry_, double rz_);
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

	/**\brief Carga una rotación.
	 * \param angle_ Ángulo de giro.
	 * \param rx_ Cantidad de giro en X.
	 * \param ry_ Cantidad de giro en Y.
	 * \param rz_ Cantidad de giro en Z.*/
	void loadRotation(double angle_, double rx_, double ry_, double rz_);
	/**\brief Carga una Translación.
	 * \param tx_ Translación en X.
	 * \param ty_ Translación en Y.
	 * \param tz_ Translación en Z.*/
	void loadTranslation(double tx_, double ty_, double tz_);
	/**\brief Carga un Escalado.
	 * \param sx_ Escalado en X.
	 * \param sy_ Escalado en Y.
	 * \param sz_ Escalado en Z.*/
	void loadScale(double sx_, double sy_, double sz_);
	/**\brief Carga la identidad.*/
	void loadIdentity();
	/**\brief Carga Translación.
	 * \param p Point donde se translada.*/
	void loadTranslation(Point);

	/**\brief Carga la transformación a OpenGL*/
	void loadOpenGL() const;

	/**\brief Devuelve el ángulo.
	 * \return Devuelve el ángulo en grados.*/
    double getAngle() const;
    /**\brief Devuelve la rotación X.
     * \return Devuelve la rotación en el eje X*/
    double getRx() const;
    /**\brief Devuelve la rotación Y.
     * \return Devuelve la rotación en el eje Y*/
    double getRy() const;
    /**\brief Devuelve la rotación Z.
     * \return Devuelve la rotación en el eje Z*/
    double getRz() const;
    /**\brief Devuelve el escalado X.
     * \return Devuelve el escalado en el eje X*/
    double getSx() const;
    /**\brief Devuelve el escalado Y.
     * \return Devuelve el escalado en el eje Y*/
    double getSy() const;
    /**\brief Devuelve el escalado Z.
     * \return Devuelve el escalado en el eje Z*/
    double getSz() const;
    /**\brief Devuelve la translación X.
     * \return Devuelve la translación en el eje X*/
    double getTx() const;
    /**\brief Devuelve la translación Y.
     * \return Devuelve la translación en el eje Y*/
    double getTy() const;
    /**\brief Devuelve la translación Z.
     * \return Devuelve la translación en el eje Z*/
    double getTz() const;

private:
    /**\brief Ángulo de girp.*/
	double angle;
	/**\brief Rotación en X*/
	double rx;
	/**\brief Rotación en Y*/
	double ry;
	/**\brief Rotación en Z*/
	double rz;

	/**\brief Translación en X*/
	double tx;
	/**\brief Translación en Y*/
	double ty;
	/**\brief Translación en Z*/
	double tz;

	/**\brief Escalado en X*/
	double sx;
	/**\brief Escalado en Y*/
	double sy;
	/**\brief Escalado en Z*/
	double sz;
};

#endif
