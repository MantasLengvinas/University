#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

const int N = 50;

// Geografines platumos koordinates
double lat[N] = { 54.683,  54.9,    55.717,  54.95,   55.733,  54.4,    54.517,  55.4,    55.083,  55.5,
                  55.283,  55.983,  55.6,    55.25,   55.25,   55.917,  55.883,  55.35,   55.483,  55.917,
                  55.717,  54.017,  54.411,  55.967,  56.2,    54.767,  54.817,  56,      55.067,  54.65,
                  55.367,  55.533,  54.65,   54.683,  56.317,  54.633,  54.395,  55.067,  55.633,  54.217,
                  54.867,  56.067,  55.833,  55.733,  56.267,  55.233,  54.45,   55.05,   54.3,    54.893 };

// Geografines ilgumos koordinates
double lon[N] = { 25.317,  23.9,    21.117,  25.067,  24.35,   24.05,   25.317,  24.7,    24.283,  25.6,
                  23.967,  22.25,   26.417,  22.283,  24.75,   21.85,   21.25,   21.483,  24.15,   21.05,
                  21.4,    23.967,  24.018,  25.583,  24.75,   24.633,  23.867,  22.933,  22.767,  23.033,
                  23.117,  25.1,    25.05,   25.083,  22.9,    23.95,   23.997,  25.65,   22.933,  24.567,
                  24.45,   24.4,    24.967,  26.25,   21.533,  25.417,  23.294,  24.95,   25.383,  23.917 };

// Populiacijos (gyventoju skaicius)
int pop[N] = {    543071,  336817,  177823,  120934,  109034,  63651,   44910,   38840,   33178,   31142,
                  29850,   29119,   26805,   26444,   25886,   22311,   20776,   19751,   18453,   17244,
                  16314,   15547,   14960,   14947,   13780,   13248,   12938,   12721,   12510,   12483,
                  11644,   11400,   11277,   11121,   10733,   10489,   10489,   10312,   9984,    9771,
                  9395,    7997,    7833,    7349,    6920,    6771,    6658,    6654,    6402,    6330 };

// Rinkoje esanciu objektu vietu indeksai
const int nP = 5;
int P[nP] = {0, 1, 2, 3, 4};

// Nauji objektai
const int nX = 3;
int X[nX];

double HaversineDistance(double* a, double* b) {
   double dlon = fabs(a[0] - b[0]);
   double dlat = fabs(a[1] - b[1]);
   double aa = pow((sin((double)dlon/(double)2*0.01745)),2) + cos(a[0]*0.01745) * cos(b[0]*0.01745) * pow((sin((double)dlat/(double)2*0.01745)),2);
   double c = 2 * atan2(sqrt(aa), sqrt(1-aa));
   double d = 6371 * c;
   return d;
}

template <typename T, size_t N>
void PrintArray(T(&arr)[N]) {

    for(int i = 0; i < N; i++){
		cout<<arr[i]<<" ";
	}

}

double Utility(int *X) {
      /* Skaičiuoja ir grąžina kiek procentų klientų tenka naujiems objektams,
         kurių vietovės (indeksai duomenų masyve) aprašytos masyve X */
	double sum = 0, u[2], c[2], dS = INT_MAX, dN = INT_MAX;

	for(int i = 0; i < N; i++){
        c[0] = lat[i];
        c[1] = lon[i];
        for(int j = 0; j < nP; j++){
            u[0] = lat[P[j]];
            u[1] = lon[P[j]];

            if(HaversineDistance(c, u) < dS) {
                dS = HaversineDistance(c, u);
            }
        }
        for(int j = 0; j < nX; j++){
            u[0] = lat[X[j]];
            u[1] = lon[X[j]];

            if(HaversineDistance(c, u) < dN) {
                dN = HaversineDistance(c, u);
            }
        }

        if(dS > dN){
            sum += pop[i];
        }
        if(dN == dS){
            sum += (double)pop[i] / 3;
        }
        dS = INT_MAX;
        dN = INT_MAX;

	}

	int tsum = 0;
    for(int i = 0; i < N; i++){
        tsum += pop[i];
    }

    return (sum / tsum) * 100;
}

int main() {

	for(int i = 0; i < 3; i++){
        cout << "Iveskite nauju imoniu indeksus ("<< 3-i <<"): "; cin >> X[i];
	}
	cout<<endl;

    PrintArray(lat);
    cout<<endl<<endl;
    PrintArray(lon);
    cout<<endl<<endl;
    PrintArray(pop);
    cout<<endl<<endl;

	cout<<Utility(X);

   /* Naudodami funkciją PrintArray atspausdinkite visus tris aukščiau nurodytus masyvus.
   Paskaičiuokite Utility funkcijos reikšmę. Kai P = {0, 1, 2, 3, 4}, X = {5, 6, 7}, Utility(X) turi būti 15.7809. */

   return 0;
}
