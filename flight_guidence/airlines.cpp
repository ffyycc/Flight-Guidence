#include "airlines.h"
#include <fstream>  
#include <iostream>
#include <unordered_map>
#include "utils.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::unordered_map;
using utils::readEntry;

Airlines::Airlines(bool test) {
    _map.clear();
    string filein = test ? "testData/airlines.dat" : "data/airlines.dat";
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
        int id = std::stoi(in[0]);
        string name = in[1];
        string alias = in[2];
        string IATA = in[3];
        string ICAO = in[4];
        string callsign = in[5];
        string country = in[6];
        bool active = in[7] == "Y";
        AirlineNode* data = new AirlineNode(name, alias, IATA, ICAO, callsign, country, active);
        _map[id] = data;
    }
    infile.close();
}

Airlines::AirlineNode* Airlines::getAirlineByID(int id) {
    if (_map.find(id) != _map.end()) return _map[id];
    return nullptr;
}