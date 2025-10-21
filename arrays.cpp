#include <iostream>
using namespace std;

int main()
{
    int n = n = 4, m = 5;

    int** arr = new int*[n];

    for(int i = 0; i < n; i++)
    {
        arr[i] = new int[m];
    }
    // fill the array
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            arr[i][j] = i * m + j;
        }
    }

    // print the array
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    // free the array
    for(int i = 0; i < n; i++)
    {
        delete[] arr[i];
    }

    delete[] arr;

}