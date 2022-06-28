#pragma once
#include <SFML/Graphics.hpp>
class pola
{
	sf::RectangleShape pole;
public:
	void ustaw_kolor(sf::Color kolor);
	void ustaw_pozycje(float x, float y);
	void draw(sf::RenderWindow& window);
	sf::RectangleShape& get_pole();
};

