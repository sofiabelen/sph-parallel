#include <omp.h>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "input.hpp"
#include "output.hpp"
#include "grid.hpp"

using namespace std;

void show_grid(vector<vector<double> > &grid) {
    for(int i = 0; i < grid.size(); i++) {
    	for(int j = 0; j < grid[i].size(); j++)
    		cout << grid[i][j] << " ";
        cout << endl;
    }
}

int main() {
    vector<vector<double> > data = get_input("xyz270.csv");
    double alpha = R * pow(10, -11);
    int n = 10;

    vector<vector<double> > grid = get_grid(n, alpha, data);
    print_output(grid, "grid.csv");
    // show_grid(grid);
    return 0;
}
