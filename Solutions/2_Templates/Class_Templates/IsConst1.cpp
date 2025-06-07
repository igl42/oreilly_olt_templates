/**************************************************************************************************
*
* \file IsConst1.cpp
* \brief C++ Training - Type Trait Introduction
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the 'is_const' type trait in the following example. The type trait should
*       determine if the given type is a const qualifed type. In case the given type is a const
*       qualified type, the type trait should inherit from 'std::true_type', else it should
*       derive from 'std::false_type'.
*
**************************************************************************************************/

#include <complex>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <type_traits>


template< typename T >
struct is_const
   : public std::false_type
{};

template< typename T >
struct is_const<T const>
   : public std::true_type
{};

template< typename T >
inline constexpr bool is_const_v = is_const<T>::value;


int main()
{
   using Type1 = int;
   using Type2 = std::complex<float>;
   using Type3 = std::unique_ptr<int const>;
   using Type4 = int*;
   using Type5 = int const*;
   using Type6 = int**;
   using Type7 = int* const*;

   using Type8  = int const;
   using Type9  = std::complex<float> const;
   using Type10 = std::unique_ptr<int const> const;
   using Type11 = int* const;
   using Type12 = int const* const;
   using Type13 = int** const;
   using Type14 = int* const* const;

   static_assert( not is_const_v<Type1> );
   static_assert( not is_const_v<Type2> );
   static_assert( not is_const_v<Type3> );
   static_assert( not is_const_v<Type4> );
   static_assert( not is_const_v<Type5> );
   static_assert( not is_const_v<Type6> );
   static_assert( not is_const_v<Type7> );

   static_assert( is_const_v<Type8>  );
   static_assert( is_const_v<Type9>  );
   static_assert( is_const_v<Type10> );
   static_assert( is_const_v<Type11> );
   static_assert( is_const_v<Type12> );
   static_assert( is_const_v<Type13> );
   static_assert( is_const_v<Type14> );

   return EXIT_SUCCESS;
}

