#include "AI.h"
#include <iostream>
void AI::ruch(szachownica& szachownica, const int poziom)
{
	koniec = 0;
	if (poziom == 1)
	{
		ruch_poziom1(szachownica);
	}
	if (poziom == 2)
	{
		ruch_poziom2(szachownica);
	}
	if (poziom == 3)
	{
		ruch_poziom3(szachownica);
	}
}
void  AI::ruch_poziom1(szachownica& szachownica)
{
	std::vector < int > dostepne_figury;
	for (int i = 0; i < szachownica.lista_figur.size(); i++)
	{
		szachownica.lista_figur[i].sprawdz_ruchy(szachownica);
		if (szachownica.lista_figur[i].get_kolor() == 2)
		{
			int* ruchy = szachownica.lista_figur[i].get_ruchy();
			for (int k = 0; k < 64; k++)
				if (ruchy[k] == 1)
				{
					int pole = szachownica.puste_pole(k);
					if (pole != -1 && szachownica.lista_figur[pole].get_kolor() == 2)
						continue;
					dostepne_figury.push_back(i);
					break;
				}
		}
	}
	if (dostepne_figury.size() > 0)
	{
		srand(time(NULL));

		int losowa_figura = (std::rand() % dostepne_figury.size());
		int* ruchy = szachownica.lista_figur[dostepne_figury[losowa_figura]].get_ruchy();
		for (int k = 0; k < 64; k++)
			if (ruchy[k] == 1)
			{
				int pole = szachownica.puste_pole(k);
				if (pole != -1 && szachownica.lista_figur[pole].get_kolor() == 2)
					continue;
				szachownica.ruch(dostepne_figury[losowa_figura], k);
				break;
			}
	}
}
void  AI::ruch_poziom2(szachownica& szachownica)
{
	for (int i = 0; i < szachownica.lista_figur.size(); i++)
	{
		szachownica.lista_figur[i].sprawdz_ruchy(szachownica);
		if (szachownica.lista_figur[i].get_kolor() == 2)
		{
			int* ruchy = szachownica.lista_figur[i].get_ruchy();
			int pole = szachownica.lista_figur[szachownica.ostatni_ruch].get_pozycja();
			if (ruchy[pole] == 1)
			{
				szachownica.ruch(i, pole);
				return;
			}	
		}
	}
	for (int i = 0; i < szachownica.lista_figur.size(); i++)
	{
		szachownica.lista_figur[i].sprawdz_ruchy(szachownica);
		if (szachownica.lista_figur[i].get_kolor() == 2)
		{
			int bialy = szachownica.ostatni_ruch;
			int* ruchy = szachownica.lista_figur[i].get_ruchy();
			int pozycja = szachownica.lista_figur[bialy].get_pozycja();
			int puste = szachownica.puste_pole(pozycja - 8);
			if (puste != -1 && szachownica.lista_figur[puste].get_kolor() == 2)
				break;
			if (ruchy[pozycja - 8] == 1)
			{
				if (szachownica.atak_pole(pozycja - 8, 2) > 0 || szachownica.atak_pole(pozycja - 8, 1) < 1)
				{
					szachownica.ruch(i, pozycja - 8);
					return;
				}
			}
		}
	}
	ruch_poziom1(szachownica);
}
void  AI::ruch_poziom3(szachownica& szachownica)
{
	niebezpieczenstwa(szachownica);
	szachuj(szachownica);
	if (koniec)
		return;

	if (atakuj(szachownica, 1) >= uciekaj(szachownica, 1))
		atakuj(szachownica);
	else
		uciekaj(szachownica);
	if (koniec)
		return;

	blokowanie_szacha(szachownica);
	if (koniec)
		return;

	blokowanie_pionka(szachownica);
	if (koniec)
		return;

	wykonaj_ruch(szachownica);
	if (koniec)
		return;

	ruch_poziom1(szachownica);
	
}
void AI::szachuj(szachownica& szachownica)
{
	for (int i = 0; i < szachownica.lista_figur.size(); i++)
	{
		szachownica.lista_figur[i].sprawdz_ruchy(szachownica);
		if (std::count(zablokowane_figury.begin(), zablokowane_figury.end(), i))
			continue;
		if (szachownica.lista_figur[i].get_kolor() == 2)
		{
			int* ruchy = szachownica.lista_figur[i].get_ruchy();
			for (int k = 0; k < 64; k++)
			{
				int puste = szachownica.puste_pole(k);
				if (puste != -1 && szachownica.lista_figur[puste].get_kolor() == 2)
					continue;

				if (ruchy[k] == 0 || szachownica.atak_pole(k, 1) > 0)
					continue;
			

				int pozycja_krol_przeciwnika = szachownica.get_krol(1);
				if (((pozycja_krol_przeciwnika + 9 == k || pozycja_krol_przeciwnika + 1 == k || pozycja_krol_przeciwnika - 7 == k) && pozycja_krol_przeciwnika % 8 != 7)
					|| pozycja_krol_przeciwnika - 8 == k || pozycja_krol_przeciwnika + 8 == k
					|| ((pozycja_krol_przeciwnika - 9 == k || pozycja_krol_przeciwnika - 1 == k || pozycja_krol_przeciwnika + 7 == k) && pozycja_krol_przeciwnika % 8 != 0))
				{
					if (szachownica.atak_pole(k, 2) <2)
						continue;
				}
				figury test(szachownica.lista_figur[i].get_id(), 2, k);
				test.sprawdz_ruchy(szachownica);
				int* ruchy_test = test.get_ruchy();
				int pozycja_krol = szachownica.get_krol(1);
				if (ruchy_test[pozycja_krol] == 1)
				{
					szachownica.ruch(i, k);
					koniec = 1;
					return;
				}
			}
		}
	}
}
int AI::atakuj(szachownica& szachownica, const int sprawdz)
{
	for (int i = szachownica.lista_figur.size(); i >= 0; i--)
	{
		szachownica.lista_figur[i].sprawdz_ruchy(szachownica);
		if (szachownica.lista_figur[i].get_kolor() == 1)
		{
			int pozycja = szachownica.lista_figur[i].get_pozycja();
			int pozycja_krol_przeciwnika = szachownica.get_krol(1);
			if (((pozycja_krol_przeciwnika + 9 == pozycja || pozycja_krol_przeciwnika + 1 == pozycja || pozycja_krol_przeciwnika - 7 == pozycja) && pozycja_krol_przeciwnika % 8 != 7)
				|| pozycja_krol_przeciwnika - 8 == pozycja || pozycja_krol_przeciwnika + 8 == pozycja
				|| ((pozycja_krol_przeciwnika - 9 == pozycja || pozycja_krol_przeciwnika - 1 == pozycja || pozycja_krol_przeciwnika + 7 == pozycja) && pozycja_krol_przeciwnika % 8 != 0))
			{
				if (szachownica.atak_pole(pozycja, 2) < 2)
					continue;
			}
			int atakujacy = szachownica.atak_pole(pozycja, 2);
			int obroncy = szachownica.atak_pole(pozycja, 1);
			if (atakujacy > 0)
			{
				int pkt_figury = 0;
				int id_figury = szachownica.lista_figur[i].get_id();
				switch (id_figury)
				{
				case 1:
					pkt_figury++;
					break;
				case 4:
					pkt_figury = pkt_figury + 3;
					break;
				case 5:
					pkt_figury = pkt_figury + 4;
					break;

				default:
					pkt_figury = pkt_figury + 2;
					break;
				}
				std::vector < int > a_figury = szachownica.atak_pole_kto(pozycja, 2);
				for (int j = 0; j < a_figury.size(); j++)
				{
					int pkt_atakujacego = 0;
					int id_figury = szachownica.lista_figur[a_figury[j]].get_id();
					switch (id_figury)
					{
					case 1:
						pkt_atakujacego++;
						break;
					case 4:
						pkt_atakujacego = pkt_atakujacego + 3;
						break;
					case 5:
						pkt_atakujacego = pkt_atakujacego + 4;
						break;

					default:
						pkt_atakujacego = pkt_atakujacego + 2;
						break;
					}
					if (obroncy<1||pkt_atakujacego <= pkt_figury)
					{
						if (sprawdz)
						{
							int* ruchy = szachownica.lista_figur[a_figury[j]].get_ruchy();
							if(ruchy[pozycja] == 1)
							return pkt_figury;
						}
						else
						{
							int* ruchy = szachownica.lista_figur[a_figury[j]].get_ruchy();
							if (ruchy[pozycja] == 1)
							{
								szachownica.ruch(a_figury[j], pozycja);
								koniec = 1;
								return 1;
							}
						}
;					}
				}
			}
		}
	}
}
int AI::uciekaj(szachownica& szachownica,const int sprawdz)
{
	for (int i = szachownica.lista_figur.size(); i >= 0; i--)
	{
		szachownica.lista_figur[i].sprawdz_ruchy(szachownica);
		if (szachownica.lista_figur[i].get_kolor() == 2 && szachownica.lista_figur[i].get_id() != 6)
		{
			if (std::count(zablokowane_figury.begin(), zablokowane_figury.end(), i))
				continue;
			int pozycja = szachownica.lista_figur[i].get_pozycja();
			int atakujacy = szachownica.atak_pole(pozycja, 1);
			if (atakujacy > 0)
			{
				if (sprawdz)
				{
					int pkt_figury = 0;
					int id_figury = szachownica.lista_figur[i].get_id();
					switch (id_figury)
					{
					case 1:
						pkt_figury++;
						break;
					case 4:
						pkt_figury = pkt_figury + 3;
						break;
					case 5:
						pkt_figury = pkt_figury + 4;
						break;

					default:
						pkt_figury = pkt_figury + 2;
						break;
					}
					return pkt_figury;
				}
				else
				{
					int* ruchy = szachownica.lista_figur[i].get_ruchy();
					int najlepszy_ruch =-1;
					int pkt_ruch = 0;
					for (int k = 0; k < 64; k++)
					{
						if (ruchy[k] == 1)
						{
							int pole = szachownica.puste_pole(k);
							if (pole != -1 && szachownica.lista_figur[pole].get_kolor() == 2)
								continue;
							if (szachownica.atak_pole(k, 1))
								continue;
							figury test(szachownica.lista_figur[i].get_id(), 2, k);
							test.sprawdz_ruchy(szachownica);
							int* ruchy_test = test.get_ruchy();
							int pkt = 0;
							for (int j = 0; j < 64; j++)
								if (ruchy_test[j] == 1 && szachownica.puste_pole(j) != -1)
									pkt++;

							if (pkt >= pkt_ruch)
							{
								pkt_ruch = pkt;
								najlepszy_ruch = k;
							}
						}
					}
					if (najlepszy_ruch != -1)
					{
						szachownica.ruch(i, najlepszy_ruch);
						koniec = 1;
						return 1;
					}
				}
			}
		}
	}
}
void AI::blokowanie_pionka(szachownica& szachownica)
{
	for (int i = 0; i < szachownica.lista_figur.size(); i++)
	{
		if (std::count(zablokowane_figury.begin(), zablokowane_figury.end(), i))
			continue;
		szachownica.lista_figur[i].sprawdz_ruchy(szachownica);
		if (szachownica.lista_figur[i].get_kolor() == 2)
		{
			int bialy = szachownica.ostatni_ruch;
			int* ruchy = szachownica.lista_figur[i].get_ruchy();
			int pozycja = szachownica.lista_figur[bialy].get_pozycja();
			if (szachownica.lista_figur[bialy].get_id() != 1)
				break;
			int puste = szachownica.puste_pole(pozycja - 8);
			if (puste != -1 && szachownica.lista_figur[puste].get_kolor() == 2)
				break;
			if (szachownica.lista_figur[i].get_id() != 1)
				continue;
			if (ruchy[pozycja - 8] == 1)
			{
				if (szachownica.atak_pole(pozycja - 8, 2) > 0 || szachownica.atak_pole(pozycja - 8, 1) < 1)
				{
					szachownica.ruch(i, pozycja - 8);
					koniec = 1;
					return;
				}
			}
		}
	}
}
void AI::wykonaj_ruch(szachownica& szachownica)
{
	int najlepszy_ruch = -1;
	int figura = -1;
	int pkt_ruch = 0;

	for (int i = 0; i < szachownica.lista_figur.size(); i++)
	{
		if (std::count(zablokowane_figury.begin(), zablokowane_figury.end(), i))
			continue;
		szachownica.lista_figur[i].sprawdz_ruchy(szachownica);
		if (szachownica.lista_figur[i].get_kolor() == 2)
		{
			int* ruchy = szachownica.lista_figur[i].get_ruchy();
			for (int k = 0; k < 64; k++)
			{
				if (ruchy[k] == 1)
				{
					int pozycja_krol_przeciwnika = szachownica.get_krol(1);
					if (((pozycja_krol_przeciwnika + 9 == k || pozycja_krol_przeciwnika + 1 == k || pozycja_krol_przeciwnika - 7 == k) && pozycja_krol_przeciwnika % 8 != 7)
						|| pozycja_krol_przeciwnika - 8 == k || pozycja_krol_przeciwnika + 8 == k
						|| ((pozycja_krol_przeciwnika - 9 == k || pozycja_krol_przeciwnika - 1 == k || pozycja_krol_przeciwnika + 7 == k) && pozycja_krol_przeciwnika % 8 != 0))
					{
						if (szachownica.atak_pole(k, 2) < 2)
							continue;
					}
					int puste = szachownica.puste_pole(k);
					if (puste != -1 && szachownica.lista_figur[puste].get_kolor() == 2)
						continue;
					if (szachownica.atak_pole(k, 1) > 0 && szachownica.atak_pole(k, 2) <2)
						continue;
					if (szachownica.atak_pole(k, 1) > 0 && szachownica.atak_pole(k, 2) > 1)
					{
						std::vector < int > a_figury = szachownica.atak_pole_kto(k, 1);
						int pkt_figury = 0;
						int id_figury = szachownica.lista_figur[i].get_id();
						switch (id_figury)
						{
						case 1:
							pkt_figury++;
							break;
						case 4:
							pkt_figury = pkt_figury + 3;
							break;
						case 5:
							pkt_figury = pkt_figury + 4;
							break;

						default:
							pkt_figury = pkt_figury + 2;
							break;
						}
						int pkt_atakujacego = 0;
						for (int j = 0; j < a_figury.size(); j++)
						{
							pkt_atakujacego = 0;
							int id_figury = szachownica.lista_figur[a_figury[j]].get_id();
							switch (id_figury)
							{
							case 1:
								pkt_atakujacego++;
								break;
							case 4:
								pkt_atakujacego = pkt_atakujacego + 3;
								break;
							case 5:
								pkt_atakujacego = pkt_atakujacego + 4;
								break;

							default:
								pkt_atakujacego = pkt_atakujacego + 2;
								break;
							}
							if (pkt_figury > pkt_atakujacego)
								break;
						}
						if (pkt_figury > pkt_atakujacego)
							continue;
					}
					figury test(szachownica.lista_figur[i].get_id(), 2, k);
					test.sprawdz_ruchy(szachownica);
					int* ruchy_test = test.get_ruchy();
					int pkt = 0;
					for (int j = 0; j < 64; j++)
						if (ruchy_test[j] == 1 && szachownica.puste_pole(j) != -1)
							pkt++;
					if (pkt > pkt_ruch)
					{
						pkt_ruch = pkt;
						najlepszy_ruch = k;
						figura = i;
					}
				}
			}
		}
	}
	if (figura != -1 && najlepszy_ruch != -1)
	{
		szachownica.ruch(figura, najlepszy_ruch);
		koniec = 1;
		return;
	}

}
void AI::niebezpieczenstwa(szachownica& szachownica)
{
	for (int k = 0; k < 64; k++)
		niebezpieczne_pola[k] = 0;
	zablokowane_figury.clear();
	for (int i = 0; i < szachownica.lista_figur.size(); i++)
	{
		szachownica.lista_figur[i].sprawdz_ruchy(szachownica);
		if (szachownica.lista_figur[i].get_kolor() == 2)
			continue;
		int* ruchy = szachownica.lista_figur[i].get_ruchy();
		for (int k = 0; k < 64; k++)
		{
			if (ruchy[k] == 1)
			{
				figury test(szachownica.lista_figur[i].get_id(), 1, k);
				test.sprawdz_ruchy(szachownica);
				int* ruchy_test = test.get_ruchy();
				int pozycja_krola = szachownica.get_krol(2);
				if (ruchy_test[pozycja_krola] == 1)
					niebezpieczne_pola[k] = 1;
			}
		}
	}
	for (int k = 0; k < 64; k++)
	{
		if (niebezpieczne_pola[k] == 1)
		{
			for (int i = 0; i < szachownica.lista_figur.size(); i++)
			{
				if (szachownica.lista_figur[i].get_kolor() == 1)
					continue;
				
				int* ruchy = szachownica.lista_figur[i].get_ruchy();
				if (ruchy[k] == 1)
				{
					niebezpieczne_pola[k] = 0;
					zablokowane_figury.push_back(i);
					break;
				}
			}
		}
	}


}
void AI::blokowanie_szacha(szachownica& szachownica)
{
	for (int i = 0; i < szachownica.lista_figur.size(); i++)
	{
		szachownica.lista_figur[i].sprawdz_ruchy(szachownica);
		if (szachownica.lista_figur[i].get_kolor() == 1)
			continue;
		int* ruchy = szachownica.lista_figur[i].get_ruchy();
		for (int k = 0; k < 64; k++)
		{
			if (ruchy[k] == 1)
			{
				int puste = szachownica.puste_pole(k);
				if (puste != -1 && szachownica.lista_figur[puste].get_kolor() == 2)
					continue;
				if (szachownica.atak_pole(k, 1) > 0)
					continue;
				figury test(szachownica.lista_figur[i].get_id(), 2, k);
				test.sprawdz_ruchy(szachownica);
				int* ruchy_test = test.get_ruchy();
				for (int j = 0; j < 64; j++)
				{
					if (ruchy_test[j] == 1 && niebezpieczne_pola[j] == 1)
					{
						szachownica.ruch(i, k);
						koniec = 1;
						return;
					}
				}
					
			}
		}

	}

}