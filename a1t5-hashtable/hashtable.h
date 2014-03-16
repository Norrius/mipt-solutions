#pragma once
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <assert.h>

typedef int t_hash;

struct Basket {
    t_hash index;
    std::list<std::pair<std::string, std::string> > entries;
    Basket();
    Basket(t_hash index, const std::string &key, const std::string &value);
};

bool operator==(const Basket &l, const Basket &r);
bool operator==(const Basket &list, const t_hash &h);

class HashTable
{
    std::vector<Basket> table_;
    size_t size_;

    t_hash hash(const std::string &value);

public:
    HashTable();
    ~HashTable();

    class iterator
    {
        std::vector<Basket>::iterator it_v_;
        std::list<std::pair<std::string, std::string> >::iterator it_l_;
    public:
        iterator(const std::vector<Basket>::iterator it_v,
                 const std::list<std::pair<std::string, std::string> >::iterator it_l);
        iterator &operator++();
        iterator &operator++(int);
        iterator &operator--();
        iterator &operator--(int);
        std::string &operator*();
        const std::string &operator*() const;
        std::string *operator->();
        const std::string *operator->() const;

        friend bool operator==(const iterator& l, const iterator& r);
        friend bool erase(const std::string &key);
    };
    iterator begin();
    iterator end();

    size_t size();
    bool empty();
    bool insert(const std::string &key, const std::string &value);
    iterator find(const std::string &key);
    std::string &operator[](const std::string &key);
    bool erase(const std::string &key);

};

bool operator==(const HashTable::iterator& l, const HashTable::iterator& r);
bool operator!=(const HashTable::iterator& l, const HashTable::iterator& r);
