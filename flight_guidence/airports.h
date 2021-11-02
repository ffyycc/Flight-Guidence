#pragma once
#include <vector>
#include <string>
#include <unordered_map>

using std::vector;
using std::string;
using std::unordered_map;

// for airports.dat
class Airports {
    public:
        /**
         * Interal storage element for all entries in airport.dat
         */
        class AirportNode {
            public:
                /** 
                 * Constructs one storage element
                 * @param name name of the airport
                 * @param city Main city served by airport
                 * @param country Country or territory where airport is located
                 * @param IATA 3-letter IATA code of the airline
                 * @param ICAO 4-letter ICAO code of the airline
                 * @param latit latitude
                 * @param longit longitude
                 * @param alt altitude in feet
                 * @param timeZone Hours offset from UTC
                 * @param DST Daylight savings time. One of E (Europe), A (US/Canada), S (South America),
                 * O (Australia), Z (New Zealand), N (None) or U (Unknown)
                 * @param tz Tz database timezone. Timezone in "tz" (Olson) format, eg. "America/Los_Angeles".
                 */
                AirportNode(string name, string city, string country, string IATA, string ICAO,
                    double latit, double longit, int alt, string timeZone, string DST,
                    string tz) : 
                    name(name), city(city), country(country), IATA(IATA), ICAO(ICAO), latit(latit),
                    longit(longit), alt(alt), timeZone(timeZone), DST(DST), tz(tz) {};

                /* All the data should be constant */
                const string name;
                const string city;
                const string country;
                const string IATA;
                const string ICAO;
                const double latit;
                const double longit;
                const int alt;
                const string timeZone;
                const string DST;
                const string tz;
        };

        /**
         * Initialzation of all the airports
         * @param test whether read the actural files or the test files
         */
        Airports(bool test);

        /** 
         * Get the internal storage element by the airport id specified
         * @param id the ID of the airport
         */
        AirportNode* getAirportByID(int id);

        /** 
         * Get the id corresponding to IATA code
         * @param IATA the IATA of the airport
         */
        int getAirportIDByIATA(string IATA);
        
        /**
         * Begin iterator of all the airports, used when traversing through the dataset to construct a graph
         * @returns const begin iterator
         */
        unordered_map<int, Airports::AirportNode*>::const_iterator begin() const { 
            return _map.begin(); 
        };

        /**
         * End iterator of all the airports, used when traversing through the dataset to construct a graph
         * @returns const end iterator
         */
        unordered_map<int, Airports::AirportNode*>::const_iterator end() const { 
            return _map.end(); 
        };

    private:
        /* Internal storage that holds all the airport infomation */
        unordered_map<int, AirportNode*> _map;
        unordered_map<string, int> _IATAToID;
};


