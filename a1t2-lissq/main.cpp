#include <iostream>
#include <list>
#include "lissq.h"
using namespace std;

int main() {
    size_t n;
    cin >> n;
    std::vector<int> data(n);
    for (size_t i=0; i<n; ++i) cin >> data[i];

    list<int> lis;

    lissq(data, lis);

    for (auto i : lis) cout << i << ' ';
    cout << endl;
    return 0;
}
