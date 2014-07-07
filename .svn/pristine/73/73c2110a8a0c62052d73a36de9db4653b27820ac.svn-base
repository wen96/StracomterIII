/*
 * Rational.cc
 *
 *  Created on: 28/10/2011
 *      Author: Chutaos Team.
 */

#include "Rational.h"

Rational::Rational(void) {
	n = 0;
	d = 1;
}

Rational::Rational(int num, int den) {
	/*int mcd = MCD(num,den);
	n = num/mcd;
	if(den != 0)
		d = den/mcd;
	else
		d = 1;
	*/
	if(den != 0)
	{
		int mcd=MCD(num,den);
		n = num/mcd;
		d = den/mcd;
	}else
	{
		n = num;
		d = 1;
	}
}

Rational::Rational(int valor) {

	n = valor;
	d = 1;
}


Rational::Rational(const Rational &rat) {

	n = rat.n;
	d = rat.d;
}

Rational::Rational(double valor) {

	double num = valor;
	double den = 1;

	for(int i = 0; i < RAT_ROUND; i++)
	{
		num *= 10;
		den *= 10;
	}
	n = num;
	d = den;


	this->Reducir();
}
Rational::~Rational(void) {
	n = 0;
	d = 1;
}

int
Rational::getNumerador(void) const {
	return n;
}

int
Rational::getDenominador(void) const {
	return d;
}

void
Rational::setNumerador(int num) {
	n = num;
	int mcd = MCD(n,d);
	n = n/mcd;
	d = d/mcd;
}

bool
Rational::setDenominador(int den) {
	bool cambio = false;
	int mcd;
	if(den != 0)
	{
		d = den;
		mcd = MCD(n,d);
		d = d/mcd;
		n = n/mcd;
		cambio = true;
	}

	return cambio;
}
float
Rational::getValor(void) const {
	if(d!=0)
	{
		float num = n;
		float den = d;
		return num/den;
	}else
	{
		return 0.0;
	}

}

int
Rational::getValorInt(void) const {
	if(d!=0)
	{
		int num = n;
		int den = d;
		return num/den;
	}else
		return 0;
}

bool
Rational::invertir(void){

	bool inversa = false;
	int aux;
	if(n != 0)
	{
		aux = n;
		n = d;
		d = aux;
		inversa = true;
	}

	return inversa;
}

bool
Rational::isInteger(void){
	Reducir();
	return d==1;
}

Rational
Rational::inversa(void) const {
	Rational rat(*this);
	if(n != 0)
	{
		rat.setNumerador(d);
		rat.setDenominador(n);
	}

	return rat;
}

void
Rational::setError() {
	n = 1;
	d = 0;
}

bool
Rational::operator!=(const Rational &rat) const {

	bool distintos = false;

	if(n != rat.n || d != rat.d)
		distintos = true;

	return distintos;
}

bool
Rational::operator==(const Rational &rat) const {

	bool iguales = false;

	if(n == rat.n && d == rat.d)
		iguales = true;

	return iguales;
}

Rational &
Rational::operator=(const Rational &rat) {

	if(this != &rat)
	{
		this->~Rational();
		this->n = rat.n;
		this->d = rat.d;
		this->Reducir();
	}

	return *this;
}

Rational &
Rational::operator=(int ent) {

	this->~Rational();
	this->n = ent;
	this->d = 1;

	return *this;
}

Rational &
Rational::operator=(const double &valor) {

	this->~Rational();

	double num = valor;
	double den = 1;

	for(int i = 0; i < RAT_ROUND; i++)
	{
		num *= 10;
		den *= 10;
	}
	n = num;
	d = den;

	this->Reducir();

	return *this;
}

Rational
Rational::operator*(const Rational &rat) const{

	Rational tmp;
	tmp.d = this->d * rat.d;
	tmp.n = this->n * rat.n;

	tmp.Reducir();
	return tmp;
}


Rational
Rational::operator/(const Rational &rat) const{

	Rational tmp;
	tmp.d = this->d * rat.n;
	tmp.n = this->n * rat.d;

	tmp.Reducir();
	return tmp;
}

Rational
Rational::operator+(const Rational &rat) const{

	Rational tmp;
	int mcm = MCM(this->d, rat.d);
	tmp.d = mcm;
	tmp.n = ((this->n*(mcm/this->d)) + (rat.n*(mcm/rat.d)));

	tmp.Reducir();
	return tmp;
}

Rational
Rational::operator-(const Rational &rat) const{

	Rational tmp;
	int mcm = MCM(this->d, rat.d);
	tmp.d = mcm;
	tmp.n = ((this->n*(mcm/this->d)) - (rat.n*(mcm/rat.d)));

	tmp.Reducir();
	return tmp;
}

void
Rational::Reducir() {

	if(n != 0 && d != 0)
	{
		int mcd=MCD(n,d);
		n /= mcd;
		d /= mcd;
		if(d < 0)
		{
			d *= -1;
			n *= -1;
		}
	}else if(n==0 && d!=0)
	{
		n=0;
		d=1;
	}else
	{
		n=1;
		d=0;
	}
}
ostream & operator<<(ostream &os, const Rational &rat) {

	if(rat.getDenominador()==1)
		os << rat.getNumerador();
	else if(rat.getDenominador() == 0)
		os << "Error";
	else
		os << rat.getNumerador() << "/" << rat.getDenominador();
	return os;
}


int MCM(int a, int b) {

	int mcm;
	if(a > b)
		mcm = a;
	else
		mcm = b;
	while(mcm%a != 0 || mcm%b != 0)
		mcm++;

	return mcm;
}

int MCD(int a, int b) {

	int mcd = 1;
	int i;
	int max;
	if(a > b)
		max = a;
	else
		max = b;
	for(i = 1; i <= max; i++)
	{
		if(a%i == 0 && b%i == 0)
			mcd = i;
	}

	return mcd;
}

bool
Rational::operator>(const Rational &rat) const {

	Rational primero, segundo;
	bool mayor = false;
	int mcm;
	if(rat.n != 0 && n != 0)
	{
		mcm = MCM(d, rat.d);
		primero = *this;
		segundo = rat;
		primero.n = primero.n*(mcm/primero.d);
		primero.d = mcm;

		segundo.n = segundo.n*(mcm/segundo.d);
		segundo.d = mcm;

		mayor = (primero.n > segundo.n);
	}else if(rat.n == 0 && n != 0)
		mayor = (n > 0);
	else if(rat.n != 0 && n == 0)
		mayor = (0 > rat.n);
	else
		mayor = false;

	return mayor;
}

bool
Rational::operator>(const int &valor) const {

	Rational primero, segundo;
	bool mayor = false;
	int mcm;
	segundo = valor;
	if(segundo.n != 0 && n != 0)
	{
		mcm = MCM(d, segundo.d);
		primero = *this;

		primero.n = primero.n*(mcm/primero.d);
		primero.d = mcm;

		segundo.n = segundo.n*(mcm/segundo.d);
		segundo.d = mcm;

		mayor = (primero.n > segundo.n);
	}else if(segundo.n == 0 && n != 0)
		mayor = (n > 0);
	else if(segundo.n != 0 && n == 0)
		mayor = (0 > segundo.n);
	else
		mayor = false;

	return mayor;
}

bool
Rational::operator>=(const Rational &rat) const {

	Rational primero, segundo;
	bool mayor = false;
	int mcm;
	if(rat.n != 0 && n != 0)
	{
		mcm = MCM(d, rat.d);
		primero = *this;
		segundo = rat;
		primero.n = primero.n*(mcm/primero.d);
		primero.d = mcm;

		segundo.n = segundo.n*(mcm/segundo.d);
		segundo.d = mcm;

		mayor = (primero.n >= segundo.n);
	}else if(rat.n == 0 && n != 0)
		mayor = (n >= 0);
	else if(rat.n != 0 && n == 0)
		mayor = (0 >= rat.n);
	else
		mayor = true;

	return mayor;
}

bool
Rational::operator>=(const int &valor) const {

	Rational primero, segundo;
	bool mayor = false;
	int mcm;
	segundo = valor;
	if(segundo.n != 0 && n != 0)
	{
		mcm = MCM(d, segundo.d);
		primero = *this;

		primero.n = primero.n*(mcm/primero.d);
		primero.d = mcm;

		segundo.n = segundo.n*(mcm/segundo.d);
		segundo.d = mcm;

		mayor = (primero.n >= segundo.n);
	}else if(segundo.n == 0 && n != 0)
		mayor = (n >= 0);
	else if(segundo.n != 0 && n == 0)
		mayor = (0 >= segundo.n);
	else
		mayor = true;

	return mayor;
}

bool
Rational::operator<(const Rational &rat) const {

	Rational primero, segundo;
	bool menor = false;
	int mcm;
	if(rat.n != 0 && n != 0)
	{
		mcm = MCM(d, rat.d);
		primero = *this;
		segundo = rat;
		primero.n = primero.n*(mcm/primero.d);
		primero.d = mcm;

		segundo.n = segundo.n*(mcm/segundo.d);
		segundo.d = mcm;

		menor = (primero.n < segundo.n);
	}else if(rat.n == 0 && n != 0)
		menor = (n < 0);
	else if(rat.n != 0 && n == 0)
		menor = (0 < rat.n);
	else
		menor = false;

	return menor;
}

bool
Rational::operator<(const int &valor) const {

	Rational primero, segundo;
	bool menor = false;
	int mcm;
	segundo = valor;
	if(segundo.n != 0 && n != 0)
	{
		mcm = MCM(d, segundo.d);
		primero = *this;

		primero.n = primero.n*(mcm/primero.d);
		primero.d = mcm;

		segundo.n = segundo.n*(mcm/segundo.d);
		segundo.d = mcm;

		menor = (primero.n < segundo.n);
	}else if(segundo.n == 0 && n != 0)
		menor = (n < 0);
	else if(segundo.n != 0 && n == 0)
		menor = (0 < segundo.n);
	else
		menor = false;

	return menor;
}

bool
Rational::operator<=(const Rational &rat) const {

	Rational primero, segundo;
	bool menor = false;
	int mcm;
	if(rat.n != 0 && n != 0)
	{
		mcm = MCM(d, rat.d);
		primero = *this;
		segundo = rat;
		primero.n = primero.n*(mcm/primero.d);
		primero.d = mcm;

		segundo.n = segundo.n*(mcm/segundo.d);
		segundo.d = mcm;

		menor = (primero.n <= segundo.n);
	}else if(rat.n == 0 && n != 0)
		menor = (n <= 0);
	else if(rat.n != 0 && n == 0)
		menor = (0 <= rat.n);
	else
		menor = true;

	return menor;
}

bool
Rational::operator<=(const int &valor) const {

	Rational primero, segundo;
	bool menor = false;
	int mcm;
	segundo = valor;
	if(segundo.n != 0 && n != 0)
	{
		mcm = MCM(d, segundo.d);
		primero = *this;

		primero.n = primero.n*(mcm/primero.d);
		primero.d = mcm;

		segundo.n = segundo.n*(mcm/segundo.d);
		segundo.d = mcm;

		menor = (primero.n <= segundo.n);
	}else if(segundo.n == 0 && n != 0)
		menor = (n <= 0);
	else if(segundo.n != 0 && n == 0)
		menor = (0 <= segundo.n);
	else
		menor = true;

	return menor;
}

bool
Rational::operator!=(const int &valor) const {

	bool distintos = false;
	Rational rat = valor;
	if(n != rat.n || d != rat.d)
		distintos = true;

	return distintos;
}

bool
Rational::operator==(const int &valor) const {

	bool iguales = false;

	Rational rat = valor;
	if(n == rat.n && d == rat.d)
		iguales = true;

	return iguales;
}
