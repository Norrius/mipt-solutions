#pragma once
#include <string>
#include <limits>
#include "heap.h"
using namespace std;

const int infty = numeric_limits<int>::max();

int edit_distance(const string &s, const string &t);
