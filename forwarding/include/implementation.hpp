#include <type_traits>
#include <iostream>

namespace impl{
/*
 * ver0 : Base case reformulaated without 'identity', and reflecting the design of forward
 * up until the lanuage change prohibiting lvalues from implicitly binding to rvalue 
 * reference.
 */
#ifdef VER0
    template <class T, class U>
    inline
    T&&
    forward(U&& u){
        std::cout << "ver0" << std::endl;
        return static_cast<T&&>(u);
    }
#endif

/*
 * ver1 : Use simple definition of forward.
 */
#ifdef VER1
    template <class T, class U>
        T&& forward(U& u){
            std::cout << "ver1" << std::endl;
            return static_cast<T&&>(u);
        }
#endif

/*
 * ver2 : use definition of forward that protects the user from as many potential mistakes
 * as possible, by actively preventing all other uses.
 */
#ifdef VER2
    template<class T, class U>
        typename std::enable_if<
        std::is_lvalue_reference<U>::value
        && !std::is_rvalue_reference<T>::value
        && std::is_same<T&, U&>::value
        , T&&>::type forward(U&& a){
            std::cout << "ver2" << std::endl;
            return static_cast<T&&>(a);
        }
#endif
/*
 * ver3 : Allow forwarding an rvalue as an rvalue, but not an rvalue as an lvalue, 
 * and places no restriction on type conversion.
 */
#ifdef VER3
    template <class T, class U,
             class = typename std::enable_if<
                 std::is_lvalue_reference<T>::value ?
                 std::is_lvalue_reference<U>::value : true
            >::type>
    inline
    T&&
    forward(U&& u){
        std::cout << "ver3" << std::endl;
        return static_cast<T&&>(u);
    }
#endif
/*
 * ver4: similar to #3 but with additional constraints preventing base type conversions(like #2),
 * but it doesn't prevent adding cv-qualifiers (unlike #2).
 */
#ifdef VER4
    template <class T>
    struct __base_type{
        typedef typename std::remove_cv<typename std::remove_reference<T>::type>::type type;
    };

    template <class T, class U,
             class = typename std::enable_if<
                 (std::is_lvalue_reference<T>::value ?
                  std::is_lvalue_reference<U>::value :
                  true) &&
                 std::is_same<typename __base_type<T>::type,
                         typename __base_type<U>::type>::value
                >::type>
    inline
    T&&
    forward(U&& u){
        std::cout << "ver4" << std::endl;
        return static_cast<T&&>(u);
    }

#endif
/*
 * ver5 : similar to #4 but not as restrictive. It allows any conversion in which 
 * a temporary is not created as a result of the conversion. 
 * This include a derived to base conversion.
 */
#ifdef VER5
    template <class T, class U,
             class = typename std::enable_if<
                 (std::is_lvalue_reference<T>::value ?
                  std::is_lvalue_reference<U>::value :
                  true) &&
                 std::is_convertible<typename std::remove_reference<U>::type*,
                                     typename std::remove_reference<T>::type*>::value>::type>
     inline
     T&&
     forward(U&& u){
         std::cout << "ver5" << std::endl;
         return static_cast<T&&>(u);
     }
#endif
}
