#include <iostream>

using namespace std;

/*
 * I have not commented my inputter functions except to call them inputter functions.
 * They cin the required input cout the results of the named functions which solve the assigned questions
 * even for the isPowerOfTwo function
 */


/**
 * A function to reverse the digits in an integer number.
 * This method is not overflow or underflow safe so use at your own peril
 * This method does respect the sign of the int though
 * @param n An integer to revers
 * @returns An integer with the reverse digits of n
 */
int reverseInteger(int in)
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


// inputter for question one
void questionOne()
{
    int in;
    cout << "Q1) Enter an integer to reverse: ";
    cin >> in;
    int reversed = reverseInteger(in);
    cout << reversed<<endl;
}


/**
 * A method to determine the GCD of two integers
 * @param a Integer 1
 * @param b Integer 2
 * @return The Greatest Common Denominator as calculated by this algorithm
 */
int getGcd(int a, int b)
{
    // we need the modulus of the bigger number divided by the smaller one
    // until there is no modulus
    // when there is no modulus, the smallest number is the original gcd
    int biggest = a > b ? a : b;
    int smallest = a < b ? a : b;

    // mod
    int mod = biggest % smallest;
    if(mod == 0)
    {
        // have our answer
        return smallest;
    }
    // loop one more
    return getGcd(smallest, mod);
}

// inputter for question two
void questionTwo()
{
    int a, b;
    cout << "Q2) Enter two integeters:"<<endl;
    cout << "Integer One: ";
    cin >> a;
    cout << "Integer Two: ";
    cin >> b;
    int gcd = getGcd(a, b);
    cout << "Greatest Common Denominator: "<< gcd << endl;
}


/**
 * A number is a palindrome IIF the integer equals the reverse of the integer
 * I couldn't find a faster way to do this.
 * @param n The integer to check for pallindromity
 * @return Returns true if it's a pallindrome, false if not
 */
bool isPallindrome(int n)
{
    if (n < 0)
    {
        // the minus sign is treated as a part of pallindromeness here
        return false;
    }
    return n == reverseInteger(n);
}

// inputter for question three
void questionThree()
{
    int candidate;
    cout << "Q3) Enter an integer to check if it's a pallindrome: ";
    cin >> candidate;
    cout << (isPallindrome(candidate)?"true":"false")<<endl;
}

/**
 * Find a base x to the power of exponent y
 * @param x The base
 * @param y The exponent
 * @return x to the power of y
 */
int pow(int x, int y)
{
    // zero to the power of anything is 0
    if(x == 0)
    {
        return 0;
    }
    // any int x to the power of 1 is x
    if(y == 1)
    {
        return x;
    }
    // any int to the power of 0 is 1
    if(y == 0)
    {
        return 1;
    }
    // here's the trick to get it down to logn
    // leveraging the exponent law a^(2b) is the same as (a^2)^b
    // this cuts the number of recursions that we have to do in half
    // but we're still doing an operation on x.
    if(y%2 == 0)
    {
        return pow(x*x, y/2);
    }
    // otherwise, we're just recursing to get the power of x the old fashioned way
    // we could do this in on by skipping the previous step.
    return x * pow(x, y -  1);
}

// inputter for question four
void questionFour()
{
    int base, exponent;
    cout << "Q4) Raise an integer base (b) to an integer exponent (e): "<<endl;
    cout << "Enter b : ";
    cin >> base;
    cout << "Enter e: ";
    cin >> exponent;
    int out = pow(base, exponent);
    cout << "b to the power of e is: "<<out<<endl;
}

/**
 * A function to determine if an int is an even power of two
 * @param n The int to determine if is an even power of two
 * @return True if is even power of two, false otherwise
 */
bool isPowerOfTwo(int n)
{
    // n is not a power of 2 if n is 0;
    if(n == 0)
    {
        return false;
    }
    // a binary number is a power of two IIF it is in the form /^10*/
    // 1 is a power of 2 in that it is 2^0
    // so 10000000 & 01111111 will be 0 because we're bitwise anding the individual bits
    // of the integers in radix2.
    // if it's zero, then the first digit was a 1 and everything else was a zero.
    // => was power of 2
    // otherwise it wasn't.
    return (n & n - 1)== 0;
}

void questionFive()
{
    int candidate;
    cout << "Q5) Enter an integer to see if it's a power of 2: "<<endl;
    cin >> candidate;
    cout << candidate << " is"<<(isPowerOfTwo(candidate)?"":" not")<<" a power of two"<<endl;
}

int main()
{
    questionOne();
    questionTwo();
    questionThree();
    questionFour();
    questionFive();
}