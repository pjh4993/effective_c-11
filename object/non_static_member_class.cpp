#include <iostream>
#include <typeinfo>

class member{
    public:
        member(){};
    private:
        int i;
};

class non_static{
    public:
        non_static(){};
        member m1;
    private:
        int i;
};

using namespace std;

int main(void){

    non_static ns;
    
    cout << typeid(ns).name() << endl;
    cout << typeid(ns.m1).name() << endl;

}
