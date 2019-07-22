#include <cassert>

template <typename T>
class optional_r
{
    T t_;
    T&  value() &;
    T&& value() &&;
    T const& value() const&;
    //T const value() const;
    //T value();
    /* Before c++11 has introduced, (non-static) member function can be thought as 
     * free function with *this. But after reference has added to cpp, *this should be changed to reference.
     * However, for backward compatibility *this had to be pointer.
     * This cause mix of *this overload and &this overload can not be allowed.
     */
};

template <typename T>
class optional_p{
    T value();
    T const value() const;
    public:
    void modify(optional_p<T>&) const;
    T t_;
};

template <typename T>
T& optional_r<T>::value() &{
    
}

template <typename T>
T&& optional_r<T>::value() &&{

}

template <typename T>
T const& optional_r<T>::value() const&{

}

template <typename T>
void optional_p<T>::modify(optional_p<T>& t) const{
    t.t_ =  1;   
}

int main(void){
    optional_p<int> p1;
    p1.modify(p1);
    assert(p1.t_ == 1);
}
