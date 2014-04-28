#include "path.h"

vector<int> ford_bellman(Graph &g, int start) {
    int n = g.edges.size();
    vector<double> dist(n, 0);
    vector<int> prev(n, -1);

    dist[start] = 1;

    int last;
    for (int i=0; i<n; ++i) {
        last = -1;
        for (int v=0; v<n; ++v) {
            for (int u=0; u<n; ++u) {
                if (dist[g.edges[v][u].first] < dist[v] * g.edges[v][u].second) {
                    dist[g.edges[v][u].first] = dist[v] * g.edges[v][u].second;
                    prev[u] = v;
                    last = u;
                }
            }
        }
    }

    if (last != -1) {
        vector<int> path;
        for (int i=last; ; i=prev[i]) {
            path.push_back(i);
            if (i == last && path.size() > 1) break;
        }
        /*int start = last;
        for (int i=0; i<n; ++i) {
            start = prev[start];
        }
        for (int v=start; (v == start && path.size() > 1); v=prev[v]) {
            path.push_back(v);
        }
        path.push_back(start);*/
        reverse(path.begin(), path.end());
        return path;
    } else {
        return vector<int>(1, -1);
    }

    /*vector<int> path;
    while (j > 0) {
        path[j] = i;
        i = prev[i][j];
        --j;
    }*/

}
