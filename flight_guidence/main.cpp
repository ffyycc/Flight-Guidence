#include <iostream>
#include <map>
#include <algorithm>
#include <fstream>
#include "airlines.h"
#include "airports.h"
#include "routes.h"
#include "planes.h"
#include "random"
#include "airlineFlow.h"
#include "cs225/graph.h"
#include "cs225/PNG.h"
#include "Dijkstra.h"
#include "pagerank.cpp"
#include "pathDrawer.cpp"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::pair;

int main() {

    AirlineFlow airlineFlow(false); // load graphs, true for test routes, false for actual routes
    Airports* airports = airlineFlow.getAirportDataset();
    Airlines* airlines = airlineFlow.getAirlineDataset();


    // test getEdgeWeight
    cout << airlineFlow.getRouteGraph()->getEdgeWeight("2965", "2990") << " km."  << endl;


    // test getAirline
    vector<int> airlinesRes = airlineFlow.getAirlineBetweenAirports("AER", "KZN");
    string airlinesReport = airlineFlow.getAirlineBetweenAirportsReport("AER", "KZN");
    cout << airlinesReport;


    // test shortest_path
    Dijkstra dijkstra(airlineFlow);
    string dijkstraReport = dijkstra.getShortestPathReport(2965, 2922);
    cout << dijkstraReport;
    
  
    // test PageRank
    Graph* g = airlineFlow.getRouteGraph();
    Pagerank* labelLoad = new Pagerank(airlineFlow, false);
    vector<pair<int, string>> pagerankRes = labelLoad->pageRank(0.85);
    string pageRankReport = labelLoad->getPageRankReport();
    cout << pageRankReport;


    // test path drawer
    PathDrawer pathDrawer(airlineFlow.getAirportDataset());
    pair<int, vector<int>> path = dijkstra.shortestPath(2965, 2922);
    pathDrawer.addPath(path.second);
    PNG* res = pathDrawer.renderPath();
    res->writeToFile("out.png");

    return 0;
}