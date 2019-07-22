#include <iostream>
#include <typeinfo>

using namespace std;

/*
template <typename T>
void F(T& paramType){
    cout << "F& :" ;
    cout << typeid(T).name();
    cout << is_const<T>::value;
    cout << is_lvalue_reference<T>::value;
    cout << is_rvalue_reference<T>::value << endl;
}

template <typename T>
void F(T&& paramType){
    cout << "T :" ;
    cout << typeid(T).name();
    cout << is_const<typename remove_reference<T>::type>::value;
    cout << is_lvalue_reference<T>::value;
    cout << is_rvalue_reference<T>::value << endl;


    cout << "ParamType :" ;
    cout << typeid(paramType).name();
    cout << is_const<typename remove_reference<decltype(paramType)>::type>::value;
    cout << is_lvalue_reference<decltype(paramType)>::value;
    cout << is_rvalue_reference<decltype(paramType)>::value << endl;

    cout << endl;
}

template <typename T>
void R(const T& paramType){
    cout << "R& :" ;
    cout << typeid(T).name();
    cout << is_const<T>::value;
    cout << is_lvalue_reference<T>::value;
    cout << is_rvalue_reference<T>::value << endl;
}

template <typename T>
void P(T* paramType){
    cout << "P :" ;
    cout << typeid(T).name();
    cout << is_const<T>::value;
    cout << is_pointer<T>::value << endl;
}
*/

template <typename T>
void PC(T paramType){
    cout << "T :" ;
    cout << typeid(T).name();
    cout << is_const<typename remove_reference<T>::type>::value;
    cout << is_pointer<T>::value << endl;


    cout << "ParamType :" ;
    cout << typeid(paramType).name();
    cout << is_const<typename remove_reference<decltype(paramType)>::type>::value;
    cout << is_pointer<decltype(paramType)>::value << endl;

    cout << "*ParamType :" ;
    cout << typeid(*paramType).name();
    cout << is_const<typename remove_reference<decltype(*paramType)>::type>::value;
    cout << is_pointer<decltype(*paramType)>::value << endl;

    cout << endl;

};

int main(void){
    const char* const ptr = "FUn pointers";
    PC(ptr);
}
