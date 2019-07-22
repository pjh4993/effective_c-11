#ifndef VER6
    #include "implementation.hpp"
    using namespace impl;
#endif

#ifdef VER6
    #include <utility>
    using namespace std;
#endif

template <class T>
struct C{
    T t_;
    C() {}
    template <class U,
             class = typename std::enable_if
                 <
                    !std::is_lvalue_reference<T>::value
                >::type>
        C(U&& u) : t_(forward<T>(std::move(u).get())) {}
    C(C&& c) : t_(forward<T>(c.t_)) {}
};

template <class T>
struct Derived
    : C<T>
{
    Derived() {}
    Derived(Derived&& d) : C<T>(forward<C<T>>(d)){}
};

int main(){
    Derived<int> d;
    Derived<int> d2(std::move(d));
}
