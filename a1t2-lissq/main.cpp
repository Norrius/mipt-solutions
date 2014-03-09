#include <iostream>
#include <list>
#include "lissq.h"
using namespace std;

int main() {
    size_t n;
    cin >> n;
    int a[n];
    for (size_t i=0; i<n; ++i) cin >> a[i];

    list<int> v = lissq(a, n);

    for (auto i : v) cout << i << ' ';
    cout << endl;
    return 0;
}
