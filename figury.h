#pragma once
#include <SFML/Graphics.hpp>
#include "szachownica.h"
class szachownica;
class figury
{
	sf::Sprite figura;
	sf::Texture t;
	int id_figury;
	int kolor;
	int ruchy[64];
	int pozycja;
	void ruch_pionek(szachownica& szachownica);
	void ruch_skoczek(szachownica& szachownica);
	void ruch_goniec(szachownica& szachownica);
	void ruch_wieza(szachownica& szachownica);
	void ruch_hetman(szachownica& szachownica);
	void ruch_krol(szachownica& szachownica);
	void zabronione_ruchy(szachownica& szachownica);
	void zabronione_ruchy_obronca(szachownica& szachownica);
public:
	int bicie_w_przelocie;
	int pierwszy_ruch = 1;
	figury(const int id, const int kolor, const int pozycja);
	void sprawdz_ruchy(szachownica& szachownica);
	void ustaw_pozycje(int pozycja);
	void draw(sf::RenderWindow& window);
	int get_pozycja() const;
	int* get_ruchy();
	int get_id() const ;
	int get_kolor() const;
	void ustaw_id(const int id);

};

