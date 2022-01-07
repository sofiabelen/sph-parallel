#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<vector<double> > get_input(string fname) {
    vector<vector<double> > data;
    vector<double> row;
    string line, word;
    
    fstream file(fname, ios::in);

    if(file.is_open()) {
        getline(file, line);
    	while(getline(file, line)) {
    	    row.clear();
    
    	    stringstream str(line);
    
    	    while(getline(str, word, ','))
                row.push_back(stod(word));
    	    data.push_back(row);
    	}
    }
    return data;
}
