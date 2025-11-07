#ifndef MATRIXHEADER_H
#define MATRIXHEADER_H

#include <string>

/**
 * A class to represent a Matrix. Positions are zero indexed, not 1 indexed.
 * Though the formal definition for addition, subtraction, and multiplications
 * have mathematical limitations defined. We have not learned how to deal with exception
 * handling in C++ and so I'm not sure if I'm supposed to implement it. As such, you /can/ add a 2x3 matrix to a 5x9
 * But adding a 5x9 to a 2x3 should cause the binary to except.
 * 
 * Any parameter which is not marked as read only (const in the paramater definition) is not read only.
 */
class Matrix
{
    public:
        /**
         * Constructor to build an empty m x n array.
         * @param m this is the number of rows
         * @param n this is the number of cols
         */
        Matrix(unsigned int m, unsigned int n);

        /**
         * Constructor for cells, m, and n
         * @param cells The cells to treat as being the contents of the matrix
         *              These cells are deep copied. This has to be the case or we can't
         *              safely delete, and this class can't be assured of enclosure. 
         * @param m     The number of rows in the array
         * @param n     The number of cols in the array
         */
        Matrix(int** array, unsigned int m, unsigned int n);

        /**
         * Copy Constructor, basically exactly maps to the array copy.
         * I considered using a paramaterised constructor in the header file 
         * but that would have lead to a coupling of pointers
         */
         Matrix(const Matrix &otherMatrix);

         /**
         * Destructor for the matrix
         * Which is required to handle the design decision that "a Matrix created from another Matrix should still work if the first is deleted"
         */
        ~Matrix();

        /**
         * Getter for the count of rows. The const suffix used because the 
         * @return The count of rows
         */
        unsigned int rows() const;

        /**
         * Getter for the count of cols
         * @returns The count of the cells
         */
        unsigned int columns() const;

        /**
         * Method to get a value by its positional indices
         * @param i The value of the row index
         * @param j The value of the column index
         * @return  The value of the int held in the Matrix at i,j
         */
        int get(unsigned int i, unsigned int j) const;
        
        /**
         * Method to set the value at the position i,j.
         * @param i     The value of the row index
         * @param j     The value of the column index
         * @param value The value to be stored at i,j
         */
        void set(unsigned int i, unsigned int j, int value);

        // The const suffix here is used because manipulating either of the operands shouldn't be allowed.
        
        /**
         * A method to create a matrix that is the sum of this matrix and thatmatrix
         * @param that The other matrix. This is a read only parameter.
         * @return The matrix which is the sum of the two matrices
         */
        Matrix operator+(const Matrix &otherMatrix) const;

        /**
         * Method to generate the matrix that is the result of subtracting that matrix from this matrix
         * @param that Another matrix . This is a read only parameter.
         * @return The resulting matrix from subtracting that from this
         */
        Matrix operator-(const Matrix &otherMatrix) const;

        /**
         * Matrix multiplication operator. Like the above operators, it creates a new array by manipulating this and that.
         * This will only work if the rules for multiplication *can* be employed. It may cause exceptions or improper behaviour if they do not.
         * Since we haven't been shown how to handle exceptions this can fail silently.
         * There should be an exception if the rows and columns constraint isn't respected.
         * @param that The other array
         * @return Returns the array resulting from multiplication 
         */
        Matrix operator*(const Matrix &otherMatrix) const;

        /**
         * Transpose operator, overloads bitwise negation operator. The transpose operator symmetrically flips the matrix along the x=y index axis.
         * @return The transpose matrix AT of this matrix A.
         */
        Matrix operator~() const;

        /**
         * Equality comparison operator. First checks for size as a hotwire, then checks each cell for equality.
         * If they're not the same at any point it returns false.
         * @param otherMatrix The matrix to check for equivalence with this matrix. This is a read only parameter
         * @returns true if equivalent false otherwise.
         */
        bool operator==(const Matrix &otherMatrix) const;

        /**
         * This creates a sring representation of the matrix in a padded manner suitable for printing.
         * @return Returns a string representation of this Matrix.
         */
        std::string toStr() const;

        /**
         * This just prints the matrix to the string. It's useful for testing and I eventually started using it in test cases.
         */
        void debug() const;

        /**
         * A method that returns a deep clone of the pointers
         * @return The deep clone of the cells in this Matrix
         */
        int** getCells() const;

        /**
         * This is just a helper function to randomly populate a Matrix with seeded random values.
         * This allows me to predictably and reliably fill matrices easily which will help with testing.
         * The resulting matrix isn't platform independent, but it does allow me to test it on any given platform reliably.
         * @param seed  The seed for the PRNG. This is read only because it may as well be.
         */
        void fillRandomly(const int seed);

        /**
         * Fills every entry in the matrix with values sequentially starting from a given number.
         * @param startingAt The number to start filling from
         */
        void fillSequentially(int startingAt);

    protected:
        /**
         * The internal representation of the cells in the matrix.
         */
        int** _cells;
        /**
         * The number of rows
         */
        int _rows;
        /**
         * The number of columns
         */
        int _cols;
        /**
         * The largest absolute value of any number stored in the matrix, used in printing
         */
        unsigned int _largestMagnitude = 0;
        /**
         * The order of magnitude of that number. I rea
         */
        unsigned int _orderOfMagnitude = 1;

        /**
         * This is just a helper method used in printing. 
         * If we know what the cardinality of the largest value number is 
         * (that is we know the floor of the log10 of the absolute value of a number);
         * we know how much whitespace padding to add to printing to make it look pretty.
         * Which was usefull for debugging and also produces a more aesthetically pleasing matrix toStr
         */
        const unsigned int getCardinality() const;

        /**
         * Get a row from the matrix based on its i index. This is really just a helper function for the matrix multiplication method.
         * The return value is const because I don't want people to be able to manipulate the internals this way.
         * The const suffix is used to prevent internal manipulation of the Matrix. This is an accessor method.
         * @param i The index of the row to return.
         */
        const int* getRow(const unsigned int i) const;

        /**
         * Get a column from the matrix based on its j index.  This is really just a helper function for the matrix multiplication method.
         * The return value is const because I don't want people to be able to manipulate the internals this way.
         * The const suffix is used to prevent internal manipulation of the Matrix. This is an accessor method.
         * @param j The index of the column to return.
         */
        const int* getCol(const unsigned int i) const;
        
};

#endif