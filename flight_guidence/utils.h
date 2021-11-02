#pragma once
#include <vector>
#include <string>
#include <math.h>
#include <iostream>

using std::vector;
using std::string;
using std::to_string;
using std::pair;
using std::cout;
using std::endl;

namespace utils {
    
    class Matrix {
        public:
            static Matrix* initialVector(int r);

            /** 
             * Constructs empty matrix
             * @param r number of rows of the matrix
             * @param c number of cols of the matrix
             * @param initialize whether the matrix need to be initialized as 0
             */
            Matrix(int r, int c, bool initialize = true);

            /** 
             * Constructs empty matrix
             * @param shape shape of the matrix
             * @param initialize whether the matrix need to be initialized as 0
             */
            Matrix(pair<int, int> shape, bool initialize = true);

            /** 
             * Constructs matrix using double pointer
             * @param r number of rows of the matrix
             * @param c number of cols of the matrix
             * @param value the double pointer that discribes the matrix
             */
            Matrix(int r, int c, long double** value);

            /** 
             * Destructor
             */
            ~Matrix();

            /** 
             * Get the number of rows the matrix has
             * @returns number of rows the matrix has
             */
            int numRows() const {
                return _nRows;
            }
            
            /** 
             * Get the number of cols the matrix has
             * @returns number of cols the matrix has
             */
            int numCols() const {
                return _nCols;
            }
            
            /** 
             * Get the shape of the matrix
             * @returns shape of the matrix
             */
            pair<int, int> shape() const {
                return pair<int, int>(_nRows, _nCols);
            }

            /** 
             * Set the entry of current matrix at row r, column c
             * @param r row of the entry
             * @param c column of the entry
             * @param entry the new value of the entry
             */
            void setEntry(int r, int c, long double entry);

            /** 
             * Get the entry of current matrix at row r, column c
             * @param r row of the entry
             * @param c column of the entry
             * @returns the value of the entry
             */
            long double getEntry(int r, int c) const;

            /**
             * 2-norm of the vector
             * REQUIRES NUM_COLS == 1
             */
            long double norm();

            /**
             * Normalize given vector using 2-norm
             * REQUIRES NUM_COLS == 1
             */
            Matrix* normalize();

            /**
             * Convert the matrix to transition matrix using damping coefficient
             * @param dampingCoeff damping coefficent
             */
            void convertToTransitionMatrix(double dampingCoeff);

            /**
             * Convert the matrix into a vector. Notice this only applies to matrices with either one 
             * column or one row. Otherwise this will throw an exception.
             * @returns transformed vector
             */
            vector<long double> toVector();
            
            /** 
             * Print the matrix
             */
            void printMatrix();

        private:
            /** number of rows */
            int _nRows;

            /** number of cols */
            int _nCols;

            /** internal storage of data */
            long double** _value;
    };

    /**
     * Prepare the raw string for inputing data
     * @param s input string
     * @returns a vector that contains all the entries
     */
    vector<string> readEntry(string &s);

    /**
     * Get the distance between two points on earth given their latitude and
     * longtitude. 
     * @param latitude1 latitude of the first point
     * @param longtitude1 longtitude of the first point
     * @param latitude2 latitude of the second point
     * @param longtitude2 longtitude of the second point
     * @returns distance between these two points
     */
    double getDistance(double latitude1, double longtitude1, double latitude2, double longtitude2);
    
    /**
     * Matrix multiplication
     * @param mat1 first matrix
     * @param mat2 second matrix
     * @returns result of multiplication
     */
    Matrix* matrixMul(Matrix* mat1, Matrix* mat2);

    /**
     * Matrix addition
     * @param mat1 first matrix
     * @param mat2 second matrix
     * @returns result of multiplication
     */
    Matrix* matrixAdd(Matrix* mat1, Matrix* mat2);

    /**
     * Matrix subtraction
     * @param mat1 first matrix
     * @param mat2 second matrix
     * @returns result of multiplication
     */
    Matrix* matrixSub(Matrix* mat1, Matrix* mat2);
    
    /** 
     * Returns of two matrixs are the same
     * @param other the other matrix
     */
    bool operator!=(const Matrix& lhs, const Matrix& rhs);

    /** 
     * Returns of two matrixs are the same
     * @param other the other matrix
     */
    bool operator==(const Matrix& lhs, const Matrix& rhs);

    /** 
     * Split a string into a vector of strings using specified delimiter
     * @param s the string needed to be splited
     * @param delim the delimiter used
     */
    vector<string> split(const string &s, char delim);

    /**
     * Return if the two double are equal
     * @returns whether the two doubles are equal
     */
    bool doubleEqual(double& lft, double& rgt);

    /** Error code used when airport ID is not recognizable */
    const static int ERROR_AIRPORT_ID = -pow(2,30);
    const static string STR_ERROR_AIRPORT_ID = to_string(ERROR_AIRPORT_ID);
    const static long double TOL = powl(10, -15);
}