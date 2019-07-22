#include <iostream>
#include <list>
#include "implementation.hpp"

#ifndef VER6
    using namespace impl;
#endif

#ifdef VER6
    #include <utility>
    using namespace std;
#endif



template <class T>
struct C
{
    T t_;

    template <class U,
             class = typename std::enable_if
                 <
                 !std::is_lvalue_reference<U>::value
                 >::type>
                 C(U&& u) : t_(forward<T>(std::move(u).get())) {}
};

class A
{
    int data_;
    public:
    explicit A(int data = 1)
        : data_(data) {}
    ~A() {data_ = -1;}

    void test() const
    {
        if (data_ < 0)
            std::cout << "A is destructed\n";
        else
            std::cout << "A = " << data_ << '\n';
    }
};

class Awrap
{
    A a_;
    public:
    explicit Awrap(const A& a) : a_(a) {}
    A get() const {return a_;}
};

    template <class C>
void test(C c)
{
    c.t_.test();
}

int main()
{
    std::list<C<A> > list;
    A a(3);
    C<A> c((Awrap(a)));
    list.push_back(c);
    test(c);
    test(list.front());
}


