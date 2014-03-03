#include <string>

template<class T>
T min(T a, T b, T c)
{
    return std::min(std::min(a, b), c);
}

/*
struct edit
{
    int type;
    int pos;
};*/

// --- Levenshein distance, recursive ---

int d(std::string s, size_t n, std::string t, size_t m)
{
    if (n == 0) return m;
    if (m == 0) return n;
    
    if (s[n-1] == t[m-1]) {
        return d(s, n-1, t, m-1);
    } else {
        return min(d(s, n-1, t, m-1) + 1,
                   d(s, n-1, t, m) + 1,
                   d(s, n, t, m-1) + 1);
    }
}

int levenshtein_distance_r(std::string s, std::string t)
{
    return d(s, s.length(), t, t.length());
}

// --- Levenshein distance, full matrix (Wagner-Fischer) ---

int levenshtein_distance_m(std::string s, std::string t)
{
    size_t n = s.length();
    size_t m = t.length();
    if (n == 0) return m;
    if (m == 0) return n;
    int **d = new int*[n+1];
    for (size_t i=0; i<n+1; ++i)
        d[i] = new int[m+1];

    for (size_t i=0; i<n+1; ++i) {
        for (size_t j=0; j<m+1; ++j) {
            if (i == 0) {
                d[i][j] = j;
            } else if (j == 0) {
                d[i][j] = i;
            } else if (s[i-1] == t[j-1]) {
                d[i][j] = d[i-1][j-1];
            } else {
                d[i][j] = min(d[i-1][j-1] + 1,
                              d[i-1][j] + 1,
                              d[i][j-1] + 1);
            }
        }
    }
    std::cout << "    ";
    for (size_t i=0; i<n+1; ++i) {
        std::cout << s[i] << ' ';
    }
    std::cout << "\n  ";
    for (size_t j=0; j<m+1; ++j) {
        if (j) std::cout << t[j-1] << ' ';
        for (size_t i=0; i<n+1; ++i)
            std::cout << d[i][j] << ' ';
        std::cout << std::endl;
    }
    int r = d[n][m];
    for (size_t i=0; i<n+1; ++i)
        delete[] d[i];
    delete[] d;
    return r;
}

// --- Levenshein distance, two columns ---

int levenshtein_distance(std::string s, std::string t)
{
    size_t n = s.length();
    size_t m = t.length();
    if (n == 0) return m;
    if (m == 0) return n;
    int **d = new int*[2];
    for (size_t i=0; i<2; ++i)
        d[i] = new int[m+1];

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
    delete[] d[0];
    delete[] d[1];
    delete[] d;
    return r;
}

// --- Hirschberg algorithm ---

std::string p(std::string s, size_t l, size_t r, std::string t, size_t x, size_t y)
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
            return "D "+std::to_string(l)+"\n";
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
    
    // left part
    int **dl = new int*[2];     // two-column matrix for first substring of string s
    for (size_t i=0; i<2; ++i)
        dl[i] = new int[m+1];

    for (size_t i=l-1; i<=c; ++i) {
        for (size_t j=0; j<m+1; ++j) {
            if (i == 0) {
                dl[i%2][j] = j;
            } else if (j == 0) {
                dl[i%2][j] = i;
            } else if (s[i-1] == t[(x-1)+j-1]) {  // note: the only actual call to the strings
                dl[i%2][j] = dl[(i-1)%2][j-1];
            } else {
                dl[i%2][j] = min(dl[(i-1)%2][j-1] + 1,
                                dl[(i-1)%2][j] + 1,
                                dl[i%2][j-1] + 1);
            }
        }
    }

    /*for (size_t j=0; j<m+1; ++j)
        std::cout << dl[0][j] << ' ' << dl[1][j] << '\n';*/

    // right part
    int **dr = new int*[2];     // two-column matrix for second substring of string s
    for (size_t i=0; i<2; ++i)
        dr[i] = new int[m+1];

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

    /*int *dm = new int[m];

    for (size_t i=0; i<m; ++i) {
        dm[i] = dl[((r-l+1)/2)%2][i+1] + dr[(c+1)%2][i];
        std::cout << dm[i] << '\n';
    }*/

    int split = 0; // index of last symbol in first substring of new divide of t [1..len]
    for (size_t i=1; i<m; ++i) {
        if (dl[c%2][i] + dr[(c+1)%2][i] <
            dl[c%2][split] + dr[(c+1)%2][split])
        split = i;
    }
    split = split + x - 1; // actual index in terms of strings is shifted
//    std::cout << split << ' ' << dl[c%2][split] + dr[(c+1)%2][split] << std::endl;

    delete[] dl[0];
    delete[] dl[1];
    delete[] dl;
    delete[] dr[0];
    delete[] dr[1];
    delete[] dr;

    /*std::cout << std::endl;
    for (size_t j=0; j<m+1; ++j)
        std::cout << dr[0][j] << ' ' << dr[1][j] << '\n';
    */
    // std::cerr << "completed\n";
    // std::string result = /**/ + "R " + std::to_string(c) + " " +  + /**/;
    return p(s, l, c, t, x, split) + p(s, c+1, r, t, split+1, y);
}

std::string prescription(std::string s, std::string t)
{
    return p(s, 1, s.length(), t, 1, t.length());
}
