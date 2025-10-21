#include <iostream>

using namespace std;

int main()
{
    int x = 65;
    char* ptr = (char*) &x;
    cout << &x << endl;
    cout << ptr << endl;
    return 0;
}