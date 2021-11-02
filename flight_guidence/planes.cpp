#include <iostream>
#include "planes.h"
#include <fstream>  
#include <unordered_map>
#include "utils.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::unordered_map;
using utils::readEntry;

Planes::Planes(bool test) {
    _map.clear();
    string filein = test ? "testData/planes.dat" : "data/planes.dat";
    ifstream infile(filein);  
    string line;
    // handle error
    if (!infile.is_open()) {
        cout << "can not open the file" << endl;
        exit(1);
    }
    // loop through dat by lines
    while(getline(infile,line)) {  
        vector<string> in = readEntry(line); 
        string name = in[0];
        string IATA = in[1];
        string ICAO = in[2];
        PlanesNode* data = new PlanesNode(name, ICAO);
        _map[IATA] = data;
    }
    infile.close();
}

Planes::PlanesNode* Planes::getPlaneByIATA(string IATA) {
    return _map[IATA];
}
