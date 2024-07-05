#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void wszukiwanie_naiwne(string tekst, string wzorzec, int dlt, int dlw, int *index){
    int e = -1;
    for (int i=0; i <= dlt-dlw; i++){
        int j=0;
        while (j<dlw && wzorzec[j] == tekst[i+j])
            j++;
        if (j == dlw){
            index[e+1] = i;
            e ++;
        }
    }
    index[dlt-dlw] = e;

}
void zbudujTabliceDopasowan(string wzorzec, int dlw, int *p){
    p[0] = 0;
    p[1] = 0;
    int t = 0;
    for (int i = 1; i<=dlw; i++){
        while ((t>0) && (wzorzec[t] != wzorzec[i]))
            t = p[t];
        if (wzorzec[t] == wzorzec[i])
            t++;
        p[i+1] = t;
    }
}

void kmp(string wzorzec, string tekst, int dlw, int dlt, int *p, int *index){//Algorytm Knutha-Morrisa-Pratta
    int
        i = 0,
        j = 0,
        e = -1;
    while ( i < dlt-dlw+1){
        while ((wzorzec[j] == tekst[i+j]) && (j < dlw))
            j++;
        if (j == dlw){
            index[e+1] = i;
            e ++;
        }
        i=i+max(1,j-p[j]);
        j = p[j];
    }
    index[dlt-dlw+1] = e;
}
void tabliczPrzesuniec(string wzorzec, int dlw, int *p, int pocz, int kon){
    int
        n_pocz = pocz,
        n_kon  = kon;
    for (int i = 0; i<=n_kon-n_pocz; i++)
        p[i] = -1;
    for (int i = 0; i<dlw; i++)
        p[wzorzec[i]-n_pocz] = i;

}

void bm(string wzorzec, string tekst, int dlw, int dlt, int *p, int pocz, int *index){ //Algorytm Boyer’a-Moore’a
    int
        e = -1,
        j,
        n_pocz = pocz;

    for (int i = 0; i <= dlt-dlw;){
        j = dlw-1;

        while ((j>-1) && (wzorzec[j] == tekst[i+j]))
            j --;

        if (j == -1){
            index[e+1] = i;
            e++; i++;
        }
        else{
            i = i + max(1, j-p[tekst[i+j]-n_pocz]);
        }
    }
    index[dlt-dlw+1] = e;


}
int main()
{
	int zadanie;
	do
	{
    cout<<"1.Wczytanie danych"<<endl; 
	cout<<"2.Algorytm naiwny"<<endl;
	cout<<"3.Algorytm Knutha-Morrisa-Pratta"<<endl;
	cout<<"4.Algorytm Boyer'a-Moore'a"<<endl;
	cout<<"0.Wyjscie"<<endl;
	cin>>zadanie;
	switch(zadanie)
	{
		case 1:
		    {
            string tekst, wzorzec;
            cout << "Podaj tekst:";
            cin.ignore();
            getline(cin,tekst);
            cout << "Podaj wzorzec:";
            getline(cin, wzorzec);
            int dlt = tekst.length();
            int dlw = wzorzec.length();
            cout << "Dlugosc tekstu jest " << dlt << endl
                 << "Dlugosc wzorca jest " << dlw << endl;
			break;
			}
		case 2:
            {
            string tekst, wzorzec;
            cout << "Podaj tekst:";
            cin.ignore();
            getline(cin,tekst);
            cout << "Podaj wzorzec: ";
            getline(cin, wzorzec);
            cout << "| ";
            int dlt = tekst.length();
            int dlw = wzorzec.length();
            if ( dlt < dlw ){
            cout << "Wzorzec ma wiecej niz tekst!" << endl;
            }
            for (int i = 0; i<dlt; i++)
                cout << tekst[i] << " | ";
            cout << endl << "| ";

            for (int i = 0; i<dlt; i++)
                cout << i << " | ";
            cout << endl;

            int *index = new int[dlt-dlw+1];
            wszukiwanie_naiwne(tekst, wzorzec, dlt, dlw, index);
            int e = index[dlt-dlw];
            if ( e == -1){
                cout << "W tekscie nie ma tego wzorca!\n";
            }
            else{
                for (int j = 0, i = 0; j <= dlt; j ++){
                    if (j == index[i]){
                        cout << "  ^ ";
                        i++;
                    }
                    else
                        cout << "    ";
                    }
                    cout << endl;
                }
			break;
			}
		case 3:
			{
            string tekst, wzorzec;
            cout << "Podaj tekst:";
            cin.ignore();
            getline(cin,tekst);
            cout << "Podaj wzorzec: ";
            getline(cin, wzorzec);
            int dlt = tekst.length();
            int dlw = wzorzec.length();
            if ( dlt < dlw ){
                cout << "Wzprzec wiecej niz tekst!" << endl;
            }
            cout << "| ";
            for (int i = 0; i<dlt; i++)
                cout << tekst[i] << " | ";

            cout << endl << "| ";
            for (int i = 0; i<dlt; i++)
                cout << i << " | ";
            cout << endl;

            int *p = new int[dlw+1];
            int *index = new int[dlt-dlw+2];
            zbudujTabliceDopasowan(wzorzec, dlw, p);

            kmp(wzorzec, tekst, dlw, dlt, p, index);
            int e = index[dlt-dlw+1];
            if ( e == -1){
                cout << "W tekscie nie ma tego wzorca!\n";
                }
            else{
                for (int j = 0, i = 0; j <= dlt; j ++){
                    if (j == index[i]){
                        cout << "  ^ ";
                        i++;
                    }
                    else
                        cout << "    ";
                }
                cout << endl;
            }
			break;
			}
        case 4:
			{ string tekst, wzorzec;
            cout << "Podaj tekst:";
            cin.ignore();
            getline(cin,tekst);
            cout << "Podaj wzorzec: ";
            getline(cin, wzorzec);
            int dlt = tekst.length();
            int dlw = wzorzec.length();
            if ( dlt < dlw )
                {
                cout << "Wzprzec wiecej niz tekst!" << endl;
                }
            cout << "| ";
            for (int i = 0; i<dlt; i++)
            cout << tekst[i] << " | ";
            cout << endl << "| ";
            for (int i = 0; i<dlt; i++)
            cout << i << " | ";
            cout << endl;
            int *p = new int[dlw+1];
            int *index = new int[dlt-dlw+2];
            zbudujTabliceDopasowan(wzorzec, dlw, p);
            tabliczPrzesuniec(wzorzec, dlw, p, tekst[0], tekst[dlt]);
            bm(wzorzec, tekst, dlw, dlt, p, tekst[0], index);
            int e = index[dlt-dlw+1];
            if ( e == -1)
            {
            cout << "W tekscie nie ma tego wzorca!\n";
            }
            else{
                for (int j = 0, i = 0; j <= dlt; j ++)
                {
                if (j == index[i])
                    {
                    cout << "  ^ ";
                    i++;
                    }
                else
                    cout << "    ";
                }
                cout << endl;
                }
			break;
			}
		case 0:
			{cout<<"Koniec";
			break;
			}
		default:
			printf("Podano nieistniejaca opcje");
	}
	}while(zadanie!=0);
}


