#include "levenshtein.h"

template<class T>
T min(T a, T b, T c)
{
    return std::min(std::min(a, b), c);
}

// --- Levenshein distance, two columns (Wagner-Fischer) ---

int levenshtein_distance(const std::string &s, const std::string &t)
{
    size_t n = s.length();
    size_t m = t.length();
    if (n == 0) return m;
    if (m == 0) return n;
    std::vector<std::vector<int> > d = {   // two-column matrix for first substring of string s
        std::vector<int>(m+1),
        std::vector<int>(m+1) };

    for (size_t i=0; i<n+1; ++i) {
        for (size_t j=0; j<m+1; ++j) {
            if (i == 0) {
                d[i%2][j] = j;
            } else if (j == 0) {
                d[i%2][j] = i;
            } else if (s[i-1] == t[j-1]) {
                d[i%2][j] = d[(i-1)%2][j-1];
            } else {
                d[i%2][j] = min(d[(i-1)%2][j-1] + 1,
                                d[(i-1)%2][j] + 1,
                                d[i%2][j-1] + 1);
            }
        }
    }
    int r = d[n%2][m];
    return r;
}

// --- Hirschberg algorithm ---

std::string hirschberg(const std::string &s, size_t l, size_t r, const std::string &t, size_t x, size_t y)
{
    if (r-l+1 == 0) {
        std::string prescr;
        for (size_t i=x-1; i<y; ++i) {
            prescr += "A "+std::to_string(i+1)+" "+t[i]+"\n";
        }
        return prescr;
    } else if (r-l+1 == 1) {
    // elementary case
        if (y-x+1 == 0) {
            return "D "+std::to_string(l)+" "+s[l-1]+"\n";
        }
        if (y-x+1 == 1) {
            if (s[l-1] == t[x-1]) {
                return "";
            } else {
                return "R "+std::to_string(l)+" "+t[x-1]+"\n";
            }
        } else {
            // look for char in t[x:y]
            size_t j = -1;
            for (size_t i=x-1; i<y; ++i) {
                if (s[l-1] == t[i]) {
                    j = i;
                    break;
                }
            }
            if (j+1) {
                // *A*
                std::string prescr;
                for (size_t i=x-1; i<j; ++i) {
                    prescr += "A "+std::to_string(i+1)+" "+t[i]+"\n";
                }
                for (size_t i=j+1; i<y; ++i) {
                    prescr += "A "+std::to_string(i+1)+" "+t[i]+"\n";
                }
                return prescr;
            } else {
                std::string prescr;
                for (size_t i=x-1; i<j; ++i) {
                    prescr += "A "+std::to_string(i+1)+" "+t[i]+"\n";
                }
                prescr += "R "+std::to_string(j+1)+" "+t[j]+"\n";
                for (size_t i=j+1; i<y; ++i) {
                    prescr += "A "+std::to_string(i+1)+" "+t[i]+"\n";
                }
                return prescr;
            }
        }
    }
    size_t c = l+(r-l)/2;   // point of spliting string s into two substrings
    size_t m = y-x+1;       // length of current substring of string t
                            // (x-1) - shift of current substring of t

    std::vector<std::vector<int> > dl = {   // two-column matrix for first substring of string s
        std::vector<int>(m+1),
        std::vector<int>(m+1) };

    for (size_t i=l-1; i<=c; ++i) {
        for (size_t j=0; j<m+1; ++j) {
            if (i == l-1) {
                dl[i%2][j] = j;
            } else if (j == 0) {
                dl[i%2][j] = i-(l-1);
            } else if (s[i-1] == t[(x-1)+j-1]) {  // note: the only actual call to the strings
                dl[i%2][j] = dl[(i-1)%2][j-1];
            } else {
                dl[i%2][j] = min(dl[(i-1)%2][j-1] + 1,
                                dl[(i-1)%2][j] + 1,
                                dl[i%2][j-1] + 1);
            }
        }
    }

    std::vector<std::vector<int> > dr = {   // two-column matrix for second substring of string s
        std::vector<int>(m+1),
        std::vector<int>(m+1) };

    for (size_t i=r+1; i>c; --i) {
        for (int j=m; j>=0; --j) {
            if (i == r+1) {
                dr[i%2][j] = m-j;
            } else if (j == int(m)) {
                dr[i%2][j] = r-i+1;
            } else if (s[i-1] == t[(x-1)+j]) {  // note: the only actual call to the strings
                dr[i%2][j] = dr[(i+1)%2][j+1];
            } else {
                dr[i%2][j] = min(dr[(i+1)%2][j+1] + 1,
                                dr[(i+1)%2][j] + 1,
                                dr[i%2][j+1] + 1);
            }
        }
    }

    int split = 0; // index of last symbol in first substring of new divide of t [1..len]
    for (size_t i=1; i<=m; ++i) {
        if (dl[c%2][i] + dr[(c+1)%2][i] <
            dl[c%2][split] + dr[(c+1)%2][split])
        split = i;
    }
    split = split + x - 1; // actual index (in terms of strings) is shifted

    /* ~~~ Debug ~~~
    std::cerr << "============\nSplitting to\n";
    for (size_t i=l-1; i<c; ++i) std::cerr << s[i];
    std::cerr << " ";
    for (size_t i=c; i<r; ++i) std::cerr << s[i];
    std::cerr << "\n";
    for (size_t i=x-1; i<split; ++i) std::cerr << t[i];
    std::cerr << " ";
    for (size_t i=split; i<y; ++i) std::cerr << t[i];
    std::cerr << "\n";*/

    return hirschberg(s, l, c, t, x, split) + hirschberg(s, c+1, r, t, split+1, y);
}

int hirschberg_d(const std::string &s, size_t l, size_t r, const std::string &t, size_t x, size_t y)
{
    if (r-l+1 == 0) {
        return y-x+1;
    } else if (r-l+1 == 1) {
    // elementary case
        if (y-x+1 == 0) {
            return 1;
        }
        if (y-x+1 == 1) {
            if (s[l-1] == t[x-1]) {
                return 0;
            } else {
                return 1;
            }
        } else {
            // look for char in t[x:y]
            size_t j = -1;
            for (size_t i=x-1; i<y; ++i) {
                if (s[l-1] == t[i]) {
                    j = i;
                    break;
                }
            }
            if (j+1) {
                return y-x;
            } else {
                return y-x+1;
            }
        }
    }
    size_t c = l+(r-l)/2;   // point of spliting string s into two substrings
    size_t m = y-x+1;       // length of current substring of string t
                            // (x-1) - shift of current substring of t

    // left part
    std::vector<std::vector<int> > dl = {   // two-column matrix for first substring of string s
        std::vector<int>(m+1),
        std::vector<int>(m+1) };

    for (size_t i=l-1; i<=c; ++i) {
        for (size_t j=0; j<m+1; ++j) {
            if (i == l-1) {
                dl[i%2][j] = j;
            } else if (j == 0) {
                dl[i%2][j] = i-(l-1);
            } else if (s[i-1] == t[(x-1)+j-1]) {  // note: the only actual call to the strings
                dl[i%2][j] = dl[(i-1)%2][j-1];
            } else {
                dl[i%2][j] = min(dl[(i-1)%2][j-1] + 1,
                                dl[(i-1)%2][j] + 1,
                                dl[i%2][j-1] + 1);
            }
        }
    }

    // right part
    std::vector<std::vector<int> > dr = {   // two-column matrix for second substring of string s
        std::vector<int>(m+1),
        std::vector<int>(m+1) };

    for (size_t i=r+1; i>c; --i) {
        for (int j=m; j>=0; --j) {
            if (i == r+1) {
                dr[i%2][j] = m-j;
            } else if (j == int(m)) {
                dr[i%2][j] = r-i+1;
            } else if (s[i-1] == t[(x-1)+j]) {  // note: the only actual call to the strings
                dr[i%2][j] = dr[(i+1)%2][j+1];
            } else {
                dr[i%2][j] = min(dr[(i+1)%2][j+1] + 1,
                                dr[(i+1)%2][j] + 1,
                                dr[i%2][j+1] + 1);
            }
        }
    }

    int split = 0; // index of last symbol in first substring of new divide of t [1..len]
    for (size_t i=1; i<=m; ++i) {
        if (dl[c%2][i] + dr[(c+1)%2][i] <
            dl[c%2][split] + dr[(c+1)%2][split])
        split = i;
    }
    split = split + x - 1; // actual index (in terms of strings) is shifted

    return hirschberg_d(s, l, c, t, x, split) + hirschberg_d(s, c+1, r, t, split+1, y);
}

std::string prescription(const std::string &s, const std::string &t)
{
    return hirschberg(s, 1, s.length(), t, 1, t.length());
}

size_t hirschberg_distance(const std::string &s, const std::string &t)
{
    return hirschberg_d(s, 1, s.length(), t, 1, t.length());
}
