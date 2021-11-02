#include "Dijkstra.h"
#include "util.h"
#include "cs225/graph.h"
#include <algorithm>
#include <limits>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <assert.h>

using std::unordered_map;
using std::vector;
using std::numeric_limits;
using std::stoi;
using std::to_string;
using std::stringstream;

Dijkstra::Dijkstra(AirlineFlow& airlineFlow) : 
        _routeGraph(airlineFlow.getRouteGraph()), _airports(airlineFlow.getAirportDataset()) {};

pair<int, vector<int>> Dijkstra::shortestPath(string sourceIATA, string destIATA) {
    int source = _airports->getAirportIDByIATA(sourceIATA);
    int dest = _airports->getAirportIDByIATA(destIATA);
    assert(source != utils::ERROR_AIRPORT_ID && dest != utils::ERROR_AIRPORT_ID);
    return shortestPath(source, dest);
}

pair<int, vector<int>> Dijkstra::shortestPath(int source, int dest) {
    assert(_routeGraph->vertexExists(to_string(source)));
    assert(_routeGraph->vertexExists(to_string(dest)));
    unordered_map<int, int> dist;       // a map to correspond each vertex to its dist from source
    unordered_map<int, int> previous;   // maps current vertex -> its previous vetex
    unordered_map<int, bool> visited;
    vector<int> pq;         // the priority queue
    vector<int> path;       // the vector used to store the airportIDs along the shortest path
    vector<string> path_s;  //the vector used to store the airport names along the shortest path
    int INF = numeric_limits<int>::max();
    auto comparator = [&] (int first, int sec) { return dist[first] > dist[sec]; };

    // make_heap(pq.begin(), pq.end(), comparator);
    // loop through all the vertices to initialize pq and dist
    for (auto & vertex : _routeGraph->getVertices()) {
        int v = stoi(vertex);
        if (v == source) {
            dist[v] = 0;
        } else {
            dist[v] = INF;
            visited[v] = false;
        }
        pq.push_back(v);
        push_heap(pq.begin(), pq.end(), comparator);
    }

    //while the priority queue is not empty
    while (!pq.empty()) {
        pop_heap(pq.begin(), pq.end(), comparator);
        int min = pq.back();
        pq.pop_back();
        Vertex m = to_string(min);
        visited[min] = true;
        // once we reach the dest, push all the values to path
        if (min == dest) {
            while(previous.find(min) != previous.end()) {
                path.push_back(min);
                min = previous[min];
            }

            break;
        }

        if (dist[min] == INF) {
            break;
        }

        //loop through all the neighbours of the current min
        for (auto & neighbour : _routeGraph->getAdjacent(m)) {
            int cost = _routeGraph->getEdgeWeight(m, neighbour);
            if (!visited[stoi(neighbour)] && _routeGraph->edgeExists(m, neighbour)
                 && dist[min] + cost < dist[stoi(neighbour)]) {
                //update neighbour's distances
                dist[stoi(neighbour)] = dist[min] + cost;
                previous[stoi(neighbour)] = min;
                make_heap(pq.begin(), pq.end(), comparator);
            }
        }
    }

    //reverse path to get the correct direction
    reverse(path.begin(), path.end());

    pair<int, vector<int>> to_return;
    to_return.second.push_back(source);
    for (int id : path) {
        to_return.second.push_back(id);
    }
    to_return.first = dist[dest];
    return to_return;
}

string Dijkstra::getShortestPathReport(string sourceIATA, string destIATA) {
    int source = _airports->getAirportIDByIATA(sourceIATA);
    int dest = _airports->getAirportIDByIATA(destIATA);
    assert(source != utils::ERROR_AIRPORT_ID && dest != utils::ERROR_AIRPORT_ID);
    return getShortestPathReport(source, dest);
}

string Dijkstra::getShortestPathReport(int source, int dest) {
    stringstream ss;
    ss << "#-------- Dijkstra Report" << endl;
    ss << "From: " << _airports->getAirportByID(source)->name << endl;
    ss << "To:   " << _airports->getAirportByID(dest)->name << "\nPassing:\n";
    pair<int, vector<int>> res = shortestPath(source, dest);
    int idx = 1;
    for (int id : res.second) {
        ss << idx++ << ".\t" << _airports->getAirportByID(id)->name << endl;
    }
    ss << "The shortest path distance is " << res.first  << " kilometers.\n";
    ss << "#-------- End Dijkstra Report" << endl;
    return ss.str();
}
