#include "lissq.h"

namespace ns_lissq {

struct extended_vector {
    const std::vector<int> *a;

    extended_vector(const std::vector<int> *a)
    : a(a)
    {}

    const int operator[](size_t n) const {
        if (n == neg_inf) {
            return neg_inf;
        } else if (n == inf) {
            return inf;
        } else {
            return (*a)[n];
        }
    }
};

class Comparator {
    const extended_vector *a;
public:
    Comparator(const extended_vector *a)
        : a(a) {}
    bool operator()(const int &x, const int &i) {
        return x<(*a)[i];
    }
};
}

void lissq(const std::vector<int> &data, std::list<int> &lis) {
    using namespace ns_lissq;
    extended_vector a(&data);
    size_t n = data.size();
    std::vector<int> d(n+1, inf);
    d[0] = neg_inf;
    std::vector<int> p(n, neg_inf);
    int max = 0;
    Comparator comparator(&a);

    for (size_t i=0; i<n; ++i) {
        int j = std::upper_bound(d.begin(), d.end(), a[i], comparator)-d.begin();
        if (a[d[j-1]] < a[i] && a[i] < a[d[j]]) {
            d[j] = i;
            p[i] = d[j-1];
            if (a[d[max]] < a[d[j]]) {
                max = j;
            }
        }
    }

    lis.clear();
    for (int i = d[max]; i != neg_inf; i = p[i]){
        lis.push_front(a[i]);
    }
}

