// MPI program code
#include <iostream>
#include <fstream>\
#include"stdio.h"
#include"stdlib.h"
#include"mpi.h"
#include "time.h"

using namespace std;

#define N 1000
#define X 1000
#define Y 1000

ofstream output("data.txt", ios::app);

int main(int argc, char** argv) {

    //define variables

    int size, rank, sum = 0, i, j, k, darbinis;
    int** matrix1;
    int** matrix2;
    int** mat_res;
    double t1 = 0, t2 = 0, result = 0;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    matrix1 = (int**)malloc(X * sizeof(int*));
    matrix2 = (int**)malloc(N * sizeof(int*));
    mat_res = (int**)malloc(X * sizeof(int*));

    for (i = 0; i < X; i++)
    {
        matrix1[i] = (int*)malloc(N * sizeof(int));
        mat_res[i] = (int*)malloc(Y * sizeof(int));
    }

    for (i = 0; i < N; i++)
        matrix2[i] = (int*)malloc(Y * sizeof(int));

    //define values of matrix1
    srand(time(NULL));

    for (i = 0; i < X; i++)
        for (int j = 0; j < N; j++)
            matrix1[i][j] = rand() % 10;


    //define values of matrix2

    for (i = 0; i < N; i++)
        for (int j = 0; j < Y; j++)
            matrix2[i][j] = rand() % 10;

    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0)
        t1 = MPI_Wtime();
    for (i = rank; i < X; i = i + size)
        for (j = 0; j < Y; j++)
        {
            sum = 0;
            for (k = 0; k < N; k++)
            {
                sum = sum + matrix1[i][k] * matrix2[k][j];
            }
            mat_res[i][j] = sum;
        }

    if (rank != 0) {
        for (i = rank; i < X; i = i + size)
            MPI_Send(&mat_res[i][0], Y, MPI_INT, 0, 10 + i, MPI_COMM_WORLD);
    }

    if (rank == 0) {
        for (j = 1; j < size; j++)
        {
            for (i = j; i < X; i = i + size)
            {
                MPI_Recv(&mat_res[i][0], Y, MPI_INT, j, 10 + i, MPI_COMM_WORLD, &status);
            }
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0)
        t2 = MPI_Wtime();
    result = t2 - t1;

    if (rank == 0) /*{

        for (i = 0; i < X; i++) {
            for (int j = 0; j < N; j++)
                cout << matrix1[i][j] << " ";
            cout << endl;
        }

        for (i = 0; i < N; i++) {
            for (int j = 0; j < Y; j++)
                cout << matrix2[i][j] << " ";
            cout << endl;

            for (i = 0; i < X; i++) {
                for (int j = 0; j < Y; j++)
                    cout << mat_res[i][j] << " ";
                cout << endl;


            }
        }
        */
        output << result << endl; //time taken
       // printf("dydis = #%d \n", size);
        //printf("rank = #%d \n", rank);
    MPI_Finalize();

    //}
}
