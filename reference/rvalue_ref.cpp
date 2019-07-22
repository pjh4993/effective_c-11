#include <iostream>
#include <string>
#include <utility>
#include <typeinfo>
using namespace std;

void f(int& x){
    cout << "lvalue reference overload f(" << typeid(x).name() << ")" << endl;
}

void f(const int& x){
    cout << "lvalue reference to const overload f(" << typeid(x).name() << ")" << endl;
}



void f(int&& x){
    cout << "rvalue reference overload f(" << typeid(x).name() << ")" << endl;
}

int main(void){
    string s1 = "test";
    const string& r2 = s1 + s1;
    string&& r3 = s1 + s1;
    r3 += "Test";
    cout << r3 << endl;

    int i = 1;
    const int ci = 2;
    f(i);
    f(ci);
    f(3);
    f(i++);
    f(++i);
    f(move(i));
    int&& x = 1;
    f(x);
    f(move(x));
}
