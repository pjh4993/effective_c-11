#include <memory>
#include <initializer_list>
#include <iostream>
#include <array>
using namespace std;

template<size_t N>
class argument{
    public:
        array<int*, N> a;
        argument(){};
        argument(initializer_list<int*> li){
            auto a_it = a.begin();
            for(int* ptr : li){
                a_it[0] = ptr;
                a_it++;
            }
        }
        ~argument(){
            for(int* ptr : a){
                delete ptr;
                cout << ptr << endl;
            }
        }

        void insert(size_t n, int m_i){
            (*a[n]) = m_i;
        }
};

template<size_t N>
class test{
    public:
        argument<N> a;
        test(){};
        test(argument<N>& ref){
           a = ref; 
        }
        test(argument<N>&& rref){
            a = move(rref);
        }
        void insert(size_t n ,int m_i){
            a.insert(n,m_i);
        }
};

/*
template<class S>
S&& forward(typename remove_reference<S>::type& a) noexcept{
    return static_cast<S&&>(a);
}
*/


template<template<size_t> typename T, template<size_t> typename Arg, size_t N>
shared_ptr<T<N>> factory(Arg<N>& arg){
    return shared_ptr<T<N>>(new T<N>(arg));
};

template<template<size_t> typename T, template<size_t> typename Arg, size_t N>
shared_ptr<T<N>> factory(Arg<N>&& arg){
    return shared_ptr<T<N>>(new T<N>(forward<Arg<N>>(arg)));
};

/*
template<template<size_t> typename T,template<size_t> typename Arg, size_t N>
shared_ptr<T<N>> factory(Arg<N> arg){
    return shared_ptr<T<N>>(new T<N>(arg));
}
*/


template<template<typename,size_t> typename f,typename T, size_t N>
void testArray(f<T,N> ta){

}
int main(void){
    argument<2> a1 = {new int(), new int()};

    auto t_ptr = factory<test>(a1);

    auto ptr = factory<test>(argument<2>({new int(), new int()}));

    t_ptr->insert(0,1);
    ptr->insert(0,1);

}
