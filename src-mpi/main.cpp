#include <mpi.h>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <sys/time.h>

#include "input.hpp"
#include "output.hpp"
#include "grid.hpp"

using namespace std;

const int N = 65536;
// const int n_arr[4] = {10, 50, 100, 1000};
const int n_arr[8] = {10, 20, 50, 100, 250, 500, 750, 1000};
const double alpha_arr[4] = {R * pow(10, -11) * 0.15,
                             R * pow(10, -11) * 0.25,
                             R * pow(10, -11) * 0.5,
                             R * pow(10, -11) * 1};

void show_grid(double *grid, int n);

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    struct timeval t1, t2;
    double time;

    double *data;
    data  = new double [N * 4];
    // Process number 0 reads input from file
    // and broadcasts it to the other processes
    if (rank == 0)
        get_input(data);

    MPI_Bcast(data, N * 4, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0)
        cout << "n t" << endl;

    for (int k = 7; k < 8; k++) {
        // Size of total grid
        int n = n_arr[k];

        // Size of partial grid for each proccess
        int pn = n / size;

        if (n % size != 0)
            pn++;

        // if (rank == 0 && (n == 10 || n == 20 || n == 500)) {
        //     cout << "n: " << n << endl;
        //     cout << "pn: " << pn << endl;
        //     cout << "size: " << size << endl;
        //     cout << "grid size: " << pn * size * n << endl;
        // }

        double *grid, *partial_grid;

        grid  = new double [pn * size * n];
        partial_grid  = new double [pn * n];

        for (int p = 0; p < 4; p++) {
            double alpha = alpha_arr[p];

            gettimeofday(&t1, 0);
            get_grid(grid, partial_grid, data, pn, n, alpha);
            gettimeofday(&t2, 0);
            
            if (rank == 0) {
                time = (1.0e6 * (t2.tv_sec - t1.tv_sec) +
                        t2.tv_usec - t1.tv_usec) / 1000.0;
                cout << n << " " << time << endl;
                print_output(grid, n, p);
            }

           MPI_Barrier(MPI_COMM_WORLD);
        }

        delete [] grid;
        delete [] partial_grid;
    }

    delete [] data;

    MPI_Finalize();
    return 0;
}

void show_grid(double *grid, int n) {
    for(int i = 0; i < n; i++) {
    	for(int j = 0; j < n; j++)
    		cout << grid[i * 4 + j] << " ";
        cout << endl;
    }
}
