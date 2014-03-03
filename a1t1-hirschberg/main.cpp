#include <iostream>
#include <string>
#include "levenshtein.h"
#include "time.h"

int f(int n) {return n<2?1:f(n-1)+f(n-2);}

int main() {
    std::string a;
    std::string b;
    std::cin >> a;
    std::cin >> b;
    Clock clock;
    std::cout << prescription(a,b) << std::endl;
    std::cout << "Total time: " << clock.elapsed() << "ms " << std::endl;
}
