#include "menu.h"
#include <iostream>
menu::menu()
{
    font.loadFromFile("arial.ttf");
    t_poziomy[0].setString(L"Łatwy");
    t_poziomy[1].setString(L"Średni");
    t_poziomy[2].setString(L"Trudny");

    for (int i = 0; i < 3; i++)
    {
        poziomy[i].setPosition(sf::Vector2f((i + 1) * 50 + i * 575, 125));
        poziomy[i].setFillColor(sf::Color(255, 255, 255, 10));
        poziomy[i].setSize(sf::Vector2f(575, 825));
        float poz_x = poziomy[i].getPosition().x;
        float poz_y = poziomy[i].getPosition().y;
        
        s_poziomy[i].setPosition(sf::Vector2f(poz_x+170, poz_y+200));
        s_poziomy[i].setColor(sf::Color(255, 255, 255, 128));
        s_poziomy[i].setScale(sf::Vector2f(2, 2));
        t_poziomy[i].setFont(font);
        t_poziomy[i].setCharacterSize(80);
        t_poziomy[i].setFillColor(sf::Color(255, 255, 255, 128));
        t_poziomy[i].setPosition(sf::Vector2f(poz_x + 165 + i*10, poz_y + 460));
    }

}
void menu::draw(sf::RenderWindow& window)
{
    i_poziomy[0].loadFromFile("images/i_1.png");
    i_poziomy[1].loadFromFile("images/i_2.png");
    i_poziomy[2].loadFromFile("images/i_3.png");

    for (int i = 0; i < 3; i++)
    {
        s_poziomy[i].setTexture(i_poziomy[i]);
        window.draw(poziomy[i]);
        window.draw(s_poziomy[i]);
        window.draw(t_poziomy[i]);
    }

}
sf::RectangleShape& menu::get_poziom(int i)
{
    return poziomy[i];
}