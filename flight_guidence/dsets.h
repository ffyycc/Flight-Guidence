#pragma once
#include <vector>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <iomanip>

using std::vector;
using std::unordered_map;
using std::cout;
using std::endl;
using std::left;
using std::setw;
using std::to_string;
using std::sort;
using std::pair;
using std::stringstream;

template <typename T>
class DisjointSets {
    public:
        /**
         * Creates one unconnected root node at the end of the vector.
         * @param ele the element needed to be added to the disjoint set
         */
        void addElement(T ele);

        /**
         * Find the representative number of the set where elem belongs, compress the size along 
         * with find
         * @param a	First element to union
         * @param b	Second element to union
         * @returns whether the two elements are in one set
         */
        bool inSameSet(T a, T b);
        
        /**
         * Union two sets, union-by-size.
         * @param a	First element to union
         * @param b	Second element to union
         */
        void setUnion(T a, T b);
        
        /**
         * Return the number of nodes in the up-tree containing the element.
         * @returns number of nodes in the up-tree containing the element
         */
        int size(int elem);

        /**
         * Get the status report of the current disjoint set
         * @param compress compress all the paths before printing
         * @param mapping output mapping information
         */
        vector<vector<T>> getStatusReport(bool compress = false, bool mapping = false) {
            if (_statusReportResult.empty()) {
                _statusReportConfig = pair<bool, bool>(compress, mapping);
                _outMsg.clear();
                _statusReportResult.clear();
                _getStatusReport(compress, mapping);
            } else {
                if (_statusReportConfig == pair<bool, bool>(compress, mapping)) 
                    return _statusReportResult;
                _outMsg.clear();
                _statusReportResult.clear();
                _getStatusReport(compress, mapping);
            }
            return _statusReportResult;
        }

        /**
         * Print out the status report of the current disjoint set, function getStatusReport must
         * be called first to generate meaningful output.
         */
        void printStatusReport() {
            cout << _outMsg.str() << endl;
        };


    private:
        /**
         * Find the representative number of the set where elem belongs, compress the size along 
         * with find
         * @param elem the element wanted to be found
         * @returns the index of the root of the up-tree in which the parameter element resides
         */
        int _find(int elem);

        /* Internal storage */
        vector<int> _storage;

        /* Interface coupling with input */
        unordered_map<T, int> _innerMapping;
        vector<T> _outerMapping;

        /* Status report */
        stringstream _outMsg;
        pair<bool, bool> _statusReportConfig;
        vector<vector<T>> _statusReportResult;
        
        /**
         * Helpper function to get the status report of the current disjoint set
         * @param compress compress all the paths before printing
         * @param mapping output mapping information
         */
        void _getStatusReport(bool compress, bool mapping) {
            _outMsg << "#-------- Disjoint Set Status Report - ";
            if (compress) {
                _outMsg << "Compressed" << endl;
                for (int i = 0; i < (int) _storage.size(); i++) {
                    _find(i);
                }
            } else {
                _outMsg << "Not Compressed" << endl;
            }
            if (_storage.size() == 0) {
                _outMsg << "Disjoint Set is Empty, aborting..." << endl;
                return;
            }
            if (mapping) {
                _outMsg << "Mapping" << endl << setw(12) << "Element" << "Idx" << endl; 
                for (auto it = _innerMapping.begin(); it != _innerMapping.end(); ++it) {
                    auto pair = *it;
                    _outMsg << left << setw(6) << pair.first << "->    " << pair.second << endl;
                }
            }
            vector<std::pair<int,int>> idxToCount;
            _outMsg << "Storage space" << endl << left << setw(12) << "Index" << "Root" << endl;
            size_t lastRoot = 0;
            int lastHeight = _storage[0];
            for (size_t i = 0; i < _storage.size(); i++) {
                if (_storage[i] != lastHeight) {
                    if (i - 1 != lastRoot)
                        _outMsg << left << setw(12) << to_string(lastRoot) + "-" + to_string(i - 1) << lastHeight << endl;
                    else
                        _outMsg << left << setw(12) << i - 1 << lastHeight << endl;
                    lastRoot = i;
                    lastHeight = _storage[i];
                }
                if (_storage[i] < 0)
                    idxToCount.push_back(std::pair<int, int>(i, -_storage[i]));
            }
            if (_storage.size() - 1 != lastRoot)
                _outMsg << left << setw(12) << to_string(lastRoot) + "-" + to_string(_storage.size() - 1) << lastHeight << endl;
            else
                _outMsg << left << setw(12) << _storage.size() - 1 << lastHeight << endl;
            sort(idxToCount.begin(), idxToCount.end(), [](auto &left, auto &right) {
                return left.second > right.second;
            });
            unordered_map<int, int> idxToReturnIdx;
            _outMsg << "Nodes" << endl << left << setw(12) << "Idx" << "Count" << endl;
            int i = 0;
            _statusReportResult.clear();
            _statusReportResult.reserve(idxToCount.size());
            for (auto it = idxToCount.begin(); it != idxToCount.end(); ++it) {
                auto pair = *it;
                _statusReportResult.push_back(vector<T>());
                idxToReturnIdx[pair.first] = i++;
                _outMsg << left << setw(6) << pair.first << "->    " << pair.second << endl;
            }
            if (compress) {
                for (int i = 0; i < (int) _storage.size(); i++) {
                    if (_storage[i] < 0) {
                        _statusReportResult[idxToReturnIdx[i]].push_back(_outerMapping[i]);
                    } else {
                        _statusReportResult[idxToReturnIdx[_storage[i]]].push_back(_outerMapping[i]);
                    }
                }
                for (auto it = _statusReportResult.begin(); it != _statusReportResult.end(); ++it) {
                    vector<T>& list = *it;
                    sort(list.begin(), list.end(), [](auto &left, auto &right) {
                        return std::stoi(left) < std::stoi(right);
                    });
                }
            }
            _outMsg << "#-------- End Disjoint Set Status Report" << endl;
        };
};

#include "dsets.hpp"
