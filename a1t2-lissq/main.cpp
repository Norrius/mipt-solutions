#include <iostream>
#include <list>
#include "lissq.h"
using namespace std;

int main() {
    int t;
    std::vector<int> data;
    while (cin >> t) {
        data.push_back(t);
    }

    list<int> lis;

    lissq(data, lis);

    for (auto i : lis) cout << i << ' ';
    cout << endl;
    return 0;
}
