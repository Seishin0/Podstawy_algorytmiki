#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>

using namespace std;

struct student
{
    string imie;
    string nazwisko;
    int punkty;
};

void wczytajStudentow(student *&tab, int *n)
{
    string linia;
    int liczbaStudentow;
    ifstream plik("studenci.csv");
    plik >> liczbaStudentow;
    plik.ignore(256, '\n'); // Ignoruj resztę linii po liczbie studentów
    tab = new student[liczbaStudentow];
    for (int i = 0; i < liczbaStudentow; i++)
    {
        getline(plik, linia);
        stringstream ss(linia);

        getline(ss, tab[i].imie, ';');
        getline(ss, tab[i].nazwisko, ';');
        string temp;
        getline(ss, temp, ';');
        tab[i].punkty = atoi(temp.c_str());
    }
    plik.close();
    *n = liczbaStudentow;
}
int podziel2czesci(student *tab, int n, int granica)
{
    int i = 0;
    int j = n - 1;
    while (i < j)
    {
        if (tab[i].punkty <= granica && i < j)
            i++;
        else if (tab[j].punkty > granica && i < j)
            j--;
        else if (i < j)
        {
            swap(tab[i], tab[j]);
            i++;
            j--;
        }
    }
    if (tab[i].punkty <= granica)
        return i + 1;
    else
        return i;
}
void podziel3czesci(student *tab, int n, int *granica1, int *granica2)
{
    int i = -1, j = 0, k = n;
    while (j < k)
    {
        if (tab[j].punkty % 3 <= 0)
        {
            i++;
            swap(tab[i], tab[j]);
            j++;
        }
        else
        {
            if (tab[j].punkty % 3 > 1)
            {
                k--;
                swap(tab[k], tab[j]);
            }
            else
            {
                j++;
            }
        }
    }
    *granica1 = i+1;
    *granica2 = k;
}
void wyswietlStudentow(student *tab, int n)
{
    cout << "Liczba studentow: " << n << endl;
    for (int i = 0; i < n; i++)
        cout << tab[i].punkty << "\t" << tab[i].imie << " " << tab[i].nazwisko << endl;
}
void wyswietlStudentow_2czesci(student *tab, int n, int indeks)
{
    cout << "Liczba studentow: " << n << endl;
    cout << "Studenci, ktorzy otrzymali <=10 punktow:" << endl;
    for (int i = 0; i < indeks; i++)
        cout << tab[i].punkty << "\t" << tab[i].imie << " " << tab[i].nazwisko << endl;
    cout << "Studenci, ktorzy otrzymali >10 punktow:" << endl;
    for (int i = indeks; i < n; i++)
        cout << tab[i].punkty << "\t" << tab[i].imie << " " << tab[i].nazwisko << endl;
}
void wyswietlStudentow_3czesci(student *tab, int n, int granica1, int granica2)
{
    cout << "Liczba studentow: " << n << endl;
    cout << "Studenci, ktorzy otrzymali ilosc punktow podzielna przez 3:" << endl;
    for (int i = 0; i < granica1; i++)
        cout << tab[i].punkty << "\t" << tab[i].imie << " " << tab[i].nazwisko << endl;
    cout << "Studenci, ktorzy otrzymali ilosc punktow podzielna przez 3 z reszta 1:" << endl;
    for (int i = granica1; i < granica2; i++)
        cout << tab[i].punkty << "\t" << tab[i].imie << " " << tab[i].nazwisko << endl;
    cout << "Studenci, ktorzy otrzymali ilosc punktow podzielna przez 3 z reszta 2:" << endl;
    for (int i = granica2; i < n; i++)
        cout << tab[i].punkty << "\t" << tab[i].imie << " " << tab[i].nazwisko << endl;
}
   int main()
{
	int znak;
	do
	{
    cout<<"1.Wczytanie i wyswietlenie danych"<<endl; 
	cout<<"2.Podzial zbioru na dwie czesci"<<endl; //1 czesc: studenci <=10pkt, 2 czesc: studenci >10pkt
	cout<<"3.Podzial zbioru na trzy czesci"<<endl;//1czesc: studenci mający liczbe pkt podzielną przez 3, 2 czesc: studenci mający liczbe pkt podzielną przez 3 z resztą 1, 3 czesc: studenci mający liczbe pkt podzielną przez 3 z resztą 2
	cout<<"0.Wyjscie"<<endl;
	cin>>znak;
	switch(znak)
	{
		case 1:
		    {
			int n;
            student *tab;
            wczytajStudentow(tab, &n);
            wyswietlStudentow(tab, n);
			break;
			}
		case 2:
			{
            int n;
            student *tab;
            wczytajStudentow(tab, &n);
            int granica = 10;
            int indeks = podziel2czesci(tab, n, granica);
            wyswietlStudentow_2czesci(tab, n, indeks);
			break;
			}
		case 3:
			{
            int n;
            student *tab;
            wczytajStudentow(tab, &n);
            int granica1, granica2;
            podziel3czesci(tab, n, &granica1, &granica2);
            wyswietlStudentow_3czesci(tab, n, granica1, granica2);
			break;
			}
		case 0:
			{cout<<"Koniec";
			break;
			}
		default:
			printf("Podano nieistniejaca opcje");
    }
	}while(znak!=0);
}

