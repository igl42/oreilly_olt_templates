/**************************************************************************************************
*
* \file IsConst1.cpp
* \brief C++ Training - Easy Type Trait Example
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


// TODO: Implement the 'is_const' type trait to determine whether a given type is a const qualified type.


int main()
{
   /*
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

   static_assert( not is_const<Type1>::value );
   static_assert( not is_const<Type2>::value );
   static_assert( not is_const<Type3>::value );
   static_assert( not is_const<Type4>::value );
   static_assert( not is_const<Type5>::value );
   static_assert( not is_const<Type6>::value );
   static_assert( not is_const<Type7>::value );

   static_assert( is_const<Type8 >::value );
   static_assert( is_const<Type9 >::value );
   static_assert( is_const<Type10>::value );
   static_assert( is_const<Type11>::value );
   static_assert( is_const<Type12>::value );
   static_assert( is_const<Type13>::value );
   static_assert( is_const<Type14>::value );
   */

   return EXIT_SUCCESS;
}

