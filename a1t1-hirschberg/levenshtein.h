#pragma once
#include <vector>
#include <string>

template<class T>
T min(T a, T b, T c);

int levenshtein_distance(const std::string &s, const std::string &t);

std::string hirschberg(const std::string &s, size_t l, size_t r, const std::string &t, size_t x, size_t y);
std::string prescription(const std::string &s, const std::string &t);
int hirschberg_d(const std::string &s, size_t l, size_t r, const std::string &t, size_t x, size_t y);
size_t hirschberg_distance(const std::string &s, const std::string &t);
