#include "Matrix.h"
#include <iostream>
#include <string>

using namespace std;



int main()
{
    Matrix* m = new Matrix(3, 5);
    Matrix* n = new Matrix(5, 7);
    
    delete n;
    delete m;
}