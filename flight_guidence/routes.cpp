#include "routes.h"
#include <fstream>  
#include <unordered_map>
#include "utils.h"
#include <iostream>

using std::cout;
using std::endl;
using std::ifstream;
using std::unordered_map;
using std::stoi;
using std::to_string;
using utils::readEntry;

Routes::Routes(bool test) {
    _vector.clear();
    string filein = test ? "testData/routes.dat" : "data/routes.dat";
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
        string airline = in[0];
        /* if there is no airline of that name, record the airline number as -1 */
        int airlineID = in[1].size() == 0 ? -1 : stoi(in[1]);
        string airport1 = in[2];
        /* potential wrong data */
        int airportID1 = in[3].size() == 0 ? utils::ERROR_AIRPORT_ID : stoi(in[3]);
        string airport2 = in[4];
        int airportID2 = in[5].size() == 0 ? utils::ERROR_AIRPORT_ID : stoi(in[5]);
        bool codeshare = in[6] == "Y";
        int stops = stoi(in[7]);
        string equipment = in[8];
        RoutesNode* data = new RoutesNode(airline, airlineID, airport1, airportID1, airport2, airportID2,
            codeshare, stops, equipment);
        _vector.push_back(data);
    }
    infile.close();
}
