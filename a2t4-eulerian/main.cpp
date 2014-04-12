#include <iostream>
#include <vector>
#include <stack>
#include "graph.h"

using namespace std;

vector<int> find_cycle(Graph g) {
    // check if there is a cycle in the first place
    /*for (vector<int>::iterator it = g.arcs_.begin(); it != g.arcs_.end(); ++it) {
        if (it->size()%2) {
            return vector<int>(1, -1);
        }
    }*/
    // okay, there is a cycle
    vector<int> res;
    stack<int> st;
    st.push(1);
    int t;
    while (!st.empty()) {
        t = st.top();
        if (!g.arcs_[t].empty()) {
            st.push(g.arcs_[t].front());
            g.arcs_[t].erase( g.arcs_[t].begin() );
        } else {
            res.push_back(t);
            st.pop();
        }
    }
    return res;
}

int main() {
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

    return 0;
}

