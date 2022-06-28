#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "pola.h"
#include "szachownica.h"
class Szachy
{
	int poziom =-1;
	sf::Sprite s_pion[4];
	sf::Texture t_pion[4];
	int wybrany = -1;
	int esc = -1;

public:
	Szachy();
	sf::RenderWindow window;
};

