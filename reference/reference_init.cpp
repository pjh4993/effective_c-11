#include <iostream>

using namespace std;

struct A{};
struct B : A{
    public:
        int i;
        B(){};
        B(const A&){};
        B(int m){
            i = m;
        };
        B(B* d){
            i = d->i;
        };
};
B f(){
    B&& b = B(1);
    return b;
}
B af(){
    B* d = new B(0);
    return d;
}

int main(void){
    const A& rca2 = f();
    A&& rra = af();

    cout << "rca2 : "<< static_cast<B>(rca2).i << endl;
    cout << "rra : "<< static_cast<B>(rra).i << endl;
    int i2  = 42;
    int&& rri = static_cast<int&&>(i2);
}
