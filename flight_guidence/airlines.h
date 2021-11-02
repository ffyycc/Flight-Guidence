#pragma once
#include <vector>
#include <string>
#include <unordered_map>

using std::vector;
using std::string;
using std::unordered_map;

// for airlines.dat
class Airlines {
    public:
        /**
         * Interal storage element for all entries in airlines.dat
         */
        class AirlineNode {
            public:
                /** 
                 * Constructs one storage element
                 * @param name name of the airline
                 * @param alias alias of the airline
                 * @param IATA IATA code of the airline
                 * @param ICAO ICAO code of the airline
                 * @param callsign callsign of the airline
                 * @param country country where the airline belongs
                 * @param active whether the airline is active
                 */
                AirlineNode(string name, string alias, string IATA, string ICAO, 
                        string callsign, string country, bool active) : 
                    name(name), alias(alias), IATA(IATA), ICAO(ICAO), callsign(callsign), country(country), 
                    active(active) {};

                /* All the data should be constant */
                const string name;
                const string alias;
                const string IATA;
                const string ICAO;
                const string callsign;
                const string country;
                const bool active;
        };

        /**
         * Initialzation of all the airlines
         * @param test whether read the actural files or the test files
         */
        Airlines(bool test);

        /** 
         * Get the internal storage element by the airline id specified
         * @param id the ID of the airline
         */
        AirlineNode* getAirlineByID(int id);
        
        /**
         * Begin iterator of all the airlines, used when traversing through the dataset to construct a graph
         * @returns const begin iterator
         */
        unordered_map<int, Airlines::AirlineNode*>::const_iterator begin() const { 
            return _map.begin(); 
        };

        /**
         * End iterator of all the airlines, used when traversing through the dataset to construct a graph
         * @returns const end iterator
         */
        unordered_map<int, Airlines::AirlineNode*>::const_iterator end() const { 
            return _map.end(); 
        };

    private:
        /* Internal storage that holds all the airline infomation */
        unordered_map<int, AirlineNode*> _map;
};


