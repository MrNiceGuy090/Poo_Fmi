//compilat cu MSVC++ 14.25 (Visual C++ 2019)
#include "Map.h"
#include <iostream>

using namespace std;

class IncrementSteps {
    int steps;
public:
    IncrementSteps(int steps_);
    int operator()(int x) { return x + steps; }
};
IncrementSteps::IncrementSteps(int steps_) : steps(steps_) {};

int increment(int x) {
    return x + 20;
}

int main()
{
    Map<string, int> dict;
    dict.add("val1", 6);
    dict.add("val2", 7);
    dict.add("val1", 8);
    dict.add("val3", 10);
    dict.delete_("val2");
    dict.delete_("none");

    IncrementSteps incrementu(10);
    dict.transform(increment);
    dict.transform(incrementu);
    cout << "dict: " << endl;
    cout << dict<< dict.getPairNum() << endl;

    cout << dict.hasKey("val1") <<" "<<dict.hasKey("val2")<< endl;
    cout << dict.getKeyValue("val1") << " "<<dict["val1"]<<" "<< endl;
    cout << dict["none"] << endl;

    Map<string, int> dict2; 
    dict2.add("val12", 7);
    dict2 = dict;
    dict.delete_("val1");
    cout << "dict2: " << endl;
    cout << dict2;


    Map<string, int> dict3(dict2);
    dict2.delete_("val1");
    cout << "dict3: " << endl << dict3;


}
