#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

long make_hash(long HASH, int s, int off, int p, int exp){
    return (s-off)*pow(p,exp);
}
long update_hash(long HASH,int s_prev, int s_next, int off, int p, int exp)
{
    long u_hash=HASH-(s_prev-off)*pow(p,exp);
        u_hash=(u_hash*p)+(s_next-off);
        return u_hash;
}
void kr(long hashP, string pattern, string text,int lenP, int lenT, int p, int off, int *&index) //Karp-Rabin 
{   long hashT=0;
    index = new int[lenT+2];

    for (int i=0; i<lenP; i++)
    {
        hashT = hashT + make_hash(hashT, text[i], off, p, lenP-i-1);
    }
    int e = -1;
    int i = lenP;
    int j = 0;
    while(i<=lenT){
        if (hashP == hashT){
            index[e+1] = j;
            e++;

        }
        if (i  < lenT){
            hashT = update_hash(hashT, text[j], text[i], off, p, lenP-1
            );
        }
        i ++;
        j ++;
    }
    index[lenT+1] = e;
 }
void wczytajplik(string *&tekst, string *pattern, int *n)
{
    string linia, pomoc;
    ifstream plik, plikTemp;

    plikTemp.open("tekst.txt");
    plik.open("tekst.txt");

    int N = -1;
    while (getline (plikTemp, pomoc))
        N ++;
    plikTemp.close();
    plik >> *pattern;
    tekst = new string[N];
    for(int i=0; i<N; i++){
        plik>>linia;
        stringstream ss(linia);
        getline(ss, tekst[i]);
    }
    plik.close();
    *n = N;
}
int main()
{   long hashP = 0;
    string *tekst;
    int *index;
    int N,p=10, dlT;
    string pattern;
    wczytajplik(tekst,&pattern, &N);
    int dlW=pattern.length();
    for (int i=0; i<dlW; i++)
    {
        hashP = hashP + make_hash(hashP, pattern[i], 'a', p, dlW-i-1);
    }
    cout<<N<<endl;
    cout<<"Wzorzec:\t"<<pattern<<endl;
    for(int i=0; i<N;i++){
        dlT=tekst[i].length();
        kr(hashP, pattern, tekst[i],dlW,dlT,p,'a',index);

        cout << "Linijka " << i+2 << " - Tekst: " << tekst[i] << endl;
        if (index[dlT+1] == -1){
            cout << "Linijka " << i+2 << ":" << index[dlT+1] << endl;
            continue;
        }
         cout << "Linijka "  << i+2 << ": ";
        for (int j=0; j<=index[dlT+1]; j++){
            cout << index[j];
            if (j != index[dlT+1])
                cout << ", ";
        }
        cout << endl;
    }
    return 0;
}
