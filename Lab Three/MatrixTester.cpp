#include "Matrix.h"
#include <iostream>
#include <string>

using namespace std;

const unsigned int ROWS = 3;
const unsigned int COLS = 5;

// test case for m x n constructor
Matrix* Test_Matrix_Constructor_1()
{
    Matrix* m = new Matrix(ROWS, COLS);
    cout << "Matrix constructor for rows and cols worked"<<endl;
    return m;
}

// test case for copy constructor
Matrix* Test_Matrix_Constructor_2(const Matrix &in)
{
    Matrix* m = new Matrix(in);
    cout << "Matrix copy constructor worked" << endl;
    return m;
}

// test case for specific values constructor
Matrix* Test_Matrix_Constructor_3(int** arrayOfInts, int m, int n)
{
    Matrix* mat = new Matrix(arrayOfInts, m, n);
    cout << "Matrix constructor for 2d pointer, m and n worked" << endl;
    return mat;
}

// test case for rows method
void Test_Case_Rows(const Matrix &mat)
{
    bool pass = mat.rows() == ROWS;
    cout << "Matrix rows "<<(pass?"":"does not ")<<"match"<<(pass?"es":"")<<" expected row size"<<endl;
}

// test case for cols method
void Test_Case_Cols(const Matrix &mat)
{
    bool pass = mat.columns() == COLS;
    cout << "Matrix rows "<<(pass?"":"does not ")<<"match"<<(pass?"es":"")<<" expected column size"<<endl;
}

// for the sequentially filled matrices, if they are odd m and n and they've started at -1/2 the size; the center point will always be 0
// I could have made the various tests that I use for his separate functions but doing so violates DRY principle
void Test_Case_Get(const Matrix &mat)
{
    bool pass = mat.get(mat.rows()/2,mat.columns()/2) == 0;
    cout << "Matrix "<<(pass?"":"does not ")<<"pass"<<(pass?"es":"")<<" center get"<<endl;
}

// test case for set. Increments the 0th 0th value and asserts that increment via a comparison. Seems like a solid test.
void Test_Case_Set(Matrix &mat)
{
    // this lets us guarantee that the value changes
    int oldVal = mat.get(0,0);

    mat.set(0, 0, oldVal + 1);
    
    bool pass = mat.get(0,0) == oldVal + 1;
    cout << "Matrix "<<(pass?"":"does not ")<<"pass"<<(pass?"es":"")<<" set test case"<<endl;
}

// Create a new Matrix and then loop through all cells and make sure the value of the new cells is the sum of the values of the cells in the same positions of
// the component Matrices.
void Test_Case_Operator_Plus(const Matrix &mat1, const Matrix &mat2)
{
    // we're going to assume that the test passes and try to falsify it
    bool pass = true;
    Matrix mat3 = mat1 + mat2;
    for(int i = 0; i < mat3.rows(); i++)
    {
        for(int j = 0; j < mat3.columns(); j++)
        {
            pass = pass && mat3.get(i, j) == mat1.get(i, j) + mat2.get(i, j);
        }
    }

    cout << "Test case for matrix addition "<<(pass?"":"dose not ")<<"pass" << (pass?"es":"")<<endl;
}

// Create a new Matrix and then loop through all cells and make sure the value of the new cells is the sum of the values of the cells in the same positions of
// the component Matrices.
void Test_Case_Operator_Minus(const Matrix &mat1, const Matrix &mat2)
{
    // we're going to assume that the test passes and try to falsify it
    bool pass = true;
    Matrix mat3 = mat1 - mat2;
    for(int i = 0; i < mat3.rows(); i++)
    {
        for(int j = 0; j < mat3.columns(); j++)
        {
            pass = pass && mat3.get(i, j) == mat1.get(i, j) - mat2.get(i, j);
        }
    }

    cout << "Test case for matrix subtraction "<<(pass?"":"dose not ")<<"pass" << (pass?"es":"")<<endl;
}

void Test_Case_ToStr(Matrix &mat)
{
    cout << "If this works, you should see the matrix you expect to see: "<<endl<<mat.toStr()<<endl;
}

// Create a new Matrix. We're not going to replicate the full logic for multiplication here.
// If it works for any matrices mat1 and mat2 at m3 (resultnig multiplicand) index 0,0 it can be inferred that the process works in general
void Test_Case_Operator_Multiplication(const Matrix &mat1, const Matrix &mat2)
{
    Matrix mat3 = mat1 * mat2;
    cout << "Multiplication operation worked for test case and a Matrix m3 has been created by multiplying m1 * m2"<<endl;
    int test = 0;
    if(mat3.rows() == mat1.rows() && mat3.columns() == mat2.columns())
    {
        cout << "M3 has the correct dimensions"<<endl;
    }
    else
    {
        cout << "M3 does not have the correct dimensions"<<endl;
    }

    for(int i = 0; i < mat1.columns(); i++)
    {
        test += mat1.get(0, i) * mat2.get(i, 0);
    }

    if(test == mat3.get(0,0))
    {
        cout << "The value of m3 at index 0,0 matches the expected value according to the rules for matrix manipuation, we can assume that the rest do"<<endl;
    }
    else
    {
        cout << "The value of m3 at index 0,0 is wrong, we should assume the test fails"<<endl;
    }
}

void Test_Case_Operator_Equals(const Matrix &mat1, const Matrix &mat2, bool pass)
{
    if(mat1 == mat2 && pass)
    {
        cout << "Equals passes when it should."<<endl;
    }
    else if(!(mat1 == mat2) && !pass)
    {
        cout << "Equals fails when it should."<<endl;
    }
    else
    {
        cout << "Equals doesn't pass when it should."<<endl;
    }
}

int main()
{
    Matrix* m1 = Test_Matrix_Constructor_1();
    // using the fill sequential method.
    m1->fillSequentially(-7);
    

    Matrix* m2 = Test_Matrix_Constructor_2(*m1);

    int** cells = m1->getCells();
    Matrix* m3 = Test_Matrix_Constructor_3(cells, m1->rows(), m1->columns());

    Test_Case_Rows(*m1);
    Test_Case_Cols(*m1);

    Test_Case_Get(*m1);
    m3->set(m3->rows()/2, m3->columns()/2, 150);
    // this should fail
    Test_Case_Get(*m3);

    // we need different shaped matrix
    Matrix* m4 = new Matrix(5, 7);
    m4->fillSequentially(-17);
    Test_Case_Get(*m4);

    Test_Case_Set(*m3);
    

    // we need a different matrix of the same cardinalities as m1 for addition and subtraction
    Matrix* m5 = new Matrix(m1->rows(), m1->rows());
    m5->fillRandomly(1337);
    Test_Case_Operator_Plus(*m1, *m5);
    Test_Case_Operator_Minus(*m1, *m5);

    // this should print out the defined matrix 
    // [
    //     [-7, -6, -5, -4, -3],
    //     [-2, -1,  0,  1,  2],
    //     [ 3,  4,  5,  6,  7]
    // ]
    Test_Case_ToStr(*m1);

    Test_Case_Operator_Multiplication(*m1, *m4);

    Test_Case_Operator_Equals(*m1, *m2, true);
    Test_Case_Operator_Equals(*m1, *m3, false);
    // done with m3 so delete it
    delete m3;



    
    // freeing memory resources;
    for(int i =0; i < 3; i++)
    {
        delete[] cells[i];
    }
    delete[] cells;

    delete m5;
    delete m2;
    delete m4;
    delete m1;
}