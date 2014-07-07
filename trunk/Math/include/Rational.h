/*
 * rational.h
 *
 *  Created on: 28/10/2011
 *      Author: Chutaos Team.
 */

#ifndef _RATIONAL_H_
#define _RATIONAL_H_

#include <iostream>
#include <math.h>

using namespace std;

/**\brief Valor de redondeo.
 * Valor de redondeo de la conversión de float a Racional.*/
const int RAT_ROUND = 5;
/**\class Rational
 * Implementa los números racionales.*/
class Rational {

	/**\brief Sobrecarga del operador salida.
	 * \param os - ostream de salida.
	 * \param rat - Racional a mostrar.
	 * \return Salida del Rational.*/
	friend ostream& operator<<(ostream &, const Rational &);
public:
	/**\brief Constructor por defecto*/
	Rational(void);
	/**\brief Constructor
	 * \param n - Numerador.
	 * \param d - Denominador.*/
	Rational(int,int);
	/**\brief Constructor.
	 * Convierte entero a Rational
	 * \param valor - Valor entero.*/
	Rational(int);
	/**\brief Constructor
	 * Convierte float a Rational. Redondeado a 5 cifras decimales.
	 * \param valor - Valor en float*/
	Rational(double);
	/**\Constructor de copia.
	 * rat - Rational a copiar.*/
	Rational(const Rational &);
	/**\brief Destructor.*/
	~Rational(void);

	/**\brief Devuelve el numerador.
	 * \return Devuelve el numerador.*/
	int getNumerador(void) const;
	/**\brief Devuelve el denominador.
	 * \return Devuelve el numerador.*/
	int getDenominador(void) const;
	/**\brief Cambia el valor del numerador.
	 * \param num - Nuevo numerador.*/
	void setNumerador(int);
	/**\brief Cambia el valor del denominador.
	 * \param den - Nuevo denominador.
	 * \return True si se ha podido cambiar y false si no.*/
	bool setDenominador(int);
	/**\brief Devuelve el valor del rational
	 * \return Devuelve el valor del rational en forma de float.*/
	float getValor(void) const;

	/**\brief Devuelve el valor del rational truncando a entero
	 * \return Devuelve el valor del rational en forma de entero, truncando.*/
	int getValorInt(void) const;

	/**\brief Invierte el Racional si se puede.
	 * \return True si se puede invertir y false si no.*/
	bool invertir(void);

	/**\brief Invierte el Racional si se puede.
	 * \return True si se puede invertir y false si no.*/
	bool isInteger(void);

	/**\brief Devuelve la inversa de un Racional.
	 * \return Inversa del rational.*/
	Rational inversa(void) const;

	/**\brief Asigna al Rational el Error(1/0).*/
	void setError();

	/**\brief Reduce el Rational*/
	void Reducir();

	/**\brief Operador de igualdad.
	 * \param rat - Rational a comparar con el llamador.
	 * \return true si son iguales y false si no lo son.
	 */
	bool operator==(const Rational &) const;
	/**\brief Operador de desigualdad.
	 * \param rat - Rational a comparar con el llamador.
	 * \return true si son desiguales y false si no lo son.
	 */
	bool operator!=(const Rational &) const;
	/**\brief Operador de comparación.
	 * \param rat - Rational a comparar con el llamador.
	 * \return true si el primero es mayor que el segundo.
	 */
	bool operator>(const Rational &) const;
	/**\brief Operador de comparación.
	 * \param rat - Rational a comparar con el llamador.
	 * \return true si el primero es mayor o igual que el segundo.
	 */
	bool operator>=(const Rational &) const;
	/**\brief Operador de comparación.
	 * \param rat - Rational a comparar con el llamador.
	 * \return true si el primero es menor que el segundo.
	 */
	bool operator<(const Rational &) const;
	/**\brief Operador de comparación.
	 * \param rat - Rational a comparar con el llamador.
	 * \return true si el primero es menor o igual que el segundo.
	 */
	bool operator<=(const Rational &) const;
	/**\brief Operador de comparación.
	 * \param valor - entero a comparar con el llamador.
	 * \return true si el primero es mayor que el segundo.
	 */
	bool operator>(const int &) const;
	/**\brief Operador de comparación.
	 * \param valor - entero a comparar con el llamador.
	 * \return true si el primero es menor que el segundo.
	 */
	bool operator<(const int &) const;
	/**\brief Operador de comparación.
	 * \param valor - entero a comparar con el llamador.
	 * \return true si el primero es mayor o igual que el segundo.
	 */
	bool operator>=(const int &) const;
	/**\brief Operador de comparación.
	 * \param valor - entero a comparar con el llamador.
	 * \return true si el primero es menor o igual que el segundo.
	 */
	bool operator<=(const int &) const;
	/**\brief Operador de igualdad.
	 * \param valor - Entero a comparar con el llamador.
	 * \return true si son iguales y false si no lo son.
	 */
	bool operator==(const int &) const;
	/**\brief Operador de desigualdad.
	 * \param valor - Entero a comparar con el llamador.
	 * \return true si son desiguales y false si no lo son.
	 */
	bool operator!=(const int &) const;
	/**\brief Operador de asignación.
	 * \param rat - Rational a asignar.
	 * \return Devuelve por referencia la asignación.*/
	Rational& operator=(const Rational &);
	/**\brief Operador de asignación.
	 * \param ent - Integer a asignar.
	 * \return Devuelve por referencia la asignación.*/
	Rational& operator=(int);
	/**\brief Operador de asignación.
	 * \param valor - Integer a asignar.
	 * \return Devuelve por referencia la asignación.*/
	Rational& operator=(const double &);
	/**\brief Operador de suma.
	 * \param rat - Rational a sumar.
	 * \return Devuelve un Rational resultado.*/
	Rational operator+(const Rational &) const;
	/**\brief Operador de resta.
	 * \param rat - Rational a restar.
	 * \return Devuelve un Rational resultado.*/
	Rational operator-(const Rational &) const;
	/**\brief Operador de Producto.
	 * \param rat - Rational a multiplicar.
	 * \return Devuelve un Rational resultado.*/
	Rational operator*(const Rational &) const;
	/**\brief Operador de división.
	 * \param rat - Rational a dividir.
	 * \return Devuelve un Rational resultado.*/
	Rational operator/(const Rational &) const;
private:
	/**\brief Numerador.*/
	int n;
	/**\brief Denominador.*/
	int d;
};

/**\brief Minimo Común Multiplo.
 * \param a - Primero número
 * \param b - Segundo número.
 * \return Devuelve el mcm de a y b.*/
int MCM(int,int);

/**\brief Máximoo Común Divisor.
 * \param a - Primero número
 * \param b - Segundo número.
 * \return Devuelve el mcd de a y b.*/
int MCD(int,int);

#endif
