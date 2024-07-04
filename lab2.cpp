#include <iostream> //2
#include <cstdlib>
#include <time.h>
#include <math.h>
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

void sortowanieBabelkowe(int* tab, int n, int tryb)
{
 if(tryb==1) // tryb rosnący
 {
    int i=n-1;
    while(i>0)
    {
        int j=0;
        while(j<i)
        {
            if(tab[j]>tab[j+1])
            swap(tab[j],tab[j+1]);
            j=j+1;
        }
        i=i-1;
    }
 }
 if(tryb==2)// tryb malejący
 {
    int i=n-1;
    while(i>0)
    {
        int j=0;
        while(j<i)
        {
            if(tab[j]<tab[j+1])
            swap(tab[j],tab[j+1]);
            j=j+1;
        }
        i=i-1;
    }
 }
}
void sortowaniePrzezWybor(int* tab, int n, int tryb)
{
if(tryb==1) // tryb rosnący
 {
    int i=n-1;
    while(i>0)
    {   int ind=0;
        int j=0;
        while(j<=i)
        {
            if(tab[j]>tab[ind])
            ind=j;
            j=j+1;
        }
        swap(tab[i],tab[ind]);
        i=i-1;
    }
 }
 if(tryb==2)// tryb malejący
 {
    int i=n-1;
    while(i>0)
    {   int ind=0;
        int j=0;
        while(j<=i)
        {
            if(tab[j]<tab[ind])
            ind=j;
            j=j+1;
        }
        swap(tab[i],tab[ind]);
        i=i-1;
    }
}
}
void sortowaniePrzezWstawianie(int* tab, int n, int tryb)
{
if(tryb==1) // tryb rosnący
 {
    int i=n-2;
    while(i>=0)
    {   int j=i;
        int temp=tab[j];
        while(temp>tab[j+1]&&j<n-1)
        {
            tab[j]=tab[j+1];
            j=j+1;
        }
        tab[j]=temp;
        i=i-1;
    }
}
if(tryb==2) // tryb malejący
 {
    int i=n-2;
    while(i>=0)
    {   int j=i;
        int temp=tab[j];
        while(temp<tab[j+1]&&j<n-1)
        {
            tab[j]=tab[j+1];
            j=j+1;
        }
        tab[j]=temp;
        i=i-1;
    }
}
}
int main() //Sortowanie tablicy o rozmiarze n, z losowymi liczbami z przedziału <a,b>, wybranym algorytmem sortowania i trybem
{ 	setlocale(LC_ALL, "pl_PL.UTF-8");
	int znak;
	do
	{cout<<"1.Sortowanie bąbelkowe"<<endl;
	cout<<"2.Sortowanie przez wybór"<<endl;
	cout<<"3.Sortowanie przez wstawianie"<<endl;
	cout<<"0.Wyjscie"<<endl;
	cin>>znak;
	switch(znak)
	{
		case 1:
			{int i,a,b,n,tryb1;
			cout<<"Podaj rozmiar tablicy: ";
			cin>>n;
			int* tab=nullptr;
			przydzielPamiec1D(tab,n);
			cout<<"Podaj przedzial liczbowy: "<<endl;
			cin>>a;
			cin>>b;
			wypelnijTablice1D(tab,n,a,b);
            wyswietl1D(tab, n);
            cout<<"Podaj tryb: 1-rosnący 2 malejący"<<endl;
			cin>>tryb1;
            sortowanieBabelkowe(tab,n,tryb1);
            wyswietl1D(tab, n);
            usunTablice1D(tab);
			break;
			}
		case 2:
			{int i,a,b,n,tryb2;
			cout<<"Podaj rozmiar tablicy: ";
			cin>>n;
			int* tab=nullptr;
			przydzielPamiec1D(tab,n);
			cout<<"Podaj przedzial liczbowy: "<<endl;
			cin>>a;
			cin>>b;
			wypelnijTablice1D(tab,n,a,b);
            wyswietl1D(tab, n);
            cout<<"Podaj tryb: 1-rosnący 2 malejący"<<endl;
			cin>>tryb2;
            sortowaniePrzezWybor(tab,n,tryb2);
            wyswietl1D(tab, n);
            usunTablice1D(tab);
			break;
			}
		case 3:
			{int i,a,b,n,tryb3;
			cout<<"Podaj rozmiar tablicy: ";
			cin>>n;
			int* tab=nullptr;
			przydzielPamiec1D(tab,n);
			cout<<"Podaj przedzial liczbowy: "<<endl;
			cin>>a;
			cin>>b;
			wypelnijTablice1D(tab,n,a,b);
            wyswietl1D(tab, n);
            cout<<"Podaj tryb: 1-rosnący 2 malejący"<<endl;
			cin>>tryb3;
            sortowaniePrzezWstawianie(tab,n,tryb3);
            wyswietl1D(tab, n);
            usunTablice1D(tab);
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