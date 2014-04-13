#include <iostream>
#include "graph.h"
#include "dfs.h"

using namespace std;

void test_1()
{ // tree
    Graph graph;

    graph.addArc(0, 1);
    graph.addArc(0, 2);
    graph.addArc(1, 3);
    graph.addArc(1, 4);
    graph.addArc(1, 5);
    graph.addArc(4, 6);
    graph.addArc(4, 7);
    graph.addArc(5, 8);

    dfs(graph);
}

void test_2()
{ // has cycles
    Graph graph;

    graph.addArc(0, 1);
    graph.addArc(0, 2);
    graph.addArc(2, 3);
    graph.addArc(3, 4);
    graph.addArc(4, 5);
    graph.addArc(1, 6);
    graph.addArc(6, 7);
    graph.addArc(7, 6);
    graph.addArc(8, 9);
    graph.addArc(9, 10);
    graph.addArc(10, 8);

    dfs(graph);
}

void test_3()
{ // acyclic graph
    Graph graph;

    graph.addArc(7, 11);
    graph.addArc(7, 8);
    graph.addArc(5, 11);
    graph.addArc(3, 8);
    graph.addArc(3, 10);
    graph.addArc(8, 9);
    graph.addArc(11, 2);
    graph.addArc(11, 9);
    graph.addArc(11, 10);

    std::vector<int> s = dfs(graph);
    for (std::vector<int>::reverse_iterator it = s.rbegin(); it != s.rend(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
}

void test_mccme()
{
    int n, m, a, b;
    std::cin >> n >> m;
    Graph g;
    for (int i=0; i<m; ++i) {
        cin >> a >> b;
        g.addArc(a, b);
    }
    std::vector<int> s = dfs(g);
    if (s[0] != -1) {
        std::cout << "Yes" << std::endl;
        for (std::vector<int>::reverse_iterator it = s.rbegin(); it != s.rend(); ++it) {
            std::cout << *it << ' ';
        }
        std::cout << std::endl;
    } else {
        std::cout << "No" << std::endl;
    }
}

int main()
{
    test_mccme();

    return 0;
}

