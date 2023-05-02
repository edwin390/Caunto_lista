#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std;

class cMotor
{
public:
	cMotor();
	void imprimir();
private:
	int iCilindros;
	int cilindrada;
};

cMotor::cMotor()
{
	iCilindros = 4;
}

void cMotor::imprimir()
{
	cout << "el motor tiene: " << iCilindros << " cilindros" << endl;
}

class cAuto
{
public:
	cAuto();
	void acelerar();
	void frenar();
	virtual void imprimir();

protected:
	cMotor motor;
	float velocidad;
};

cAuto::cAuto()
{
	velocidad = 0;
}

void cAuto::acelerar()
{
	if (velocidad <= 200)
		velocidad++;
}

void cAuto::frenar()
{
	if (velocidad > 0)
		velocidad--;
}

void cAuto::imprimir()
{
	if (velocidad > 0)
	{
		cout << "auto:" << endl;
		motor.imprimir();
		cout << "el auto va a una velocidad de: " << velocidad << "km/h" << endl;

	}
	else
		cout << "usted no se esta moviendo" << endl;
}

class cPatrulla : public cAuto
{
public:
	cPatrulla();
	void acelerar();
	void encender_sirena(bool);
	void imprimir();
private:
	bool sirena;
};

cPatrulla::cPatrulla()
{
	sirena = false;
}

void cPatrulla::acelerar()
{
	if (velocidad <= 200)
		velocidad += 2;
}

void cPatrulla::encender_sirena(bool encender)
{
	if (encender == true)
		sirena = true;
}

void cPatrulla::imprimir()
{

	if (velocidad > 0)
	{
		cout << "patrulla:" << endl;
		motor.imprimir();
		cout << "la patrulla va a una velocidad de: " << velocidad << "km/h" << endl;
	}
	else
		cout << "usted no se esta moviendo" << endl;
	if (sirena == true)
		cout << "la sirena esta encendida" << endl;
	else
		cout << "la sirena esta apagada" << endl;
}

class cPatrullablin : public cAuto
{
public:
	cPatrullablin();
	void acelerar();
	void encender_sirena(bool);
	void disparo();
	void imprimir();
private:
	bool sirena;
	int blin;
};

cPatrullablin::cPatrullablin()
{
	sirena = false;
	blin = 100;
}

void cPatrullablin::acelerar()
{
	if (velocidad <= 200)
		velocidad += 1.5;
}

void cPatrullablin::encender_sirena(bool encender)
{
	if (encender == true)
		sirena = true;
}

void cPatrullablin::imprimir()
{

	if (velocidad > 0)
	{
		cout << "patrulla blindada:" << endl;
		motor.imprimir();
		cout << "la patrulla blindada va a una velocidad de: " << velocidad << "km/h" << endl;
		cout << "tiene un blindaje de:" << blin << "%" << endl;
	}
	else
		cout << "usted no se esta moviendo" << endl;
	if (sirena == true)
		cout << "la sirena esta encendida" << endl;
	else
		cout << "la sirena esta apagada" << endl;
}

void cPatrullablin::disparo()
{
	blin -= 5;
}

class cToreto : public cAuto
{
public:
	cToreto();
	void acelerar();
	void imprimir();
	void nitro(bool);
private:
	int nit;
};

cToreto::cToreto()
{
	nit = 100;
}

void cToreto::imprimir()
{
	if (velocidad > 0)
	{
		cout << "auto de toreto:" << endl;
		motor.imprimir();
		cout << "el auto va a una velocidad de: " << velocidad << "km/h" << endl;
		cout << "y le queda:" << nit << "% de nitro" << endl;

	}
	else
		cout << "usted no se esta moviendo" << endl;
}
void cToreto::acelerar()
{
	velocidad += 3;
}

void cToreto::nitro(bool boton_rojo)
{
	if (boton_rojo == true)
	{
		velocidad += 10;
		nit -= 10;
	}
}

class cTaxi :public cAuto
{
public:
	void acelerar();
	void imprimir();
};

void cTaxi::acelerar()
{
	velocidad += 5;
}


void cTaxi::imprimir()
{
	if (velocidad > 0)
	{
		cout << "taxi:" << endl;
		motor.imprimir();
		cout << "el auto va a una velocidad de: " << velocidad << "km/h" << endl;

	}
	else
		cout << "usted no se esta moviendo" << endl;
}


class cNodo
{
private:
	void insertar_adelante(cAuto* nd);
	cAuto* eliminar_adelante();
	cAuto* aDat;
	cNodo* pSig;
	cNodo* pAnt;
	friend class cLista;
};

void cNodo::insertar_adelante(cAuto* nd)
{
	cNodo* pNuevo = new cNodo;
	pNuevo->aDat = nd;
	pSig->pAnt = pNuevo;
	pNuevo->pAnt = this;
	pNuevo->pSig = pSig;
	this->pSig = pNuevo;
}

cAuto* cNodo::eliminar_adelante()
{
	cAuto* f;
	cNodo* pEli = pSig;
	f = pEli->aDat;
	pSig = pEli->pSig;
	pSig->pAnt = this;
	delete pEli;
	return f;

}

class cLista
{
public:
	cLista();
	~cLista();
	void insertar_inicio(cAuto*);
	cAuto* eliminar_inicio();
	void insertar_final(cAuto*);
	cAuto* eliminar_final();
	int size();
	bool isfun();
	bool isempty();
	void vaciar();
	void imprimir();

private:
	cNodo inicio;
	cNodo final;

};

cLista::cLista()
{
	final.pAnt = &inicio;
	inicio.pSig = &final;
}

cLista::~cLista()
{
	vaciar();
}
void cLista::insertar_inicio(cAuto* nd)
{
	inicio.insertar_adelante(nd);
}

cAuto* cLista::eliminar_inicio()
{
	cAuto* f;
    f=inicio.eliminar_adelante();
	return f;
}
void cLista::insertar_final(cAuto* nd)
{
	final.pAnt->insertar_adelante(nd);
}

cAuto* cLista::eliminar_final()
{
	cAuto* f;
    f=final.pAnt->pAnt->eliminar_adelante();
	return f;
}

bool cLista::isfun()
{
	return true;

}

bool cLista::isempty()
{
	return(&inicio == final.pAnt);
}

int cLista::size()
{
	int i = 0;
	cNodo* p = inicio.pSig;
	while (&final != p)
	{
		i++;
		p = p->pSig;
	}
	return i;
}

void cLista::vaciar()
{
	cAuto* f;
	while (not isempty())
	{
		f=eliminar_inicio();
		delete f;
	}
}

void cLista::imprimir()
{
	cNodo* p = inicio.pSig;
	while (&final != p)
	{
		p->aDat->imprimir();
		p = p->pSig;
	}
}

int main()
{
	int iO = 0, iO2 = 0;
	bool band, band2 = true;
	cLista l;
	while (band2 == true)
	{
        cAuto* a = new cAuto();
		cPatrulla* p = new cPatrulla();
		cPatrullablin* pb = new cPatrullablin();
		cToreto* at = new cToreto();
		cTaxi* t = new cTaxi();
		band = true;
		cout << endl << "desea usar un:" << endl << "1) auto" << endl << "2) patrulla" << endl << "3) patrulla blindada" << endl << "4) auto de toreto" << endl << "5) taxi" << endl << "6) imprimir" << endl << "7) salir" << endl;
		cin >> iO;
		switch (iO)
		{ 
			
		case 1:
            
			while (band == true)
			{
				cout << endl << "auto:" << endl;
				cout << endl << "que desea hacer:" << endl << "1) acelerar" << endl << "2) frenar" << endl << "3) imprimir" << endl << "4) salir" << endl;
				cin >> iO2;
				switch (iO2)
				{
				case 1:
					cout << "acelerando..." << endl;
					a->acelerar();
					break;
				case 2:
					cout << "frenando..." << endl;
					a->frenar();
					break;
				case 3:
					a->imprimir();
					break;
				case 4:
					band = false;
					break;
				default:
					cout << "opcion no validad" << endl;
					break;
				}
			}
			l.insertar_inicio(a);
			break;
		case 2:
			
			while (band == true)
			{
				cout << endl << "patrulla:" << endl;
				cout << endl << "que desea hacer:" << endl << "1) acelerar" << endl << "2) frenar" << endl << "3) encender sirena" << endl << "4) imprimir" << endl << "5) salir" << endl;
				cin >> iO2;
				switch (iO2)
				{
				case 1:
					cout << "acelerando..." << endl;
					p->acelerar();
					break;
				case 2:
					cout << "frenando..." << endl;
					p->frenar();
					break;
				case 3:
					cout << "encendiendo sirena..." << endl;
					p->encender_sirena(true);
					break;
				case 4:
					p->imprimir();
					break;
				case 5:
					band = false;
					break;
				default:
					cout << "opcion no validad" << endl;
					break;
				}
			}
			l.insertar_final(p);
			break;
		case 3:
			while (band == true)
			{
				cout << endl << "patrulla blindada:" << endl;
				cout << endl << "que desea hacer:" << endl << "1) acelerar" << endl << "2) frenar" << endl << "3) encender sirena" << endl << "4) recibir un disparo" << endl << "5) imprimir" << endl << "6) salir" << endl;
				cin >> iO2;
				switch (iO2)
				{
				case 1:
					cout << "acelerando..." << endl;
					pb->acelerar();
					break;
				case 2:
					cout << "frenando..." << endl;
					pb->frenar();
					break;
				case 3:
					cout << "encendiendo sirena..." << endl;
					pb->encender_sirena(true);
					break;
				case 4:
					cout << "disparo recibido..." << endl;
					pb->disparo();
					break;
				case 5:
					pb->imprimir();
					break;
				case 6:
					band = false;
					break;
				default:
					cout << "opcion no validad" << endl;
					break;
				}
			}
			l.insertar_final(pb);
			break;
		case 4:
			while (band == true)
			{
				cout << endl << "auto de toreto:" << endl;
				cout << endl << "que desea hacer:" << endl << "1) acelerar" << endl << "2) frenar" << endl << "3) encender nitro" << endl << "4) imprimir" << endl << "5) salir" << endl;
				cin >> iO2;
				switch (iO2)
				{
				case 1:
					cout << "acelerando..." << endl;
					at->acelerar();
					break;
				case 2:
					cout << "frenando..." << endl;
					at->frenar();
					break;
				case 3:
					cout << "encendiendo el nitro...";
					at->nitro(true);
				case 4:
					at->imprimir();
					break;
				case 5:
					band = false;
					break;
				default:
					cout << "opcion no validad" << endl;
					break;
				}
			}
			l.insertar_final(at);
			break;
		case 5:
			while (band == true)
			{
				cout << endl << "taxi:" << endl;
				cout << endl << "que desea hacer:" << endl << "1) acelerar" << endl << "2) frenar" << endl << "3) imprimir" << endl << "4) salir" << endl;
				cin >> iO2;
				switch (iO2)
				{
				case 1:
					cout << "acelerando..." << endl;
					t->acelerar();
					break;
				case 2:
					cout << "frenando..." << endl;
					t->frenar();
					break;
				case 3:
					t->imprimir();
					break;
				case 4:
					band = false;
					break;
				default:
					cout << "opcion no validad" << endl;
					break;
				}
			}
			l.insertar_final(t);
			break;
		case 6:
			l.imprimir();
			break;
		case 7:
			band2 = false;
			break;
		default:
			cout << "opcion no validad";
			break;
		}
	}
}