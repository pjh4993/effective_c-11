#include <iostream>
#include <type_traits>

#ifndef VER6
#include "implementation.hpp"
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

    C() {}

    explicit C(const T& t) : t_(t) {}

    template <class U,
             class = typename std::enable_if
                 <
                 std::is_convertible<U, T>::value
                 >::type>
                 C(C<U>&& c) : t_(forward<T>(c.t_)) {}
    template <class U,
             class = typename std::enable_if
                 <
                 std::is_convertible<U, T>::value
                 >::type>
                 C(C<U>& c) : t_(forward<T>(c.t_)) {}

};

class B
{
    int data_;
    friend class A;
    public:
    explicit B(int data = 1)
        : data_(data) {}
    ~B() {data_ = -1;}

    void test() const
    {
        if (data_ < 0)
            std::cout << "B is destructed\n";
        else
            std::cout << "B = " << data_ << '\n';
    }
};

class A
{
    int data_;

    public:
    explicit A(int data = 1)
        : data_(data) {}
    ~A() {data_ = -1;}

    B b;
    operator B&() {
        b.data_ = data_;
        return b;
    }

    operator B() {
        b.data_ = data_;
        return b;
    }

    void test() const
    {
        if (data_ < 0)
            std::cout << "A is destructed\n";
        else
            std::cout << "A = " << data_ << '\n';
    }
};
int main()
{
    A a(3);
    C<A&> ca(a);
    C<B&> cb(ca);
    cb.t_.test();
}
