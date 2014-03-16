#include "palindrome.h"

std::string palindrome(std::string s) {
    size_t n = s.length();

    if (!n) return s;

    // main array: d[i][j] = max len of palindrome in s[i:j+1]
    std::vector<std::vector<int> > d(n, std::vector<int>(n));
    // transition array: -1 for top, 1 for right, 0 for diagonal (match)
    std::vector<std::vector<int> > t(n, std::vector<int>());
    for (std::vector<std::vector<int> >::iterator i=t.begin(); i!=t.end(); ++i) {
        *i = std::vector<int>(i-t.begin()+1);
    }

    for (size_t i=0; i<n; ++i) {
        for (size_t j=0; j<n-i; ++j) {
            if (i == 0) {
                d[j][j] = 1;
            } else if (i == 1) {
                if (s[i+j] == s[j]) {
                    d[i+j][j] = 2;
                    t[i+j][j] = 0;
                } else {
                    d[i+j][j] = 1;
                    t[i+j][j] = -1;
                }
            } else {
                if (s[i+j] == s[j]) {
                    d[i+j][j] = d[i+j-1][j+1] + 2;
                    t[i+j][j] = 0;
                } else {
                    if (d[i+j][j+1] > d[i+j-1][j]) {
                        d[i+j][j] = d[i+j][j+1];
                        t[i+j][j] = 1;
                    } else {
                        d[i+j][j] = d[i+j-1][j];
                        t[i+j][j] = -1;
                    }
                }
            }
        }
    }

    std::string palindrome;

    for (int i=n-1, j=0; j<=i; )
        switch (t[i][j]) {
        case 0:
            palindrome.insert(palindrome.length()/2, (i==j?d[i][j]:2), s[i]);
            --i; ++j;
            break;
        case -1: --i; break;
        case  1: ++j; break;
    }

    return palindrome;
}
