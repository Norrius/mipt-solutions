#include <iostream>
#include <vector>
#include "graph.h"
#include "cycle.h"
#include "test.h"
//#define MANUAL

using namespace std;

int main() {
#ifdef MANUAL
    int n, m, x, y;
    cin >> n >> m;
    Graph g(n);
    for (int i=0; i<m; ++i) {
        cin >> x >> y;
        g.addArc(x, y);
    }

    vector<int> c = find_cycle(g);

    if (c[0] != -1) {
        for (vector<int>::reverse_iterator it = c.rbegin(); it != c.rend(); ++it) {
            cout << *it << ' ';
        }
    } else {
        cout << "No cycle";
    }
    cout << endl;
#else
    test();
#endif

    return 0;
}

