#pragma once
#include <SFML/Graphics.hpp>
#include "pola.h"
#include "figury.h"
#include <vector>
class szachownica
{
	friend class figury;
	friend class AI;
	pola pola[64];
	std::vector < figury > lista_figur;
	int szach;
	int wynik;
	int promocja;
	int ostatni_ruch;


public:
	szachownica();
	void draw(sf::RenderWindow& window);
	friend class Szachy;
	int puste_pole(int id);
	int atak_pole(int id, int kolor);
	int get_krol(int kolor);
	void czy_szach();
	int kolor_pola(int pole);
	std::vector < int > atak_pole_kto(int id, int kolor);
	void czy_mat();
	void ruch(int figura, int pole);
	void reset();
};
