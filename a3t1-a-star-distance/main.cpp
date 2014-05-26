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
    ifstream fin;
    fin.open(argv[1]);
    string s;
    getline(fin, s, '\0');
    fin.close();

    string t;
    fin.open(argv[2]);
    getline(fin, t, '\0');
    fin.close();

    s.insert(s.begin(), '\0');
    t.insert(t.begin(), '\0');

    cout << edit_distance(s, t) << endl;

    return 0;
}
