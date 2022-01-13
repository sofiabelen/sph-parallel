#include <openacc.h>
#include <math.h>
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
const int n_arr[8] = {10, 20, 50, 100, 250, 500, 750, 1000};
const double alpha_arr[4] = {R * pow(10, -11) * 0.15,
                             R * pow(10, -11) * 0.25,
                             R * pow(10, -11) * 0.5,
                             R * pow(10, -11) * 1};

void show_grid(double *grid, int n);

int main(int argc, char* argv[]) {
    double *data;
    data  = new double [N * 4];

    get_input(data);

    struct timeval t1, t2;
    double time;

    cout << "n t" << endl;
    for (int k = 0; k < 8; k++) {
        // Size of total grid
        int n = n_arr[k];

        double *grid;
        grid  = new double [n * n];

        for (int p = 0; p < 4; p++) {
            double alpha = alpha_arr[p];

            gettimeofday(&t1, 0);
            get_grid(grid, data, n, alpha);
            gettimeofday(&t2, 0);

            time = (1.0e6 * (t2.tv_sec - t1.tv_sec) +
                    t2.tv_usec - t1.tv_usec) / 1000.0;
            cout << n << " " << time << endl;

            // show_grid(grid, n);
            print_output(grid, n, p);
        }
        delete [] grid;
    }
    delete [] data;

    return 0;
}

void show_grid(double *grid, int n) {
    cout << endl << "Grid:" << endl;
    for(int i = 0; i < n; i++) {
    	for(int j = 0; j < n; j++)
    		cout << grid[i * n + j] << " ";
        cout << endl;
    }
}
