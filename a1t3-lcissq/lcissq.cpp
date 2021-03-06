#include "lcissq.h"

int lcissq(const std::vector<int> &a, const std::vector<int> &b) {
    int n = a.size();
    int m = b.size();

    std::vector<std::vector<int> > d(n);
    for (int i=0; i<2; ++i) {
        d[i] = std::vector<int>(m);
    }

    int best;

    for (int i=0; i<n; ++i) {
        best = 0;
        for (int j=0; j<m; ++j) {
            d[i%2][j] = (i>0?d[(i-1)%2][j]:0);
            if (a[i] == b[j] && d[i%2][j] <= best) {
                d[i%2][j] = best + 1;
            } else if (a[i] > b[j] && d[i%2][j] > best) {
                best = d[i%2][j];
            }
        }
    }

    return *(std::max_element(d[(n-1)%2].begin(), d[(n-1)%2].end()));
}
