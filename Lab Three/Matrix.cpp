#include "Matrix.h"
#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;



/**
 * A helper function to get the order of magnitude of a number
 * All other Documentation Style comments are found in the .h file, that appears to be the best practice for C++
 * I've only internally commented methods if I think I'm doing anything that requires it (like commenting that I used three lines of code from an O'Reilly page)
 */
unsigned int getOrderOfMagnitude(unsigned int n)
{
    int l10 = 1;
    while(n/10 >= 1)
    {
        l10++;
        n /= 10;
    }
    return l10;
}



Matrix::Matrix(unsigned int m, unsigned int n)
{
    this->_rows = m;
    this->_cols = n;
    this->_cells = new int*[m];
    for(int i = 0; i < m; i++)
    {
        this->_cells[i] = new int[n];
    }
}

Matrix::Matrix(int** cells, unsigned int m, unsigned int n)
{
    this->_rows = m;
    this->_cols = n;
    this->_cells = new int*[m];
    for(int i = 0; i < m; i++)
    {
        this->_cells[i] = new int[n];
        for(int j = 0; j < n; j++)
        {
            this->set(i, j, cells[i][j]);
        }
    }
}


Matrix::Matrix(const Matrix &otherMatrix)
{
    this->_rows = otherMatrix._rows;
    this->_cols = otherMatrix._cols;
    this->_cells = new int*[otherMatrix._rows];
    for(int i = 0; i < this->_rows; i++)
    {
        this->_cells[i] = new int[otherMatrix._cols];
        for(int j = 0; j < this->_cols; j++)
        {
            this->set(i, j, otherMatrix._cells[i][j]);
        }
    }

}


Matrix::~Matrix()
{
    for(int i = 0; i < this->_rows; i++)
    {
        delete[] this->_cells[i];
    }
    delete[] this->_cells;
    this->_cells = NULL;
}


unsigned int Matrix::rows() const
{
    return this->_rows;
}

unsigned int Matrix::columns() const
{
    return this->_cols;
}

string Matrix::toStr() const
{
    string out = "";
    for(int i = 0; i < this->_rows; i++)
    {
        // this just adds a nice ascii symbol than | to left hand side
        out += (char)179;
        for(int j = 0; j < this->_cols; j++)
        {
            int cell = this->_cells[i][j];
            string cellStr = to_string(cell);
            // I found this code, more or less, here.
            // https://www.oreilly.com/library/view/c-cookbook/0596007612/ch04s02.html
            // it's the only "not from first principles" code I've used so far
            // but I have tailored it to work for my specific use case by tracking a value
            // _largestMagnitudeCardinality and padding to that
            cellStr.insert(
                cellStr.begin(),
                this->_orderOfMagnitude - cellStr.length() + 1,
                ' '
            );
            // this just adds a nice ascii symbol than | to right hand side
            out += cellStr + (j < this->_cols - 1?", ":"");
        }
        out += (char)179;
        if(i < this->_rows - 1)
        {
            out += "\n";
        }
    }
    return out;
}

int Matrix::get(unsigned int i, unsigned int j) const
{
    return this->_cells[i][j];
}

void Matrix::set(unsigned int i, unsigned int j, int value)
{
    if(i >= this->_rows)
    {
        return;
    }
    if(j >= this->_cols)
    {
        return;
    }
    // we use the _largest magnitude for just one purpose, padding length.
    unsigned int magnitude = value > 0 ? value : -value;
    if(this->_largestMagnitude < magnitude)
    {
        this->_largestMagnitude = magnitude;
        // we only worry about updating the cardinality if the new value is bigger than the old value
        this->_orderOfMagnitude = getOrderOfMagnitude(magnitude);
        
    }
    
    this->_cells[i][j] = value;
}

bool Matrix::operator==(const Matrix &otherMatrix) const
{
    // AIUI it doesn't matter whether !(a && b) "is more effiecent" than !a || !b because
    // the compiler does hot swapping.
    if(this->_rows != otherMatrix._rows || this->_cols != otherMatrix._cols)
    {
        return false;
    }

    // check every int in every index.
    for(int i = 0; i < this->_rows; i++)
    {
        for(int j = 0; j < this->_cols; j++)
        {
            if(this->_cells[i][j] != otherMatrix._cells[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

Matrix Matrix::operator+(const Matrix &that) const
{
    Matrix newM(this->_rows, this->_cols);
    for(int i = 0; i < this->_rows; i++)
    {
        for(int j = 0; j < this->_cols; j++)
        {
            newM.set(i, j, this->_cells[i][j] + that._cells[i][j]);
        }
    }
    return newM;
}

Matrix Matrix::operator-(const Matrix &that) const
{
    Matrix newM(this->_rows, this->_cols);
    for(int i = 0; i < this->_rows; i++)
    {
        for(int j = 0; j < this->_cols; j++)
        {
            newM.set(i, j, this->_cells[i][j] - that._cells[i][j]);
        }
    }
    return newM;
}

const int* Matrix::getRow(const unsigned int i) const
{
    return this->_cells[i];
}

const int* Matrix::getCol(const unsigned int j) const
{
    int* column = new int[this->_rows];
    for(int i = 0; i < this->_rows; i++)
    {
        column[i] = this->_cells[i][j];
    }
    return column;
}

Matrix Matrix::operator*(const Matrix &that) const
{
    Matrix newM(this->_rows, that._cols);

    for(int i = 0; i < this->_rows; i++)
    {
        const int* row = this->getRow(i);
        for(int j = 0; j < that._cols; j++)
        {
            
            const int* col = that.getCol(j);
            int val = 0;
            
            for(int k = 0; k < this->_cols; k++)
            {
                val += row[k] * col[k];
            }
            newM.set(i, j, val);
            delete[] col;
        }
    }
    return newM;
}

Matrix Matrix::operator~() const
{
    Matrix newM(this->_cols, this->_rows);

    for(int i = 0; i < this->_rows; i++)
    {
        for(int j = 0; j < this->_cols; j++)
        {
            newM.set(j, i, this->get(i,j));
        }
    }
    return newM;
}


void Matrix::fillRandomly(const int seed)
{
    srand(seed);

    for(int i = 0; i < this->_rows; i++)
    {
        for(int j = 0; j < this->_cols; j++)
        {
        	this->set(i, j, (rand() % 201) - 100);
        }
    }
}

void Matrix::fillSequentially(int startingAt)
{
    for(int i = 0; i < this->_rows; i++)
    {
        for(int j = 0; j < this->_cols; j++)
        {
            this->set(i, j, startingAt++);
        }
    }
}

int** Matrix::getCells() const
{
    int** cells = new int*[this->_rows];
    for(int i = 0; i < this->_rows; i++)
    {
        cells[i] = new int[this->_cols];
        for(int j = 0; j < this->_cols; j++)
        {
            cells[i][j] = this->_cells[i][j];
        }
    }
    return cells;
}

const unsigned int Matrix::getCardinality() const
{
    return this->_orderOfMagnitude;
}

void Matrix::debug() const
{
    cout << this->toStr() << endl;
}