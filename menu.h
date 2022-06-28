#pragma once
#include <SFML/Graphics.hpp>
class menu
{
private:
	sf::RectangleShape poziomy[3];
	sf::Sprite s_poziomy[3];
	sf::Text t_poziomy[3];
	sf::Texture i_poziomy[3];
	sf::Font font;
public:
	menu();
	void draw(sf::RenderWindow& window);
	sf::RectangleShape& get_poziom(int i);
};

