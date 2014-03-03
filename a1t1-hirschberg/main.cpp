#include <iostream>
#include <string>
#include "levenshtein.h"

int main() {
    std::string a;
    std::string b;
    std::cin >> a;
    std::cin >> b;
    // std::cout << levenshtein_distance_m(a, b) << std::endl;
    // std::cout << levenshtein_distance(a, b) << std::endl;
    std::cout << prescription(a,b) << std::endl;
}
