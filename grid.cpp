#include <omp.h>
#include <math.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int R = 3526229;

double get_coord(double i, double n) {
    return -R + i / (n - 1) * 2 * R;
}

vector<vector<double> > get_grid(int n, double alpha,
        vector<vector<double> > &data) {
    vector<vector<double> > grid(n, vector<double>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double xij = get_coord((double)i, (double)n);
            double zij = get_coord((double)j, (double)n);

            double tmp = 0;
            // for (int k = 0; k < 100; k++) {
            for (int k = 0; k < data.size(); k++) {
                double x = data[k][0];
                double y = data[k][1];
                double z = data[k][2];
                double density = data[k][3];

                grid[i][j] += density * exp(-alpha *
                        sqrt((x - xij) * (x - xij) +
                             (z - zij) * (z - zij) +
                             (y - 0)   * (y - 0)));

                // tmp += density * exp(-alpha *
                //         sqrt((x - xij) * (x - xij) +
                //              (z - zij) * (z - zij) +
                //              (y - 0)   * (y - 0)));
            }
            // cout << i << " " << j << " " << tmp << endl;
        }
    }

    return grid;
}
