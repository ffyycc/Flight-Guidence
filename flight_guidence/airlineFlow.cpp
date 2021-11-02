#include "airlineFlow.h"
#include <queue>
#include <stack>
#include <sstream>

using std::queue;
using std::stack;
using std::stoi;
using std::stringstream;
using utils::getDistance;

AirlineFlow::AirlineFlow(bool test) : _airlines(new Airlines(test)), _airports(new Airports(test)), 
        _planes(new Planes(test)), _routes(new Routes(test)), _routeGraph(new Graph(true, true)) {
    // Initial rng engine
    _rng = default_random_engine(time(nullptr));

    // add all the routes to the graph and construct edge list 
    for (auto it = _routes->begin(); it != _routes->end(); ++it) {
        int id = (*it)->airlineID;
        int source = (*it)->airportID1;
        // prevent possible error in the dataset 
        if (source == utils::ERROR_AIRPORT_ID) {
            source = _airports->getAirportIDByIATA((*it)->airport1);
            if (source == utils::ERROR_AIRPORT_ID) continue;
        }
        int destination = (*it)->airportID2;
        // prevent possible error in the dataset 
        if (destination == utils::ERROR_AIRPORT_ID) {
            destination = _airports->getAirportIDByIATA((*it)->airport2);
            if (destination == utils::ERROR_AIRPORT_ID) continue;
        }
        string strSource = to_string(source);
        string strDestination = to_string(destination);
        if (!_routeGraph->vertexExists(strSource)) {
            _routeGraph->insertVertex(strSource);
            _d.addElement(strSource);
        } 
        if (!_routeGraph->vertexExists(strDestination)) {
            _routeGraph->insertVertex(strDestination);
            _d.addElement(strDestination);
        } 
        string label = to_string(source) + "_" + to_string(destination);
        auto edge = _edgeList.find(label);
        if (edge != _edgeList.end()) {
            // the edge already exists 
            edge->second.push_back(id);
            int num = stoi(_routeGraph->getEdge(to_string(source), to_string(destination)).getLabel());
            _routeGraph->setEdgeLabel(to_string(source), to_string(destination), to_string(num + 1));
        } else {
            // the edge does not exist 
            auto sourceAirport = _airports->getAirportByID(source);
            double sourceLatitude = sourceAirport->latit;
            double sourceLongitude = sourceAirport->longit;
            auto destAirport = _airports->getAirportByID(destination);
            double destLatitude = destAirport->latit;
            double destLongitude = destAirport->longit;
            double distance = getDistance(sourceLatitude, sourceLongitude, destLatitude, destLongitude);
            _edgeList[label].push_back(id);
            _routeGraph->insertEdge(to_string(source), to_string(destination));
            _routeGraph->setEdgeLabel(to_string(source), to_string(destination), "1");
            _routeGraph->setEdgeWeight(to_string(source), to_string(destination), distance);
            _d.setUnion(strSource, strDestination);
        }
    }
    auto parts = _d.getStatusReport(true);
    // _d.printStatusReport();
    // remove inactive airports
    vector<Vertex> vList = _routeGraph->getVertices();
    //cout << vList.size() << endl;
}

AirlineFlow::~AirlineFlow() {
    delete _airlines;
    delete _airports;
    delete _planes;
    delete _routes;
}

vector<int> AirlineFlow::getAirlineBetweenAirports(int sourceAirportID, int destAirportID) {
    string label = to_string(sourceAirportID) + "_" + to_string(destAirportID);
    auto res = _edgeList.find(label);
    if (res == _edgeList.end()) return vector<int>();
    return res->second;
}

vector<int> AirlineFlow::getAirlineBetweenAirports(string sourceIATA, string destIATA) {
    int sourceAirportID = _airports->getAirportIDByIATA(sourceIATA);
    int destAirportID = _airports->getAirportIDByIATA(destIATA);
    string label = to_string(sourceAirportID) + "_" + to_string(destAirportID);
    auto res = _edgeList.find(label);
    if (res == _edgeList.end()) return vector<int>();
    return res->second;
}

Graph* AirlineFlow::getRouteGraph() const {
    return _routeGraph;
}

vector<Vertex> AirlineFlow::bfs(int startAirportID) {
    if (startAirportID == utils::ERROR_AIRPORT_ID) {
        cout << "In function dfs, airport ID is not vaild, aborting..." << endl;
        return _bfsResult;
    }
    string strStartID = to_string(startAirportID);
    if (startAirportID == -1 && _bfsStartingAirportID == utils::STR_ERROR_AIRPORT_ID) {
        // none is initialized, random select one
        auto vList = _routeGraph->getVertices();
        _bfsStartingAirportID = vList[_rng() % vList.size()];
    } else if ((startAirportID == -1 && _bfsStartingAirportID != utils::STR_ERROR_AIRPORT_ID) 
            || strStartID == _bfsStartingAirportID)
        // startAirportID is not changed and _bfsStartingAirportID is properly initialized, or they are equal 
        return _bfsResult;
    else {
        // startAirportID is different from _bfsStartingAirportID
        if (!_routeGraph->vertexExists(strStartID)) {
            cout << "In function BFS, specified vertex " << strStartID << " does not exist, aborting..." << endl;
            return vector<Vertex>();
        }
        _bfsStartingAirportID = strStartID;
    }
    _bfsResult.clear();
    unordered_map<Vertex, int> visited;
    queue<Vertex> q;
    visited[_bfsStartingAirportID] = 0;
    q.push(_bfsStartingAirportID);
    while (!q.empty()) {
        Vertex curr = q.front();
        int currHeight = visited[curr];
        q.pop();
        _bfsResult.push_back(curr);
        vector<Vertex> l = _routeGraph->getAdjacent(curr);
        for (auto it = l.begin(); it != l.end(); ++it) {
            if (visited.count(*it)) continue;
            visited[*it] = currHeight + 1;
            q.push(*it);
        }
    }
    return _bfsResult;
}

vector<Vertex> AirlineFlow::dfs(int startAirportID) {
    if (startAirportID == utils::ERROR_AIRPORT_ID) {
        cout << "In function dfs, airport ID is not vaild, aborting..." << endl;
        return _dfsResult;
    }
    string strStartID = to_string(startAirportID);
    if (startAirportID == -1 && _dfsStartingAirportID == utils::STR_ERROR_AIRPORT_ID) {
        // none is initialized, random select one
        auto vList = _routeGraph->getVertices();
        _dfsStartingAirportID = vList[_rng() % vList.size()];
    } else if ((startAirportID == -1 && _dfsStartingAirportID != utils::STR_ERROR_AIRPORT_ID) 
            || strStartID == _dfsStartingAirportID)
        // startAirportID is not changed and _dfsStartingAirportID is properly initialized, or they are equal 
        return _dfsResult;
    else {
        // startAirportID is different from _dfsStartingAirportID
        if (!_routeGraph->vertexExists(strStartID)) {
            cout << "In function DFS, specified vertex " << strStartID << " does not exist, aborting..." << endl;
            return vector<Vertex>();
        }
        _dfsStartingAirportID = strStartID;
    }
    
    _dfsResult.clear();
    unordered_map<Vertex, int> visited;
    stack<Vertex> s;
    visited[_dfsStartingAirportID] = 0;
    s.push(_dfsStartingAirportID);
    while (!s.empty()) {
        Vertex curr = s.top();
        int currHeight = visited[curr];
        s.pop();
        _dfsResult.push_back(curr);
        vector<Vertex> l = _routeGraph->getAdjacent(curr);
        for (auto it = l.begin(); it != l.end(); ++it) {
            if (visited.count(*it)) continue;
            visited[*it] = currHeight + 1;
            s.push(*it);
        }
    }
    return _dfsResult;
}


string AirlineFlow::getAirlineBetweenAirportsReport(int sourceAirportID, int destAirportID) {
    stringstream ss;
    vector<int> a = getAirlineBetweenAirports(sourceAirportID, destAirportID);
    ss << "#-------- AirlineFlow Report" << endl;
    ss << "From: " << _airports->getAirportByID(sourceAirportID)->name << endl;
    ss << "To:   " << _airports->getAirportByID(destAirportID)->name << endl;
    if (a.size() != 0) {
        ss << "There are total " << a.size() << " airline(s) that operates this path" << endl;
        int num = 1;
        for (int i : a) {
            ss << num++ << ".\t" << _airlines->getAirlineByID(i)->name << endl;
        }
    } else {
        ss << "There is no airline operate this path" << endl;
    }
    ss << "#-------- End AirlineFlow Report" << endl;
    return ss.str();
}

string AirlineFlow::getAirlineBetweenAirportsReport(string sourceIATA, string destIATA) {
    int sourceAirportID = _airports->getAirportIDByIATA(sourceIATA);
    int destAirportID = _airports->getAirportIDByIATA(destIATA);
    return getAirlineBetweenAirportsReport(sourceAirportID, destAirportID);
}