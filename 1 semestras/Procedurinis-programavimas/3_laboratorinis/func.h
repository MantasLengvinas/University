#ifndef FUNC_H
#define FUNC_H

#include <cmath>
#include <iostream>
#include <fstream>
#include <climits>

// Rinkoje esanciu objektu vietu indeksai
const int N = 50;
const int nP = 5;
static int P[N] = { 0, 1, 2, 3, 4 };

//Strukturos deklaravimas
struct miestas {
	double lon;
	double lat;
	int pop;
};

void PrintArray(int);
void PrintArray(double);
double HaversineDistance(miestas, miestas);
double Utility(miestas*, int*, int);
void BestLocation(miestas*, int, int&, int*, int);

#endif