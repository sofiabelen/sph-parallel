#include <mpi.h>
#include <fstream>
#include <string>

using namespace std;

void print_output(double *grid, int n) {
    fstream file("../data/grid" + to_string(n) + ".csv", ios::out);

    for(int i = 0; i < n; i++) {
    	for(int j = 0; j < n; j++)
    		file << grid[i * n + j] << " ";
        file << endl;
    }
}

