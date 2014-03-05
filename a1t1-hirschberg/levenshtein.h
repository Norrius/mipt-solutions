#include <string>

template<class T>
T min(T a, T b, T c);

int levenshtein_distance(std::string s, std::string t);

std::string hirschberg(std::string s, size_t l, size_t r, std::string t, size_t x, size_t y);
std::string prescription(std::string s, std::string t);
int hirschberg_d(std::string s, size_t l, size_t r, std::string t, size_t x, size_t y);
size_t hirschberg_distance(std::string s, std::string t);
