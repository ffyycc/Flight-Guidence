#pragma once
#include "airlines.h"
#include "airports.h"
#include "planes.h"
#include "routes.h"
#include "cs225/graph.h"
#include "utils.h"
#include "airlineFlow.h"
#include <unordered_map>

using utils::Matrix;

/**
 * Pagerank class, use the method of Markov Chain
 */
class Pagerank {
    public:
        /** 
         * Constructs pageRank
         * @param g the pointer to graph
         * @param loadType load label with 0, load weight with 1
         */
        Pagerank(AirlineFlow& _airlineFlow, bool loadType);

        /**
         * Return the matrix used for PageRank
         * @returns matrix used for PageRank
         */
        Matrix* returnMatrix() {
            return _graphMat;
        }

        /**
         * Do pagerank and return a ranked list, ordered in decreasing popular order, the return 
         * vector contains pairs which first entry is the airportID, and second entry the airport
         * name
         * @param _airlineFlow airlineflow pointer to get airport
         * @param alpha used in inital transition matrix generation
         * @returns vector specified above
         */
        vector<pair<int, string>> pageRank(double alpha);

        /**
         * Generate a report about PageRank, outputing the most populat airports in the given airlineFlow
         * @param top the number of most popular airports included in the report
         */
        string getPageRankReport(int top = 10);
        
    private:
        /**
         * Load the matrix with edge label (number of airlines that fly in this route) as the weight
         */
        void _loadLabelRank();

        /**
         * Load the matrix with edge weight (distance between two airports) as the weight
         */
        void _loadWeightRank();

        /** Graph used when generating matrix */
        const Graph* _graph;

        /** Graph used when generating matrix */
        Airports* _airportsData;

        //AirlineFlow _airlineFlow;

        /** Generated matrix */
        Matrix* _graphMat;

        /** Mapping from vertex to its associated index in the matrix */
        unordered_map<Vertex, int> _vertexToIdx;

        /** PageRank result */
        vector<pair<int, string>> _rankingResult;

        /** Alpha used in last PageRank operation */
        double _lastAlpha;

};