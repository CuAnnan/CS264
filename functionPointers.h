#ifndef FUNCTION_POINTERS_H
#define FUNCTION_POINTERS_H

int wing_add(int a, int b)
{
    return a + b;
}

int wing_mul(int a, int b)
{
    return a * b;
}

int wing_div(int a, int b)
{
    return a / b;
}

int wing_minus(int a, int b)
{
    return a - b;
}

int wing_reverseInteger(int in)
{
    // edge case to handle reversing negative ints
    bool isReversed = false;
    if(in < 0)
    {
        isReversed = true;
        in *= -1;
    }

    int out = 0;
    while(in > 0)
    {
        // move the last digit one to the left by left shifting the number in base 10
        out *= 10;
        // add the least significant digit of what remains of in
        out += in %10;
        // chop that digit off by right shifting the int in
        in /=10;
    }

    if(isReversed)
    {
        // if we reversed at the start, do it again
        out *= -1;
    }
    return out;
}


#endif