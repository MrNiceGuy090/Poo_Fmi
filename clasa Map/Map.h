#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <list> 
#include <stdexcept>
#include <assert.h>
using namespace std;

template <class K, class V> class Map {

    list<pair<K, V> >* dictionary;
   
public:
    Map();
    Map(const Map<K, V>& other);
    ~Map();
    void add(K x, V y);
    void delete_(K x);
    V getKeyValue(K x) const;
    int getPairNum() const;
    bool hasKey(K x)const;
    template <class F> void transform(F func);
    Map<K, V>& operator=(const Map<K, V>& other);
    V& operator[](K other);
    friend ostream& operator<< <>(ostream& os, const Map<K, V>& dictionar);
};
// destructor
template <class K, class V> Map<K, V>::~Map() {
    delete dictionary;
}

//basic constructor
template <class K, class V> Map<K, V>::Map() {
    try {
        dictionary = new list<pair<K, V>>;
    }
    catch (const bad_alloc& e) {
        cout << "List initialization failed: " << e.what() << endl;
    }
    catch (...) {
        cout << "List initialization failed: something went unexpected" << endl;
    };
    assert(dictionary != NULL);
};

//copy constructor
template <class K, class V> Map<K, V>::Map(const Map& other) {
    try {
        dictionary = new list<pair<K, V>>;
    }
    catch (const bad_alloc& e) {
        cout << "List initialization failed: " << e.what() << endl;
    }
    catch (...) {
        cout << "List initialization failed: something went unexpected" << endl;
    };
    assert(dictionary != NULL);

    for (typename list<pair<K, V> >::iterator it = other.dictionary->begin(); it != other.dictionary->end(); it++) {
        dictionary->push_back(*it);
    }
}


//add method
template <class K, class V> void Map<K, V>::add(K x, V y) {
    pair<K, V> pereche;
    pereche.first = x;
    pereche.second = y;
    // in for verificam daca exista deja cheia x, caz in care suprascriem valoarea
    for (typename list<pair<K, V> >::iterator it = dictionary->begin(); it != dictionary->end(); it++) {
        if (it->first == x) {
            it->second = y;
            return;
        }
    }
    // daca nu exista in deja cheia x, inseram perechea in dictionar
    dictionary->push_back(pereche);
};

//delete_ method
template <class K, class V> void Map<K, V>::delete_(K x) {
    pair<K, V> temp;
    // cauta cheia x in dictionar si memoreaza perechea cheie-valoare in temp
    for (typename list<pair<K, V> >::iterator it = dictionary->begin(); it != dictionary->end(); it++) {
        if (it->first == x) {
            temp.first = x;
            temp.second = it->second;
            break;
        }
    }
    // sterge perechea temp
    try {
        dictionary->remove(temp);
    }
    catch (...) {
        cout << "Can not delete the " << x << " key from Map";
    }
};

//getKeyValue method
template <class K, class V> V Map<K, V>::getKeyValue(K x)const {
    try {
        for (typename list<pair<K, V> >::iterator it = dictionary->begin(); it != dictionary->end(); it++) {
            if (it->first == x) {
                return it->second;
            }
        }
        throw "Key not found.";
    }
    catch (const char* e) {
        cout << "Error: " << e << " Returning empty value ";
        // returneaza un element de tip V initializat fara parametrii
        V err = V();
        return err;
    }

}

//getPairNum method
template <class K, class V> int Map<K, V>::getPairNum()const {
    return dictionary->size();
}

//hasKey method
template <class K, class V> bool Map<K, V>::hasKey(K x)const {
    for (typename list<pair<K, V> >::iterator it = dictionary->begin(); it != dictionary->end(); it++) {
        if (it->first == x) return true;
    }
    return false;
}

// functie-obiect, transform method
template <class K, class V> template <class F>
void Map<K, V>::transform(F func) {
    for (typename list<pair<K, V> >::iterator it = dictionary->begin(); it != dictionary->end(); it++) {
        it->second = func(it->second);
    }
}


//operator= overloading
template <class K, class V>
Map<K, V>& Map<K, V>::operator=(const Map<K, V>& other) {
    typename list< pair<K, V> >::iterator it1 = this->dictionary->begin();        //it1 iterator pentru this
    typename list< pair<K, V> >::iterator it2 = other.dictionary->begin();         //it2 iterator pentru other
    while (it1 != this->dictionary->end() && it2 != other.dictionary->end()) {    //parcurge simultan ambele liste si copiaza
        it1->first = it2->first;
        it1->second = it2->second;
        it1++; it2++;
    }
    if (this->dictionary->size() > other.dictionary->size()) {                    //daca dictionarul lui this este mai mare, sterge elementele ramase
        while (it1 != this->dictionary->end()) {
            it1 = this->dictionary->erase(it1);
        }
    }
    else if (this->dictionary->size() < other.dictionary->size()) {               //daca dictionarul lui other este mai mare, adauga in this elementele ramase
        while (it2 != other.dictionary->end()) {
            this->add(it2->first, it2->second);
            it2++;
        }
    }
    return *this;
}

//operator[] overloading
template <class K, class V>
V& Map<K, V>::operator[](K other) {
    try {
        for (typename list<pair<K, V> >::iterator it = dictionary->begin(); it != dictionary->end(); it++) {
            if (it->first == other)
                return it->second;
        }
        throw "Key not found.";
    }
    catch (const char* e) {
        cout << "Error: " << e <<" Returning empty value ";
        V err = V();
        return err;
    }
}

//operator<< overloading
template <class K, class V>
ostream& operator<<(ostream& os, const Map<K, V>& dictionar)
{
    for (typename list<pair<K, V> >::iterator it = dictionar.dictionary->begin(); it != dictionar.dictionary->end(); it++) {
        os << "key: " << it->first << ", value: " << it->second << endl;
    }
    return os;
}

#endif