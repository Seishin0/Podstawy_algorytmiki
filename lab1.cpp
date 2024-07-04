
#include <iostream> //1.2 1.3 1.4
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <unordered_map>
using namespace std;

void przydzielPamiec1D(int *&tab, int n){	//przydzieleniepamięci  w  tablicy jednowymiarowej,n –rozmiar tablicy
	tab=new int[n];
}

void wypelnijTablice1D(int *tab, int n, int a, int b){ //wypełnienie  tablicy jednowymiarowej wygenerowanymi liczbami z zakresu <a,b>
	int i;
	for (i=0;i<n;i++)
		tab[i]=rand()%(b-a+1)+a;
}

void usunTablice1D(int *&tab){ // zwolnieniepamięci w tablicy jednowymiarowej,
	delete[] tab;
}

void wyswietl1D(int* tab, int n)//wyświetlenie   zawartości   tablicy jednowymiarowej,
{
	for(int i=0;i<n;i++)
		{cout<<tab[i]<<",";
		}
	cout<<endl;
}

bool czyPierwsza(int x) {//sprawdzanie czy liczba jest liczbą pierwszą
    if (x <= 1) {
        return false;
    }
    for (int i = 2; i <= sqrt(x); i++) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

int main()
{
	int znak;
	do
	{cout<<"1.Minimalny element"<<endl;  //Znajdz najmniejszy element tablicy i sprawdz czy jest liczba pierwsza, przedział losowanych liczb <a,b>
	cout<<"2.Zliczanie elementów w tablicy"<<endl; //Zliczenie elementów tablicy i wyświetlenie ile razy dana cyfra wystąpiła, przedział losowanych liczb <0,9>
	cout<<"3.Maksymalny element"<<endl; ////Znajdz największy element tablicy i policz sume cyfr znalezionej liczby, przedział losowanych liczb <a,b>
	cout<<"0.Wyjscie"<<endl; //zakoncz program
	cin>>znak;
	switch(znak)
	{
		case 1: 
			{int i,a,b,n;
			cout<<"Podaj rozmiar tablicy: ";
			cin>>n;			
			int* tab=nullptr;
			przydzielPamiec1D(tab,n);
			cout<<"Podaj przedzial liczbowy: "<<endl;
			cin>>a;
			cin>>b;			
			wypelnijTablice1D(tab,n,a,b);
			int najmniejszy=tab[0];
			for(i=0;i<n;i++) //wybór najmniejszego elementu tablicy
			{if (tab[i]<najmniejszy)
				najmniejszy=tab[i]; 
			}
			cout<<"Najmniejszy element: "<<najmniejszy<<endl;
			if (czyPierwsza(najmniejszy)){
				cout << najmniejszy << " jest liczba pierwsza" << endl;
			}
			else{
				cout << najmniejszy << " nie jest liczba pierwsza"<<endl;
			}
			break;
			}
		case 2:
			{int i,a=0,b=9,n;
			cout<<"Podaj rozmiar tablicy: ";
			cin>>n;
			int* tab=new int[n];
			wypelnijTablice1D(tab,n,a,b);
			unordered_map<int, int> counts;
			for(i=0;i<n;i++)
			{++counts[tab[i]];
			}
			wyswietl1D(tab,n);
			for (const auto& entry : counts) {
        	cout << entry.first << ": " << entry.second << endl;
    		}
			break;
			}
		case 3:
			{int x,i,a,b,n,maks,suma=0;
			cout<<"Podaj rozmiar tablicy: ";
			cin>>n;
			int* tab=nullptr;
			przydzielPamiec1D(tab,n);
			cout<<"Podaj przedzial liczbowy: "<<endl;
			cin>>a;
			cin>>b;
			wypelnijTablice1D(tab,n,a,b);
			maks=tab[0];
			for(i=0;i<n;i++)
			{if (tab[i]>maks)
				{maks=tab[i];
				x=i;
				}
			}
			while(maks>0){
				suma+=maks%10;
				maks/=10;
			}
			cout<<"Największa liczba: "<<tab[x]<<endl;
			cout<<"Suma cyfr: "<<suma<<endl;
			break;
			}
		case 0:
			{cout<<"Koniec";
			break;
			}
		default:
			cout<<("Podano nieistniejaca opcje");
	}
	}while(znak!=0);
}
