#include <cassert>
#include <iostream>

using namespace std;


struct S{
    char c;
    float f;
    bool operator==(const S arg) const {
        return c == arg.c && f == arg.f;
    }
    /*operator for const object S*/
    bool operator==(const S arg) {
        return c == arg.c && f == arg.f;
    }

};

int main(void){
    assert(sizeof(S) == 8);
    S s1 = {'a',3.14};
    S s2 = s1;
    reinterpret_cast<char*>(&s1)[2] = 'b';
    assert(s1 == s2);
}
