#include <utility>
#include <array>
#include <iostream>
#include <initializer_list>

template<typename T, std::size_t N>
constexpr void copy(std::array<T,N> t,std::array<T,N> f) noexcept{
    for(int i=0; i<N; i++){
        t[i] = f[i];
    }
};


template<typename T, std::size_t N>
constexpr void copy(std::array<T,N> t,T (&f)[N]) noexcept{
    for(int i=0; i<N; i++){
        t[i] = f[i];
    }
};

template<typename T, std::size_t N>
constexpr void copy(std::array<T,N> t,std::initializer_list<T> f) noexcept{
    for(int i : f){
        int tmp=0;
        t[++tmp] = i;
    }
};




template<typename T, std::size_t N>
class test{
    public:
        std::array<T,N> pRes;
        test(){
        }

        //?????
        /*
        test(T *arr){
            copy(pRes, arr);
        }

        */
        test(T (&arr)[N]):test(){
            copy(pRes,arr); 
        }

        test(T (&&arr)[N]){
            std::array<T,N>::swap(std::array<T,N>(arr));
        }

        test(std::initializer_list<T> list):test(){
            copy(pRes, list);
        }
        test& operator=(test&& t){
            pRes = std::move(t.pRes);
        }
        test& operator=(test& t){
            copy(pRes, t.pRes);
        }
};

int main(void){
    int arr[3] = {2,4,6};
    int arr2[3] = {5,6,7};
    int (&ref)[3] = arr;
    test<int, 3> t1 {1,2,3}, t2 (ref), t3(arr), t4(std::move(arr2));
    t1 = t2;
    t4 = std::move(test<int,3> {9,10,11});

}
