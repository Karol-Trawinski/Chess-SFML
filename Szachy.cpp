#include "Szachy.h"
#include "menu.h"
#include "pola.h"
#include "szachownica.h"
#include "AI.h"
Szachy::Szachy()
{
    window.create(sf::VideoMode(1920, 1080), "Szachy");
    menu menu;
    szachownica szachownica;
    AI czarne;

    t_pion[0].loadFromFile("images/2.png");
    t_pion[1].loadFromFile("images/3.png");
    t_pion[2].loadFromFile("images/4.png");
    t_pion[3].loadFromFile("images/5.png");
    for (int i = 0; i < 4; i++)
    {
        s_pion[i].setTexture(t_pion[i]);
        s_pion[i].setPosition(sf::Vector2f(400 + i * 300, 450));
        s_pion[i].scale(sf::Vector2f(3, 3));
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    if (esc == -1)
                    {
                        esc = poziom;
                        poziom = -1;
                    }
                    else
                    {
                        poziom = esc;
                        esc = -1;
                    }
                }
            }
            if (event.type == sf::Event::Closed)
                window.close();

            if (poziom == -1)
                if (event.type == sf::Event::MouseMoved)
                {
                    for (int i = 0; i < 3; i++)
                        if (menu.get_poziom(i).getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
                        {
                            menu.get_poziom(i).setOutlineThickness(2);
                            menu.get_poziom(i).setOutlineColor(sf::Color(255, 255, 255));
                        }
                        else
                            menu.get_poziom(i).setOutlineThickness(0);

                }
            if (poziom == -1)
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        for (int i = 0; i < 3; i++)
                            if (menu.get_poziom(i).getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                            {
                                poziom = i+1;
                                szachownica.reset();
                            }
                    }
                }
            if(szachownica.promocja != -1)
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    for(int i = 0;i<4;i++)
                        if (s_pion[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                        {
                            szachownica.lista_figur[szachownica.promocja].ustaw_id(2 + i);
                            szachownica.promocja = -1;
                            szachownica.czy_szach();
                            szachownica.czy_mat();
                            if (szachownica.wynik != 0)
                                break;
                            czarne.ruch(szachownica, poziom);
                            break;
                        }
                    
                }
            }
            if (poziom > 0 && szachownica.wynik == 0)
            {
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (wybrany != -1)
                        {
                            int* w_ruchy = szachownica.lista_figur[wybrany].get_ruchy();
                            for (int k = 0; k < 64; k++)
                            {
                                if (w_ruchy[k] == 1)
                                {
                                    if (szachownica.pola[k].get_pole().getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                                    {
                                        int puste = szachownica.puste_pole(k);
                                        if (puste != -1 && szachownica.lista_figur[puste].get_kolor() == szachownica.lista_figur[wybrany].get_kolor())
                                            break;
  
                                        szachownica.ruch(wybrany, k);
                                        if (szachownica.wynik != 0)
                                            break;
                                        if(szachownica.promocja == -1)
                                            czarne.ruch(szachownica, poziom);

                                       break;
                                    }
                                }
                            } 
                                wybrany = -1;
                        }
                        else
                        {
                            for (int i = 0; i < szachownica.lista_figur.size(); i++)
                            {
                                if (szachownica.lista_figur[i].get_kolor() == 2)
                                    continue;

                                int id_pole = szachownica.lista_figur[i].get_pozycja();
                                if(id_pole!=-1)
                                if (szachownica.pola[id_pole].get_pole().getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                                {
                                    wybrany = i;
                                    szachownica.lista_figur[wybrany].sprawdz_ruchy(szachownica);
                                }

                            }
                        }


                    }
                }
            }
        }
        
        window.clear();
        if(poziom ==-1)
        menu.draw(window);
        else
        {
            szachownica.draw(window);
            if (wybrany != -1)
            {
                int* ruchy = szachownica.lista_figur[wybrany].get_ruchy();
                for (int k = 0; k < 64; k++)
                {
                    if (ruchy[k] == 1)
                    {
                        int i = szachownica.puste_pole(k);
                        if (k != -1 && szachownica.lista_figur[i].get_kolor() == szachownica.lista_figur[wybrany].get_kolor())
                            continue;
                        sf::CircleShape shape(20);
                        shape.setFillColor(sf::Color(0, 100, 0,150));
                        shape.setPosition(sf::Vector2f(490 + (k % 8) * 120, 90 + k / 8 * 120));
                        window.draw(shape);
                    }
                }
            }
            sf::RectangleShape p;
            if (szachownica.promocja != -1)
            {
                p.setPosition(sf::Vector2f(0, 370));
                p.setFillColor(sf::Color(255, 255, 255, 200));
                p.setSize(sf::Vector2f(1920, 300));
                window.draw(p);
                for (int i = 0; i < 4; i++)
                    window.draw(s_pion[i]);
            }
            if (szachownica.wynik != 0)
            {
                sf::RectangleShape p;
                p.setPosition(sf::Vector2f(0, 370));
                p.setFillColor(sf::Color(255, 255, 255, 200));
                p.setSize(sf::Vector2f(1920, 300));
                window.draw(p);
                sf::Text text;
                sf::Font font;
                font.loadFromFile("arial.ttf");
                text.setFont(font);
                text.setCharacterSize(80);
                text.setFillColor(sf::Color::Black);
                
                if (szachownica.wynik == 1)
                {
                    text.setPosition(sf::Vector2f(750, 470));
                    text.setString("Wygrana");
                }
                if (szachownica.wynik == 2)
                {
                    text.setPosition(sf::Vector2f(750, 470));
                    text.setString("Przegrana");
                }
                if (szachownica.wynik == 3)
                {
                    text.setPosition(sf::Vector2f(900, 470));
                    text.setString("Pat");
                }
                window.draw(text);
            }

        }
        window.display();
    }
}
