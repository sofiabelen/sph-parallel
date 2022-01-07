#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

void print_output(vector<vector<double> > &grid, string fname) {
    fstream file(fname, ios::out);
    for(int i = 0; i < grid.size(); i++) {
    	for(int j = 0; j < grid[i].size(); j++)
    		file << grid[i][j] << " ";
        file << endl;
    }
}

