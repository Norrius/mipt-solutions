#include "path.h"

vector<int> ford_bellman(Graph &g) {
    int n = g.edges.size();
    for (int start = 0; start < n; ++start) {
        vector<double> dist(n, 0);
        vector<int> prev(n, -1);

        dist[start] = 1;

        int last;
        for (int i=0; i<n; ++i) {
            last = -1;
            for (int v=0; v<n; ++v) {
                for (int u=0; u<n; ++u) {
                    if (dist[g.edges[v][u].to] < dist[v] * g.edges[v][u].weight) {
                        dist[g.edges[v][u].to] = dist[v] * g.edges[v][u].weight;
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
            reverse(path.begin(), path.end());
            return path;
        } else {
            // if last == -1, this means that the n-th iteration
            // made no changes to the path matrix, so there is no
            // negative weight (greater than 1 cost) path
            return vector<int>(1, -1);
        }
    }
}

void get_path(vector<vector<int> > &phase, vector<int> &path, int from, int to) {
    if (phase[from][to] == -1) {
        path.push_back(from);
    } else {
        get_path(phase, path, from, phase[from][to]);
        get_path(phase, path, phase[from][to], to);
    }
}

vector<int> floyd_warshall(MGraph g) {
    int n = g.edges.size();
    vector<vector<int> > phase(n, vector<int>(n, -1));
    int entry;
    bool cycle = false;
    for (int k=0; k<n; ++k) {
        for (int i=0; i<n; ++i) {
            for (int j=0; j<n; ++j) {
                if (g.edges[i][j] < g.edges[i][k] * g.edges[k][j]) {
                    g.edges[i][j] = g.edges[i][k] * g.edges[k][j];
                    phase[i][j] = k;
                    if (i == j && g.edges[i][j] > 1) {
                        cycle = true;
                        entry = i;
                    }
                }
                if (cycle) break;
            }
            if (cycle) break;
        }
        if (cycle) break;
    }
    //int t;
    /*bool c = false;
    for (t=0; t<n; ++t) {
        if (g.edges[t][t] > 1) {
            c = true;
            break;
        }
    }*/
    if (cycle) {
        vector<int> path;
        get_path(phase, path, entry, entry);
        path.push_back(entry);
        return path;
    } else {
        return vector<int>(1, -1);
    }
}
