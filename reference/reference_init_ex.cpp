#include <utility>
#include <iostream>
#include <sstream>
using namespace std;


struct S {
    int mi;
    const pair<int, int>& mp;
};

void foo(int){}

struct A{
    int nk;
};
struct B : A{
    int n;
    operator int&() { return n; }
};

B bar(){ return B();}
B bar_t(B& br){return br;}

extern int& ext_r;

int main(){
    int n = 1;
    int& r1 = n;
    const int& cr(n);
    volatile int& cv{n};
    int& r2 = r1;
    int& r3 = const_cast<int&>(cr);

    void (&rf)(int) = foo;
    int ar[3];
    int (&ra)[3] = ar;

    B b;
    A& base_ref = b;
    int& converted_ref = b;

    const int& cref = 1;
    int&& rref = 1;
    const A& cref2 = bar();
    A&& rref2 = bar();
    A&& rref3 = bar_t(b);

    int&& xref = static_cast<int&&>(n);
    double&& copy_ref = n;
    S a {1, {2,3}};
    S *p = new S{1, {2,3}};
    cout << p->mp.first << p->mp.second << endl;
}
