#pragma once

#include<iostream>
#include<vector>
#include<fstream>
#include<list>
#include<string>

//#include "memory.h"

using namespace std;


class PCB
{
private:
	int PID;
	int PPID;
	PCB* ojciec = NULL;

	string NazwaProcesu;
	int r1, r2, r3;
	int stanProcesu;  //1-nowy, 2-czekający, 3-gotowy, 4-aktywny, 5-zakończony, 6-zombie
	int LicznikRozkazow;
	int Priorytet;
	int PriorytetBazowy;
	int Size;

public:
	list<PCB*> dzieci;
	static PCB *idle;
	void sprawdzOjca();
	int toGo;
	int baza;
	int limit;
	vector<vector<int>> tablicaStronic;
	vector<int> workingSet;
	PCB();
	PCB(string nazwa, int size, string nazwaPliku);
	~PCB();
	PCB(string nazwa);
	void wyswietlInformacje();
	PCB* addPro(string name, int siz, string plik);
	void ustawLicznik(int n);
	void ustawStan(int s);
	int getStan();
	int getSize();
	void ustawPriorytet(int p);
	int getPriorytet();
	int getPriorytetBazowy();
	string getNazwa();
	int getID();
	int getPPID();
	PCB* getOjciec();
	void ustawOjciec(PCB* o);
	void dodajDziecko(PCB* d);
	void wyswietlListeDzieci();
	void ustawR1(int r);
	void ustawR2(int r);
	void ustawR3(int r);
	int getR1();
	int getR2();
	int getR3();
	void dodajLicznik(int licz);
	int getLicznik();
	int getBaza();
	void ustawBaza(int i);
	int getLimit();
	void ustawLimit(int i);
	void czytTabStronic();
	void plik(string p1);
	void ustawRozmTablicyStronic(int size);


};

extern list<PCB*>ListaProcesow;
extern list<PCB*>ListaGotowych;
