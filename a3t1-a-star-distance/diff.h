#pragma once
#include <string>
#include <limits>
#include "heap.h"
using namespace std;

const int infty = numeric_limits<int>::max();

int edit_distance(const string &s, const string &t);

int potential(index_pair a, index_pair b);
int remove_potentials(index_pair a, index_pair b, int weight);
