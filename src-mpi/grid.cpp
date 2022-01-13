#include <mpi.h>
#include <math.h>
#include <iostream>

using namespace std;

const int N = 65536;
const int M = 1000;
const double R = 3526229;

double get_coord(double i, double n) {
    return -R + i / (n - 1) * 2 * R;
}

void get_grid(double *grid, double *partial_grid, double *data,
        int pn, int n, double alpha) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    for (int i = 0; i < pn; i++)
        for (int j = 0; j < n; j++)
            partial_grid[i * n + j] = 0;

    for (int i = 0; i < pn; i++) {
        for (int j = 0; j < n; j++) {
            double xij = get_coord((double)(i + rank * pn),
                    (double)n);
            double zij = get_coord((double)j, (double)n);

            for (int k = 0; k < N; k++) {
                double x       = data[k * 4 + 0];
                double y       = data[k * 4 + 1];
                double z       = data[k * 4 + 2];
                double density = data[k * 4 + 3];

                partial_grid[i * n + j] += density * exp(-alpha *
                        sqrt((x - xij) * (x - xij) +
                             (z - zij) * (z - zij) +
                             (y - 0)   * (y - 0)));

            }
        }
    }
    MPI_Gather(partial_grid, pn * n, MPI_DOUBLE, grid, pn * n,
            MPI_DOUBLE, 0, MPI_COMM_WORLD);
}
