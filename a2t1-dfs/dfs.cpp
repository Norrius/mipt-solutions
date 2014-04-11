#include "dfs.h"

std::vector<int> dfs(Graph &graph)
{
    std::stack<std::pair<size_t, std::list<size_t>::iterator> > stack;
    std::vector<int> visited(graph.arcs_.size(), 0);
    std::vector<int> sorted;

    for (size_t subgraph_head=1 /* begin with index 1 */; subgraph_head < graph.arcs_.size(); ++subgraph_head) {
        if (!visited[subgraph_head]) {
            stack.push(std::make_pair(subgraph_head, graph.arcs_[subgraph_head].begin()));
            size_t current;
            std::list<size_t>::iterator last_child;
            while (!stack.empty()) {
                current = stack.top().first;
                last_child = stack.top().second;

                if (visited[current] == 0) {
                    visited[current] = 2;
                }
                if (last_child != graph.arcs_[current].end()) {
                    if (visited[*last_child] == 0) {
                        stack.top().second++;
                        stack.push(std::make_pair(*last_child, graph.arcs_[*last_child].begin()));
                    } else if (visited[*last_child] == 2) {
                        return std::vector<int>(1, -1);
                    } else {
                        stack.top().second++;
                    }
                } else {
                    sorted.push_back(current);
                    visited[current] = 1;
                    stack.pop();
                }
            }
        }
    }

    return sorted;
}
