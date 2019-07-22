#include <iostream>
#include <utility>
#include <vector>

using namespace std;

template <typename T> void org_swap(T& a, T& b){
    T tmp = a;
    a = b;
    b = tmp;
}

template <typename T> void swap(T& a, T& b){
    T tmp(move(a));
    a = move(b);
    b = move(tmp);
    //move return argument as rvalue without triggering a copy construction
    //destructive read
}

template <typename T>
class clone_ptr{
    private:
        T* ptr;
    public:
        //constructor & destructor
        explicit clone_ptr(T *p = 0) : ptr(p) {}
        ~clone_ptr() {delete ptr;}

        //copy semantics
        clone_ptr(const clone_ptr& p)
            :ptr(p.ptr ? p.ptr->clone() : 0){}
        clone_ptr& operator=(const clone_ptr& p){
            if(this != &p){
                delete ptr;
                ptr = p.ptr ? p.ptr->clone() : 0;
            }
            return *this;
        }

        //move semantics
        clone_ptr(clone_ptr&& p)
            :ptr(p.ptr) {p.ptr = 0;}
        clone_ptr& operator=(clone_ptr&& p){
            swap(ptr, p.ptr);
            return *this;
        }

        //other operations
        T& operator*() const {return *ptr;}
};

class Base{
    private:
        vector<bool> flags;
    public:
        Base()
            : flags(move(vector<bool>{true, false})){};
        Base(Base&& x)
            : flags(move(x.flags)){};
        Base& operator=(Base&& x){
            flags = move(x.flags);
            return *this;
        }

};

class Derived : public Base{
    private:
        vector<int> vec;
        string name;
    public:
        explicit Derived()
            : name(move("default")){}
        Derived(Derived&& x)
            : Base(move(x)),
              vec(move(x.vec)),
              name(move(x.name)) {}
        Derived& operator=(Derived&& x){
            Base::operator=(move(x));
            vec = move(x.vec);
            name = move(x.name);
            return *this;
        }
        //clone

};


int main(void){
    clone_ptr<Derived> p1(new Derived);
    clone_ptr<Derived> p2 = move(p1);
    const clone_ptr<Derived> p3(new Derived);
    p1 = p3;
}
