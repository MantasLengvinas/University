#include "func.h"

using namespace std;

void PrintArray(int arrayToPrint[]) {

    for (int i = 0; i < N; i++)
        cout << arrayToPrint[i] << " ";

}

void PrintArray(double arrayToPrint[]) {

    for (int i = 0; i < N; i++)
        cout << arrayToPrint[i] << " ";

}

//Funkcija utility apskaiciuoti statomu objektu naudinguma procentine israiska nuo vartotoju dalies
double Utility(miestas City[], int X[], int nX) {

    int Nauji = 0;
    double APa = INT_MAX, APl = INT_MAX; //Arciausiai pastatytas, arciausiai planuojamas

    for (int i = 0; i < N; i++) {

        //Randamas arciausiai pastytas objektas
        for (int j = 0; j < nP; j++) {

            double Pa = HaversineDistance(City[i], City[P[j]]);
            if (Pa < APa)
                APa = Pa;
        }
        
        //Randamas arciausiai planuojamas statyti objektas
        for (int j = 0; j < nX; j++) {

            double Pl = HaversineDistance(City[i], City[X[j]]);
                if (Pl < APl)
                    APl = Pl;
        }

        //Tikrinama ar jau esamas objektas toliau nei planuojamas statyti
        if (APa > APl)
            Nauji += City[i].pop; //Jei taip, visi to miesto klientai pereina i planuojama statyti objekta
        else if (APa == APl)
            Nauji += City[i].pop / 3; //Jei atstumai lygus, tai i nauja objekta pereina trecdalis klientu
        
        APa = INT_MAX;
        APl = INT_MAX;
    }

    double Visi = 0;

    //Surandami visi klientai
    for(int i = 0; i < N; i++){
        Visi += City[i].pop;
    }

    //Apskaiciuojamas vidurkis
    return (Nauji / Visi) * 100;
}