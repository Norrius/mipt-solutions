#include "diff.h"

template <typename T>
T min(const T &a, const T &b, const T &c) {
    return std::min(std::min(a, b), c);
}

class hasher {
public:
    size_t operator()(const index_pair &index) const {
        return index.i*179425423 + index.j;
    }
};

int edit_distance(const string &s, const string &t) {
    heap<hasher> front_heap;

    front_heap.update(make_pair(index_pair(0, 0), 0));

    size_t i,j;
    size_t n = s.size();
    size_t m = t.size();
    weighted_index res;
#ifdef STATISTICS
    int u=0;
    int m_f=0;
    int m_w=0;
#endif
    while (!front_heap.empty()) {
        weighted_index min = front_heap.pop(s, t);

        i = min.first.i;
        j = min.first.j;

        if (i+1 < n && s[i+1] != t[j]) {
            index_pair to(i+1, j);
            int weight = min.second + potential(min.first, to) + 1;
            front_heap.update(make_pair(to, weight));
        }

        if (j+1 < m && s[i] != t[j+1]) {
            index_pair to(i, j+1);
            int weight = min.second + potential(min.first, to) + 1;
            front_heap.update(make_pair(to, weight));
        }

        if (i+1 < n && j+1 < m) {
            index_pair to(i+1, j+1);
            if (s[i+1] == t[j+1]) {
                int weight = min.second + potential(min.first, to);
                front_heap.update(make_pair(to, weight));
            } else {
                int weight = min.second + potential(min.first, to) + 1;
                front_heap.update(make_pair(to, weight));
            }
        }

        if (min.first == index_pair(n-1, m-1)) {
            res = min;
            break;
        }

#ifdef STATISTICS
        if (m_f < front_heap.size()) m_f = front_heap.size();
        int w = abs((int)min.first.i-(int)min.first.j);
        if (m_w < w) m_w = w;
        ++u; if (u%5000 == 0) cout << "\rIteration: " << u << " heap size: " << front_heap.size()
                                   << " hastable size: " << front_heap.ref_size()
                                   << " diversion: " << w << "   ";
#endif
    }
#ifdef STATISTICS
    cout << "\rSample size: " << s.size() << "+" << t.size() << " iterations: " << u
         << " max hashtable size: " << m_f << " max diversion: " << m_w << "\n";
#endif

    return res.second - potential(index_pair(0, 0), res.first);
}

int potential(index_pair a, index_pair b) {
    int p_a = abs((int)a.i - (int)a.j);
    int p_b = abs((int)b.i - (int)b.j);
    return p_b - p_a;
}
