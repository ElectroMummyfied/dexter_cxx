#ifndef DXT_FUNCTIONS_HXX
#define DXT_FUNCTIONS_HXX

#include "dexter.hxx"

namespace dxt {
    #pragma region reduce_add //{
        template <class T>
        void reduce_add(
            const vec<T>& v1,
            T& val
        );
    #pragma endregion //} reduce_add
    #pragma region reduce_multiply //{
        template <class T>
        void reduce_multiply (
            const vec<T> v1,
            T& val
        );
    #pragma endregion //} reduce_multiply
    #pragma region multiply_add //{
        template <class T>
        bool multiply_add (
            const vec<T>& v1,
            const vec<T>& v2,
            T& val
        );
    #pragma endregion //} multiply_add
    #pragma region less_than //{
        template <class T>
        bool less_than (
            const vec<T>& v1,
            const vec<T>& v2,
            bool& val
        );
    #pragma endregion //} less_than
    #pragma region transpose //{
        template <class T>
        tensor<T> transpose (
            const tensor<T>& t1,
            ull it1,
            ull it2
        );
    #pragma endregion //} transpose
    #pragma region print //{
        template <class T>
        void print(
            const vec<T>& _vec
        );
        template <class T>
        void print(
            const tensor<T>& obj 
        );
    #pragma endregion //} print
};

#include "dxtFunctions.txx"

#endif
