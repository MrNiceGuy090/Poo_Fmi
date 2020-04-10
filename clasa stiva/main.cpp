#include "stiva.h"
using namespace std;

int main()
{
    // tests
    stiva x, y;
    x.push(4);
    x.pop();
    x.pop();
    cout << x;
    y.push(6); y.push(8); y.push(9);
    x = y;
    stiva z = x;
    z.push(5);
    cout << (z < x) << " " << (z > x) << " " << (z == x) << " " << (y == x);
    vector<int> m;
    m.push_back(5); m.push_back(7);
    stiva t(m);
    t.Reverse();
    cout << t.getSize() << " " << t.isEmpty();

    return 0;
}
