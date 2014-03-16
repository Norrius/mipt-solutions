#include "hashtable.h"

// = = = = = = Entry = = = = = =

Basket::Basket(){}

Basket::Basket(t_hash index, const std::string &key, const std::string &value)
    :index(index)
    ,entries(std::list<std::pair<std::string, std::string> >(1,std::pair<std::string, std::string>(key, value)))
{}

bool operator==(const Basket &l, const Basket &r)
{
    return l.index == r.index;
}
bool operator==(const Basket &list, const t_hash &h)
{ // required to use std::find
    return list.index == h;
}

// = = = = = HashTable = = = = =

HashTable::HashTable()
    :size_(0)
{}

HashTable::~HashTable(){}

t_hash HashTable::hash(const std::string &value)
{
    return value.length();
}

size_t HashTable::size()
{
    return size_;
}
bool HashTable::empty()
{
    return !size_;
}

bool HashTable::insert(const std::string &key, const std::string &value)
{
    t_hash h = hash(key);
    std::vector<Basket>::iterator it_v = std::find(table_.begin(), table_.end(), h);
    if (it_v != table_.end()) {
        std::list<std::pair<std::string, std::string> >::iterator it_l;
        for (it_l = it_v->entries.begin(); it_l != it_v->entries.end(); ++it_l) {
            if (it_l->first == key) {
                return false;
            }
        }
        (*it_v).entries.push_back(std::pair<std::string, std::string>(key, value));
        ++size_;
        return true;
    } else {
        table_.push_back(Basket(h, key, value));
        ++size_;
        return true;
    }
}

HashTable::iterator HashTable::find(const std::string &key)
{
    t_hash h = hash(key);
    std::vector<Basket>::iterator it_v = std::find(table_.begin(), table_.end(), h);
    if (it_v != table_.end()) {
        std::list<std::pair<std::string, std::string> >::iterator it_l;
        for (it_l = it_v->entries.begin(); it_l != it_v->entries.end(); ++it_l) {
            if (it_l->first == key) {
                return HashTable::iterator(it_v, it_l);
            }
        }
        return end();
    } else {
        return end();
    }
}

std::string &HashTable::operator[](const std::string &key)
{
    return *find(key);
}

bool HashTable::erase(const std::string &key)
{
    t_hash h = hash(key);
    std::vector<Basket>::iterator it_v = std::find(table_.begin(), table_.end(), h);
    std::list<std::pair<std::string, std::string> >::iterator it_l;
    bool found = false;
    if (it_v != table_.end()) {
        for (it_l = it_v->entries.begin(); it_l != it_v->entries.end(); ++it_l) {
            if (it_l->first == key) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    } else {
        return false;
    }
    assert(HashTable::iterator(it_v, it_l) != end());
    it_v->entries.erase(it_l);
    if (it_v->entries.empty()) {
        table_.erase(it_v);
    }
    --size_;
    return true;
}

// = = = HashTable::iterator = = =

HashTable::iterator HashTable::begin()
{
    return HashTable::iterator(table_.begin(), table_.begin()->entries.begin());
}

HashTable::iterator HashTable::end()
{
    return HashTable::iterator(table_.end(), table_.end()->entries.begin());
}


HashTable::iterator::iterator(const std::vector<Basket>::iterator it_v,
                              const std::list<std::pair<std::string, std::string> >::iterator it_l)
    :it_v_(it_v)
    ,it_l_(it_l)
{}

HashTable::iterator &HashTable::iterator::operator++()
{ // prefix
    if (it_l_ != it_v_->entries.end()) {
        ++it_l_;
        if (it_l_ == it_v_->entries.end()) {
            ++it_v_;
            it_l_ = it_v_->entries.begin();
        }
    } else {
        ++it_v_;
        it_l_ = it_v_->entries.begin();
    }
    return *this;
}

HashTable::iterator &HashTable::iterator::operator++(int)
{ // postfix
    HashTable::iterator tmp(*this);
    operator++();
    return tmp;
}

HashTable::iterator &HashTable::iterator::operator--()
{ // prefix
    if (it_l_ != it_v_->entries.begin()) {
        --it_l_;
    } else {
        --it_v_;
        it_l_ = it_v_->entries.end();
        --it_l_;
    }
    return *this;
}

HashTable::iterator &HashTable::iterator::operator--(int)
{ // postfix
    HashTable::iterator tmp(*this);
    operator--();
    return tmp;
}

std::string &HashTable::iterator::operator*()
{
    return it_l_->second;
}
const std::string &HashTable::iterator::operator*() const
{
    return it_l_->second;
}

std::string *HashTable::iterator::operator->()
{
    return &it_l_->second;
}
const std::string *HashTable::iterator::operator->() const
{
    return &it_l_->second;
}

bool operator==(const HashTable::iterator& l, const HashTable::iterator& r)
{
    return (l.it_v_ == r.it_v_ && l.it_l_ == r.it_l_);
}
bool operator!=(const HashTable::iterator& l, const HashTable::iterator& r)
{
    return !(l==r);
}
