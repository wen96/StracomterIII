/*
 * Simplex.h
 *
 *  Created on: 14/11/2011
 *      Author: Chutaos Team
 */

#ifndef SIMPLEX_H_
#define SIMPLEX_H_

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stdlib.h>

using namespace std;

#include "Matrix.h"
#include "Rational.h"
/**\class Simpex
 * Clase que sirve para implementar el algoritmo Simplex*/
class Simplex {

	/**\brief Sobrecarga del operador de salida.
	 * Muestra las matrices del problema y si ya se ha obenido el optimo, muestra Z.
	 * \param os - ostring de salida.
	 * \param simplex - Objeto simplex para mostrar.
	 * \return Devuelve el ostring de salida.*/
	friend ostream& operator<<(ostream &, const Simplex &);
public:
	/**\brief Constructor por defecto.*/
	Simplex();

	/**\brief Destructor por defecto.*/
	virtual ~Simplex();

	/**\brief Constructor de copia.
	 * \param simplex - Simplex del que hacer la copia.*/
	Simplex(const Simplex &);

	/**\brief Sobrecarga del operador =.
	 * \param simplex - Simplex a copiar.
	 * \return Devuelve el objeto copiado. */
	Simplex& operator=(const Simplex &);

	/**\brief Añade una restricción.
	 * restriccion - String con la restricción.*/
	void addRestriccion(string);

	/**\brief Carga un objetivo.
	 * obj - String con el objetivo.*/
	void setObjetivo(string);

	/**\brief Devuelve el puntero a la matriz Objetivo.
	 * \return *obtejto puntero a matrix */
	Matrix<Rational> *getObjetivo() const;

	/**\brief Devuelve el puntero a la matriz Restricciones.
	 * \return *obtejto puntero a matrix */
	Matrix<Rational> *getRestricciones() const;

	/**\brief Devuelve el puntero a la matriz Soluciones.
	 * \return *obtejto puntero a matrix */
	Matrix<Rational> *getSoluciones() const;

	/**\brief Devuelve el puntero a la matriz Variables.
	 * \return *obtejto puntero a matrix */
	Matrix<Rational> *getVariables() const;

	/**\brief Devuelve Rational Z.
	 * \return Z Rational con resultado de simplex */
	Rational getZ() const;

	/**\brief Setter de Z .
	 * \param z - Rational del resultado a asignar.*/
	void setZ(Rational z);

	vector<int> getBase() const;
	void setBase(vector<int> Base);

	/**\brief Devuelve true si simplex cumple todas las restricciones.
	 * \return correcto si se cumple. */
	bool isCorrect(void);

	/**\brief Obtener la Base Inicial
	 * \param tam Tamaño de la matriz
	 * \return devuelve un vector con la BaseInicial y un 0 si no existe esa columna*/
	vector<int> getBaseInicial(const int) const;

	/**\brief Obtener la Base Inicial para Dual (admite el -1)
	 * \param tam Tamaño de la matriz
	 * \return devuelve un vector con la BaseInicial y un 0 si no existe esa columna*/
	vector<int> getBaseInicialD(const int);

	/**\brief Obtener CB
	 * (valor en funcion Objetivo de los indices que estan en la base)
	 * \return Devuelve un Vector tipo Matrix con los valores CB*/
	Matrix<Rational> getCB(void);

	/**\brief Obtener la variable Xi
	 * \param i - indice de la variable
	 * \return Devuelve un rational*/
	Rational getXi(int i);

	/**\brief Cambia Indice de la base
	 * \param s el numero del indice que sale
	 * \param e el numero del indice que entra*/
	void cambiaIndice(int, int);

	/**\brief Devuelve el indice que entra a la Base
	 * \param zjcj La matrix(unidimensional) Zj-Cj para elegir cual entra
	 * \return entra el numero del indice que entra*/
	int indiceEntraP(const Matrix<Rational>&);

	/**\brief Devuelve el indice que sale a la Base
	 * \param indice el numero del indice que entrara
	 * \return sale el numero del indice que sale*/
	int indiceSaleP(const int);

	/**\brief Devuelve el indice que entra a la Basee
	 * \return entra el numero del indice que entra*/
	int indiceSaleD(void);

	/**\brief Devuelve el indice que entra a la Base
	 * \param indice el numero del indice que sale
	 * \param zjcj La matrix(unidimensional) Zj-Cj de la que elegiremos quien entra
	 * \return sale el numero del indice que sale*/
	int indiceEntraD(const int, Matrix<Rational>&);

	/**\brief Calcula el valor de Z mediante los vectores Soluciones y Objetivo*/
	void CalculaZ(void);

	/**\brief Imprime por pantalla las variables con sus valores y el valor del Optimo Z*/
	void MuestraSolucion(void);

	/**\brief Dice si un Base es correcto
	 * \return true si el vector es base correcto*/
	bool isBase(void);

	/**\brief Inserta las variables Artificiales para poder obtener la base
	 * \return vart vector con los indices de las variables artifiviales*/
	vector<int> insertarArtificiales(void);

	/**\brief Depende la solucion de las variables artificiales
	 * \param vart el vector con los indices de las variables artificiales
	 * \return depende = true, si una variable artificial pertenece a soluciones, con valor != de 0 */
	bool dependeArtificial(vector<int>&);

	/**\brief Variables Enteras
	 * \return true, si una variable son todas enteras */
	bool varEnteras(void);

	/**\brief Variables Reales
	 * \return vFloat un vector con los indices de las variables que son reales ordenado de menor a mayor*/
	vector<int> varFloat(void);

	/**\brief Posicion en la base
	 * \param n indice de la variable a buscar en la base
	 * \return pos referencia la posicion de la variable en el vector Base*/
	int posBase(const int);

	/**\brief Elimina las variables Artificiales*/
	void eliminaArtificiales(void);

	/**\brief Depende la solucion de las variables artificiales
	 * \param def el Simplex donde haremos que la variable sea menor
	 * \param exc el Simplex donde haremos que la variable sea mayor
	 * \param pos el indice de la variable que queremos forzar a ser entera*/
	void forzarEntero(Simplex&, Simplex&, int);

	/**\brief Metodo Simplex por Penalizaciones.
	 * (resuelve el estandar y el de penalizaciones)
	 * \return status devuelve un 0 si tiene optimo y -1 si es no acotado. */
	int SimplexPenal(void);

	/**\brief Metodo Simples Dual.
	 * \return status devuelve un 0 si tiene optimo, -1 si es no acotado y -2 si no se puede optener la base. */
	int SimplexDual(void);

	/**\brief Metodo Simples para Enteros.(Recursiva)
	 * \param Base el vector base en el estado actual, se empieza siendo Base=Null
	 * \return status devuelve un 0 si tiene optimo, -1 si es no acotado y -2 si no se puede optener la base. */
	int SimplexInt(void);

private:
	/**\brief Restricciones.*/
	Matrix<Rational> *restricciones;
	/**\brief Función Objetivo.*/
	Matrix<Rational> *objetivo;
	/**\brief Vector Soluciones.*/
	Matrix<Rational> *soluciones;
	/**\brief Vector Variables.*/
	Matrix<Rational> *variables;
	/**\brief Vector Base.*/
	vector<int> Base;
	/**\brief Rational resultado Z.*/
	Rational Z;
};

//Funciones Ajenas a la clase Simplex.

/**\bief Corta una cadena por un caracter.
 * \param cadena - string a partir.
 * \param c - char por el que partir la cadena.
 * \return Un vector con los string resultantes.*/
vector<string> Split(string, char);

/**\bief Detecta el tipo de la restriccion.
 * \param cadena - string con la restriccion.
 * \param c - char con el tipo de la restriccion.
 * \return existe devuelve True, si la restriccion "cadena" es de tipo "c".*/
bool restriccionTipo(string, char);

/**\bief Elimina un caracter de una cadena.
 * \param cadena - string tratar.
 * \param c - char que queremos eliminar de la cadena.
 * \return tmp contiene el resultado "cadena" sin el char "c".*/
string deleteChar(string, char);

/** \beif Ordena numeros enteros
 * \param x primer numero
 * \param y segundo numero
 * \return True si x<y*/
bool ordenaEnteros(const int&, const int&);

#endif /* SIMPLEX_H_ */
