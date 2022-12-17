#include <iostream>
#include "mpi.h"
#include <fstream>


int main(int argc, char* argv[])
{
    int size = 2500;
    int rank;
    int numproc;
    int localSize;
    int i, j, k;
    double start, finish;
    int tem;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numproc);

    localSize = size / numproc;

    int* A = new int[size * size];
    int* B = new int[size * size];

    int* loc_mat_one = new int[localSize * size];
    int* loc_res = new int[localSize * size];

    int* C = new int[size * size];

    if (rank == 0)
    {
        for (i = 0; i < size; i++)
            for (j = 0; j < size; j++)
                A[i * size + j] = rand() % 10;

        for (j = 0; j < size; j++)
            for (i = 0; i < size; i++)
                B[i * size + j] = rand() % 10;

        start = MPI_Wtime();
        MPI_Scatter(A, localSize * size, MPI_INT, loc_mat_one, localSize * size, MPI_INT, 0, MPI_COMM_WORLD);

        MPI_Bcast(B, size * size, MPI_INT, 0, MPI_COMM_WORLD);

        for (i = 0; i < localSize; i++)
            for (j = 0; j < size; j++) {
                tem = 0;
                for (k = 0; k < size; k++)
                    tem += loc_mat_one[i * size + k] * B[j * size + k];
                loc_res[i * size + j] = tem;
            }

        delete[] loc_mat_one;

        MPI_Gather(loc_res, localSize * size, MPI_INT, C, localSize * size, MPI_INT, 0, MPI_COMM_WORLD);

        int rest = size % numproc;
        if (rest != 0)
            for (i = size - rest - 1; i < size; i++)
                for (j = 0; j < size; j++) {
                    tem = 0;
                    for (k = 0; k < size; k++)
                        tem += A[i * size + k] * B[j * size + k];
                    C[i * size + j] = tem;
                }
        finish = MPI_Wtime();

        delete[] A;
        delete[] B;
        delete[] loc_res;

        std::ofstream result;
        result.open("result2.txt", std::ios::app);

        result << size << " " << finish - start << " " << numproc << std::endl;
        result.close();
    }
    else {
        MPI_Scatter(A, localSize * size, MPI_INT, loc_mat_one, localSize * size, MPI_INT, 0, MPI_COMM_WORLD);

        MPI_Bcast(B, size * size, MPI_INT, 0, MPI_COMM_WORLD);

        for (i = 0; i < localSize; i++)
            for (j = 0; j < size; j++) {
                tem = 0;
                for (k = 0; k < size; k++)
                    tem += loc_mat_one[i * size + k] * B[j * size + k];
                loc_res[i * size + j] = tem;
            }

        delete[] loc_mat_one;
        delete[] B;

        MPI_Gather(loc_res, localSize * size, MPI_INT, C, localSize * size, MPI_INT, 0, MPI_COMM_WORLD);
        delete[] loc_res;
    }
    MPI_Finalize();


    return 0;
}