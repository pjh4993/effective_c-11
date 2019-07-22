#include <iostream>
#include <typeinfo>

using namespace std;

class base{
    public:
        base(){
            cout << "Base constructed " << endl;
        }
        virtual void print(){
            cout << "print base class" << endl;
        }
        void show(){
            cout << "it's all same" << endl;
        }
        virtual ~base(){
            cout << "~Base is excuted" << endl;
        }
};

class derived : public base{
    public:
        derived(){
            cout << "derived constructed " << endl;
        }
        void print(){
            cout << "print derived virtual class " << endl;
        }
        void show(){
            cout << "no it's not" << endl;
        }
        ~derived(){
            cout << "~derived is excuted" << endl;
        }
};
class derived2 : public derived{
    public:
        derived2(){
            cout << "derived2 constructed" << endl;
        }
        void print(){
            cout << "print derived derived class" << endl;
        }
        ~derived2(){
            cout << "~derived2 is exucted" <<endl;
        }
};

int main(void){
    /*
    base *bptr_d, *bptr_dd;
    derived d,n;
    derived2 d2;
    bptr_d = &d;
    bptr_dd = &d2;

    bptr_d->print();
    bptr_dd->print();
    bptr_d->show();
    (*bptr_d).show();
    d.show();
    cout << typeid(*bptr_d).name() << endl;
    delete bptr_dd;
    */

    base *pbtr_d = new derived2();
    delete pbtr_d;
}
