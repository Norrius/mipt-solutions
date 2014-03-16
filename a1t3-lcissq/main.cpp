#include <iostream>
#include "lcissq.h"
using namespace std;

int main() {
    int n, m, t;
    std::vector<int> a;
    std::vector<int> b;
    std::cin >> n;
    for (size_t i=0; i<n; ++i) {
        cin >> t;
        a.push_back(t);
    }
    std::cin >> m;
    for (size_t i=0; i<m; ++i) {
        cin >> t;
        b.push_back(t);
    }
    std::cout << lcissq(a, b) << std::endl;
    return 0;
}
