#include "test.h"

void test_random() {
    string word;
    int n = 2+rand()%10;
    for (int i=0; i<n; ++i) {
        word += 'A'+rand()%26;
    }

    map<char, vector<int> > letters;
    for (int i=0; i<n; ++i) {
        letters[word[i]].push_back(i);
    }

    Graph g(n);

    int k = 20+rand()%100;
    vector<vector<char> > cubes(k, vector<char>(N, 0));

    char c;
    for (int i=0; i<k; ++i) {
        for (int j=0; j<N; ++j) {
            c = 'A'+rand()%26;
            cubes[i][j] = c;
            for (int v=0; v<letters[c].size(); ++v) {
                g.edges[letters[c][v]].push_back(i);
//                g.edges[i].push_back(k);
            }
        }
    }

    vector<pair<int, int> > result = assign_cubes(g, k);
    if (result.size() == n) {
        for (int i=0; i<n; ++i) {
            assert(find(cubes[result[i].first].begin(), cubes[result[i].first].end(), word[result[i].second]) != cubes[result[i].first].end());
        }
    }
}

void test() {
    srand(time(0));

    for (int u=0; u<1000; ++u) test_random();
}
