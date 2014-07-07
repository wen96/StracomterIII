/*
 * Color.h
 *
 *  Created on: 04/11/2011
 *      Author: Chutaos Team
 */

#ifndef COLOR_H_
#define COLOR_H_

#include <typeinfo>


/**\class Color
 * Template que indica el color. Puede representarse por floats [0..1] o por enteros [0..255]*/
template <class T>
class Color {
public:
	/**\brief Constructor por defecto*/
	Color();
	/**\brief Constructor Sobrecargado
	 * \param r_ - Color Rojo.
	 * \param g_ - Color Verde.
	 * \param b_ - Color Azul.*/
	Color(T,T,T);
	/**\brief Constructor Sobrecargado
	 * \param r_ - Color Rojo.
	 * \param g_ - Color Verde.
	 * \param b_ - Color Azul.
	 * \param a_ - Alpha*/
	Color(T,T,T,T);
	/**\brief Constructor de Copia.
	 * \param c - Colorf a copiar.*/
	Color(const Color &);
	/**\brief Destructor*/
	virtual ~Color();
	/**\brief Operador de asignación.
	 * \param c - Colorf a copiar.
	 * \return Devuelve el nuevo valor por referencia. */
	Color& operator=(const Color &);
	/**\brief Get del color Rojo
	 * \return Devuelve el color Rojo*/
	T getR(void) const;
	/**\brief Get del color Verde
	 * \return Devuelve el color Verde*/
	T getG(void) const;
	/**\brief Get del color Azul
	 * \return Devuelve el color Azul*/
	T getB(void) const;
	/**\brief Get del color Alpha
	 * \return Devuelve el color Alpha*/
	T getAlpha(void) const;


	//Setters
	/**\brief Asigna un nuevo color.
	 * \param r_ - Color Rojo.
	 * \param g_ - Color Verde.
	 * \param b_ - Color Azul.
	 * \return Devuelve true si se ha podido cambiar el color, false en caso contrario.*/
	bool setColor(T,T,T);

	/**\brief Asigna un nuevo color.
	 * \param r_ - Color Rojo.
	 * \param g_ - Color Verde.
	 * \param b_ - Color Azul.
	 * \param a_ - Alhpa
	 * \return Devuelve true si se ha podido cambiar el color, false en caso contrario.*/
	bool setColor(T,T,T,T);
	/**\brief Asigna un nuevo valor al color Rojo.
	 * \param r_ - Nuevo valor del Rojo.
	 * \return Devuelve true si se ha podido cambiar el color, false en caso contrario*/
	bool setR(T);
	/**\brief Asigna un nuevo valor al color Verde.
	 * \param g_ - Nuevo valor del Verde.
	 * \return Devuelve true si se ha podido cambiar el color, false en caso contrario*/
	bool setG(T);
	/**\brief Asigna un nuevo valor al color Azul.
	 * \param b_ - Nuevo valor del Azul.
	 * \return Devuelve true si se ha podido cambiar el color, false en caso contrario*/
	bool setB(T);
	/**\brief Asigna un nuevo valor al color Alpha.
	 * \param alpha_ - Nuevo valor del Alpha.
	 * \return Devuelve true si se ha podido cambiar el Alpha, false en caso contrario*/
	bool setAlpha(T);
	/**\brief Exporta a OpenGL*/
	void exportOpenGL() const{

		if(typeid(r) == typeid(float))
			glColor4f(r,g,b,a);
		else if(typeid(r) == typeid(int))
			glColor4i(r,g,b,a);
	}
private:
	/**\brief Luz Roja*/
	T r;
	/**\brief Luz Verde*/
	T g;
	/**\brief Luz Azul*/
	T b;
	/**\brief Alpha*/
	T a;
};

//Color.cc
template <class T>
Color<T>::Color() {
	r = g = b = 0;
}

template <class T>
Color<T>::Color(T r_, T g_, T b_) {

	if(typeid(T) == typeid(float))
	{
		if(r_ >= 0.0 && r_ <= 1.0)
			r = r_;
		else
			r = 0.0;

		if(g_ >= 0.0 && g_ <= 1.0)
			g = g_;
		else
			g = 0.0;

		if(b_ >= 0.0 && b_ <= 1.0)
			b = b_;
		else
			b = 0.0;
	}
	else if(typeid(T) == typeid(int))
	{
		if(r_ >= 0 && r_ <= 255)
			r = r_;
		else
			r = 0;

		if(g_ >= 0 && g_ <= 255)
			g = g_;
		else
			g = 0;

		if(b_ >= 0 && b_ <= 255)
			b = b_;
		else
			b = 0;
	}

	a = 1.0;

}

template <class T>
Color<T>::Color(T r_, T g_, T b_, T a_) {

	if(typeid(T) == typeid(float))
	{
		if(r_ >= 0.0 && r_ <= 1.0)
			r = r_;
		else
			r = 0.0;

		if(g_ >= 0.0 && g_ <= 1.0)
			g = g_;
		else
			g = 0.0;

		if(b_ >= 0.0 && b_ <= 1.0)
			b = b_;
		else
			b = 0.0;
	}
	else if(typeid(T) == typeid(int))
	{
		if(r_ >= 0 && r_ <= 255)
			r = r_;
		else
			r = 0;

		if(g_ >= 0 && g_ <= 255)
			g = g_;
		else
			g = 0;

		if(b_ >= 0 && b_ <= 255)
			b = b_;
		else
			b = 0;
	}

	a = a_;

}

template <class T>
Color<T>::Color(const Color<T> &c) {

	r = c.r;
	g = c.g;
	b = c.b;
	a = c.a;
}

template <class T>
Color<T>::~Color() {
	r = g = b = a = -1;
}

template <class T>
Color<T>&
Color<T>::operator=(const Color<T> &c) {

	if(this != &c)
	{
		this->~Color();
		r = c.r;
		g = c.g;
		b = c.b;
		a = c.a;
	}

	return *this;

}

template <class T>
T
Color<T>::getR(void) const {
	return r;
}

template <class T>
T
Color<T>::getG(void) const {
	return g;
}

template <class T>
T
Color<T>::getB(void) const {
	return b;
}

template <class T>
T
Color<T>::getAlpha(void) const {
	return a;
}

template <class T>
bool
Color<T>::setColor(T r_, T g_, T b_) {
	bool cambio = false;

	if(typeid(T) == typeid(float))
	{
		if(r_ >= 0.0 && r_ <= 1.0 && g_ >= 0.0 && g_ <= 1.0 && b_ >= 0.0 && b_ <= 1.0)
		{
			r = r_;
			g = g_;
			b = b_;
			cambio = true;
		}
	}
	else if(typeid(T) == typeid(int))
	{
		if(r_ >= 0 && r_ <= 255 && g_ >= 0 && g_ <= 255 && b_ >= 0 && b_ <= 255)
		{
			r = r_;
			g = g_;
			b = b_;
			cambio = true;
		}
	}

	return cambio;
}

template <class T>
bool
Color<T>::setColor(T r_, T g_, T b_, T a_) {
	bool cambio = false;

	if(typeid(T) == typeid(float))
	{
		if(r_ >= 0.0 && r_ <= 1.0 && g_ >= 0.0 && g_ <= 1.0 && b_ >= 0.0 && b_ <= 1.0)
		{
			r = r_;
			g = g_;
			b = b_;
			cambio = true;
		}
	}
	else if(typeid(T) == typeid(int))
	{
		if(r_ >= 0 && r_ <= 255 && g_ >= 0 && g_ <= 255 && b_ >= 0 && b_ <= 255)
		{
			r = r_;
			g = g_;
			b = b_;
			cambio = true;
		}
	}

	a = a_;
	return cambio;
}
template<class T>
bool
Color<T>::setR(T r_) {

	bool cambio = false;

	if(typeid(T) == typeid(float))
	{
		if(r_ >= 0.0 && r_ <= 1.0)
		{
			r = r_;
			cambio = true;
		}
	}
	else if(typeid(T) == typeid(int))
	{
		if(r_ >= 0 && r_ <= 255)
		{
			r = r_;
			cambio = true;
		}
	}

	return cambio;
}

template<class T>
bool
Color<T>::setG(T g_) {

	bool cambio = false;

	if(typeid(T) == typeid(float))
	{
		if(g_ >= 0.0 && g_ <= 1.0)
		{
			g = g_;
			cambio = true;
		}
	}
	else if(typeid(T) == typeid(int))
	{
		if(g_ >= 0 && g_ <= 255)
		{
			g = g_;
			cambio = true;
		}
	}

	return cambio;
}

template<class T>
bool
Color<T>::setB(T b_) {

	bool cambio = false;

	if(typeid(T) == typeid(float))
	{
		if(b_ >= 0.0 && b_ <= 1.0)
		{
			b = b_;
			cambio = true;
		}
	}
	else if(typeid(T) == typeid(int))
	{
		if(b_ >= 0 && b_ <= 255)
		{
			b = b_;
			cambio = true;
		}
	}

	return cambio;
}

template<class T>
bool
Color<T>::setAlpha(T alpha_) {
	bool cambio = false;
	if(alpha_ >= 0.0 && alpha_ <= 1.0)
	{
		cambio = true;
		a = alpha_;
	}
	return cambio;
}

#endif /* COLOR_H_ */
