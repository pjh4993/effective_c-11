#include <iostream>
#include <utility>
using namespace std;
/*
void fn(const X &){cout << "const X &" << endl;}
void fn(X &){cout << "X &" << endl;}
void fn(X &&){cout << "X &&" << endl;}
*/
/*
 *  possible number of case 12
 *  1. X& for copy constructor or assignment
 *  2. const X& for copy constructor or assignment **
 *  3. X&& for copy constructor or assignment
 *  4. X& for move constructor or assignemt **
 *  5. const X& for move constructor or assignment
 *  6. X&& for move constructor or assignemt
 *
 *  const X& @@ can bind to X& and X&& -> useful
 *  X&& used for forwarding reference template argument deduction
 *
 *  std::move used to make function overloaded to rvalue reference version
 *  std::forward used to make argument in function body to original value category that it was called
 *  stopping compiletime attempts to convert from rvalue to lvalue
 */


template<typename T>
void fn(T &&){ cout << "template" << endl;}

struct Y
{
    Y(){}
    Y(const Y &){cout << "arg copied" << endl; }
    Y(Y &&){cout << "arg moved" << endl; }
};

struct X
{
    template<typename A, typename B>
    X(A &&a, B &&b)
    :   a_{std::forward<A>(a) },
        b_{std::forward<B>(b) }
    {}
    Y a_;
    Y b_;
};

template<typename A, typename B>
X factory(A && a,B && b){
    return X(std::forward<A>(a), std::forward<B>(b));
}

int main(){
    Y y;
    X two = factory(y,Y());
}
