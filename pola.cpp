#include "pola.h"

void pola::ustaw_kolor(sf::Color kolor)
{
	pole.setFillColor(kolor);
}
void pola::ustaw_pozycje(float x, float y)
{
	pole.setPosition(sf::Vector2f(x, y));
}
void pola::draw(sf::RenderWindow& window)
{
	pole.setSize(sf::Vector2f(120, 120));
	window.draw(pole);
}
sf::RectangleShape& pola::get_pole()
{
	return pole;
}