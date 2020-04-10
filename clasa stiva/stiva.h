#pragma once
#include <vector>
#include <iostream>

using namespace std;

// clasa stiva implementata prin liste inlantuite
class stiva {

    // clasa ajutatoare prin care memoram fiecare element din lista inlantuita
    class node {
        int info;
        node* prev;
    public:
        node();
        void setInfo(int x);
        int getInfo();
        void setPrev(node* x);
        node* getPrev();
    };


    int Size;
    node *varf;
    void insertBelow(int x);
public:
    stiva(); // constructor
    stiva(vector<int> v); // constructor cu parametru
    stiva(const stiva& x); // copy constructor
    ~stiva(); // destructor
    // overloaded operators
    friend istream& operator>>(istream& in, stiva& stk);
    friend ostream& operator<<(ostream& out, const stiva& stk);
    stiva& operator=(const stiva& x);
    bool operator==(const stiva& x) const;
    bool operator>(const stiva& x) const;
    bool operator<(const stiva& x) const;
    // functiile clasei
    void push(int x);
    int pop();
    int top();
    bool isEmpty();
    int getSize();
    void Reverse();


};

