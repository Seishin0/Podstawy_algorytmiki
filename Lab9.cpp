#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;
//stos zwykly
struct element{
    int number;
    element * next;
};
void push(element* &Stack, int value){ //dodawanie elementu na stos
    element *el = new element;
    el->number = value;
    el->next = Stack;
    Stack = el;
}
bool isEmpty(element *Stack){
    return (Stack==nullptr);
}
int top(element *Stack){    //pobranei ostatniej wartosci stosu
    if(!isEmpty(Stack))
        return Stack->number;
    return -1;
}
void pop(element *&Stack){  //usuniecie elementu ze stosu
    if (!isEmpty(Stack)){
        element *temp = Stack;
        Stack = Stack->next;
        delete temp;
    }
}
void wyswitlStack(element Stack){
    bool stop = false;
    element *TEMP = &Stack;
    while(!stop){
        if (!isEmpty(TEMP)){
            element *temp = TEMP;
            cout << TEMP->number << " ";
            TEMP = TEMP->next;
            delete temp;
        }
        else
            stop = true;
    }
    cout << endl;
}
void lab_9_1();

//stos odwrocenie kolejnosci
struct elementT{
    char litera;
    elementT * next;
};
bool isEmptyT(elementT *Stack){
    return (Stack==nullptr);
}
void push(elementT *&Stack, char litera){
    elementT *el = new elementT;
    el->litera = litera;
    el->next = Stack;
    Stack = el;
}
void popT(elementT *& Stack){
    if (!isEmptyT(Stack)){
        elementT *temp = Stack;
        Stack = Stack->next;
        delete temp;
    }
}
char topT(elementT *Stack){
    if(!isEmptyT(Stack))
        return Stack->litera;
    return '1';
}
void zapisWynika(elementT *tekst){
    ofstream zapis;
    zapis.open("wyniki.txt");
    bool stop = false;
    while(!stop){
        if (!isEmptyT(tekst)){
            zapis << topT(tekst);
            popT(tekst);
        }
        else
            stop = true;
    }
    zapis.close();
}
void wczytajPlik(elementT *&litery){
    ifstream plik, plikTemp;

    char sim;

    plikTemp.open("znaki1.txt");
    plik.open("znaki1.txt");
    int dl = 0;
    while (plikTemp.get(sim))
        dl ++;
    plikTemp.close();
    int i = 0;
    while (plik.get(sim) && i<dl){
        push(litery,sim);
        i++;
    }
    plik.close();
}
void lab_9_2();

int main()
{
  int n;
    unsigned short znak = 0;
    do{
        system("cls");
        cout << "Podaj nr zadanka:" << endl
             << "0 - wyjscie\n"
             << "1 - 9.1\n"
             << "2 - 9.2\n"
             << ">>>>> ";
        cin >> znak;
        switch(znak){
            case 0:
                break;
            case 1:
                lab_9_1();

                break;
            case 2:
                lab_9_2();

                break;
            default:
                break;
        }
    }while(znak == 0);

    return 0;
}
void lab_9_1(){

    element* Stack=nullptr;
    element* Temp =nullptr;
    int n, delEl, temp, ost;
    bool stop;
    unsigned short wyjsc = 0;
    do{
        cout << "Podaj nr zadanka:" << endl
             << "1 - 1) sprawdzenie czy stos jest pusty\n"
             << "2 - 2) dodanie elementu na stos\n"
             << "3 - 3) usuniecie elementu ze stosu\n"
             << "4 - 4) pobranie elementu ze stosu\n"
             << "5 - 5) usuniecie wszystkich elementow ze stosu\n"
             << "6 - 6) wyjscie z programu\n"
             << ">>>>> ";
        cin >> n;
        switch(n){
            case 1:
                if (isEmpty(Stack))
                    cout << "Stos jest pusty!" << endl;
                else{
                    cout << "Stos nie jest pusty." << endl;
                    wyswitlStack(*Stack);
                }

                break;
            case 2:
                cout << "Podaj liczbe elementow stosu: ";
                cin  >> n;
                cout << "Podaj liczbe od 1 do 10" << endl;
                for(int i=0; i<n;){
                    cin  >> temp;
                    if (temp >= 1 && temp <= 10){
                        i++;
                        push(Stack, temp);
                    }
                    else
                        cout << "To nie byla liczba z zakresu 1-10!" << endl;
                }
                break;
            case 3:
                cout << "Ile elementow chcesz usunac: ";
                cin  >> delEl;
                for(int i = 0; i<delEl; i++){
                    pop(Stack);
                }
                if (isEmpty(Stack))
                    cout << "Stos jest pusty!" << endl;

                break;
            case 4:
                ost = top(Stack);
                if(ost != -1)
                    cout << "Ostatni stos - " << ost << endl;
                else
                    cout << "Stos juz jest pusty!" << endl;

                break;
            case 5:
                stop = false;
                while(!stop){
                    if (!isEmpty(Stack)){
                        pop(Stack);
                    }
                    else
                        stop = true;
                }
                cout << "Wszytkie elementy zostaly usuniete!" << endl;

                break;
            case 6:
                delete Stack;
                wyjsc = true;
                break;
            default:
                break;
        }
    }while(wyjsc == 0);
}

void lab_9_2(){
    elementT* tekst=nullptr;
    cout << "Wczytanie pliku!" << endl;
    wczytajPlik(tekst);
    cout << "Odwrocenie kolejnosci" << endl;
    zapisWynika(tekst);

}
