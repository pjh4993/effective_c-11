#include <iostream>
#include <cstdlib>

using namespace std;

int (*cate())[3]{
    cout << "o" << endl;
    return (int(*)[3])malloc(sizeof(int)*3);
};

struct C {int m;};

int main(void){
    int (*(*x[2])())[3];
    x[0] = cate;
    (*(x[0]))();
    x[0]();
    int C::*p = &C::m;
    C c = {7};
    cout << c.*p << endl;
    cout << sizeof(C) << endl;


}
