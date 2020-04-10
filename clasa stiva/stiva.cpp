#include "stiva.h"
using namespace std;

/*
Fiecare variabila, nume de functie sau alte denumiri respecta capitalizarea camel case.
La acestea fac exceptie denumirile pentru care exista un keyword in c++, fiind scrise cu majuscula la inceput. ( int Size si void Reverse() )
*/


// constructor clasa ajutatoare
stiva::node::node() {
    info = 0;
    prev = 0;
};
// setters and getters
void stiva::node::setInfo(int x) {
    info = x;
};
int stiva::node::getInfo() {
    return info;
};
void stiva::node::setPrev(node* x) {
    prev = x;
};
stiva::node* stiva::node::getPrev() {
    return prev;
};


// constructor stiva. Initializeaza o stiva vida cu pointerul catre varful acesteia null.
stiva::stiva() {
    varf = new node;
    varf = NULL;
    Size = 0;
};
// constructor cu parametru. Primeste ca parametru un obiect de tip vector, elementul de pe pozitia 0 fiind varful stivei.
stiva::stiva(vector<int> v) {
    varf = new node;
    varf = NULL;
    Size = 0;
    // ultimul element adaugat in stiva trebuie sa fie varful acesteia, deci umplerea stivei se face de la capatul vectorului
    for (int i = v.size() - 1; i >= 0; i--)
        push(v[i]);
};
// copy constructor. Insereaza pe rand fiecare elemnt din stiva data ca parametru incepand din varf, rezultand intr o stiva inversata. Asadar, inversam la final stiva
stiva::stiva(const stiva& x) {
    varf = NULL;
    Size = 0;
    node* ptr = x.varf;
    while (ptr) {
        push(ptr->getInfo());
        ptr = ptr->getPrev();
    }
    Reverse();
};
// destructor. Se elemina fiecare element pe rand cu ajutorul functiei pop()
stiva::~stiva() {
    while (!isEmpty()) {
        pop();
    }

};
// functia push(). Creeaza un nou obiect de tip node care devine varful stivei (cu valoarea data prin parametru)
void stiva::push(int x) {
    Size++;
    node* ptr = new node;
    ptr->setInfo(x);
    ptr->setPrev(varf);
    varf = ptr;
};
// functia pop().
int stiva::pop() {
    Size--;
    int i = -1;
    if (varf) {
        i = varf->getInfo();
        varf = varf->getPrev();
        // se apeleaza automat destructorul fostului varf
    }
    return i;
};
int stiva::top() {
    return varf->getInfo();
};

// daca pointerul catre varful stivei nu este nul, inseamanca ca stiva contine cel putin un element
bool stiva::isEmpty() {
    if (varf) return false;
    else return true;
};
int stiva::getSize() {
    return Size;
};

// functie ajutatoare pentru functia Reverse(). Functioneaza ca un push() la celalalt capat
void stiva::insertBelow(int x) {
    if (Size == 0) push(x);
    else {
        int temp = top();
        pop();
        insertBelow(x);
        push(temp);
    }
};

// functia Reverse(). Functie recursiva care tine in stiva functiei toate valorile stivei obiectului pe care se aplica functia si le insereaza in oridine inversa
void stiva::Reverse() {
    if (Size > 0) {
        int temp = top();
        pop();
        Reverse();
        insertBelow(temp);
    }
};


// overloaded operator>>. Se citeste de la tastatura un obiect de tip stiva, urmand indicatiile din consola. 
// Prima data este introdus dimensiunea stivei, apoi elementele acesteia. Primul element este varful stivei, al doilea este elementul de sub varf, etc.
istream& operator>>(istream& in, stiva& stk) {
    int x, s;
    cout << "Size: ";
    in >> s;
    cout << "Stack: ";
    for (int i = 0; i < s; i++) {
        in >> x;
        stk.push(x);
    }
    // pentru ca elemetele au fost introduse in stiva in ordine inversa, aceasta trebuie inversata
    stk.Reverse();
    return in;
};

// overloaded operator<<. Se afiseaza stiva, incepand cu varful acesteia.
ostream& operator<<(ostream& out, const stiva& stk) {
    // folosim un pointer auxiliar pentru a nu modifica adresa varfului stivei
    stiva::node* ptr = stk.varf;
    while (ptr) {
        out << ptr->getInfo();
        ptr = ptr->getPrev();
        cout << " ";
    }
    cout << endl;
    return out;
};

// overloaded operator=. Duplicarea continutului celui de al doilea operand in primul obiect.
stiva& stiva::operator=(const stiva& x) {
    if (this == &x) {
        return *this;
    }
    // stergerea varfului este suficienta pentru a sterge toata stiva, se declanseaza o reactie in lant la nivelul clasei node, in ceea ce priveste stergearea elementelor
    delete varf;
    this->Size = x.Size;
    this->varf = x.varf;
    return *this;
};

// overloaded operator==. Returneaza true daca cele doua stive care se compara au aceleasi valori in aceeasi oridine
bool stiva::operator==(const stiva& x) const {
    if (varf == x.varf)return true;
    if (Size == x.Size)
    {
        node* ptr1 = varf;
        node* ptr2 = x.varf;
        while (ptr1) {
            if (ptr1->getInfo() != ptr2->getInfo()) return false;
            ptr1 = ptr1->getPrev();
            ptr2 = ptr2->getPrev();
        }
        return true;
    }
    return false;
};

// overloaded operator> & overloaded operator<. Compara 2 stive element cu element incepand cu varful. Prima stiva ce are pe aceeasi pozitie un element de valoare mai mare, este mai mare.
// O valoarea oricare este mai mare decat un element null. Stiva: 2 3 < Stiva: 2 3 0
bool stiva::operator>(const stiva& x) const {
    node* ptr1 = varf;
    node* ptr2 = x.varf;
    // pointeri auxiliari pentru a nu modifica pointerii catre varfurile stivei
    if (ptr1->getInfo() >= ptr1->getInfo()) {
        while (ptr1->getInfo() == ptr2->getInfo()) {
            ptr1 = ptr1->getPrev();
            ptr2 = ptr2->getPrev();
            if (ptr1 == 0 && ptr2 == 0)return false; // daca ambele stive sunt egale, nici una nu este mai mare
            if (ptr1 == 0) return false; // a doua stiva inca mai are elemente, deci este mai mare
            if (ptr2 == 0) return true; // prima stiva inca mai are elemente, deci este mai mare
        }
        if (ptr1->getInfo() > ptr2->getInfo())return true;
        return false;
    }
    return false;
};
bool stiva::operator<(const stiva& x) const {
    node* ptr1 = varf;
    node* ptr2 = x.varf;
    // pointeri auxiliari pentru a nu modifica pointerii catre varfurile stivei
    if (ptr1->getInfo() <= ptr1->getInfo()) {
        while (ptr1->getInfo() == ptr2->getInfo()) {
            ptr1 = ptr1->getPrev();
            ptr2 = ptr2->getPrev();
            if (ptr1 == 0 && ptr2 == 0)return false; // daca ambele stive sunt egale, nici una nu este mai mica
            if (ptr1 == 0) return true; // a doua stiva inca mai are elemente, deci este mai mare
            if (ptr2 == 0) return false; // prima stiva inca mai are elemente, deci este mai mare
        }
        if (ptr1->getInfo() < ptr2->getInfo())return true;
        return false;
    }
    return false;
};
