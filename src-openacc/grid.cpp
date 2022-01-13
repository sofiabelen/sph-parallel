#include <openacc.h>
#include <math.h>
#include <iostream>

using namespace std;

const int N = 65536;
const double R = 3526229;

double get_coord(double i, double n) {
    return -R + i / (n - 1) * 2 * R;
}

void get_grid(double *grid, double *data, int n, double alpha) {

    #pragma acc data copyin(data[0:N*4]) copyout(grid[0:n*n])
    // #pragma acc data copyin(data[0:N*4]) copyout(grid[0:n*n])
    // #pragma acc data copyin(data[0:N*4]) create(cell_ij) copy(grid[0:n*n])
    // #pragma acc data copy(data[0:N*4], cell_ij, grid[0:n*n])
    // #pragma acc enter data copyin(data[0:N*4]) create(cell_ij) create(grid[0:n*n])
    // #pragma acc data create(data[0:N*4], grid[0:n*n], cell_ij)
    {
        #pragma acc parallel loop
        for (int i = 0; i < n; i++) {
            #pragma acc loop
            for (int j = 0; j < n; j++) {
                // double xij = get_coord((double)i, (double)n);
                // double zij = get_coord((double)j, (double)n);
                double xij = -R + (double)i / (double)(n - 1) * 2 * R;
                double zij = -R + (double)j / (double)(n - 1) * 2 * R;

                double cell_ij = 0;

                #pragma acc loop reduction(+:cell_ij)
                for (int k = 0; k < N; k++) {
                    double x       = data[k * 4 + 0];
                    double y       = data[k * 4 + 1];
                    double z       = data[k * 4 + 2];
                    double density = data[k * 4 + 3];
                    
                    // grid[i * n + j] += density * exp(-alpha *
                    cell_ij += density * exp(-alpha *
                            sqrt((x - xij) * (x - xij) +
                                 (z - zij) * (z - zij) +
                                 (y - 0)   * (y - 0)));
                }
                grid[i * n + j] = cell_ij;
            }
        }
    }
}
