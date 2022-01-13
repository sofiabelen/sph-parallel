#include <openacc.h>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void get_input(double *data) {
    double *row;
    row = new double [4];
    string line, word;
    
    fstream file("../data/xyz270.csv", ios::in);

    if(file.is_open()) {
        getline(file, line);
        int j = 0;
    	while(getline(file, line)) {
    	    stringstream str(line);
    
            int i = 0;
    	    while(getline(str, word, ',')) {
                row[i] = std::stod(word);
                i++;
            }
            i = 0;

            for (int k = 0; k < 4; k++)
                data[j * 4 + k] = row[k];
            j++;
    	}
    }
}
