#include <cmath>
#include <iostream>
#include <fstream>

using namespace std;

//Geografinio tasko (miesto) struktura
struct miestas {
	double lon;
	double lat;
	int pop;
};

double HaversineDistance(miestas a, miestas b) {
	double dlon = fabs(a.lat - b.lat);
	double dlat = fabs(a.lon - b.lon);
	double aa = pow((sin((double)dlon / (double)2 * 0.01745)), 2) + cos(a.lat * 0.01745) * cos(b.lat * 0.01745) * pow((sin((double)dlat / (double)2 * 0.01745)), 2);
	double c = 2 * atan2(sqrt(aa), sqrt(1 - aa));
	double d = 6371 * c;
	return d;
}

const int N = 50;

// Rinkoje esanciu objektu vietu indeksai
int nP = 5;
int P[N] = { 0, 1, 2, 3, 4 };


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

void BestLocation(miestas City[], int count, int& nX, int X[], int n) {

    double laikinas = 0;
    double naujas = 0;
    int indeksas = 0;

    //Del sito, funkcija iesko vis didesnio indekso, pvz: 0, 1, 2, ...
    X[nX-1] = nX - 1;

    if(count < n) {
        for(int i = nX-1; i < N; i++) {
            
            naujas = Utility(City, X, nX);

            if (naujas > laikinas) {
                indeksas = i;
                laikinas = naujas;
            }

            X[nX-1]++;
        }

        X[nX-1] = indeksas;
        nX++;  

        count++;
        BestLocation(City, count, nX, X, n);
    }
}

int main() {


	ifstream input("l2.dat");
    miestas* City = new miestas[N];

    //Duomenu nuskaitymas is failo
	for(int i = 0; i < N; i++) 
		input >> City[i].lat >> City[i].lon >> City[i].pop;

    int n, nX = 1;
    
    cout<<"Kiek nauju objektu planuojama atidaryti? ";cin >> n;cout<<endl;

    int count = 0; //Kintamasis skirtas tikrinti ar ji yra mazense uz n (rekursijos funkcijai)
    int *X = new int[n] { 0 }; //Sukuria masyva dinamineje atmintyje ir priskiria visiem elementam 0

    cout << "(";
    BestLocation(City, count, nX, X, n);

    for(int i = 0; i < nX - 1; i++) {
        if (i == nX - 2){
            cout << X[i];
        }
        else {
            cout << X[i] << ", ";
        }
    }
    cout << ")";

    delete[] City;
	delete[] X;
    
}

