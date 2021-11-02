#pragma once
#include <vector>
#include <string>

using std::vector;
using std::string;

// for routes.dat
class Routes {
    public:
        /**
         * Interal storage element for all entries in routes.dat
         */
        class RoutesNode {
            public:
                /** 
                 * Constructs one storage element
                 * @param airline 2 letter IATA or 3 letter ICAO code of the airline
                 * @param airlineID airline ID, corresponding to airline.dat
                 * @param airport1 source airport, 3-letter(IATA) or 4-letter(ICAO)
                 * @param airportID1 unique OpenFlights identifier for source airport, see airport.dat
                 * @param airport2 destination airport, 3-letter(IATA) or 4-letter(ICAO)
                 * @param airportID2 unique OpenFlights identifier for destination airport, see airport.dat
                 * @param codeshare "Y" if this flight is a codeshare(that is, not operated by airline but another carrier), empty otherwise
                 * @param stops Number of stops on this flight ("0" for direct)
                 * @param equipment 3-letter codes for plane type
                 */
                RoutesNode(string airline, int airlineID, string airport1, int airportID1, 
                        string airport2, int airportID2, bool codeshare, int stops, string equipment) : 
                    airline(airline), airlineID(airlineID), airport1(airport1), airportID1(airportID1), airport2(airport2),
                    airportID2(airportID2), codeshare(codeshare), stops(stops), equipment(equipment) {};

                /* All the data should be constant */
                const string airline;
                const int airlineID;
                const string airport1;
                const int airportID1;
                const string airport2;
                const int airportID2;
                const bool codeshare;
                const int stops;
                const string equipment;
        };

        /**
         * Initialzation of all the airlines
         * @param test whether read the actural files or the test files
         */
        Routes(bool test);

        /** 
         * Get the internal storage element by the airline id specified
         * @param id the ID of the airline
         */
        RoutesNode* getAirlineByID(int id);

        /**
         * Begin iterator of all the routes, used when traversing through the dataset to construct a graph
         * @returns const begin iterator
         */
        vector<RoutesNode*>::const_iterator begin() const { 
            return _vector.begin(); 
        };

        /**
         * End iterator of all the routes, used when traversing through the dataset to construct a graph
         * @returns const end iterator
         */
        vector<RoutesNode*>::const_iterator end() const { 
            return _vector.end(); 
        };

    private:
        /* Internal storage that holds all the routes infomation */
        vector<RoutesNode*> _vector;
};
