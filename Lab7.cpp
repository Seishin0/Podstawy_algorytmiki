#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;

struct student{
    string imie    ;
    string nazwisko;
    int    punkty;
};
void wczytajStudentow(student *&tab, int *n){
    string sciezka,linia,pomoc;
    int liczbaStudentow;
    ifstream plik;
    char sredniki;
    plik.open("D:\\Sem2\\Podstawy algorytmiki\\lab7\\studenci.csv");
    plik >> liczbaStudentow;
    for(int i = 0; i < 2; i++) plik >> sredniki;

    tab = new student[liczbaStudentow];

    for(int i=0; i<liczbaStudentow; i++){
        plik>>linia;
        stringstream ss(linia);
        getline(ss, tab[i].imie, ';');
        getline(ss, tab[i].nazwisko, ';');
        getline(ss, pomoc);
        tab[i].punkty=atoi(pomoc.c_str());
        }
    plik.close();
    *n = liczbaStudentow;
}

void wyswietlStudentow(student* tab, int n){
    cout << "W pliku " << n
         << " studentow" << endl;
    for (int i = 0; i < n; i++){
        cout << i << " Punkty: " << tab[i].punkty << "\t"
             << tab[i].imie     << " "
             << tab[i].nazwisko << endl;
    }
}

void zadanie_7_1(){  //Wczytanie z pliku
    student *tab;
    int rozmiar_tablicy;
    wczytajStudentow(tab, &rozmiar_tablicy);
    wyswietlStudentow(tab, rozmiar_tablicy);
}

void wyszLiniowe(student *tab, int n, int wartosc, int *index){
    int e = -1;
    for (int i=0; i < n; i++){
        if (tab[i].punkty == wartosc){
            index[e+1] = i;
            e++;
        }
    }
    index[n] = e;
}

void zadanie_7_2(){ //Wyszukiwanie liniowe
    student *tab;
    int rozmiar_tablicy;
    wczytajStudentow(tab, &rozmiar_tablicy);
    wyswietlStudentow(tab, rozmiar_tablicy);
    int n, *index = new int[rozmiar_tablicy+1];;
    cout << "Podaj wartosc do wyszukiwania: ";
    cin >> n;
    wyszLiniowe(tab, rozmiar_tablicy, n, index);
    if (index[rozmiar_tablicy] != -1){
        for (int j=0; j<=index[rozmiar_tablicy]; j++){
            cout << "I:" << index[j] << " "
                 << tab[index[j]].punkty       << " "
                 << tab[index[j]].imie         << " "
                 << tab[index[j]].nazwisko     << " "
                 << endl;
        }
    }
    else{
        cout << "Nie ma takiej wartosci w tablicy!" << endl;
    }
}

void zapis(student *tab, int *index, int n){
    ofstream zapis;
    zapis.open("wyniki.csv");
    zapis<<index[n]+1<<";;"<<endl;
    for (int i=0; i<=index[n]; i++){
        zapis<<tab[index[i]].imie<<";"<<tab[i].nazwisko<<";";
        zapis<<tab[index[i]].punkty<<endl;
    }

    zapis.close();

}

void sortowanieQuickSort(student* tab, int lewy, int prawy, int tryb){
    int srodek = (lewy + prawy)/2;

    struct student piwot  = tab[srodek];

    tab[srodek] = tab[prawy];

    int granica = lewy;

    for (int i = lewy; i < prawy; i++){
        if (tryb == 1){
            if (tab[i].punkty < piwot.punkty){
                swap(tab[granica], tab[i]);
                granica ++ ;
            }
        }
        else{
            if (tab[i].punkty > piwot.punkty){
                swap(tab[granica], tab[i]);
                granica ++ ;
            }
        }
    }
    tab[prawy] = tab[granica];
    tab[granica] = piwot;

    if (lewy  < granica-1) sortowanieQuickSort(tab, lewy, granica-1, tryb);
    if (prawy > granica+1) sortowanieQuickSort(tab, granica+1, prawy, tryb);
}

void wyszBisekcyjne(student *tab, int n, int wartosc, int *index){

    int l = 0,p = n-1,srodek;
    index[n] = -1;
    while(l<=p){
        srodek = (p+l)/2;
        if(tab[srodek].punkty == wartosc){
            int e = index[n]+1;
            index[e] = srodek;
            index[n] = e;
            p--;
        }
        if (wartosc < tab[srodek].punkty)
        {
            p = srodek+1;
            while ((p<n) && (tab[p].punkty == wartosc))
                p++;
        }
        else
        {
                l = srodek-1;
                while((l>=0) && (tab[l].punkty == wartosc))
                p--;
        }
    }
}

void zadanie_7_3(){ //Wyszukiwanie bisekcyjne
    student *tab;
    int rozmiar_tablicy;
    wczytajStudentow(tab, &rozmiar_tablicy);
    sortowanieQuickSort(tab, 0, rozmiar_tablicy-1, 1);
    wyswietlStudentow(tab, rozmiar_tablicy);

    int wartosc,
        *index = new int[rozmiar_tablicy+1];

    cout << "Podaj wartosc do wyszukiwania: ";
    cin >> wartosc;

     wyszBisekcyjne(tab, rozmiar_tablicy, wartosc, index);
    if (index[rozmiar_tablicy] != -1){
        for (int j=0; j<=index[rozmiar_tablicy]; j++){
            cout << "I:" << index[j] << " "
                 << tab[index[j]].punkty       << " "
                 << tab[index[j]].imie         << " "
                 << tab[index[j]].nazwisko     << " "
                 << endl;
        }
        zapis(tab, index, rozmiar_tablicy);
    }
    else{
        cout << "Nie ma takiej wartosci w tablicy!" << endl;
    }
}
int main()
{
	int znak;
	do
	{
    cout << "Podaj zadanie ktore chcesz zobaczyc\n"
         << "0 - Wyjscie\n"
        << "1 - Zadanie 7.1\n"
        << "2 - Zadanie 7.2\n"
        << "3 - Zadanie 7.3\n"
        << ">>>>> ";
	cin>>znak;
	switch(znak)
	{
		case 1:
		    {
			zadanie_7_1();
            system("pause");
            system("cls");
            break;
			}
		case 2:
			{
            zadanie_7_2();
            system("pause");
            system("cls");
            break;
			}
		case 3:
			{
            zadanie_7_3();
            system("pause");
            system("cls");
            break;
			}
		case 0:
			{cout<<"Koniec";
			break;
			}
		default:
		    system("cls");
			printf("Podano nieistniejaca opcje");
    }
	}while(znak!=0);
}

