#include "cycle.h"

vector<int> find_cycle(Graph g) {
    // check if there is a cycle in the first place
    vector<int> arc_count(g.size()+1, 0);
    for (size_t i=1; i<g.size()+1; ++i) {
        for (std::list<size_t>::iterator jt = g.arcs_[i].begin(); jt != g.arcs_[i].end(); ++jt) {
            ++arc_count[i];
            --arc_count[*jt];
        }
    }
    for (vector<int>::iterator it = arc_count.begin(); it != arc_count.end(); ++it) {
        if (*it) {
            return vector<int>(1, -1); // no cycle, return { -1 }
        }
    }
    // there is a cycle, find it
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
