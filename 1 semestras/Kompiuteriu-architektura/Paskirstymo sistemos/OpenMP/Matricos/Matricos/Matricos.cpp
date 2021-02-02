#include <iostream>
#include <fstream>
#include <time.h>
#include <omp.h>

using namespace std;

const int k = 2500, n = 2500, p = 2500;
int matrix_a[n][k] = { 0 }, matrix_b[k][p] = { 0 }, matric_c[n][p] = { 0 };

ofstream output("results.txt");

void Skaiciavimai() {

	int nthreads, tid, chunk = 4;
	double start = omp_get_wtime();
	srand(time(NULL));
	omp_set_num_threads(8);

	int i, j, z, x;

#pragma omp parallel shared(matrix_a, matrix_b, matric_c,nthreads,chunk) private(tid, i, j, z, x)
	{
		x = 10;	//maksimali pirmosios matricos reiksme
		tid = omp_get_thread_num();
		nthreads = omp_get_num_threads();

#pragma omp for schedule (static, chunk)
		//Priskiriamos reiksmes pirmajai matricai
		for (i = 0; i < n; i++) {
			for (j = 0; j < k; j++) {
				matrix_a[i][j] = 1 + rand() % x;
			}
		}

#pragma omp single
		//Priskiriamos reiksmes antrajai matricai
		for (i = 0; i < k; i++) {
			for (j = 0; j < p; j++) {
				int temp = rand() % 2;
				if (temp == 0)
					matrix_b[i][j] = 1;
				else
					matrix_b[i][j] = -1;
			}
		}

#pragma omp for schedule (static, chunk)

		//Pirmosios ir antrosios matricu daugyba
		for (i = 0; i < n; i++) {
			for (j = 0; j < p; j++) {
				int sum = 0;
				for (z = 0; z < k; z++) {
					sum = sum + matrix_a[i][z] * matrix_b[z][j];
				}
				matric_c[i][j] = sum;
			}
		}
	}
	output << omp_get_wtime() - start <<endl;

}

int main(){
/*	int nthreads, tid, chunk = 4;
	double start = omp_get_wtime();
	srand(time(NULL));
	omp_set_num_threads(8);

	int i, j, z, x;
	
	cout << "Pirmos matricos matmenys: " << n << " " << k << endl;
	cout << "Antros matricos matmenys: " << k << " " << p << endl;
	cout << "Trecios matricos matmenys: " << n << " " << p << endl << endl;

#pragma omp parallel shared(matrix_a, matrix_b, matric_c,nthreads,chunk) private(tid, i, j, z, x)
	{
		x = 10;	//maksimali pirmosios matricos reiksme
		tid = omp_get_thread_num();
		nthreads = omp_get_num_threads();

#pragma omp for schedule (static, chunk)
		//Priskiriamos reiksmes pirmajai matricai
		for (i = 0; i < n; i++) {
			for (j = 0; j < k; j++) {
				matrix_a[i][j] = 1 + rand() % x;
			}
		}

#pragma omp single
		//Priskiriamos reiksmes antrajai matricai
		for (i = 0; i < k; i++) {
			for (j = 0; j < p; j++) {
				int temp = rand() % 2;
				if (temp == 0)
					matrix_b[i][j] = 1;
				else
					matrix_b[i][j] = -1;
			}
		}

#pragma omp for schedule (static, chunk)

		//Pirmosios ir antrosios matricu daugyba
		for (i = 0; i < n; i++) {
			for (j = 0; j < p; j++) {
				int sum = 0;
				for (z = 0; z < k; z++) {
					sum = sum + matrix_a[i][z] * matrix_b[z][j];
				}
				matric_c[i][j] = sum;
			}
		}
	}

	double dif = omp_get_wtime() - start; 

	cout << "Programa, naudojant " << nthreads << " branduolius, veiksmus atliko per " << dif << " s" << endl << endl;
	*/

	for (int i = 0; i < 50; i++) {
		Skaiciavimai();
	}
	system("pause");
	return 0;
}