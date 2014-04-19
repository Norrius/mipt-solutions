#include "condensation.h"

// = = = Kosaraju = = =

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

// = = = = Tarjan = = = =

stack<int> cond_stack;
vector<int> visited;
vector<int> lowlink;
size_t t_in;
size_t component_count;

void tarjan_dfs(Graph &g, int v, vector<int> &condensation) {
    visited[v] = gray;
    lowlink[v] = t_in++;
    cond_stack.push(v);
    bool root = true;

    for (list<size_t>::iterator child = g.arcs_[v].begin(); child != g.arcs_[v].end(); ++child) {
        if (!visited[*child]) {
            tarjan_dfs(g, *child, condensation);
        }
        if (lowlink[v] > lowlink[*child]) {
            lowlink[v] = lowlink[*child];
            root = false;
        }
    }

    if (root) {
        ++component_count;
//        condensation[v] = component_count;
//        lowlink[v] = g.arcs_.size();
        int u;
        do {
            u = cond_stack.top();
            condensation[u] = component_count;
            lowlink[u] = g.arcs_.size(); // a.k.a. "the very big number"
            cond_stack.pop();
        } while (u != v);
    }

    visited[v] = black;
}

int condensation_tarjan(Graph &graph, vector<int> &condensation) {
    cond_stack.empty();
    condensation = vector<int>(graph.arcs_.size(), 0);
    visited = vector<int>(graph.arcs_.size(), white);
    lowlink = vector<int>(graph.arcs_.size(), 0);
    component_count = 0;
    t_in = 0;

    // start a dfs
    for (size_t vertex=1; vertex < graph.arcs_.size(); ++vertex) {
        if (!visited[vertex]) {
            tarjan_dfs(graph, vertex, condensation);
        }
    }

    return component_count;
}
