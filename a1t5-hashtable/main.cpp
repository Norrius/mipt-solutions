#include <iostream>
#include <string>
#include "hashtable.h"
using namespace std;

int main() {
    HashTable table(1);

/**/cout << "add and display size" << endl;
    cout << "size: " << table.size() << endl;
    table.insert("key", "string");
    cout << "size: " << table.size() << endl;
    table.insert("key1", "string2");
    cout << "size: " << table.size() << endl;
    table.insert("key2", "string3");
    cout << "size: " << table.size() << endl;
    table.insert("key3", "string4r");
    cout << "size: " << table.size() << endl;
    table.insert("key_long", "string5");
    cout << "size: " << table.size() << endl;
    table.insert("key_dup", "string6");
    cout << "size: " << table.size() << endl;
    table.insert("key_dup", "string7");
    cout << "size: " << table.size() << endl;
    cout << endl;

/**/cout << "iterate forward" << endl;
    for (HashTable::iterator it = table.begin(); it != table.end(); ++it) {
        cout << *it << endl;
    }
    cout << endl;

/**/cout << "iterate backward" << endl;
    for (HashTable::iterator it = table.end(); it != table.begin(); ) {
        --it;
        cout << *it << endl;
    }
    cout << endl;

/**/cout << "search" << endl;
    cout << *table.find("key") << endl;
    cout << *table.find("key1") << endl;
    cout << *table.find("key2") << endl;
    cout << *table.find("key3") << endl;
    cout << *table.find("key_long") << endl;
    cout << *table.find("key_dup") << endl;
    cout << endl;

/**/cout << "access via [] and ." << endl;
    cout << table["key"] << ' ' << table["key"].length() << endl;
    cout << table["key3"] << ' ' << table["key3"].length() << endl;
    table["key2"] = "mod_string";
    cout << table["key2"] << endl;
    cout << endl;

/**/cout << "access via find() and ->" << endl;
    cout << *table.find("key") << ' ' << table.find("key")->length() << endl;
    cout << *table.find("key3") << ' ' << table.find("key3")->length() << endl;
    cout << endl;

/**/cout << "look for element" << endl;
    cout << (table.find("key")!=table.end()?"found":"not found") << endl;
    cout << (table.find("key_dup")!=table.end()?"found":"not found") << endl;
    cout << (table.find("key0")!=table.end()?"found":"not found") << endl;
    cout << (table.find("key_nonexistent")!=table.end()?"found":"not found") << endl;
    cout << endl;

/**/cout << "delete element" << endl;
    table.erase("key");
    for (HashTable::iterator it = table.begin(); it != table.end(); ++it) {
        cout << *it << endl;
    }
    cout << endl;
    table.erase("key3");
    for (HashTable::iterator it = table.begin(); it != table.end(); ++it) {
        cout << *it << endl;
    }
    cout << endl;

    return 0;
}
