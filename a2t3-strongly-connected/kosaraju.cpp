#include <cstddef>
#include <vector>
#include <stack>
#include <iostream> /*DEBUG*/
#include "graph.h"

using namespace std;

enum vertex_colour {
    white,
    gray,
    black
};

int condensation_kosaraju(Graph &g, vector<int> &condensation) {

    // first dfs
    stack<pair<size_t, list<size_t>::iterator> > stack;
    vector<int> visited(g.arcs_.size(), 0);
    vector<int> sorted;

    for (size_t subgraph_head=1; subgraph_head < g.arcs_.size(); ++subgraph_head) {
        if (!visited[subgraph_head]) {
            stack.push(make_pair(subgraph_head, g.arcs_[subgraph_head].begin()));
            size_t current;
            list<size_t>::iterator last_child;
            while (!stack.empty()) {
                current = stack.top().first;
                last_child = stack.top().second;

                if (visited[current] == white) {
                    visited[current] = gray;
                }
                if (last_child != g.arcs_[current].end()) {
                    if (visited[*last_child] == white) {
                        stack.top().second++;
                        stack.push(make_pair(*last_child, g.arcs_[*last_child].begin()));
                    } else {
                        stack.top().second++;
                    }
                } else {
                    sorted.push_back(current);
                    visited[current] = black;
                    stack.pop();
                }
            }
        }
    }

    // invert graph
    Graph h = g.getInverted();

    // second dfs (on inverted graph)
    stack.empty();
    for (vector<int>::iterator it = visited.begin(); it != visited.end(); ++it) {
        *it = white;
    }

    vector<int>::reverse_iterator it;
    int component_count;

    for (it=sorted.rbegin(), component_count=0; it != sorted.rend(); ++it) {
        size_t subgraph_head = *it;
        if (!visited[subgraph_head]) {
            ++component_count;
            stack.push(make_pair(subgraph_head, h.arcs_[subgraph_head].begin()));
            size_t current;
            list<size_t>::iterator last_child;
            while (!stack.empty()) {
                current = stack.top().first;
                last_child = stack.top().second;

                if (visited[current] == white) {
                    visited[current] = gray;
                }
                if (last_child != h.arcs_[current].end()) {
                    if (visited[*last_child] == white) {
                        stack.top().second++;
                        stack.push(make_pair(*last_child, h.arcs_[*last_child].begin()));
                    } else {
                        stack.top().second++;
                    }
                } else {
                    visited[current] = black;
                    condensation[current] = component_count;
                    stack.pop();
                }
            }
        }
    }
    return component_count;
}
