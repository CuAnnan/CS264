#include <iostream>
#include "functionPointers.h"
using namespace std;




int main()
{
    struct {
        int (*add)(int, int);
        int (*sub)(int, int);
        int (*mul)(int, int);
        int (*div)(int, int);
        int (*rev)(int);
    } calculator;
    calculator.add = wing_add;
    calculator.sub = wing_minus;
    calculator.mul = wing_mul;
    calculator.rev = wing_reverseInteger;
    calculator.div = wing_div;

    cout << calculator.rev(calculator.mul(5, 7)) << endl;
}