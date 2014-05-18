#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "graph.h"
#include "kuhn.h"
#include "test.h"
using namespace std;

void test_manual() {
    ifstream fin("cubes.in");
    string word;
    fin >> word;
    int n = word.size();
    map<char, vector<int> > letters;
    for (int i=0; i<n; ++i) {
        letters[word[i]].push_back(i);
    }

    int k;
    fin >> k;

    Graph g(word.size());

    char c;
    for (int i=0; i<k; ++i) {
        for (int j=0; j<N; ++j) {
            fin >> c;
            for (int v=0; v<letters[c].size(); ++v) {
                g.edges[letters[c][v]].push_back(i);
//                g.edges[i].push_back(k);
            }
        }
    }

    vector<pair<int, int> > cubes = assign_cubes(g, k);
    if (cubes.size() == n) {
        for (int i=0; i<n; ++i) {
            cout << cubes[i].first+1 << ' ' << word[cubes[i].second] << endl;
        }
    } else {
        cout << "No solution.\n";
    }
}

int main()
{
    test();

    return 0;
}
