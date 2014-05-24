#ifndef HEAP_H
#define HEAP_H
#include <utility>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <assert.h>
using namespace std;

class index_pair {
public:
    size_t i;
    size_t j;

    index_pair(){}
    index_pair(int i, int j) :
        i(i),
        j(j)
    {}

    bool operator==(const index_pair &other) const {
        return (i == other.i && j == other.j);
    }
};

typedef pair<index_pair, int> weighted_index;

template <typename Hash>
class heap {
    class node {
    public:
        size_t heap_index;
        int counter;
        bool real;

        node(){}
        node(size_t heap_index, int counter, bool real) :
            heap_index(heap_index),
            counter(counter),
            real(real)
        {}
    };

    vector<weighted_index> data;
    unordered_map<index_pair, node, Hash> data_ref;

public:
    heap(){}

    size_t size() {
        return data.size();
    }

    bool empty() {
        return data.empty();
    }

    bool push(const weighted_index &value) {
        bool success = data_ref.insert( make_pair(value.first, node(data.size(), 1, true)) ).second;
        if (success) {
            data.push_back(value);
            heapify_up(data.size()-1);
        }
        return success;
    }

    weighted_index pop(const string &s, const string &t) {
        weighted_index top = data.front();
        // find a corresponding entry in the reference
        auto front = data_ref.find(data.front().first);
        front->second.real = false;
        // find an entry to swap with
        auto back = data_ref.find(data.back().first);

        swap(data.front(), data.back());
        swap(front->second.heap_index, back->second.heap_index);
        data.pop_back(); // extract min from heap

        size_t i = front->first.i; // position in s
        size_t j = front->first.j; // position in t

        if (i == 0 || j == 0 || s[i] == t[j]) {
            data_ref.erase(front); // on final pass, extract reference as well
        }

        heapify_down(0);
        return top;
    }

    void heapify_up(size_t heap_index) {
        auto current_it = data_ref.find(data[heap_index].first);
        size_t parent_index = (heap_index - 1)/2;
        while (heap_index > 0 && data[heap_index].second < data[parent_index].second) {
            auto parent_it = data_ref.find(data[parent_index].first);
            swap(data[heap_index], data[parent_index]);
            swap(current_it->second.heap_index, parent_it->second.heap_index);

            heap_index = parent_index;
            parent_index = (heap_index - 1)/2;
        }
    }

    void heapify_down(size_t heap_index) {
        auto current_it = data_ref.find(data[heap_index].first);
        while (heap_index < data.size()) {
            size_t left_index = heap_index * 2 + 1;
            size_t right_index = heap_index * 2 + 2;
            if (right_index < data.size()) {
                if (data[left_index].second <= data[right_index].second &&
                    data[left_index].second < data[heap_index].second) {
                    // heapify down left
                    auto left_it = data_ref.find(data[left_index].first);
                    assert(left_it != data_ref.end());
                    swap(data[heap_index], data[left_index]);
                    swap(current_it->second.heap_index, left_it->second.heap_index);
                    heap_index = left_index;
                } else if (data[left_index].second >= data[right_index].second &&
                           data[right_index].second < data[heap_index].second) {
                    // heapify down right
                    auto right_it = data_ref.find(data[right_index].first);
                    assert(right_it != data_ref.end());
                    swap(data[heap_index], data[right_index]);
                    swap(current_it->second.heap_index, right_it->second.heap_index);
                    heap_index = right_index;
                } else {
                    return;
                }
            } else if (left_index < data.size() && // only left son exists
                       data[left_index].second < data[heap_index].second) {
                // heapify down left
                auto left_it = data_ref.find(data[left_index].first);
                assert(left_it != data_ref.end());
                swap(data[heap_index], data[left_index]);
                swap(current_it->second.heap_index, left_it->second.heap_index);
                heap_index = left_index;
                return;
            } else {
                return;
            }
        }
    }

    bool update(const weighted_index &suggested) {
        auto suggested_it = data_ref.find(suggested.first);
        if (suggested_it == data_ref.end()) {
            push(suggested);
            return true;
        } else {
            ++suggested_it->second.counter;
            if (suggested_it->second.real) {
                // check if the suggested variat is better
                if (data[suggested_it->second.heap_index].second > suggested.second) {
                    data[suggested_it->second.heap_index].second = suggested.second;
                    heapify_up(suggested_it->second.heap_index);
                    return true;
                } else {
                    if (suggested_it->second.counter == 3) {
//                        data_ref.erase(suggested_it);
                    }
                    return false;
                }
            }
        }
    }
};

#endif // HEAP_H

/*
                    cout << "~~~~~~~~~~~\n";
                    for (auto i : data_ref) {
                        cout << i.first.i << ' ' << i.first.j << endl;
                    }
*/
