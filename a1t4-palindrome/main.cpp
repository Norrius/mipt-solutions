#include "palindrome.h"
#include <iostream>
#include <string>

int main()
{
    std::string string;
    std::cin >> string;
    std::cout << palindrome(string) << std::endl;
    return 0;
}

