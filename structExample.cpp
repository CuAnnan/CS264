#include <iostream>
using namespace std;

int main()
{
    enum Color { RED, GREEN, BLUE };

    struct Point
    {
        double x;
        double y;
        Color color;
    };

    Point p1 = {2.0, 1.0, RED}, p2 = {3.0, 4.0, GREEN};

    Point* p3 = &p1;
    p3->x = 5.0;
    p3->y = 6.0;

    Point *pt4 = new Point;

    (*p3).x = 7.0;
    (*p3).y = 8.0;

    cout << "p1: (" << p1.x << ", " << p1.y << ", "<<p1.color<<")\n";
    cout << "p2: (" << p2.x << ", " << p2.y << ", "<<p2.color<<")\n";
    

    delete pt4;
    return 0;
}