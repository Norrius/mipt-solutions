#include "bridges.h"

namespace ns_bridges {
    vector<int> visited;
    vector<int> t_in;
    vector<int> f_up;
    size_t time_;

    int component_count;
    stack<int> vert_stack;
    stack<edge> edge_stack;
}

void bridges_dfs(vector<edge> &result, Graph &graph, int current, int parent=0) {
    using namespace ns_bridges;

    visited[current] = gray;
    t_in[current] = f_up[current] = time_++;
    list<size_t>::iterator it;
    for (it = graph.arcs_[current].begin(); it != graph.arcs_[current].end(); ++it) {
        int pointee = *it;
        if (pointee == parent) {
            continue;
        } else if (visited[pointee]) {
            f_up[current] = min(f_up[current], t_in[pointee]);
        } else {
            bridges_dfs(result, graph, pointee, current);
            f_up[current] = min(f_up[current], f_up[pointee]);
            if (t_in[current] < f_up[pointee]) {
                result.push_back(edge(current, pointee));
            }
        }
    }
}

void findBridges(Graph &graph, vector<edge> &result) {
    using namespace ns_bridges;

    int n1 = graph.size()+1;
    visited = vector<int>(n1, 0);
    t_in = vector<int>(n1, 0);
    f_up = vector<int>(n1, 0);
    result.empty();
    time_ = 0;

    for (size_t subgraph_head=1; subgraph_head < n1; ++subgraph_head) {
        if (!visited[subgraph_head]) {
            bridges_dfs(result, graph, subgraph_head);
        }
    }
}

void div_dfs(vector<int> &result, Graph &graph, int current, int parent=0) {
    using namespace ns_bridges;

    visited[current] = gray;
    t_in[current] = f_up[current] = time_++;
    list<size_t>::iterator it;
    int children = 0;
    for (it = graph.arcs_[current].begin(); it != graph.arcs_[current].end(); ++it) {
        int pointee = *it;
        if (pointee == parent) {
            continue;
        } else if (visited[pointee]) {
            f_up[current] = min(f_up[current], t_in[pointee]);
        } else {
            div_dfs(result, graph, pointee, current);
            ++children;
            f_up[current] = min(f_up[current], f_up[pointee]);
            if (parent != 0 && t_in[current] <= f_up[pointee]) {
                if (find(result.begin(), result.end(), current) == result.end()) {
                    result.push_back(current);
                }
            }
        }
    }
    if (parent == 0 && children > 1) {
        result.push_back(current);
    }
}

void findDivPoints(Graph &graph, vector<int> &result) {
    using namespace ns_bridges;

    int n1 = graph.size()+1;
    visited = vector<int>(n1, 0);
    t_in = vector<int>(n1, 0);
    f_up = vector<int>(n1, 0);
    result.empty();
    time_ = 0;

    for (size_t subgraph_head=1; subgraph_head < n1; ++subgraph_head) {
        if (!visited[subgraph_head]) {
            div_dfs(result, graph, subgraph_head);
        }
    }
}


void biconnected_edges_dfs(vector<int> &result, Graph &graph, int current, int parent=0) {
    using namespace ns_bridges;

    visited[current] = gray;
    t_in[current] = f_up[current] = time_++;
    vert_stack.push(current);
    list<size_t>::iterator it;
    for (it = graph.arcs_[current].begin(); it != graph.arcs_[current].end(); ++it) {
        int pointee = *it;
        if (pointee == parent) {
            continue;
        } else if (visited[pointee]) {
            f_up[current] = min(f_up[current], t_in[pointee]);
        } else {
            biconnected_edges_dfs(result, graph, pointee, current);
            vert_stack.push(current);
            f_up[current] = min(f_up[current], f_up[pointee]);
            if (t_in[current] < f_up[pointee]) {
//                result.push_back(edge(current, pointee));
                ++component_count;
                vert_stack.pop();
                while (vert_stack.top() != current) {
                    result[vert_stack.top()] = component_count;
                    vert_stack.pop();
                };
            }
        }
    }
    if (parent == 0) {
        ++component_count;
        while (!vert_stack.empty()) {
            result[vert_stack.top()] = component_count;
            vert_stack.pop();
        }
    }
}

void findBiconnectedEdgeComponents(Graph &graph, vector<int> &result) {
    using namespace ns_bridges;

    int n1 = graph.size()+1;
    visited = vector<int>(n1, 0);
    t_in = vector<int>(n1, 0);
    f_up = vector<int>(n1, 0);
    vert_stack.empty();
    component_count = 0;
    result = vector<int>(n1, 0);
    time_ = 0;

    for (size_t subgraph_head=1; subgraph_head < n1; ++subgraph_head) {
        if (!visited[subgraph_head]) {
            biconnected_edges_dfs(result, graph, subgraph_head);
        }
    }
}
