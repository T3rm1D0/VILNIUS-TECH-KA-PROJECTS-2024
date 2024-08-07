#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <atomic>
#include <typeinfo>
#include <conio.h>
#include <set>



using namespace std;
struct Masina { // Sukurta struktura vienai juostai
    string EBusena;
    char ESimbolis;
    char NSimbolis;
    char Kryptis;
    string NBusena;
};
struct Masina2 { // Sukurta struktura dviem juostom
    string EBusena;
    char ESimbolisT1;
    char ESimbolisT2;
    char NSimbolisT1;
    char NSimbolisT2;
    char KryptisT1;
    char KryptisT2;
    string NBusena;
};


void IsvalytiEkr() { // Isvalyti koncole
    (void)system("cls");
}
int main(int argc, char* argv[]) { //Argumento padavimas

    int failas;
    cin >> failas;
    int LinijuKiekis;
    set<string> VisosB;
    ifstream fd(argv[failas]);

    fd >> LinijuKiekis;
    if (LinijuKiekis == 1) { // 1 juosta
        string juosta;
        int galvutespozicija;
        fd >> juosta >> galvutespozicija;
        galvutespozicija--;


        vector<Masina> a;
        Masina temp; //Ivedami duomenys
        while (fd >> temp.EBusena >> temp.ESimbolis >> temp.NSimbolis >> temp.Kryptis >> temp.NBusena) {
            a.push_back(temp);
            VisosB.insert(temp.EBusena);
        }

        fd.close();

        string busena = "0";
        bool veikimas = true;

        while (veikimas) {
            if (_kbhit())//Priverstinis sustabdymas
            {
                int isjungimas = _getch();
                if (isjungimas == 120)
                {
                    cout << "Priverstinis sustabdymas" << endl;
                    break;
                }
            }
            bool KeitimasSekmingas = false;
            IsvalytiEkr();//Koncoles isvalymas

            for (int g = 0; g < a.size(); g++)
            {
                if (a[g].EBusena == busena && a[g].ESimbolis == juosta[galvutespozicija])
                {
                    busena = a[g].NBusena;
                    juosta[galvutespozicija] = a[g].NSimbolis;
                    if (a[g].Kryptis == 'R')
                        galvutespozicija++;

                    if (a[g].Kryptis == 'L')
                        galvutespozicija--;
                    KeitimasSekmingas = true;
                    break;

                }
            }

            if (!KeitimasSekmingas) { // Uzbaigimas
                cout << juosta << endl;
                for (int j = 0; j < galvutespozicija; j++) cout << ' ';
                cout << '^' << endl;
                if (VisosB.find(busena) == VisosB.end()) {
                    cout << "Halted. Pasiekta galine busena: " << busena << endl;
                    break;
                }
                else {
                    cout << "Halted. Nera taisykles busenai: " << busena << " ir simboliui: " << juosta[galvutespozicija] << endl;
                    break;
                }
            }
            else { // Juostos spauzdinimas
                cout << juosta << endl;
                for (int j = 0; j < galvutespozicija; j++) cout << ' ';
                cout << '^' << endl;
            }
            this_thread::sleep_for(chrono::milliseconds(1));//Paletinima koncole

        }
    }
    else if (LinijuKiekis == 2) { // 2 juostos
        string juosta, juosta2;
        int galvutespozicija, galvutespozicija2;
        fd >> juosta >> juosta2 >> galvutespozicija >> galvutespozicija2;
        galvutespozicija--;
        galvutespozicija2--;

        vector<Masina2> b; // Ivedami duomenys
        Masina2 temp;
        while (fd >> temp.EBusena >> temp.ESimbolisT1 >> temp.ESimbolisT2 >> temp.NSimbolisT1 >> temp.NSimbolisT2 >> temp.KryptisT1 >> temp.KryptisT2 >> temp.NBusena) {
            b.push_back(temp);
        }

        fd.close();

        string busena = "0";
        bool veikimas = true;

        while (veikimas) {

            if (_kbhit()) // Priverstinis sustabdymas
            {
                int isjungimas = _getch();
                if (isjungimas == 120)
                {
                    cout << "Priverstinis sustabdymas" << endl;
                    break;
                }
            }
            IsvalytiEkr(); //Koncoles isvalymas
            bool KeitimasSekmingas = false;

            for (int g = 0; g < b.size(); g++) { //Tiuringo masinos veikimas
                if (b[g].EBusena == busena && b[g].ESimbolisT1 == juosta[galvutespozicija] && b[g].ESimbolisT2 == juosta2[galvutespozicija2]) {
                    juosta[galvutespozicija] = b[g].NSimbolisT1;
                    juosta2[galvutespozicija2] = b[g].NSimbolisT2;
                    busena = b[g].NBusena;
                    if (b[g].KryptisT1 == 'R')
                        galvutespozicija++;
                    else if (b[g].KryptisT1 == 'L')
                        galvutespozicija--;
                    if (b[g].KryptisT2 == 'R')
                        galvutespozicija2++;
                    else if (b[g].KryptisT2 == 'L')
                        galvutespozicija2--;
                    KeitimasSekmingas = true;
                    break;
                }
            }

            if (!KeitimasSekmingas) {// Uzbaigimas
                cout << juosta << endl;
                for (int j = 0; j < galvutespozicija; j++) cout << ' ';
                cout << '^' << endl;
                cout << juosta2 << endl;
                for (int j = 0; j < galvutespozicija2; j++) cout << ' ';
                cout << '^' << endl;
                cout << "Halted. Nera taisykles busenai: " << busena << " ir simboliui: " << juosta[galvutespozicija] << endl;
                cout << "Halted. Nera taisykles busenai: " << busena << " ir simboliui: " << juosta2[galvutespozicija2] << endl;
                break;
            }
            else {// Juostu spauzdinimas
                cout << juosta << endl;
                for (int j = 0; j < galvutespozicija; j++) cout << ' ';
                cout << '^' << endl;
                cout << juosta2 << endl;
                for (int j = 0; j < galvutespozicija2; j++) cout << ' ';
                cout << '^' << endl;

            }

            this_thread::sleep_for(chrono::milliseconds(1));//Paletinima koncole
        }
    }

    return 0;
}


