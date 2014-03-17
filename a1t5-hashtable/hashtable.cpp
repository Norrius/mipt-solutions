#include "hashtable.h"

// = = = = = = Entry = = = = = =

Basket::Basket(){}

Basket::Basket(t_hash index, const std::string &key, const std::string &value)
    :index(index)
    ,entries(std::list<std::pair<std::string, std::string> >(1,std::pair<std::string, std::string>(key, value)))
{}

bool operator==(const Basket &list, const t_hash &h)
{ // required to use std::find
    return list.index == h;
}

// = = = = = HashTable = = = = =

HashTable::HashTable(size_t basket_count)
    :table_(basket_count)
    ,size_(0)
    ,basket_count_(basket_count)
{
    for (std::vector<Basket>::iterator it = table_.begin(); it != table_.end(); ++it) {
        it->index = it-table_.begin();
    }
}

HashTable::~HashTable(){}

t_hash HashTable::hash(const std::string &value)
{
    return value.length()%(basket_count_?basket_count_:1);
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
    std::vector<Basket>::iterator it_v = table_.begin() + h;
    std::list<std::pair<std::string, std::string> >::iterator it_l;
    for (it_l = it_v->entries.begin(); it_l != it_v->entries.end(); ++it_l) {
        if (it_l->first == key) {
            return false;
        }
    }
    it_v->entries.push_back(std::pair<std::string, std::string>(key, value));
    ++size_;

    if (size_ > 4*basket_count_) {
        realloc();
    }

    return true;
}

HashTable::iterator HashTable::find(const std::string &key)
{
    t_hash h = hash(key);
    std::vector<Basket>::iterator it_v = table_.begin() + h;
    std::list<std::pair<std::string, std::string> >::iterator it_l;
    for (it_l = it_v->entries.begin(); it_l != it_v->entries.end(); ++it_l) {
        if (it_l->first == key) {
            return HashTable::iterator(*this, it_v, it_l);
        }
    }
    return end();
}

std::string &HashTable::operator[](const std::string &key)
{
    return *find(key);
}

bool HashTable::erase(const std::string &key)
{
    t_hash h = hash(key);
    std::vector<Basket>::iterator it_v = table_.begin() + h;
    std::list<std::pair<std::string, std::string> >::iterator it_l;
    bool found = false;

    for (it_l = it_v->entries.begin(); it_l != it_v->entries.end(); ++it_l) {
        if (it_l->first == key) {
            found = true;
            break;
        }
    }
    if (!found) return false;

    assert(HashTable::iterator(*this, it_v, it_l) != end());
    it_v->entries.erase(it_l);
    if (it_v->entries.empty()) {
        table_.erase(it_v);
    }
    --size_;
    return true;
}

void HashTable::realloc()
{
    ++basket_count_;
    std::vector<Basket> table__(basket_count_);
    std::swap(table_, table__);
    size_ = 0;
    std::vector<Basket>::iterator it_v;
    std::list<std::pair<std::string, std::string> >::iterator it_l;
    for (std::vector<Basket>::iterator it = table_.begin(); it != table_.end(); ++it) {
        it->index = it-table_.begin();
    }

    for (it_v = table__.begin(), it_l = it_v->entries.begin(); it_v != table__.end(); ) {
        insert(it_l->first, it_l->second);
        // increment
        ++it_l;
        while (it_l == it_v->entries.end() && it_v != table__.end()) {
            ++it_v;
            it_l = it_v->entries.begin();
        }
    }
}

// = = = HashTable::iterator = = =

HashTable::iterator HashTable::begin()
{
    std::vector<Basket>::iterator it_v;
    std::list<std::pair<std::string, std::string> >::iterator it_l;
    it_v = table_.begin();
    it_l = it_v->entries.begin();
    while (it_l == it_v->entries.end() && it_v != table_.end()) {
        ++it_v;
        it_l = it_v->entries.begin();
    }
    return HashTable::iterator(*this, it_v, it_l);
}

HashTable::iterator HashTable::end()
{
    std::vector<Basket>::iterator it_v;
    std::list<std::pair<std::string, std::string> >::iterator it_l;
    it_v = table_.end();
    --it_v;
    it_l = it_v->entries.end();
    while (it_l == it_v->entries.begin() && it_v != table_.begin()) {
        --it_v;
        it_l = it_v->entries.end();
    }
    return HashTable::iterator(*this, it_v, it_l);
}

HashTable::iterator::iterator(const HashTable &parent,
                              const std::vector<Basket>::iterator it_v,
                              const std::list<std::pair<std::string, std::string> >::iterator it_l)
    :parent_(parent)
    ,it_v_(it_v)
    ,it_l_(it_l)
{}

HashTable::iterator &HashTable::iterator::operator++()
{ // prefix
    // it's user's concern if the iterator was already at .end()
    ++it_l_;
    std::vector<Basket>::const_iterator last = parent_.table_.end(); --last;
    while (it_l_ == it_v_->entries.end() && it_v_ != last) {
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
    } else { // once again, it's user's concern if they decide to use -- on .begin()
        while (it_l_ == it_v_->entries.begin() && it_v_ != parent_.table_.begin()) {
            --it_v_;
            it_l_ = it_v_->entries.end();
        }
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

std::string &HashTable::iterator::getKey()
{
    return it_l_->first;
}

bool operator==(const HashTable::iterator& l, const HashTable::iterator& r)
{
    return (l.it_v_ == r.it_v_ && l.it_l_ == r.it_l_);
}
bool operator!=(const HashTable::iterator& l, const HashTable::iterator& r)
{
    return !(l==r);
}
