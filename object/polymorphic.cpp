#include <iostream>
#include <typeinfo>

struct Base1{
    virtual ~Base1(){}
};
struct Derived1 : Base1 {
    ~Derived1(){};
};

struct Base2{

};
struct Derived2 : Base2{

};

int main(){
    Derived1 obj1;
    Derived2 obj2;

    Base1& b1 = obj1;
    Base2& b2 = obj2;
    std::cout << "Expression type of b1: " << typeid(decltype(b1)).name() << ' '
        << "Expression type of b2: " << typeid(decltype(b2)).name() << '\n'
        << "Object type of b1: " << typeid(b1).name() << ' '
        << "Object type of b2: " << typeid(b2).name() << '\n'
        << "size of b1: " << sizeof b1 << ' '
        << "size of b2: " << sizeof b2 << '\n';
}
