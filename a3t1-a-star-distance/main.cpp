#include <string>
#include <iostream>
#include <fstream>
#include "diff.h"

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 3) {
        return -1;
    }
    ifstream fin1(argv[1]);
    string s;
    getline(fin1, s, '\0');
    fin1.close();

    ifstream fin2(argv[2]);
    string t;
    getline(fin2, t, '\0');

    s.insert(0, "\0");
    t.insert(0, "\0");

    cout << edit_distance(s, t) << endl;

    return 0;
}
