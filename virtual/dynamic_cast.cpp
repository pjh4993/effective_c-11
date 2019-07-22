#include <iostream>

using namespace std;

struct V {
    virtual void f() {};
};

struct A : virtual V {};
struct B : virtual V {
    B(V* v, A* a){
        dynamic_cast<B*>(v);
        dynamic_cast<V*>(a);
    }
};

struct D : A,B{
    D(): B(static_cast<A*>(this), this) {}
};

struct Base{
    virtual ~Base(){}  
};

struct Derived : Base {
    virtual void name() {}
};

int main(){
    D d;
    A &a = d;
    D& new_d = dynamic_cast<D&>(a);
    B& new_b = dynamic_cast<B&>(a);

    Base* b1 = new Base;
    if(Derived* d = dynamic_cast<Derived*>(b1)){
        cout << "downcast from b1 to d" << endl;
        d->name();
    }
    Base *b2 = new Derived;
    if(Derived* d = dynamic_cast<Derived*>(b2)){
        cout << "downcast from b2 to d" << endl;
        d->name();
    }
    delete b1;
    delete b2;
}
