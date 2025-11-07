#ifndef MATRIXHEADER_H
#define MATRIXHEADER_H

#include <string>

class Matrix
{
    public:
        Matrix(unsigned int m, unsigned int n);
        Matrix(int** array, unsigned int m, unsigned int n);
        Matrix(const Matrix &otherMatrix);

        ~Matrix();
        unsigned int rows() const;
        unsigned int columns() const;
        int get(unsigned int i, unsigned int j) const;
        void set(unsigned int i, unsigned int j, int value);
        const Matrix operator+(const Matrix &otherMatrix) const;
        const Matrix operator-(const Matrix &otherMatrix) const;
        const Matrix operator*(const Matrix &otherMatrix) const;
        const Matrix operator~() const;
        bool operator==(const Matrix &otherMatrix) const;
        std::string toStr() const;

        int** getCells() const;
        void fillRandomly(int seed);
        void fillSequentially(int startingAt);
        const unsigned int getCardinality() const;
    protected:
        int** _cells;
        int _rows;
        int _cols;
        unsigned int _largestMagnitude = 0;
        unsigned int _largestMagnitudeCardinality = 1;
        const int* getRow(unsigned int i) const;
        const int* getCol(unsigned int i) const;
        
};

#endif