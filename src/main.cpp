#include <mpi.h>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "input.hpp"
#include "output.hpp"
#include "grid.hpp"

using namespace std;

const int N = 65536;
const int n_arr[4] = {10, 50, 100, 1000};

void show_grid(double *grid, int n);

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double alpha = R * pow(10, -11);

    for (int k = 0; k < 4; k++) {
        // Size of total grid
        int n = n_arr[k];

        // Size of partial grid for each proccess
        int pn = n / size;

        if (rank == 0) {
            cout << "n: " << n << endl;
            cout << "pn: " << pn << endl;
            cout << "size: " << size << endl;
        }

        double *data, *grid, *partial_grid;

        data  = new double [N * 4];
        grid  = new double [n * n];
        partial_grid  = new double [pn * n];

        // Process number 0 reads input from file
        // and broadcasts it to the other processes
        if (rank == 0)
            get_input(data);
        MPI_Bcast(data, N * 4, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        get_grid(grid, partial_grid, data, pn, n, alpha);

        if (rank == 0)
            print_output(grid, n);

        delete [] grid;
        delete [] partial_grid;
        delete [] data;
    }

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
