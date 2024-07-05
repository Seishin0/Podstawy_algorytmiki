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

void wczytajStudentow(student *&tab, int *n) //wczytanie tablicy z pliku studenci.csv
{
    string linia, temp;
    int liczbaStudentow;
    ifstream plik;
    char sredniki;
    plik.open("studenci.csv");
    plik >> liczbaStudentow;
    for (int i = 0; i < 2; i++)
        plik >> sredniki;
    tab = new student[liczbaStudentow];
    for (int i = 0; i < liczbaStudentow; i++)
    {
        plik >> linia;
        stringstream ss(linia);
        getline(ss, tab[i].imie, ';');
        getline(ss, tab[i].nazwisko, ';');
        getline(ss, temp);
        tab[i].punkty = atoi(temp.c_str());
    }
    plik.close();
    *n = liczbaStudentow;
}
void przydzielPamiec1D(int *&tab, int n)//przydzieleniepamięci  w  tablicy jednowymiarowej,n –rozmiar tablicy
{
    tab = new int[n];
}
void usunTabliceStudentow(student *&tab)// zwolnieniepamięci w tablicy jednowymiarowej
{
    delete[] tab;
}
void wyswietlStudentow(student *tab, int n)
{
    cout << "Liczba studentow: " << n << endl;
    for (int i = 0; i < n; i++)
        cout << tab[i].punkty << "\t" << tab[i].imie << " " << tab[i].nazwisko << endl;
}
void sortowanieQuickSort(student *tab, int lewy, int prawy, int tryb)
{
    int srodek = (lewy + prawy) / 2;
    struct student piwot = tab[srodek];
    tab[srodek] = tab[prawy];
    int granica = lewy;
    for (int i = lewy; i < prawy; i++)
    {
        if (tryb == 1) // tryb rosnący
        {
            if (tab[i].punkty < piwot.punkty)
            {
                swap(tab[granica], tab[i]);
                granica++;
            }
        }
        if (tryb == 2) // tryb malejący
        {
            if (tab[i].punkty > piwot.punkty)
            {
                swap(tab[granica], tab[i]);
                granica++;
            }
        }
    }
    tab[prawy] = tab[granica];
    tab[granica] = piwot;
    if (lewy < granica - 1)
        sortowanieQuickSort(tab, lewy, granica - 1, tryb);
    if (prawy > granica + 1)
        sortowanieQuickSort(tab, granica + 1, prawy, tryb);
}

int main()
{
    int n, tryb;
    student *tab;
    wczytajStudentow(tab, &n);
    wyswietlStudentow(tab, n);
    cout << "Podaj tryb sortowania (1 - rosnacy, 2 - malejacy): ";
    cin >> tryb;
    sortowanieQuickSort(tab, 0, n - 1, tryb);
    wyswietlStudentow(tab, n);
    usunTabliceStudentow(tab);
    return 0;
}