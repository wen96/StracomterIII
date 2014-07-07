/*
 * Simplex.cc
 *
 *  Created on: 14/11/2011
 *      Author: Chutaos Team
 */

#include "Simplex.h"

const string r4 = "x1 <= 1";
const string r5 = "x2 <= 6";

Simplex::Simplex() {
	// TODO Auto-generated constructor stub
	restricciones = new Matrix<Rational>(0, 0);
	objetivo = new Matrix<Rational>(0, 0);
	soluciones = new Matrix<Rational>(0, 0);
	variables = new Matrix<Rational>(0, 0);
	Z.setError();
}

Simplex::~Simplex() {

	if (restricciones != NULL)
	{
		delete restricciones;
		restricciones = NULL;
	}
	if (objetivo != NULL)
	{
		delete objetivo;
		objetivo = NULL;
	}
	if (soluciones != NULL)
	{
		delete soluciones;
		soluciones = NULL;
	}
	if (variables != NULL)
	{
		delete variables;
		variables = NULL;
	}
	while(!Base.empty())
		Base.pop_back();
	Base.clear();
	Z=0;
}

Simplex::Simplex(const Simplex &simplex) {

	if (simplex.restricciones != NULL
		)
		restricciones = new Matrix<Rational>(*simplex.restricciones);
	else
		restricciones = NULL;

	if (simplex.objetivo != NULL
		)
		objetivo = new Matrix<Rational>(*simplex.objetivo);
	else
		objetivo = NULL;

	if (simplex.soluciones != NULL
		)
		soluciones = new Matrix<Rational>(*simplex.soluciones);
	else
		soluciones = NULL;

	if (simplex.variables != NULL
		)
		variables = new Matrix<Rational>(*simplex.variables);
	else
		variables = NULL;
	Base = simplex.Base;
	for(unsigned int i = 0; i < simplex.Base.size(); i++)
		Base.push_back(simplex.Base[i]);
	Z = simplex.Z;

}

Simplex&
Simplex::operator=(const Simplex &simplex) {

	if (this != &simplex) {
		this->~Simplex();

		if (simplex.restricciones != NULL
			)
			restricciones = new Matrix<Rational>(*simplex.restricciones);
		else
			restricciones = NULL;

		if (simplex.objetivo != NULL
			)
			objetivo = new Matrix<Rational>(*simplex.objetivo);
		else
			objetivo = NULL;

		if (simplex.soluciones != NULL
			)
			soluciones = new Matrix<Rational>(*simplex.soluciones);
		else
			soluciones = NULL;

		if (simplex.variables != NULL
			)
			variables = new Matrix<Rational>(*simplex.variables);
		else
			variables = NULL;

		Base = simplex.Base;
		for(unsigned int i = 0; i < simplex.Base.size(); i++)
			Base.push_back(simplex.Base[i]);
		Z = simplex.Z;
	}

	return *this;
}
void Simplex::addRestriccion(string restriccion) {

	string tmp;
	string res;
	char c;
	int signo = 1;
	int campo = 0; // 0 = coeficiente; 1 = num_variable; 2 = Término independiente.
	int coeficiente = 0;
	int num_variable = 0;
	int num_restricciones = restricciones->getF() + 1;
	bool escribir = false;
	int inde; //Término Independiente.
	unsigned int i;

	int tipo;

	if (restriccionTipo(restriccion, '>'))
		tipo = 1;
	else if (restriccionTipo(restriccion, '<'))
		tipo = 2;
	else
		tipo = 0;

	vector<string> vres = Split(restriccion, '=');

	if (tipo == 1)
		res = deleteChar(vres[0], '>');
	else if (tipo == 2)
		res = deleteChar(vres[0], '<');
	else
		res = vres[0];

	tmp = "";
	for (i = 0; i < res.length(); i++) {
		c = res[i];

		switch (c) {
		case '+': //Cuando leamos el signo pasamos a escribir en el campo de variable.
			signo = 1;
			campo = 1;
			escribir = true;
			break;
		case '-': //Cuando leamos el signo pasamos a escribir en el campo de varible.
			signo = -1;
			campo = 1;
			escribir = true;
			break;
		case 'x': //Cuando leamos la variable, escribirmos el coeficiente.
			campo = 0;
			escribir = true;
			break;
		}

		if (escribir) {
			switch (campo) {
			case 0:
				coeficiente = atoi(tmp.c_str());
				if (coeficiente == 0)
					coeficiente = 1;
				coeficiente *= signo;
				campo = 1;
				break;
			case 1:
				num_variable = atoi(tmp.c_str());
				(*restricciones)(num_restricciones, num_variable) = coeficiente;
				break;
			}
			tmp = "";
			escribir = false;
		} else
			tmp += c; //si no escribirmos añadimos al tmp.
	}

	//Se repite el proceso de inserción para la última variable.
	num_variable = atoi(tmp.c_str());
	(*restricciones)(num_restricciones, num_variable) = coeficiente;

	//Aquí se añaden las variables de Holgura.
	if (tipo == 1)
		(*restricciones)(num_restricciones, restricciones->getC() + 1) = -1;
	else if (tipo == 2)
		(*restricciones)(num_restricciones, restricciones->getC() + 1) = 1;

	//Término independiente es la parte después del igual.
	inde = atoi(vres[1].c_str());
	(*soluciones)(num_restricciones, 1) = inde;

	//Incrementar el tamaño de la matriz objetivo para contemplar...
	for (int j = objetivo->getC() -1; j <= restricciones->getC(); j++)//antes con objetivo->getC() - 1
		(*objetivo)(1, j) = 0;

}

void Simplex::setObjetivo(string obj) {

	string tmp;
	char c;
	int signo = 1;
	int campo = 0; // 0 = coeficiente; 1 = num_variable; 2 = Término independiente.
	int coeficiente = 0;
	int num_variable = 0;
	bool escribir = false;
	unsigned int i;
	bool salir = false;

	//Cuando se normalice, en vez de hacer Z=1, habra que hacer si es Min Z=1 y si es Max Z=-1;, por que se simplifica como -Min
	Z = 0;

	tmp = "";
	for (i = 0; i < obj.length() && !salir; i++) {
		if (obj[i] == ' ') {
			if (tmp == "Max")
				Z = -1;
			else if (tmp == "Min")
				Z = 1;
		}

		if (obj[i] == 'z') {
			salir = true;
			i++;
		}

		if (obj[i] != ' ')
			tmp += obj[i];
	}

	tmp = "";

	for (; i < obj.length(); i++) {
		c = obj[i];

		switch (c) {
		case '+': //Cuando leamos el signo pasamos a escribir en el campo de variable.
			signo = 1;
			campo = 1;
			escribir = true;
			break;
		case '-': //Cuando leamos el signo pasamos a escribir en el campo de varible.
			signo = -1;
			campo = 1;
			escribir = true;
			break;
		case 'x': //Cuando leamos la variable, escribirmos el coeficiente.
			campo = 0;
			escribir = true;
			break;
		}

		if (escribir) {
			switch (campo) {
			case 0:
				coeficiente = atoi(tmp.c_str());
				if (coeficiente == 0)
					coeficiente = 1;
				coeficiente *= signo;
				campo = 1;
				break;
			case 1:
				num_variable = atoi(tmp.c_str());
				(*objetivo)(1, num_variable) = coeficiente;
				break;
			}
			tmp = "";
			escribir = false;
		} else
			tmp += c; //si no escribirmos añadimos al tmp.
	}

	//Se repite el proceso de inserción para la última variable.
	num_variable = atoi(tmp.c_str());
	(*objetivo)(1, num_variable) = coeficiente;

	*objetivo = (*objetivo) * Z;

}

ostream& operator<<(ostream &os, const Simplex &simplex) {
	Rational err;
	err.setError();
	if (simplex.objetivo != NULL
		)
		os << "Funcion objetivo: " << endl << (*simplex.objetivo) << endl;
	if (simplex.restricciones != NULL
		)
		os << "Restricciones: " << endl << (*simplex.restricciones) << endl;
	if (simplex.soluciones != NULL
		)
		os << "d: " << endl << (*simplex.soluciones) << endl;
	//if(simplex.Z != err)
	//	os << "Optimo: Z = "<<simplex.Z<<endl;
	return os;
}

Matrix<Rational> *Simplex::getObjetivo() const {
	return objetivo;
}

Matrix<Rational> *Simplex::getRestricciones() const {
	return restricciones;
}

Matrix<Rational> *Simplex::getSoluciones() const {
	return soluciones;
}

Matrix<Rational> *Simplex::getVariables() const {
	return variables;
}

Rational Simplex::getZ() const {
	return Z;
}

void Simplex::setZ(Rational z) {
	Z = z;
}

vector<int> Simplex::getBase() const {
	return Base;
}

void Simplex::setBase(vector<int> Base) {
	this->Base = Base;
}

bool Simplex::isCorrect() {
	bool correcto = false;
	if (Z != Rational(-1)) {
		Rational pz = 0;
		for (int i = 0; i < objetivo->getC(); i++)
			pz = pz + (objetivo->getNM(0, i) * variables->getNM(0, i));
		if (pz == Z) {
			correcto = true;
			Rational aux;
			for (int i = 0; i < restricciones->getF() && correcto; i++) {
				aux = 0;
				for (int j = 0; j < restricciones->getC(); j++)
					aux = aux
							+ (restricciones->getNM(i, j)
									* variables->getNM(0, i));
				if (aux != soluciones->getNM(0, i))
					correcto = false;
			}
		}
	}
	return correcto;
}

vector<int> Simplex::getBaseInicial(const int tam) const {
	vector<int> base(tam);
	bool enc = true;

	const Matrix<Rational> aux = (*restricciones);
	/*for(int i=tam-1; i>=0; i--)
	 base.push_back((*restricciones).getC()-i);
	 */

	for (int i = 1; i <= tam; i++) {
		for (int j = 1; j <= aux.getC(); j++)
			if (aux(i, j) == 1) {
				enc = true;
				for (int k = 1; k <= tam; k++)
					if (k != i && aux(k, j) != 0)
						enc = false;
				if (enc)
					base[i - 1] = j;
			}
		if (!enc)
			base[i-1] = 0;

	}
	return base;
}

vector<int> Simplex::getBaseInicialD(const int tam) {
	vector<int> base(tam);
	bool enc = true;
	/*for(int i=tam-1; i>=0; i--)
	 base.push_back((*restricciones).getC()-i);
	 */

	for (int i = 1; i <= tam; i++) {
		for (int j = 1; j <= (*restricciones).getC(); j++)
			if ((*restricciones)(i, j) == 1 || (*restricciones)(i, j) == -1) {
				enc = true;
				for (int k = 1; k <= tam; k++)
					if (k != i && (*restricciones)(k, j) != 0)
						enc = false;
				if (enc)
					base[i - 1] = j;
				if ((*restricciones)(i, j) == -1) {
					for (int k = 1; k <= (*restricciones).getC(); k++)
						(*restricciones)(i, k) = (*restricciones)(i, k) * -1;
					(*soluciones)(i, 1) = (*soluciones)(i, 1) * -1;
				}
			}
		if (!enc)
			base[i] = 0;
	}
	return base;
}

Matrix<Rational> Simplex::getCB(void) {
	Matrix<Rational> cb(1, Base.size());
	for (unsigned int i = 1; i <= Base.size(); i++)
		cb(1, i) = (*objetivo)(1, Base[i - 1]);

	return cb;
}

void Simplex::cambiaIndice(int s, int e) {
	for (int unsigned i = 0; i < Base.size(); i++)
		if (Base[i] == s)
			Base[i] = e;
}

int Simplex::indiceSaleP(int indice) {
	Rational min = 99;
	int sale = 0;
	Matrix<Rational> Yk = (*restricciones).getCol(indice);
	for (int i = 1; i <= Yk.getF(); i++)
		if (Yk(i, 1) > 0) {
			if ((*soluciones)(i, 1) / Yk(i, 1) < min) {
				min = (*soluciones)(i, 1) / Yk(i, 1);
				sale = Base[i - 1];
			}
		}
	return sale;
}

int Simplex::indiceEntraP(const Matrix<Rational> &zjcj) {
	Rational max = 0;
	int entra = 0;

	for (int i = 1; i <= zjcj.getC(); i++)
		if (max < zjcj(1, i)) {
			max = zjcj(1, i);
			entra = i;
		}

	return entra;
}

int Simplex::indiceSaleD(void) {
	Rational min = 0;
	int sale = 0;
	for (int i = 1; i <= (*soluciones).getF(); i++)
		if (min > (*soluciones)(i, 1)) {
			min = (*soluciones)(i, 1);
			sale = Base[i - 1];
		}

	return sale;
}

int Simplex::indiceEntraD(int indice, Matrix<Rational>& zjcj) {
	Rational min = 99;
	int fil, entra = 0;
	for (unsigned int i = 0; i < Base.size(); i++)
		if (Base[i] == indice)
			fil = i;
	Matrix<Rational> Yk = (*restricciones).getFil(fil + 1);
	for (int i = 1; i <= Yk.getC(); i++)
		if (Yk(1, i) < 0) {
			if (zjcj(1, i) / Yk(1, i) < min) {
				min = zjcj(1, i) / Yk(1, i);
				entra = i;
			}
		}
	return entra;
}

void Simplex::CalculaZ(void) {
	Rational z = 0;

	for (unsigned int i = 1; i <= Base.size(); i++)
		z = z + (*soluciones)(i, 1) * (*objetivo)(1, Base[i - 1]);

	Z = Z * z;
}

void Simplex::MuestraSolucion(void) {
	cout << "Solucion Optima: " << endl;
	cout << "Z: " << (Z) << endl << endl;
	for (int i = 1; i <= soluciones->getF(); i++)
		cout << "X" << Base[i-1] << ": " << (*soluciones)(i, 1) << endl;
}

bool Simplex::isBase() {
	bool esbase = true;
	for (unsigned int i = 0; i < Base.size(); i++)
		if (Base[i] == 0)
			esbase = false;

	return esbase;
}

vector<int> Simplex::insertarArtificiales(void) {
	/*Aqui iria lo mismo que en insertarOlgura.
	 * solo que las insertara donde en base halla un 0
	 * tras insertarlo el 0 lo cmabaira x su indice
	 * y añade a la funcion objetico el M*/
	vector<int> vart;
	for (unsigned int i = 0; i < Base.size(); i++)
		if (Base[i] == 0) {
			(*restricciones)(i + 1, restricciones->getC() + 1) = 1;
			(*objetivo)(1, restricciones->getC()) = 999999;
			Base[i] = objetivo->getC();
			vart.push_back((*restricciones).getC());
		}
	return vart;
}

bool Simplex::dependeArtificial(vector<int>& vart) {
	bool depende = false;
	for (unsigned int i = 0; i < vart.size(); i++)
		for (unsigned int j = 0; j < Base.size(); j++)
			if (vart[i] == Base[j])
				if ((*soluciones)(j + 1, 1) != 0)
					depende = true;
	return depende;
}

void Simplex::eliminaArtificiales(void) {
	for (int i = 1; i <= (*objetivo).getC(); i++)
		if ((*objetivo)(1, i) == 999999)
		{
			(*objetivo)=(*objetivo).chaMatrix(1, i - 1);
			(*restricciones)=(*restricciones).chaMatrix((*restricciones).getF(),i-1);
		}
}

bool Simplex::varEnteras(void) {
	bool enteras = true;
	for (int i = 1; i < (*soluciones).getF(); i++)
		if (!(*soluciones)(i, 1).isInteger())
			enteras = false;
	return enteras;
}

vector<int> Simplex::varFloat(void) {
	vector<int> vFloat;
	for (int i = 1; i <= (*soluciones).getF(); i++)
		if (!(*soluciones)(i, 1).isInteger())
			vFloat.push_back(Base[i-1]);
	sort(vFloat.begin(),vFloat.end(), ordenaEnteros);

	return vFloat;
}

int Simplex::posBase(const int n) {
	int pos;
	for (unsigned int i = 0; i < Base.size(); i++)
		if (Base[i]==n)
			pos=i;
	return pos;
}

int Simplex::SimplexPenal(void) {
	bool optimo = false, acotado = true, bArti = false;
	int entra, status = -2;
	if (!(*soluciones).isOneNegative()) {
		Matrix<Rational> FO= (*objetivo);
		if (Base.size() == 0)
		{
			vector<int> aux;
			int filas = soluciones->getF();
			//Copio el vector a mano. Pese a que todo el mundo diga que si que se copian.
			aux = this->getBaseInicial(filas);
			//cout << "AQUI " << *this << endl;
			for(unsigned int i = 0; i < aux.size(); i++)
				Base.push_back(aux[i]);
			//Base = this->getBaseInicial((*soluciones).getF());
		}
		vector<int> artificiales;

		if (!isBase()) {
			artificiales = insertarArtificiales();
			bArti = true;
		}
		Matrix<Rational> CB = getCB();
		Matrix<Rational> RS(1, 1);
		Matrix<Rational> ZjCj(1, (*restricciones).getC());
		while (acotado && !optimo) {
			for (int i = 1; i <= (*restricciones).getC(); i++)
			{
					ZjCj(1, i) = (CB * (*restricciones).getCol(i))(1, 1) - (*objetivo)(1, i);
			}
			if (ZjCj.isNegative()) {
				if (!(bArti && dependeArtificial(artificiales))) {
					optimo = true;
					bArti = false;
					CalculaZ();
				}else
				{
					acotado=false;
				}
			} else {
				entra = indiceEntraP(ZjCj);
				if ((*restricciones).getCol(entra).isNegative())
					acotado = false;
				else {
					cambiaIndice(indiceSaleP(entra), entra);
					CB = getCB();
					//Creamos la la nueva matriz de restricciones con la base nueva
					RS = ((*restricciones).conMatrix((*soluciones))).baseTo(
							Base);
					(*soluciones) = RS.getCol(RS.getC());
					(*restricciones) = RS.chaMatrix(RS.getF(), RS.getC() - 1);
				}
			}
		}
		eliminaArtificiales();
		if (optimo)
			status = 0;
		else if (!acotado)
			status = -1;
		else if (bArti)
			status = -3;
	} else {
		status = SimplexDual();
	}
	return status;
}

int Simplex::SimplexDual(void) {
	bool optimo = false, acotado = true;
	int entra, sale, status = -2;
	if ((*soluciones).isOneNegative()) {
		if (Base.size() == 0)
			Base = getBaseInicialD((*soluciones).getF());
		if (isBase()) {
			Matrix<Rational> CB = getCB();
			Matrix<Rational> RS(1, 1);
			Matrix<Rational> ZjCj(1, (*restricciones).getC());

			while (acotado && !optimo) {
				for (int i = 1; i <= (*restricciones).getC(); i++)
					ZjCj(1, i) = (CB * (*restricciones).getCol(i))(1, 1)
							- (*objetivo)(1, i);
				if ((*soluciones).isPositive()) {
					optimo = true;
					CalculaZ();
				} else {
					sale = indiceSaleD();
					entra = indiceEntraD(sale, ZjCj);
					if (!ZjCj.isNegative())
						acotado = false;
					else {
						cambiaIndice(sale, entra);
						CB = getCB();
						//Creamos la la nueva matriz de restricciones con la base nueva
						RS = ((*restricciones).conMatrix((*soluciones))).baseTo(
								Base);
						(*soluciones) = RS.getCol(RS.getC());
						(*restricciones) = RS.chaMatrix(RS.getF(),
								RS.getC() - 1);
					}
				}
			}

			if (optimo)
				status = 0;
			else if (!acotado)
				status = -1;
		}
	} else {
		status = SimplexPenal();
	}
	return status;
}

void Simplex::forzarEntero(Simplex& def, Simplex& exc, int pos)
{
	int x = (*soluciones)(posBase(pos)+1,1).getValorInt();
	(*def.restricciones)((*def.restricciones).getF()+1,pos)=1;
	(*exc.restricciones)((*exc.restricciones).getF()+1,pos)=1;
	(*def.restricciones)((*def.restricciones).getF(),(*def.restricciones).getC()+1)=1;
	(*exc.restricciones)((*exc.restricciones).getF(),(*exc.restricciones).getC()+1)=-1;
	(*def.soluciones)((*def.soluciones).getF()+1,1)=x;
	(*exc.soluciones)((*exc.soluciones).getF()+1,1)=x+1;
	for (int j = def.objetivo->getC(); j <= def.restricciones->getC(); j++)
		(*def.objetivo)(1, j) = 0;
	for (int j = exc.objetivo->getC(); j <= exc.restricciones->getC(); j++)
		(*exc.objetivo)(1, j) = 0;
}

int Simplex::SimplexInt(void) {
	int status,statusGlobal = -2, numNodos = 0;
	bool optimo = false;
	int maxZ;
	vector<Simplex*> NV, Enteros;
	Simplex *nodo;
	NV.push_back(this);
	vector<int> vFloat;//Posicion de la variable en BASE

	while (NV.size() > 0 && (!optimo))
	{
		nodo = new Simplex(*NV[0]);
		numNodos++;
		status = nodo->SimplexPenal();
		if(numNodos==1)
			maxZ=nodo->getZ().getValorInt();
		vFloat = nodo->varFloat();
		if (status == 0 && vFloat.size()>0)
		{
			Simplex *def; def = new Simplex(*NV[0]);
			Simplex *exc; exc = new Simplex(*NV[0]);
			nodo->forzarEntero(*def,*exc,vFloat[0]);//Crear las nuevas restricciones en los Simplex def y exc para la variable vFloat[0]
			NV.push_back(def);
			NV.push_back(exc);
		} else if (status == 0)
		{
			if (numNodos == 1)
			{
				optimo=true;
				*this=*nodo;
				statusGlobal=0;
			} else
			{
				if (maxZ == nodo->getZ().getValor())
				{
					optimo = true;
					*this=*nodo;
					statusGlobal=0;
				} else
				{
					if(Z <= nodo->Z)
					{
						*this=*nodo;
						statusGlobal=0;
					}
				}
			}
		}
		NV.erase(NV.begin());
	}
	eliminaArtificiales();
	return statusGlobal;
}

bool ordenaEnteros(const int& x, const int& y)
{
	return x<y;
}


vector<string> Split(string cadena, char c) {

	string tmp = "";
	vector<string> v;

	for (unsigned int i = 0; i < cadena.length(); i++) {
		if (cadena[i] == '=') {
			v.push_back(tmp);
			tmp = "";
		} else
			tmp += cadena[i];
	}

	v.push_back(tmp);

	return v;
}

bool restriccionTipo(string cadena, char c) {

	bool existe = false;

	for (unsigned int i = 0; i < cadena.length() && !existe; i++) {
		if (cadena[i] == c)
			existe = true;
	}

	return existe;
}

string deleteChar(string cadena, char c) {

	string tmp = "";

	for (unsigned int i = 0; i < cadena.length(); i++) {
		if (cadena[i] != c)
			tmp += cadena[i];
	}

	return tmp;
}
