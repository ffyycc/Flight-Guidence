#include "pathDrawer.h"
#include "util.h"
#include <iostream>
#include <assert.h>

using std::pair;
using std::string;
using std::unordered_map;
using std::stoi;
using std::to_string;
using utils::split;

PathDrawer::PathDrawer(Airports* airports) : _canvas(new PNG()) {
    _canvas->readFromFile("data/map-2048.png");
    _center = pair<int, int>((int) _canvas->width() / 2, (int) _canvas->height() / 2);
    _pixelPerDegree = pair<double, double>(_canvas->width() / 360.0, _canvas->height() / 180.0);
    this->_airports = airports;
}

void PathDrawer::addPath(vector<Vertex> list, const HSLAPixel& renderPixel) {
    assert(list.size() >= 2);
    Vertex from = list[0];
    for (size_t i = 1; i < list.size(); i++) {
        Vertex to = list[i];
        addPath(from, to, renderPixel);
        from = to;
    }
}

void PathDrawer::addPath(vector<int> list, const HSLAPixel& renderPixel) {
    assert(list.size() >= 2);
    Vertex from = to_string(list[0]);
    for (size_t i = 1; i < list.size(); i++) {
        Vertex to = to_string(list[i]);
        addPath(from, to, renderPixel);
        from = to;
    }
}

void PathDrawer::addPath(Vertex from, Vertex to, const HSLAPixel& renderPixel) {
    string key = from + "_" + to;
    _pathList[key] = renderPixel;
}

void PathDrawer::addPath(int from, int to, const HSLAPixel& renderPixel) {
    string key = to_string(from) + "_" + to_string(to);
    _pathList[key] = renderPixel;
}

void PathDrawer::removePath(vector<Vertex> list) {
    assert(list.size() >= 2);
    Vertex from = list[0];
    for (size_t i = 1; i < list.size(); i++) {
        Vertex to = list[i];
        removePath(from, to);
        from = to;
    }
}

void PathDrawer::removePath(vector<int> list) {
    assert(list.size() >= 2);
    Vertex from = to_string(list[0]);
    for (size_t i = 1; i < list.size(); i++) {
        Vertex to = to_string(list[i]);
        removePath(from, to);
        from = to;
    }
}

void PathDrawer::removePath(Vertex from, Vertex to) {
    string key = from + "_" + to;
    if (_pathList.count(key))
        _pathList.erase(key);
}

void PathDrawer::removePath(int from, int to) {
    string key = to_string(from) + "_" + to_string(to);
    if (_pathList.count(key))
        _pathList.erase(key);
}


PNG* PathDrawer::renderPath() {
    PNG* res = new PNG(*_canvas);
    for (auto it = _pathList.begin(); it != _pathList.end(); ++it) {
        vector<string> s = split(it->first, '_'); 
        HSLAPixel& p = it->second;
        int source = stoi(s[0]);
        int destination = stoi(s[1]);
        double sourceLatitude = _airports->getAirportByID(source)->latit;
        double sourceLongitude = _airports->getAirportByID(source)->longit;
        int x1 = (int) sourceLongitude * _pixelPerDegree.first + _center.first;
        int y1 = (int) -sourceLatitude * _pixelPerDegree.second + _center.second;
        double destLatitude = _airports->getAirportByID(destination)->latit;
        double destLongitude = _airports->getAirportByID(destination)->longit;
        pair<int, int> destCoordinate;
        int x2 = (int) destLongitude * _pixelPerDegree.first + _center.first;
        int y2 = (int) -destLatitude * _pixelPerDegree.second + _center.second;
        _drawLine(res, x1, y1, x2, y2, p);
    }
    return res;
}

void PathDrawer::renderPath(string fileName) {
    PNG* res = renderPath();
    res->writeToFile(fileName);
    cout << "Saving to file " << fileName << endl;
}


void PathDrawer::_drawLine(PNG* canvas, int x1, int y1, int x2, int y2, HSLAPixel& renderPixel) {
    if (x1 == x2) {
        if (y1 == y2) 
            return;
        if (y1 > y2) 
            std::swap(y1, y2);
        int x = x1;
        for (int y = y1; y <= y2; y++) {
            HSLAPixel& pc = canvas->getPixel(x, y);
            HSLAPixel& pl = canvas->getPixel(x - 1, y);
            HSLAPixel& pr = canvas->getPixel(x + 1, y);
            HSLAPixel& pu = canvas->getPixel(x, y - 1);
            HSLAPixel& pd = canvas->getPixel(x, y + 1);
            pc = renderPixel;
            pl = renderPixel;
            pr = renderPixel;
            pu = renderPixel;
            pd = renderPixel;
        }
        return;
    }
    if (x1 > x2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }
    double slope = double(y2 - y1) / double(x2 - x1);
    for (int x = x1; x <= x2; x++) {
        int y = (int) (y1 + (x - x1) * slope);
            HSLAPixel& pc = canvas->getPixel(x, y);
            HSLAPixel& pl = canvas->getPixel(x - 1, y);
            HSLAPixel& pr = canvas->getPixel(x + 1, y);
            HSLAPixel& pu = canvas->getPixel(x, y - 1);
            HSLAPixel& pd = canvas->getPixel(x, y + 1);
            pc = renderPixel;
            pl = renderPixel;
            pr = renderPixel;
            pu = renderPixel;
            pd = renderPixel;
    }
    return;
}
