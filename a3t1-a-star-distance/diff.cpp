#include "diff.h"

template <typename T>
T min(const T &a, const T &b, const T &c) {
    return std::min(std::min(a, b), c);
}

class hasher {
public:
    size_t operator()(const index_pair &index) const {
        return index.i*index.i + index.j;
    }
};

int edit_distance(const string &s, const string &t) {
    heap<hasher> front_heap;

    front_heap.push(make_pair(index_pair(0, 0), 0));

    size_t i,j;
    size_t n = s.size();
    size_t m = t.size();
    weighted_index res;
    while (!front_heap.empty()) {
        weighted_index min = front_heap.pop(s, t);

        i = min.first.i;
        j = min.first.j;

        if (i+1 < n && s[i+1] != t[j]) {
            index_pair to(i+1, j);
            int weight = min.second + 1;
            front_heap.update(make_pair(to, weight));
        }

        if (j+1 < m && s[i] != t[j+1]) {
            index_pair to(i, j+1);
            int weight = min.second + 1;
            front_heap.update(make_pair(to, weight));
        }

        if (i+1 < n && j+1 < m) {
            index_pair to(i+1, j+1);
            if (s[i+1] == t[j+1]) {
                int weight = min.second;
                front_heap.update(make_pair(to, weight));
            } else {
                int weight = min.second + 1;
                front_heap.update(make_pair(to, weight));
            }
        }

        if (min.first == index_pair(n-1, m-1)) {
            res = min;
        }
    }

    return res.second;
}
