#include "Matrix.h"
#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;


// helper function for printing
unsigned int getMagnitudeCardinality(unsigned int n)
{
    int l10 = 1;
    while(n/10 >= 1)
    {
        l10++;
        n /= 10;
    }
    return l10;
}

/**
 * Constructor for the m and n only properties.
 * @param m this is the number of rows
 * @param n this is the number of cols
 */
Matrix::Matrix(unsigned int m, unsigned int n)
{
    // initialise rows
    this->_rows = m;
    // initialise cols
    this->_cols = n;
    // initialise cells and all rows in cells
    // cells will be a pointer representing 
    // an m-length array of n-length arrays
    this->_cells = new int*[m];
    for(int i = 0; i < m; i++)
    {
        this->_cells[i] = new int[n];
    }
}

/**
 * Constructor for cells, m, and n
 * @param cells The cells to treat as being the contents of the matrix
 *              These cells are deep copied. This has to be the case or we can't
 *              safely delete, and this class can't be assured of enclosure. 
 * @param m     The number of rows in the array
 * @param n     The number of cols in the array
 */
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

/**
 * Copy Constructor, basically exactly maps to the array copy.
 * I considered using a paramaterised constructor in the header file but that would have lead to a coupling of pointers, which would violate
 * my design choice
 */
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


/**
 * Destructor for the matrix
 * Which is required to handle the design decision that "a Matrix created from another Matrix should still work if the first is deleted"
 */
Matrix::~Matrix()
{
    for(int i = 0; i < this->_rows; i++)
    {
        delete[] this->_cells[i];
    }
    delete[] this->_cells;
    this->_cells = NULL;
}

/**
 * Getter for the count of rows
 * @return The count of rows
 */
unsigned int Matrix::rows() const
{
    return this->_rows;
}

/**
 * Getter for the count of cols
 * @return the count of the cells
 */
unsigned int Matrix::columns() const
{
    return this->_cols;
}

/**
 * Printer for the matrix.
 * @return Returns a string representation of this Matrix.
 */
string Matrix::toStr() const
{
    string out = "[\n";
    for(int i = 0; i < this->_rows; i++)
    {
        out += "\t[";
        for(int j = 0; j < this->_cols; j++)
        {
            int cell = this->_cells[i][j];
            string cellStr = to_string(cell);
            // I found this code, more or less, here.
            // https://www.oreilly.com/library/view/c-cookbook/0596007612/ch04s02.html
            // it's the only "not from first principles" code I've used so far
            // but I have tailored it to work for my specific use case
            cellStr.insert(
                cellStr.begin(),
                this->_largestMagnitudeCardinality - cellStr.length() + 1,
                ' '
            );

            out += cellStr + (j < this->_cols - 1?", ":"");
        }
        out += "]";
        if(i < this->_rows - 1)
        {
            out += ",";
        }
        out += "\n";
    }
    return out+"]";
}

/**
 * Method to get a value by its positional indices
 */
int Matrix::get(unsigned int i, unsigned int j) const
{
    return this->_cells[i][j];
}

/**
 * Method to set the value at a given positional index pair. This is the only way to manipulate the values of the Matrix by design.
 * The cells field is private. Manipulating it directly is not advised.
 */
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
        this->_largestMagnitudeCardinality = getMagnitudeCardinality(magnitude);
        
    }
    
    this->_cells[i][j] = value;
}

/**
 * Equality comparison operator. First checks for size as a hotwire, then checks each cell for equality.
 * If they're not the same at any point it returns false.
 */
bool Matrix::operator==(const Matrix &otherMatrix) const
{
    if(this->_rows != otherMatrix._rows)
    {
        return false;
    }
    if(this->_cols != otherMatrix._cols)
    {
        return false;
    }

    

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

/**
 * A method to create a matrix that is the sum of this matrix and thatmatrix
 * @param that The other matrix
 * @return The matrix which is the sum of the two matrices
 */
const Matrix Matrix::operator+(const Matrix &that) const
{
    Matrix newM(this->_rows, this->_cols);
    for(int i = 0; i < this->_rows; i++)
    {
        for(int j = 0; j < this->_cols; j++)
        {
            // add the two values of the cells in both internal arrays
            // and set the value of the matrix for that i, j, cell sum
            newM.set(i, j, this->_cells[i][j] + that._cells[i][j]);
        }
    }
    return newM;
}

/**
 * Method to generate the matrix that is the result of subtracting that matrix from this matrix
 * @param that Another matrix
 * @return The resulting matrix from subtracting that from this
 */
const Matrix Matrix::operator-(const Matrix &that) const
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

/**
 * Get a row from the matrix based on its i index. This is really just a helper function for the matrix multiplication method.
 * @param i The index of the row to return.
 */
const int* Matrix::getRow(unsigned int i) const
{
    return this->_cells[i];
}

/**
 * Get a column from the matrix based on its j index.  This is really just a helper function for the matrix multiplication method.
 * @param j The index of the column to return.
 */
const int* Matrix::getCol(unsigned int j) const
{
    int* column = new int[this->_rows];
    for(int i = 0; i < this->_rows; i++)
    {
        column[i] = this->_cells[i][j];
    }
    return column;
}

/**
 * Matrix multiplication operator. Like the above operators, it creates a new array by manipulating this and that.
 * This will only work if the rules for multiplication *can* be employed. It may cause exceptions or improper behaviour if they do not.
 * Since we haven't been shown how to handle exceptions this can fail silently.
 * There should be an exception if the rows and columns constraint isn't respected.
 * @param that The other array
 * @return Returns the array resulting from multiplication 
 */
const Matrix Matrix::operator*(const Matrix &that) const
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

/**
 * Transpose operator, overloads bitwise negation operator.
 * @return The tras
 */
const Matrix Matrix::operator~() const
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


// helper functions
// These are not required for in the spec but they make building and confirming test cases much easier

/**
 * This is just a helper function to randomly populate a Matrix with seeded random values.
 * This allows me to predictably and reliably fill matrices easily which will help with testing.
 * @param seed  The seed for the PRNG
 */
void Matrix::fillRandomly(int seed)
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

/**
 * Fills every entry in the matrix with values sequentially starting from a given number.
 * @param startingAt The number to start filling from
 */
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

/**
 * A method that returns a deep clone of the pointers
 * @return The deep clone of the cells in this Matrix
 */
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
    return this->_largestMagnitudeCardinality;
}