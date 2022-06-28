#pragma once
#include <SFML/Graphics.hpp>
#include "szachownica.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include "figury.h"
class AI
{
	int koniec = 0;
	int niebezpieczne_pola[64];
	std::vector < int > zablokowane_figury;
	void szachuj(szachownica& szachownica);
	void niebezpieczenstwa(szachownica& szachownica);
	int atakuj(szachownica& szachownica, const int sprawdz = 0);
	int uciekaj(szachownica& szachownica, const  int sprawdz = 0);
	void blokowanie_pionka(szachownica& szachownica);
	void blokowanie_szacha(szachownica& szachownica);
	void wykonaj_ruch(szachownica& szachownica);
	void ruch_poziom1(szachownica& szachownica);
	void ruch_poziom2(szachownica& szachownica);
	void ruch_poziom3(szachownica& szachownica);

public:
	void ruch(szachownica& szachownica, const int poziom);
};

