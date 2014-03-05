#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <random>
#include <stdexcept>
#include "levenshtein.h"
#include "time_measure.h"

void test_one_edit()
{
    const int maxtests = 10000;
    const int avg_length = 50;

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine engine(seed);
    std::uniform_int_distribution<int> dist_len(avg_length*0.5, avg_length*1.5);
    std::uniform_int_distribution<char> dist_char('a', 'z');

    for (int i=0; i<maxtests; ++i) {
        std::string s(dist_len(engine), 0);
        for (size_t i=0; i<s.length(); ++i) s[i] = dist_char(engine);
        std::string t(s);
        std::uniform_int_distribution<int> dist_num(0, s.length()-1);
        int n = dist_num(engine);
        if (t[n] != 'z') t[n]++;
        else t[n] = 'a';

        int levnsht = levenshtein_distance(s, t);
        int hirschb = hirschberg_distance(s, t);

//        std::clog << levnsht << ' ' << hirschb << std::endl;
        if (levnsht != hirschb) {
            throw std::runtime_error(std::string("Test failed in ")+std::string(__func__));
        }
    }
}

void test_distance()
{
    const int maxtests = 10000;
    const int avg_length = 50;

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine engine(seed);
    std::uniform_int_distribution<int> dist_len(avg_length*0.5, avg_length*1.5);
    std::uniform_int_distribution<char> dist_char('a', 'z');

    for (int i=0; i<maxtests; ++i) {
        std::string s(dist_len(engine), 0);
        for (size_t i=0; i<s.length(); ++i) s[i] = dist_char(engine);
        std::string t(dist_len(engine), 0);
        for (size_t i=0; i<t.length(); ++i) t[i] = dist_char(engine);

        int levnsht = levenshtein_distance(s, t);
        int hirschb = hirschberg_distance(s, t);

//        std::clog << levnsht << ' ' << hirschb << std::endl;
        if (levnsht != hirschb) {
            throw std::runtime_error(std::string("Test failed in ")+std::string(__func__));
        }
    }
}

void test_tolkien()
{
    Clock clock;
    std::ifstream fin("lor.txt");
    std::ifstream fin2("lor_edited.txt");
    std::string data = "";
    std::string buffer;
    while (fin >> buffer) {
        data += buffer+" ";
    }
    std::string data2 = "";
    while (fin2 >> buffer) {
        data2 += buffer+" ";
    }
    std::cout << "Sample size: " << data.length() << std::endl;
    std::cout << levenshtein_distance(data, data2) << std::endl;
    std::cout << "Levenshtein: " << clock.elapsed() << "ms" << std::endl;
    std::cout << prescription(data, data2) << std::endl;
    std::cout << "Hirschberg: " << clock.elapsed() << "ms" << std::endl;
}

void test()
{
    try {
        test_one_edit();
        test_distance();
        test_tolkien();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
