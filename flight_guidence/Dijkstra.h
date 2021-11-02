#pragma once
#include "airlines.h"
#include "airports.h"
#include "planes.h"
#include "routes.h"
#include "airlineFlow.h"
#include "cs225/graph.h"

using std::vector;
using std::string;
using std::pair;

class Dijkstra {
    public:
        /**
         * Constructor of Dijkstra class
         * @param airlineFlow the airlineFlow need
        */
        Dijkstra(AirlineFlow& airlineFlow);

        /**
         * Use Dijkstra's Algorithm to find the shortest path between airports, returns a pair which the
         * first entry is the shortest distance (in kilometers) between airports, and the second entry is 
         * a vector of airport IDs thar this shortest path fly by.
         * @param source the ID of the source airport
         * @param dest the ID of the destination airport
         * @return a pair as described above
        */
        pair<int, vector<int>> shortestPath(int source, int dest);

        /**
         * Use Dijkstra's Algorithm to find the shortest path between airports, returns a pair which the
         * first entry is the shortest distance (in kilometers) between airports, and the second entry is 
         * a vector of airport IDs thar this shortest path fly by.
         * @param sourceIATA the IATA code of the source airport
         * @param destIATA the IATA code of the destination airport
         * @return a pair as described above
        */
        pair<int, vector<int>> shortestPath(string sourceIATA, string destIATA);
        
        /**
         * Use Dijkstra's Algorithm to find the shortest path between airports, returns a report of the
         * shortest path.
         * @param source the ID of the source airport
         * @param dest the ID of the destination airport
         * @return a report of the path
        */
        string getShortestPathReport(int source, int dest);

        /**
         * Use Dijkstra's Algorithm to find the shortest path between airports, returns a report of the
         * shortest path.
         * @param sourceIATA the IATA code of the source airport
         * @param destIATA the IATA code of the destination airport
         * @return a report of the path
        */
        string getShortestPathReport(string sourceIATA, string destIATA);

    private:
        /** Route graph */
        Graph* _routeGraph;

        /** Airports info */
        Airports* _airports;
};