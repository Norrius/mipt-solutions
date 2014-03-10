#include "palindrome.h"
#include <iostream>

std::string palindrome(std::string s) {
    size_t n = s.length();

    int **d = new int*[n]; // main array: d[i][j] = max len of palindrome in s[i:j+1]
    for (size_t i=0; i<n; ++i) d[i] = new int[i+1];
    int **t = new int*[n]; // transition array: -1 for top, 1 for right, 0 for diagonal (match)
    for (size_t i=0; i<n; ++i) t[i] = new int[i+1];

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

    for (size_t i=n-1, j=0; j<=i; )
        switch (t[i][j]) {
        case 0:
            palindrome.insert(palindrome.length()/2, (i==j?d[i][j]:2), s[i]);
            --i; ++j;
            break;
        case -1: --i; break;
        case  1: ++j; break;
    }

    for (size_t i=0; i<n; ++i) delete d[i]; delete d;
    for (size_t i=0; i<n; ++i) delete t[i]; delete t;

    return palindrome;
}
