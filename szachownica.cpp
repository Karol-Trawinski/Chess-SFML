
#include "szachownica.h"
#include <iostream>
szachownica::szachownica()
{
    reset();
}
void szachownica::reset()
{
    lista_figur.clear();
    szach = -1;
    wynik = 0;
    promocja = -1;
    ostatni_ruch = -1;
    for (int i = 0; i < 64; i++)
    {

        if ((i % 8) % 2 != (i / 8) % 2)
            pola[i].ustaw_kolor(sf::Color(180, 135, 100));
        else
            pola[i].ustaw_kolor(sf::Color(240, 215, 180));
        pola[i].ustaw_pozycje(450 + (i % 8) * 120, 50 + i / 8 * 120);
    }

    for (int i = 0; i < 8; i++)
    {
        lista_figur.push_back(figury(1, 1, 48 + i));
        lista_figur.push_back(figury(1, 2, 8 + i));
    }
    lista_figur.push_back(figury(2, 1, 62));
    lista_figur.push_back(figury(2, 1, 57));
    lista_figur.push_back(figury(3, 1, 61));
    lista_figur.push_back(figury(3, 1, 58));
    lista_figur.push_back(figury(4, 1, 63));
    lista_figur.push_back(figury(4, 1, 56));
    lista_figur.push_back(figury(5, 1, 59));
    lista_figur.push_back(figury(6, 1, 60));

    lista_figur.push_back(figury(2, 2, 1));
    lista_figur.push_back(figury(2, 2, 6));
    lista_figur.push_back(figury(3, 2, 2));
    lista_figur.push_back(figury(3, 2, 5));
    lista_figur.push_back(figury(4, 2, 0));
    lista_figur.push_back(figury(4, 2, 7));
    lista_figur.push_back(figury(5, 2, 3));
    lista_figur.push_back(figury(6, 2, 4));
}
void szachownica::draw(sf::RenderWindow& window)
{

    for (int i = 0; i < 64; i++)
        pola[i].draw(window);
    sf::Font font;
    sf::Text T;
    font.loadFromFile("arial.ttf");
    T.setFont(font);
    T.setCharacterSize(30);
    for (int i = 0; i < 8; i++)
    {
        if (i % 2 == 0)
            T.setFillColor(sf::Color(180, 135, 100));
        else
            T.setFillColor(sf::Color(240, 215, 180));
        T.setPosition(sf::Vector2f(545 + ((63-i*8) % 8) * 120, 50 + (63 - i * 8) / 8 * 120));
        T.setString(std::to_string(i+1));
        window.draw(T);
        T.setPosition(sf::Vector2f(455 + ((63 - i) % 8) * 120, 125 + (63 - i) / 8 * 120));
        T.setString(char(104-i));
        window.draw(T);
    }
    for (int i = 0; i < lista_figur.size(); i++)
    {
        lista_figur[i].sprawdz_ruchy(*this);
        lista_figur[i].draw(window);
    }

}

int szachownica::puste_pole(int id)
{
    for (int i = 0; i < lista_figur.size(); i++)
        if (lista_figur[i].get_pozycja() == id)
            return i;
  
    return -1;
}
int szachownica::atak_pole(int id, int kolor)
{
    int ile = 0;
    for (int i = 0; i < lista_figur.size(); i++)
    {
        if (lista_figur[i].get_kolor() == kolor)
        {
            if (lista_figur[i].get_id() == 1)
            {
                int pozycja = lista_figur[i].get_pozycja();
                if (lista_figur[i].get_kolor() == 1)
                {
                    if (pozycja - 9 == id && pozycja / 8 - 1 == (pozycja - 9) / 8)
                        ile++;

                    if (pozycja - 7 == id && pozycja / 8 - 1 == (pozycja - 7) / 8)
                        ile++;
                }
                else
                {
                    if (pozycja + 9 == id && pozycja / 8 + 1 == (pozycja + 9) / 8)
                        ile++;

                     if (pozycja + 7 == id && pozycja / 8 + 1 == (pozycja + 7) / 8)
                         ile++;
                }
            }
            else
            {
                int* ruchy = lista_figur[i].get_ruchy();
                if (ruchy[id] == 1)
                    ile++;
            }
        }

    }
    return ile;
}
std::vector < int > szachownica::atak_pole_kto(int id, int kolor)
{
    std::vector < int > a_figury;
    for (int i = 0; i < lista_figur.size(); i++)
    {
        if (lista_figur[i].get_kolor() == kolor)
        {
            if (lista_figur[i].get_id() == 1)
            {
                int pozycja = lista_figur[i].get_pozycja();
                if (lista_figur[i].get_kolor() == 1)
                {
                    if (pozycja - 9 == id && pozycja / 8 - 1 == (pozycja - 9) / 8)
                        a_figury.push_back(i);

                    if (pozycja - 7 == id && pozycja / 8 - 1 == (pozycja - 7) / 8)
                        a_figury.push_back(i);
                }
                else
                {
                    if (pozycja + 9 == id && pozycja / 8 + 1 == (pozycja + 9) / 8)
                        a_figury.push_back(i);

                    if (pozycja + 7 == id && pozycja / 8 + 1 == (pozycja + 7) / 8)
                        a_figury.push_back(i);
                }
            }
            else
            {
                int* ruchy = lista_figur[i].get_ruchy();
                if (ruchy[id] == 1)
                    a_figury.push_back(i);
            }                
        }

    }
    return a_figury;
}
int szachownica::get_krol(int kolor)
{
    for (int i = 0; i < lista_figur.size(); i++)
        if (lista_figur[i].get_kolor() == kolor && lista_figur[i].get_id() == 6)
            return lista_figur[i].get_pozycja();
}
void szachownica::czy_szach()
{
    szach = -1;
    for (int i = 0; i < lista_figur.size(); i++)
        lista_figur[i].sprawdz_ruchy(*this);
    int b_krol = get_krol(1);
    int c_krol = get_krol(2);

    if (atak_pole(b_krol, 2) != 0)
    {
        szach = atak_pole_kto(b_krol, 2)[0];
        pola[b_krol].ustaw_kolor(sf::Color::Red);
            
    }
    if (atak_pole(c_krol, 1) != 0)
    {
        szach = atak_pole_kto(c_krol, 1)[0];
        pola[c_krol].ustaw_kolor(sf::Color::Red);
    }
        
}
void szachownica::czy_mat()
{
    int b_moze_wygrac =0;
    int c_moze_wygrac =0;
    int b_skoczki = 0;
    int b_gonce = 0;
    int c_skoczki = 0;
    int c_gonce = 0;
    for (int i = 0; i < lista_figur.size(); i++)
    {
        if (b_skoczki > 1 || b_gonce >1 || (b_skoczki>0 && b_gonce>0))
        {
            b_moze_wygrac = 1;
            break;
        }
        if (c_skoczki > 1 || c_gonce > 1 || (c_skoczki > 0 && c_gonce > 0))
        {
            c_moze_wygrac = 1;
            break;
        }
        int id = lista_figur[i].get_id();
        if (lista_figur[i].get_kolor() == 1)
        {
            if (id == 1 || id == 4 || id == 5)
            {
                b_moze_wygrac = 1;
                break;
            }
            if(id == 2)
                b_skoczki++;
            if (id == 3)
                b_gonce++;
        }
        else
        {
            if (id == 1 || id == 4 || id == 5)
            {
                c_moze_wygrac = 1;
                break;
            }
            if (id == 2)
                c_skoczki++;
            if (id == 3)
                c_gonce++;
        }
    }
    if (b_moze_wygrac == 0 && c_moze_wygrac == 0)
        wynik = 3;
    int b_mat = 1;
    int c_mat = 1;
    for (int i = 0; i < lista_figur.size(); i++)
    {
        lista_figur[i].sprawdz_ruchy(*this);
        int *ruchy = lista_figur[i].get_ruchy();
        for(int k = 0;k<64;k++)
            if (ruchy[k] == 1)
            {
                int z = puste_pole(k);
                if (z != 1 && lista_figur[z].get_kolor() == lista_figur[i].get_kolor())
                    continue; 
                if (lista_figur[i].get_kolor() == 1)
                    b_mat = 0;
                else
                    c_mat = 0;
            }
        if (b_mat == 0 && c_mat == 0)
            break;
   
    }
    if (b_mat || c_mat)
        wynik = 3;

    if (b_mat && szach != -1)
        wynik = 2;

    if (c_mat && szach != -1)
        wynik = 1;
}

int szachownica::kolor_pola(int pole)
{
    return (pole % 8) % 2 != (pole / 8) % 2;
}
void szachownica::ruch(int figura, int pole)
{
    int krol_pozycja;
    if (lista_figur[szach].get_kolor() == 1)
        krol_pozycja = get_krol(2);
    else
        krol_pozycja = get_krol(1);

    if (kolor_pola(krol_pozycja) == 1)
        pola[krol_pozycja].ustaw_kolor(sf::Color(180, 135, 100));
    else
        pola[krol_pozycja].ustaw_kolor(sf::Color(240, 215, 180));

    int puste = puste_pole(pole);
    if (puste != -1)
    {
        if (lista_figur[puste].get_kolor() == lista_figur[figura].get_kolor())
            return;
        lista_figur.erase(lista_figur.begin() + puste);
        if (puste < figura)
            figura--;
    }
    if (lista_figur[figura].get_id() == 1)
    {
        if (lista_figur[figura].get_kolor() == 1)
        {
            if(pole/8 == 2 && lista_figur[figura].get_pozycja()/8 == 3)
            if (lista_figur[figura].get_pozycja() - 7 == pole || lista_figur[figura].get_pozycja() - 9)
            {
                int puste = puste_pole(pole +8);
                if (puste != -1 && lista_figur[puste].get_id() == 1 && lista_figur[puste].bicie_w_przelocie == 1)
                {
                    lista_figur.erase(lista_figur.begin() + puste);
                    if (puste < figura)
                        figura--;
                }
            }
        }
        else
        {
            if (pole / 8 == 5 && lista_figur[figura].get_pozycja() / 8 == 4)
            if (lista_figur[figura].get_pozycja() + 7 == pole || lista_figur[figura].get_pozycja() + 9 == pole)
            {
                int puste = puste_pole(pole - 8);
                if (puste != -1 && lista_figur[puste].get_id() == 1 && lista_figur[puste].bicie_w_przelocie == 1)
                {
                    lista_figur.erase(lista_figur.begin() + puste);
                    if (puste < figura)
                        figura--;
                }
            }
        }
    }
   
    lista_figur[figura].ustaw_pozycje(pole);
    ostatni_ruch = figura;

    for (int i = 0; i < lista_figur.size(); i++)
        if (lista_figur[i].get_id()==1 && lista_figur[i].bicie_w_przelocie == 1)
            lista_figur[i].bicie_w_przelocie = 0;

    if (lista_figur[figura].pierwszy_ruch)
    {   
            if (lista_figur[figura].get_id() == 1 && (pole / 8 == 3 || pole / 8 == 4))
                lista_figur[figura].bicie_w_przelocie = 1;

        if (lista_figur[figura].get_id() == 6)
        {
            if (pole == 62 || pole == 6)
            {
                int wieza1 = puste_pole(pole + 1);
                lista_figur[wieza1].ustaw_pozycje(pole - 1);
                lista_figur[wieza1].pierwszy_ruch = 0;
            }
            if (pole == 2 || pole == 58)
            {
                int wieza2 = puste_pole(pole - 2);
                lista_figur[wieza2].ustaw_pozycje(pole + 1);
                lista_figur[wieza2].pierwszy_ruch = 0;
            }
        }
            lista_figur[figura].pierwszy_ruch = 0;
    }

    if (lista_figur[figura].get_id() == 1)
    {
        if (pole / 8 == 0 || pole / 8 == 7)
        {
            if (lista_figur[figura].get_kolor() == 2)
                lista_figur[figura].ustaw_id(5);
            else
                promocja = figura;
        }
    }
    for (int i = 0; i < lista_figur.size(); i++)
        lista_figur[i].sprawdz_ruchy(*this);
    czy_szach();
    czy_mat();
}
