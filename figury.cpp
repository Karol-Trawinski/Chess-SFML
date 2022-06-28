#include "figury.h"
#include <iostream>

figury::figury(const int id, const int kolor,const int pozycja)
{
	for (int i = 0; i < 64; i++)
		ruchy[i] = 0;

	bicie_w_przelocie = 0;
	this->id_figury = id;
	this->kolor = kolor;
	this->pozycja = pozycja;
	figura.scale(sf::Vector2f(2,2));
	figura.setPosition(sf::Vector2f(460 + (pozycja % 8) * 120, 60 + pozycja / 8 * 120));
}
void figury::sprawdz_ruchy(szachownica& szachownica)
{
	for (int i = 0; i < 64; i++)
		ruchy[i] = 0;
	if (id_figury == 1)
	{
		ruch_pionek(szachownica);
			
	}
	if (id_figury == 2)
	{
		ruch_skoczek(szachownica);
	
	}
	if (id_figury == 3)
	{
		ruch_goniec(szachownica);
	}
	if (id_figury == 4)
	{
		ruch_wieza(szachownica);
	}
	if (id_figury == 5)
	{
		ruch_hetman(szachownica);
	}
	if (id_figury == 6)
	{
		ruch_krol(szachownica);
	}
	zabronione_ruchy(szachownica);
	zabronione_ruchy_obronca(szachownica);
}
void figury::draw(sf::RenderWindow& window)
{
	switch (id_figury)
	{
	case 1:
		t.loadFromFile(kolor == 1 ? "images/1.png" : "images/7.png");
		break;
	case 2:
		t.loadFromFile(kolor == 1 ? "images/2.png" : "images/8.png");
		break;
	case 3:
		t.loadFromFile(kolor == 1 ? "images/3.png" : "images/9.png");
		break;
	case 4:
		t.loadFromFile(kolor == 1 ? "images/4.png" : "images/10.png");
		break;
	case 5:
		t.loadFromFile(kolor == 1 ? "images/5.png" : "images/11.png");
		break;
	case 6:
		t.loadFromFile(kolor == 1 ? "images/6.png" : "images/12.png");
		break;

	default:
		t.loadFromFile(kolor == 1 ? "images/1.png" : "images/7.png");
		break;
	}
	figura.setTexture(t);
	window.draw(figura);
}
int figury::get_pozycja() const
{
	return pozycja;
}
void figury::ustaw_pozycje(int pozycja)
{
	this->pozycja = pozycja;
	figura.setPosition(sf::Vector2f(460 + (pozycja % 8) * 120, 60 + pozycja / 8 * 120));
}
int* figury::get_ruchy()
{
	return ruchy;
}
int figury::get_id() const
{
	return id_figury;
}
int figury::get_kolor() const
{
	return kolor;
}
void figury::ustaw_id(const int id)
{
	id_figury = id;
}
void figury::zabronione_ruchy(szachownica& szachownica)
{
	if (szachownica.szach != -1 && id_figury != 6)
	{
		int pola[8];
		for (int i = 0; i < 8; i++)
			pola[i] = -1;
		int atakujacy = szachownica.lista_figur[szachownica.szach].get_pozycja();
		int id_atakujacy = szachownica.lista_figur[szachownica.szach].get_id();
		int k_atakujacy = szachownica.lista_figur[szachownica.szach].get_kolor();
		int k_krol = k_atakujacy == 1 ? 2 : 1;
		int krol = szachownica.get_krol(k_krol);
		if (kolor != k_krol)
			return;
		if (szachownica.atak_pole(krol, k_atakujacy)>1)
		{
			for (int k = 0; k < 64; k++)
				ruchy[k] = 0;
			return;
		}
		if (id_atakujacy == 2)
		{
			pola[0] = atakujacy;
		}
		else
		{
			if (atakujacy % 8 == krol % 8)
			{
				if (atakujacy / 8 > krol / 8)
					for (int i = 0; atakujacy - 8 * i > krol; i++)
						pola[i] = atakujacy - 8 * i;
				if (atakujacy / 8 < krol / 8)
					for (int i = 0; atakujacy + 8 * i < krol; i++)
						pola[i] = atakujacy + 8 * i;
			}
			if (atakujacy / 8 == krol / 8)
			{
				if (atakujacy % 8 > krol % 8)
					for (int i = 0; atakujacy - i > krol; i++)
						pola[i] = atakujacy - i;
				if (atakujacy % 8 < krol % 8)
					for (int i = 0; atakujacy + i < krol; i++)
						pola[i] = atakujacy + i;
			}

			if (atakujacy % 8 < krol % 8 && atakujacy / 8 != krol / 8)
			{
				if(atakujacy / 8 < krol / 8)
					for (int i = 0; atakujacy +9*i < krol; i++)
						pola[i] = atakujacy +9 * i;
				if (atakujacy / 8 > krol / 8)
					for (int i = 0; atakujacy -7 * i > krol; i++)
						pola[i] = atakujacy -7 * i;
			}
			if (atakujacy % 8 > krol % 8 && atakujacy / 8 != krol / 8)
			{
				if (atakujacy / 8 < krol / 8)
					for (int i = 0; atakujacy + 7 * i < krol; i++)
						pola[i] = atakujacy + 7 * i;
				if (atakujacy / 8 > krol / 8)
					for (int i = 0; atakujacy - 9 * i > krol; i++)
						pola[i] = atakujacy - 9 * i;
			}
		}
		if (kolor == k_krol)
		{
			for (int i = 0; i < 64; i++)
			{
				if (ruchy[i] != 0 )
				{
					ruchy[i] = 0;
					for (int k = 0; pola[k] != -1; k++)
						if (pola[k] == i)
						{
							ruchy[i] = 1;
							break;
						}
				}
			}
		}
	}
	if (szachownica.szach != -1 && id_figury == 6)
	{
		int atakujacy = szachownica.lista_figur[szachownica.szach].get_pozycja();
		int kolor_pola_atakujacy = szachownica.kolor_pola(atakujacy);
		int kolor_pola_krol = szachownica.kolor_pola(pozycja);
		for (int k = 0; k < 64; k++)
		{
			if (ruchy[k] == 1 && atakujacy != k)
			{
				int kolor_pola = szachownica.kolor_pola(k);
				if (pozycja % 9 == k % 9 && atakujacy % 9 == k % 9 && kolor_pola_krol == kolor_pola_atakujacy && kolor_pola_atakujacy == kolor_pola)
					ruchy[k] = 0;
				if (pozycja % 7 == k % 7 && atakujacy % 7 == k % 7 && kolor_pola_krol == kolor_pola_atakujacy && kolor_pola_atakujacy == kolor_pola)
					ruchy[k] = 0;
				if (pozycja % 8 == k % 8 && k % 8 == atakujacy % 8)
					ruchy[k] = 0;
				if (pozycja / 8 == k / 8 && k / 8 == atakujacy / 8)
					ruchy[k] = 0;

			}
		}
	}
}
void figury::ruch_pionek(szachownica& szachownica)
{
	if (kolor == 1)
	{
		if (pozycja - 8 >= 0)
			if (szachownica.puste_pole(pozycja - 8) == -1)
				ruchy[pozycja - 8] = 1;
		if (pierwszy_ruch)
			if (szachownica.puste_pole(pozycja - 16) == -1 && szachownica.puste_pole(pozycja - 8) == -1)
				ruchy[pozycja - 16] = 1;

		if (pozycja - 9 >= 0 && pozycja / 8 - 1 == (pozycja - 9) / 8)
			if(szachownica.puste_pole(pozycja - 9) !=-1)
				ruchy[pozycja - 9] = 1;

		if (pozycja - 7 >= 0 && pozycja / 8 - 1 == (pozycja - 7) / 8)
			if (szachownica.puste_pole(pozycja - 7) != -1)
				ruchy[pozycja - 7] = 1;
	
		if (pozycja / 8 == 3)
		{
			if (pozycja + 1 < 64 && szachownica.puste_pole(pozycja -7) == -1)
			{
				int puste = szachownica.puste_pole(pozycja + 1);
				if (puste != -1 && szachownica.lista_figur[puste].get_id() == 1 && szachownica.lista_figur[puste].bicie_w_przelocie == 1)
				{
					if (pozycja - 7 >= 0)
					ruchy[pozycja - 7] = 1;
				}
			}
			if (pozycja - 1 >= 0 && szachownica.puste_pole(pozycja - 9) == -1)
			{
				int puste = szachownica.puste_pole(pozycja - 1);
				if (puste != -1 && szachownica.lista_figur[puste].get_id() == 1 && szachownica.lista_figur[puste].bicie_w_przelocie == 1)
				{
					if(pozycja - 9>=0)
					ruchy[pozycja - 9] = 1;
				}
			}
		}
	}
	else
	{
		if (pozycja + 8 < 64)
			if (szachownica.puste_pole(pozycja + 8) == -1)
				ruchy[pozycja + 8] = 1;
		if (pierwszy_ruch)
			if (szachownica.puste_pole(pozycja + 16) == -1 && szachownica.puste_pole(pozycja + 8) == -1)
				ruchy[pozycja + 16] = 1;
		if (pozycja + 9 < 64 && pozycja / 8 + 1 == (pozycja + 9) / 8)
			if (szachownica.puste_pole(pozycja +9) != -1)
					ruchy[pozycja + 9] = 1;

		if (pozycja + 7 < 64 && pozycja / 8 + 1 == (pozycja + 7) / 8)
			if (szachownica.puste_pole(pozycja + 7) != -1)
				ruchy[pozycja + 7] = 1;
		if (pozycja / 8 == 4)
		{
			if (pozycja + 1 < 64 && szachownica.puste_pole(pozycja + 9) ==-1)
			{
				int puste = szachownica.puste_pole(pozycja + 1);
				if (puste != -1 && szachownica.lista_figur[puste].get_id() == 1 && szachownica.lista_figur[puste].bicie_w_przelocie == 1)
				{
					if (pozycja + 9 <64)
					ruchy[pozycja +9] = 1;
				}
			}
			if (pozycja - 1 >= 0 && szachownica.puste_pole(pozycja + 7) == -1)
			{
				int puste = szachownica.puste_pole(pozycja - 1);
				if (puste != -1 && szachownica.lista_figur[puste].get_id() == 1 && szachownica.lista_figur[puste].bicie_w_przelocie == 1)
				{
					if (pozycja + 7 < 64)
					ruchy[pozycja + 7] = 1;
				}
			}
		}
	}
}
void figury::ruch_skoczek(szachownica& szachownica)
{
	if (pozycja - 17 >= 0 && pozycja / 8 - 2 == (pozycja - 17) / 8)
		ruchy[pozycja - 17] = 1;
	if (pozycja - 10 >= 0 && pozycja / 8 - 1 == (pozycja - 10) / 8)
		ruchy[pozycja - 10] = 1;
	if (pozycja - 15 >= 0 && pozycja / 8 - 2 == (pozycja - 15) / 8)
		ruchy[pozycja - 15] = 1;
	if (pozycja - 6 >= 0 && pozycja / 8 - 1 == (pozycja - 6) / 8)
		ruchy[pozycja - 6] = 1;
	if (pozycja + 17 < 64 && pozycja / 8 + 2 == (pozycja + 17) / 8)
		ruchy[pozycja + 17] = 1;
	if (pozycja + 10 < 64 && pozycja / 8 + 1 == (pozycja + 10) / 8)
		ruchy[pozycja + 10] = 1;
	if (pozycja + 15 < 64 && pozycja / 8 + 2 == (pozycja + 15) / 8)
		ruchy[pozycja + 15] = 1;
	if (pozycja + 6 < 64 && pozycja / 8 + 1 == (pozycja + 6) / 8)
		ruchy[pozycja + 6] = 1;

}
void figury::ruch_goniec(szachownica& szachownica)
{
	for (int i = 1; i < 9; i++)
	{
		if (pozycja - 7 * i >= 0 && pozycja / 8 - i == (pozycja - 7 * i) / 8)
		{
			ruchy[pozycja - 7 * i] = 1;
			int pole = szachownica.puste_pole(pozycja - 7 * i);
			if (pole != -1)
				break;
		}
		else break;
	}
	for (int i = 1; i < 9; i++)
	{
		if (pozycja - 9 * i >= 0 && pozycja / 8 - i == (pozycja - 9 * i) / 8)
		{
			ruchy[pozycja - 9 * i] = 1;
			int pole = szachownica.puste_pole(pozycja - 9 * i);
			if (pole != -1)
				break;

		}
		else break;
	}
	for (int i = 1; i < 9; i++)
	{
		if (pozycja + 9 * i < 64 && pozycja / 8 + i == (pozycja + 9 * i) / 8)
		{
			ruchy[pozycja + 9 * i] = 1;
			int pole = szachownica.puste_pole(pozycja + 9 * i);
			if (pole != -1)
				break;
		}
		else break;
	}
	for (int i = 1; i < 9; i++)
	{
		if (pozycja + 7 * i < 64 && pozycja / 8 + i == (pozycja + 7 * i) / 8)
		{
			ruchy[pozycja + 7 * i] = 1;
			int pole = szachownica.puste_pole(pozycja + 7 * i);
			if (pole != -1)
				break;
		}
		else break;
	}
}
void figury::ruch_wieza(szachownica& szachownica)
{
	for (int i = 1; i < 9; i++)
	{
		if (pozycja - 8 * i >= 0)
		{
			ruchy[pozycja - 8 * i] = 1;
			int pole = szachownica.puste_pole(pozycja - 8 * i);
			if (pole != -1)
				break;
			
		}
		else break;
	}
	for (int i = 1; i < 9; i++)
	{
		if (pozycja + 8 * i < 64)
		{
			ruchy[pozycja + 8 * i] = 1;
			int pole = szachownica.puste_pole(pozycja + 8 * i);
			if (pole != -1)
				break;
		}
		else break;
	}
	for (int i = 1; i < 9; i++)
	{
		if (pozycja - i >= 0 && pozycja / 8 == (pozycja - i) / 8)
		{
			ruchy[pozycja - i] = 1;
			int pole = szachownica.puste_pole(pozycja - i);
			if (pole != -1)
				break;
		}
		else break;
	}
	for (int i = 1; i < 9; i++)
	{
		if (pozycja + i < 64 && pozycja / 8 == (pozycja + i) / 8)
		{
			ruchy[pozycja + i] = 1;
			int pole = szachownica.puste_pole(pozycja + i);
			if (pole != -1)
				break;
		}
		else break;
	}


}
void figury::ruch_hetman(szachownica& szachownica)
{
	ruch_wieza(szachownica);
	ruch_goniec(szachownica);
}
void figury::ruch_krol(szachownica& szachownica)
{
			if (pozycja - 8 >= 0 && (pozycja - 8) % 8 == pozycja % 8)
				ruchy[pozycja - 8] = 1;
			if (pozycja - 9 >= 0 && pozycja / 8 - 1 == (pozycja - 9) / 8)
					ruchy[pozycja - 9] = 1;
			if (pozycja - 7 >= 0 && pozycja / 8 - 1 == (pozycja - 7) / 8)
					ruchy[pozycja - 7] = 1;
			if (pozycja + 8 < 64 && (pozycja + 8) % 8 == pozycja % 8)
				ruchy[pozycja + 8] = 1;
			if (pozycja + 9 < 64 && pozycja / 8 + 1 == (pozycja + 9) / 8)
					ruchy[pozycja + 9] = 1;
			if (pozycja + 7 < 64 && pozycja / 8 + 1 == (pozycja + 7) / 8)
					ruchy[pozycja + 7] = 1;
			if(pozycja+1<64 && (pozycja+1) / 8 == pozycja / 8)
				ruchy[pozycja + 1] = 1;
			if (pozycja - 1 >=0 && (pozycja - 1) / 8 == pozycja / 8)
				ruchy[pozycja - 1] = 1;
			if (pierwszy_ruch && szachownica.szach ==-1)
			{
				int wieza1 = szachownica.puste_pole(pozycja + 3);
				int wieza2 = szachownica.puste_pole(pozycja - 4);
				if (szachownica.lista_figur[wieza2].pierwszy_ruch)
				ruchy[pozycja - 2] = 1;
				if (szachownica.lista_figur[wieza1].pierwszy_ruch)
				ruchy[pozycja + 2] = 1;
			}
			for (int i = 0; i < 64; i++)
			{
				if (ruchy[i] == 1)
				{
					int pozycja_krol_przeciwnika = szachownica.get_krol(kolor == 1 ? 2 : 1);
					if (((pozycja_krol_przeciwnika + 9 == i || pozycja_krol_przeciwnika + 1 == i || pozycja_krol_przeciwnika - 7 == i) && pozycja_krol_przeciwnika % 8 != 7)
						|| pozycja_krol_przeciwnika - 8 == i || pozycja_krol_przeciwnika + 8 == i
						|| ((pozycja_krol_przeciwnika - 9 == i || pozycja_krol_przeciwnika - 1 == i || pozycja_krol_przeciwnika + 7 == i) && pozycja_krol_przeciwnika % 8 != 0))
					{
						ruchy[i] = 0;
						continue;
					}
					if (szachownica.atak_pole(i, kolor == 1 ? 2 : 1) != 0)
					{
						ruchy[i] = 0;
						continue;
					}
					if (pierwszy_ruch)
					{
						for (int k = 1; k < 3; k++)
						{
							if (szachownica.atak_pole(pozycja + k, kolor == 1 ? 2 : 1) > 0 || szachownica.puste_pole(pozycja + k)!=-1)
							{
								ruchy[pozycja + 2] = 0;
								break;
							}
						}
						for (int k = 1; k < 4; k++)
						{
							if (szachownica.atak_pole(pozycja - k, kolor == 1 ? 2 : 1) > 0 || szachownica.puste_pole(pozycja - k) != -1)
							{
								ruchy[pozycja - 2] = 0;
								break;
							}
						}
					}
				}
			}
}
void figury::zabronione_ruchy_obronca(szachownica& szachownica)
{
	std::vector < int > atakujacy = szachownica.atak_pole_kto(pozycja,kolor == 1?2:1);
	if (atakujacy.size() > 0 && id_figury!=6)
	{
		for (int k = 0; k < atakujacy.size(); k++)
		{
			int id_atakujacy = atakujacy[k];
			if (szachownica.lista_figur[id_atakujacy].get_id() == 1 || szachownica.lista_figur[id_atakujacy].get_id() == 6)
				continue;

			int pozycja_atakujacy = szachownica.lista_figur[id_atakujacy].get_pozycja();
			int krol = szachownica.get_krol(kolor);
			int kolor_pola_krol = szachownica.kolor_pola(krol);
			int kolor_pola_atakujacy = szachownica.kolor_pola(pozycja_atakujacy);
			int kolor_pola_figura = szachownica.kolor_pola(pozycja);

			if (krol % 9 == pozycja % 9 && pozycja_atakujacy % 9 == pozycja % 9 && kolor_pola_krol == kolor_pola_atakujacy && kolor_pola_atakujacy == kolor_pola_figura)
			{
				if (krol % 8 < pozycja % 8)
					for (int i = 1; pozycja - i * 9 > krol; i++)
						if (szachownica.puste_pole(pozycja - i * 9) != -1)
							return;
				if (krol % 8 > pozycja % 8)
					for (int i = 1; pozycja + i * 9 < krol; i++)
						if (szachownica.puste_pole(pozycja + i * 9) != -1)
							return;
				for (int i = 0; i < 64; i++)
					if (ruchy[i] == 1)
					{
						int* ruchy_atakuajcy = szachownica.lista_figur[id_atakujacy].get_ruchy();
						if ((ruchy[i] == ruchy_atakuajcy[i] && i % 9 == pozycja_atakujacy % 9) || i == pozycja_atakujacy)
							continue;
						else
							ruchy[i] = 0;
					}
			}
			if (krol % 7 == pozycja % 7 && pozycja_atakujacy % 7 == pozycja % 7 && kolor_pola_krol == kolor_pola_atakujacy && kolor_pola_atakujacy == kolor_pola_figura)
			{
				if (krol % 8 > pozycja % 8)
					for (int i = 1; pozycja - i * 7 > krol; i++)
						if (szachownica.puste_pole(pozycja - i * 7) != -1)
							return;
				if (krol % 8 < pozycja % 8)
					for (int i = 1; pozycja + i * 7 < krol; i++)
						if (szachownica.puste_pole(pozycja + i * 7) != -1)
							return;
				for (int i = 0; i < 64; i++)
					if (ruchy[i] == 1)
					{
						int* ruchy_atakuajcy = szachownica.lista_figur[id_atakujacy].get_ruchy();
						if ((ruchy[i] == ruchy_atakuajcy[i] && i % 7 == pozycja_atakujacy % 7) || i == pozycja_atakujacy)
							continue;
						else
							ruchy[i] = 0;
					}
			}
			if (krol % 8 == pozycja % 8 && pozycja_atakujacy % 8 == pozycja % 8)
			{
				if (krol / 8 < pozycja / 8)
					for (int i = 1; pozycja - i * 8 > krol; i++)
						if (szachownica.puste_pole(pozycja - i * 8) != -1)
							return;
				if (krol / 8 > pozycja / 8)
					for (int i = 1; pozycja + i * 8 < krol; i++)
						if (szachownica.puste_pole(pozycja + i * 8) != -1)
							return;

				for (int i = 0; i < 64; i++)
					if (ruchy[i] == 1)
					{
						int* ruchy_atakuajcy = szachownica.lista_figur[id_atakujacy].get_ruchy();
						if ((ruchy[i] == ruchy_atakuajcy[i] && i % 8 == pozycja_atakujacy % 8) || i == pozycja_atakujacy)
							continue;
						else
							ruchy[i] = 0;
					}
			}
			if (krol / 8 == pozycja / 8 && pozycja_atakujacy / 8 == pozycja / 8)
			{
				if (krol % 8 < pozycja % 8)
					for (int i = 1; pozycja - i  > krol; i++)
						if (szachownica.puste_pole(pozycja - i) != -1)
							return;
				if (krol % 8 > pozycja % 8)
					for (int i = 1; pozycja + i < krol; i++)
						if (szachownica.puste_pole(pozycja + i) != -1)
							return;

				for (int i = 0; i < 64; i++)
					if (ruchy[i] == 1)
					{
						int* ruchy_atakuajcy = szachownica.lista_figur[id_atakujacy].get_ruchy();
						if ((ruchy[i] == ruchy_atakuajcy[i] && i / 8 == pozycja_atakujacy / 8) || i == pozycja_atakujacy)
							continue;
						else
							ruchy[i] = 0;
					}
			}
		}
	}
}