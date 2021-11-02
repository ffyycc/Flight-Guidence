#include "pagerank.h"
#include "utils.h"
#include <algorithm>
#include <sstream>

using std::stoi;
using std::pair;
using std::sort;
using std::vector;
using std::stringstream;
using utils::matrixSub;
using utils::matrixMul;
using utils::doubleEqual;

Pagerank::Pagerank(AirlineFlow& _airlineFlow, bool loadType) {
    _graph = _airlineFlow.getRouteGraph();
    _airportsData = _airlineFlow.getAirportDataset();
    int matSize = _graph->getVertices().size();
    _graphMat = new Matrix(matSize, matSize, true);
    vector<Vertex> tempVertex = _graph->getVertices();
    for (size_t i = 0; i < tempVertex.size(); i++) {
        _vertexToIdx[tempVertex[i]] = i;
    }
    if (loadType) 
        _loadWeightRank();
    else
        _loadLabelRank();
}

void Pagerank::_loadLabelRank() {
    vector<Edge> tempEdges = _graph->getEdges();
    for (size_t i = 0; i < tempEdges.size(); i++) {
        Edge e = tempEdges[i];
        _graphMat->setEntry(_vertexToIdx[e.source], _vertexToIdx[e.dest], stoi(e.getLabel()));
    }
}

void Pagerank::_loadWeightRank() {
    vector<Edge> tempEdges = _graph->getEdges();
    for (size_t i = 0; i < tempEdges.size(); i++) {
        Edge e = tempEdges[i];
        _graphMat->setEntry(_vertexToIdx[e.source], _vertexToIdx[e.dest], e.getWeight());
    }

}

vector<pair<int, string>> Pagerank::pageRank(double alpha) {
    if (doubleEqual(alpha, _lastAlpha))
        return _rankingResult;
    _lastAlpha = alpha;
    Matrix* mat = returnMatrix();
    mat->convertToTransitionMatrix(alpha);
    Matrix * temp = Matrix::initialVector(mat->numRows());
    Matrix* lastMatrix = new Matrix(temp->shape());
    int runTime = 0;
    while(matrixSub(temp, lastMatrix)->norm() > powl(10, -8)) {
        lastMatrix = temp;
        temp = matrixMul(mat, temp);
        temp = temp->normalize();
        runTime++;
    }
    vector<long double> res = temp->toVector();
    vector<pair<int, long double>> groupedVec;
    for (int i = 0; i < (int) res.size(); i++) {
        groupedVec.push_back(pair<int, long double>(stoi(_graph->getVertices().at(i)), res[i]));
    }
    sort(groupedVec.begin(), groupedVec.end(), [](auto &left, auto &right) {
        return left.second > right.second;
    });
    _rankingResult.clear();
    for (auto it = groupedVec.begin(); it != groupedVec.end(); ++it) {
        _rankingResult.push_back(pair<int, string>(it->first, _airportsData->getAirportByID(it->first)->name));
    }
    return _rankingResult;
}

string Pagerank::getPageRankReport(int top) {
    stringstream ss;
    ss << "#-------- PageRank Report" << endl;
    ss << "Most Popular Airports" << endl;
    int ranking = 1;
    for (auto it = _rankingResult.begin(); it != _rankingResult.end(); ++it) {
        if (ranking > top) break;
        ss << ranking++ << ".\t" << it->second << endl;
    }
    ss << "#-------- End PageRank Report" << endl;
    return ss.str();
}