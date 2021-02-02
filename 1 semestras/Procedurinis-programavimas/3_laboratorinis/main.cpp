#include "func.h"

using namespace std;

//Failo pavadinimo deklaravimas (nebutina)
const string instream = "l2.dat";

//Haversine formule atstumui gaublyje skaiciuoti
double HaversineDistance(miestas a, miestas b) {
	double dlon = fabs(a.lat - b.lat);
	double dlat = fabs(a.lon - b.lon);
	double aa = pow((sin((double)dlon / (double)2 * 0.01745)), 2) + cos(a.lat * 0.01745) * cos(b.lat * 0.01745) * pow((sin((double)dlat / (double)2 * 0.01745)), 2);
	double c = 2 * atan2(sqrt(aa), sqrt(1 - aa));
	double d = 6371 * c;
	return d;
}

void BestLocation(miestas City[], int count, int& nX, int X[], int n) {

    double laikinas = 0;
    double naujas = 0;
    int indeksas = 0;

    //Del sito, funkcija iesko vis didesnio indekso, pvz: 0, 1, 2, ...
    X[nX-1] = 0;

    if(count < n) {
        for(int i = 0; i < N; i++) {
            
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

    for(int i = 0; i < n; i++) {
        if (i == n - 1){
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

