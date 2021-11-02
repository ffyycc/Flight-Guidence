#pragma once
#include "airlines.h"
#include "airports.h"
#include "planes.h"
#include "routes.h"
#include "cs225/graph.h"
#include "dsets.h"
#include "utils.h"
#include <unordered_map>
#include <vector>
#include <random>

using std::unordered_map;
using std::vector;
using std::default_random_engine;

class AirlineFlow {
    public:
        /**
         * Initialization of the analysis
         */
        AirlineFlow(bool test);

        /**
         * Destructor
         */
        ~AirlineFlow();
        
        /**
         * Find all the routes ID that flies from source to desination
         * @param sourceAirportID the ID of the source airport
         * @param destAirportID the ID of the destination airport
         */
        vector<int> getAirlineBetweenAirports(int sourceAirportID, int destAirportID);

        /**
         * Find all the routes ID that flies from source to desination
         * @param sourceIATA the IATA of the source airport
         * @param destIATA the IATA of the destination airport
         */
        vector<int> getAirlineBetweenAirports(string sourceIATA, string destIATA);

        /**
         * Return the graph that containing all the routes, the graph cannot be modified
         * @returns the graph constructed
         */
        Graph* getRouteGraph() const;

        /** Returns the bfs of the graph given starting airport. If the airport ID is not specified and
         * bfs was done, return the result of last time, else randomly select an airport as starting
         * point
         * @param startAirportID the ID of the starting airport
         */
        vector<Vertex> bfs(int startAirportID = -1);

        /** Returns the dfs of the graph given starting airport. If the airport ID is not specified and
         * dfs was done, return the result of last time, else randomly select an airport as starting
         * point
         * @param startAirportID the ID of the starting airport
         */
        vector<Vertex> dfs(int startAirportID = -1);
        
        /**
         * Return the airport dataset
         * @returns airport dataset
         */
        Airports* getAirportDataset() const {
            return _airports;
        }

        /**
         * Return the airlines dataset
         * @returns airlines dataset
         */
        Airlines* getAirlineDataset() const {
            return _airlines;
        }

        /**
         * Generate a report about airlines fly between two given airports, outputing the 
         * airlines that operates this path
         * @param sourceAirportID the ID of the source airport
         * @param destAirportID the ID of the destination airport
         * @return a report of the path
        */
        string getAirlineBetweenAirportsReport(int sourceAirportID, int destAirportID);

        /**
         * Generate a report about airlines fly between two given airports, outputing the 
         * airlines that operates this path
         * @param sourceIATA the IATA code of the source airport
         * @param destIATA the IATA code of the destination airport
         * @return a report of the path
        */
        string getAirlineBetweenAirportsReport(string sourceIATA, string destIATA);


    private:
        /** All the airlines */
        Airlines* _airlines;
        
        /** All the airports */
        Airports* _airports;
        
        /** All the planes */
        Planes* _planes;
        
        /** All the routes */
        Routes* _routes;

        /**
         * A weighted directed graph using airport ID as vertices and using the number of
         * airlines fly the same route as the edge
         */
        Graph* _routeGraph;
        
        /**
         * An unordered map using concatenated string "airportIDSource" + "_" + "airportIDDestination"
         * as key and the vector that holds all the airline IDs as value
         */
        unordered_map<string, vector<int>> _edgeList;

        /** Stores the result of bfs */
        vector<Vertex> _bfsResult;

        /** Stores the starting point of bfs */
        string _bfsStartingAirportID = utils::STR_ERROR_AIRPORT_ID;

        /** Stores the result of dfs */
        vector<Vertex> _dfsResult;
        
        /** Stores the starting point of dfs */
        string _dfsStartingAirportID = utils::STR_ERROR_AIRPORT_ID;

        /** The disjoint set */
        DisjointSets<string> _d;

        /** random number generator */
        default_random_engine _rng;

};
