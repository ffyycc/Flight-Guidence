#include "utils.h"
#include <algorithm>
#include <iostream>
#include <assert.h>
#include <math.h>
#include <sstream>

using std::cout;
using std::stringstream;
using std::stringstream;

namespace utils {
    vector<string> readEntry(string &s) {
        string item;
        vector<string> elems;
        size_t idx = 0;
        while (idx < s.size()) {
            if (s[idx] == '\"') {
                idx++;
                while (s[idx] != '\"') {
                    item.push_back(s[idx++]);
                }
            } else {
                while (idx < s.size()) {
                    if (s[idx] == ',') break;
                    item.push_back(s[idx++]);
                }
                if (item == "\\N") elems.push_back("");
                else elems.push_back(item);
                item.clear();
            }
            idx++;
        }
        if (item == "\\N") elems.push_back("");
        else elems.push_back(item);
        return elems;
    }

    double getDistance(double latitude1, double longtitude1, double latitude2, double longtitude2) {
        /**
         * Change to Radian  
         * lat = latitude / 180 * pi 
         * long = longt / 180 *pi
         */
        double latiR1 = latitude1 / 180 * M_PI;
        double latiR2 = latitude2 / 180 * M_PI;
        double longR1 = longtitude1 / 180 * M_PI;
        double longR2 = longtitude2 / 180 * M_PI;

        double latiDiff = latiR2 - latiR1;
        double longDiff = longR2 - longR1;

        double part1 = pow(sin(latiDiff / 2), 2) + pow(sin(longDiff / 2), 2) * cos(latiR1) * cos(latiR2); 
        //6371 is the radian of earth in km
        return 2 * asin(sqrt(part1)) * 6371;
    }

    Matrix* Matrix::initialVector(int r) {
        long double** arr = new long double*[r];
        for (int i = 0; i < r; i++) {
            arr[i] = new long double[1];
            arr[i][0] = powl(r, -1);
        }
        Matrix* res = new Matrix(r, 1, arr);
        return res;
    }

    Matrix::Matrix(int r, int c, bool initialize) {
        _nRows = r;
        _nCols = c;
        _value = new long double*[_nRows];
        for (int i = 0; i < _nRows; i++) {
            _value[i] = new long double[_nCols];
            if (initialize) {
                for (int j = 0; j < _nCols; j++) {
                    _value[i][j] = 0;
                }
            }
        }
    }

    Matrix::Matrix(pair<int, int> shape, bool initialize) {
        _nRows = shape.first;
        _nCols = shape.second;
        _value = new long double*[_nRows];
        for (int i = 0; i < _nRows; i++) {
            _value[i] = new long double[_nCols];
            if (initialize) {
                for (int j = 0; j < _nCols; j++) {
                    _value[i][j] = 0;
                }
            }
        }
    }

    Matrix::Matrix(int rows, int cols, long double** value) {
        _nRows = rows;
        _nCols = cols;
        _value = value;
    }
    
    Matrix::~Matrix() {
        delete[] _value;
    }
    
    bool operator!=(const Matrix& lhs, const Matrix& rhs) {
        return !(lhs == rhs);
    }
    
    bool operator==(const Matrix& lhs, const Matrix& rhs) {
        if (lhs.shape() != rhs.shape()) return false;
        for (int i = 0; i < lhs.numRows(); i++)
            for (int j = 0; j < lhs.numCols(); j++)
                if (abs(lhs.getEntry(i, j) - rhs.getEntry(i, j)) > TOL)
                    return false;
        return true;
    }

    void Matrix::setEntry(int r, int c, long double entry) {
        _value[r][c] = entry;
    }

    long double Matrix::getEntry(int r, int c) const {
        return _value[r][c];
    }

    long double Matrix::norm() {
        assert(_nCols == 1);
        long double sum = 0;
        for (int r = 0; r < _nRows; r++) {
            sum += powl(_value[r][0], 2);
        }
        return powl(sum, 0.5);
    }

    Matrix* Matrix::normalize() {
        assert(_nCols == 1);
        long double n = this->norm();
        assert(n != 0);
        Matrix* res = new Matrix(this->shape(), false);
        for (int r = 0; r < _nRows; r++) {
            res->setEntry(r, 0, _value[r][0] / n);
        }
        return res;
    }

    Matrix* matrixMul(Matrix* mat1, Matrix* mat2) {
        assert(mat1->numCols() == mat2->numRows());
        int mat1Row = mat1->numRows();
        int mat1Col = mat1->numCols();
        int mat2Col = mat2->numCols();
        Matrix* toReturn = new Matrix(mat1Row, mat2Col, false);
        for (int i = 0; i < mat1Row; i++) {
            for (int j = 0; j < mat2Col; j++) {
                long double sum = 0;
                for (int k = 0; k < mat1Col; k ++) {
                    sum += mat1->getEntry(i, k) * mat2->getEntry(k, j);
                }
                toReturn->setEntry(i, j, sum);
            }
        }
        return toReturn;
    }

    Matrix* matrixAdd(Matrix* mat1, Matrix* mat2) {
        assert(mat1->shape() == mat2->shape());
        int r = mat1->numRows();
        int c = mat1->numCols();
        Matrix* toReturn = new Matrix(r, c, false);
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                toReturn->setEntry(i, j, mat1->getEntry(i, j) + mat2->getEntry(i, j));
            }
        }
        return toReturn;
    }
    
    Matrix* matrixSub(Matrix* mat1, Matrix* mat2) {
        assert(mat1->shape() == mat2->shape());
        int r = mat1->numRows();
        int c = mat1->numCols();
        Matrix* toReturn = new Matrix(r, c, false);
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                toReturn->setEntry(i, j, mat1->getEntry(i, j) - mat2->getEntry(i, j));
            }
        }
        return toReturn;
    }
    
    void Matrix::convertToTransitionMatrix(double dampingCoeff) {
        assert(_nRows == _nCols);
        int n = _nRows;
        long double c = (1 - dampingCoeff) / n;
        for (int j = 0; j < n; j++) {
            long double cSum = 0;
            for (int i = 0; i < n; i++) {
                cSum += _value[i][j];
            }
            if (cSum == 0) {
                for (int i = 0; i < n; i++) {
                    _value[i][j] = 1 / n;
                    _value[i][j] = _value[i][j] * dampingCoeff + c;
                }
            } else {
                for (int i = 0; i < n; i++) {
                    _value[i][j] /= cSum;
                    _value[i][j] = _value[i][j] * dampingCoeff + c;
                }
            }
        }
    }

    vector<long double> Matrix::toVector() {
        vector<long double> res;
        assert(_nRows == 1 || _nCols == 1);
        if (_nCols == 1) {
            for (int i = 0; i < _nRows; i++) 
                res.push_back(_value[i][0]);
        } else if (_nRows == 1) {
            for (int j = 0; j < _nCols; j++) 
                res.push_back(_value[0][j]);
        }
        return res;
    }
    
    void Matrix::printMatrix() {
        for (int i = 0; i < _nRows; i++) {
            for (int j = 0; j < _nCols; j++) {
                printf("%.5Lf\t", _value[i][j]);
            }
            cout << endl;
        }
    }

    vector<string> split(const string &s, char delim) {
        vector<string> result;
        stringstream ss(s);
        string item;
        while (getline(ss, item, delim)) {
            result.push_back(item);
        }
        return result;
    }
    
    bool doubleEqual(double& lft, double& rgt) {
        return abs(lft - rgt) < TOL;
    }
}
