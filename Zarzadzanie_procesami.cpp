#include<iostream>
#include<vector>
#include<fstream>
#include<list>
#include<string>
#include<iterator>
#include "Zarzadzanie_procesami.h"
#include "Memory.h"

using namespace std;

//extern memoryManagement mem;
list<PCB*>ListaProcesow;
list<PCB*>ListaGotowych;

int x = 1;
int z = 7;

PCB::PCB() {};

PCB::PCB(string nazwa, int size, string nazwaPliku)
{
	PID = x;
	x++;
	NazwaProcesu = nazwa;
	r1, r2, r3 = 0;
	stanProcesu = 1;
	LicznikRozkazow = 0;
	PriorytetBazowy = z;
	Priorytet = PriorytetBazowy;
	z--;
	toGo, baza, limit = 0;
	Size = size;
	ustawRozmTablicyStronic(size);
	ListaProcesow.push_back(this);
	plik(nazwaPliku);
}



PCB::PCB(string nazwa)
{
	PID = x;
	x++;
	NazwaProcesu = nazwa;
	r1, r2, r3 = 0;
	stanProcesu = 1;
	LicznikRozkazow = 0;
	PriorytetBazowy = 1;
	Priorytet = PriorytetBazowy;
	baza, limit = 0;
	ojciec = this;
	ListaProcesow.push_back(this);
}

void PCB::wyswietlInformacje()
{
	cout << "ID procesu: " << this->PID << endl;
	cout << "Nazwa procesu: " << this->NazwaProcesu << endl;
	cout << "Parent ID procesu: " << this->PPID << endl;
	cout << "Stan procesu: " << this->stanProcesu << endl;
	cout << "Rejestry procesu: " << endl << "   R1 - " << this->r1 << endl;
	cout << "   R2 - " << this->r2 << endl;
	cout << "   R3 - " << this->r3 << endl;
	cout << "Licznik rozkazow: " << this->LicznikRozkazow << endl;
	cout << "Priorytet bazowy: " << this->PriorytetBazowy << endl;
	cout << "Priorytet: " << this->Priorytet << endl;
	cout << "Baza: " << this->baza << endl;
	cout << "Limit: " << this->limit << endl;
}

PCB* PCB::addPro(string name, int siz, string plik)
{
	PCB* z = new PCB(name, siz, plik);
	z->ustawOjciec(this);
	z->PPID = (*ojciec).getID();
	this->dodajDziecko(z);
	return z;
}

int PCB::getSize()
{
	return Size;
}

void PCB::ustawLicznik(int n)
{
	LicznikRozkazow = n;
}

void PCB::ustawStan(int s)
{
	if (stanProcesu != 3 && s == 3)
	{
		stanProcesu = s;
		ListaGotowych.push_back(this);
	}
	if (stanProcesu == 3 && s == 3) { return; }
	else if (stanProcesu == 3 && s != 3)
	{
		stanProcesu = s;
		int x = 0;

		for (auto it = ListaGotowych.begin(); it != ListaGotowych.end(); it++)
		{

			if ((*it)->PID == this->PID)
			{
				ListaGotowych.erase(it);
				break;
			}

			if (x == ListaGotowych.size()) {
				x = 0;
				break;
			}
			x++;
		}
	}
}

int PCB::getStan()
{
	return stanProcesu;
}

void PCB::ustawPriorytet(int p)
{
	Priorytet = p;
}

int PCB::getPriorytet()
{
	return Priorytet;
}

int PCB::getPriorytetBazowy()
{
	return PriorytetBazowy;
}

string PCB::getNazwa()
{
	return NazwaProcesu;
}

int PCB::getID()
{
	return PID;
}

int PCB::getPPID()
{
	return PPID;
}

PCB* PCB::getOjciec()
{
	return ojciec;
}

void PCB::ustawOjciec(PCB* o)
{
	ojciec = o;
}

void PCB::dodajDziecko(PCB* d)
{
	dzieci.push_back(d);
}

void PCB::wyswietlListeDzieci()
{
	for (auto it : dzieci)
	{
		cout << it->getNazwa() << endl;
	}
}

void PCB::ustawR1(int r)
{
	r1 = r;
}

void PCB::ustawR2(int r)
{
	r2 = r;
}

void PCB::ustawR3(int r)
{
	r3 = r;
}

int PCB::getR1()
{
	return r1;
}

int PCB::getR2()
{
	return r2;
}

int PCB::getR3()
{
	return r3;
}

void PCB::dodajLicznik(int licz)
{
	LicznikRozkazow += licz;
}

int PCB::getLicznik()
{
	return LicznikRozkazow;
}

int PCB::getBaza()
{
	return baza;
}

void PCB::ustawBaza(int i)
{
	baza = i;
}

int PCB::getLimit()
{
	return limit;
}

void PCB::ustawLimit(int i)
{
	baza = i;
}

void PCB::czytTabStronic()
{
	for (int i = 0; i < tablicaStronic.size(); i++)
	{
		for (int j = 0; j < tablicaStronic[i].size(); j++)
		{
			cout << tablicaStronic[i][j] << " ";
		}
		cout << endl;
	}
}

void PCB::plik(string p1)
{
	//mem.writeToPF(this, p1);
	stanProcesu = 3;
	ListaGotowych.push_back(this);
}

void PCB::ustawRozmTablicyStronic(int size)
{
	if (size % 16 == 0)
	{
		tablicaStronic.resize(size / 16);
		for (int i = 0; i < size / 16; ++i)
			tablicaStronic[i].resize(2);
	}
	if (size % 16 != 0)
	{
		tablicaStronic.resize((size / 16) + 1);
		for (int i = 0; i < (size / 16) + 1; ++i)
			tablicaStronic[i].resize(2);
	}
}

void PCB::sprawdzOjca()
{
	for (auto it : ListaProcesow)
	{
		if (it == this->getOjciec())
			cout << it->getNazwa() << endl;
	}
}

/*PCB* idle()
{

auto INIT = new PCB();
INIT->ustawOjciec(NULL);
INIT->ustawBaza(0);
INIT->ustawPriorytet(0);
INIT->ustawStan(1);
return INIT;
}*/

PCB::~PCB()
{
	if (this->getStan() == 3)
	{
		ListaGotowych.remove(this);
	}
	for (auto it : dzieci)
	{
		if (it->getOjciec() == this)
		{
			for (auto ite : ListaProcesow)
			{
				if (ite->getID() == 1)
				{
					(it)->ustawOjciec(ite);
					ite->dzieci.push_back(it);
				}
			}
		}
	}
	ListaProcesow.remove(this);
	getOjciec()->dzieci.remove(this);
}

int main()
{
	PCB* init = new PCB("init");
	PCB* p1 = (*init).addPro("p1", 3, "help.txt");
	PCB* p2 = (*init).addPro("p2", 3, "please.txt");
	PCB* p3 = (*p2).addPro("p3", 3, "black.txt");

	PCB* p11 = (*p1).addPro("p11", 5, "killme.txt");

	cout << "Lista wszystkich procesow:" << endl;
	for (auto it : ListaProcesow)
	{
		cout << (it)->getNazwa() << endl;
	}


	cout << "Lista dzieci INIT:" << endl;
	init->wyswietlListeDzieci();

	cout << "Sprawdzanie ojca p1:" << endl;
	p1->sprawdzOjca();

	cout << "Sprawdzanie ojca p11:" << endl;
	p11->sprawdzOjca();

	cout << "Lista wszystkich procesow:" << endl;
	for (auto it : ListaProcesow)
	{
		cout << (it)->getNazwa() << endl;
	}

	/*cout << "Lista wszystkich procesow:" << endl;
	for (auto it : ListaProcesow)
	{
	cout << (it)->getNazwa() << endl;
	}*/

	cout << "Lista procesow gotowych:" << endl;
	for (auto it : ListaGotowych)
	{
		cout << (it)->getNazwa() << endl;
	}

	delete p2;

	cout << "Sprawdzanie ojca p3 po usunieciu p2:" << endl;
	p3->sprawdzOjca();

	cout << "Lista dzieci INIT po usunieciu p2:" << endl;
	init->wyswietlListeDzieci();

	cout << "Lista procesow gotowych po usunieciu p2:" << endl;
	for (auto it : ListaGotowych)
	{
		cout << (it)->getNazwa() << endl;
	}


	/*cout << "Info p1" << endl;
	p1->wyswietlInformacje();
	p1->ustawStan(5);
	cout << "Info p1" << endl;
	p1->wyswietlInformacje();
	for (auto it : ListaGotowych)
	{
	cout << it->getNazwa() << endl;
	}*/


	/*cout << endl;
	p2->wyswietlInformacje();
	cout << endl;
	p3->wyswietlInformacje();
	cout << endl;*/



	/*cout << "Lista wszystkich procesow po usunieciu p2:" << endl;
	for (auto it : ListaProcesow)
	{
		cout << (it)->getNazwa() << endl;
	}

	p3->ustawStan(5);
	cout << "Lista procesow gotowych po zmianie stanu p3:" << endl;
	for (auto it : ListaGotowych)
	{
		cout << (it)->getNazwa() << endl;
	}*/

	p3->ustawStan(4);
	cout << "Lista procesow gotowych po zmianie stanu p3:" << endl;
	for (auto it : ListaGotowych)
	{
		cout << (it)->getNazwa() << endl;
	}

	/*cout << "Lista procesow gotowych:" << endl;
	for (auto it : ListaGotowych)
	{
		cout << (it)->getNazwa() << endl;
	}

	p11->ustawStan(5);

	cout << "Lista procesow gotowych:" << endl;
	for (auto it : ListaGotowych)
	{
		cout << (it)->getNazwa() << endl;
	}*/

	cout << endl << endl;

	/*cout << "Lista procesow gotowych:" << endl;
	for (auto it : ListaGotowych)
	{
	cout << (it)->getNazwa() << endl;
	}

	cout << endl;

	*/
	//cout << "INIT ID: " << init->getID();


	cin.get();
	return 0;
}
