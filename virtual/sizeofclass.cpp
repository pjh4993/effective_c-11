#include <iostream>
using namespace std;

class A
{
    public:
        virtual void fun() = 0;
};
void A::fun(){
    cout << "haha" << endl;
}

class B
{
    public:
        void fun();
};

int main()
{
    B b1;
    cout << alignof(A) << alignof(B) << endl;
    int a = sizeof(A), b = sizeof(B);
    if (a == b) cout << "a == b";
    else if (a > b) cout << "a > b";
    else cout << "a < b";
    return 0;
}

