#include <iostream>
#include "graph.h"
#include "dsu.h"

using namespace std;

int main()
{
    size_t n, m;
    cin >> n >> m;
    Graph g(n);
    dsu d(n);

    size_t x, y, z;
    for (size_t i=0; i<m; ++i) {
        cin >> x >> y;
        z = d.unite_sets(x-1, y-1);
        if (d.rank(z) == n) {
            cout << i+1 << endl;
            return 0;
        }
    }

    cout << n << endl;
    return 0;
}

