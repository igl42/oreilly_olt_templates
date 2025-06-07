/**************************************************************************************************
*
* \file RemoveConst1.cpp
* \brief C++ Training - Type Traits Introduction
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the 'remove_const' type trait in the following example. The type trait should
*       remove any top level const qualifier from the given type.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <type_traits>


template< typename T >
struct remove_const
{
   using type = T;
};

template< typename T >
struct remove_const<T const>
{
   using type = T;
};

template< typename T >
using remove_const_t = typename remove_const<T>::type;


int main()
{
   using Type1  = int;
   using Type2  = int const;
   using Type3  = int volatile;
   using Type4  = int const volatile;
   using Type5  = int*;
   using Type6  = int* const;
   using Type7  = int* volatile;
   using Type8  = int* const volatile;
   using Type9  = int const*;
   using Type10 = int const* const;
   using Type11 = int const* volatile;
   using Type12 = int const* const volatile;
   using Type13 = int&;
   using Type14 = int const&;
   using Type15 = int volatile&;
   using Type16 = int const volatile&;

   static_assert( std::is_same< remove_const_t<Type1>, int          >::value, "Invalid type detected" );
   static_assert( std::is_same< remove_const_t<Type2>, int          >::value, "Invalid type detected" );
   static_assert( std::is_same< remove_const_t<Type3>, int volatile >::value, "Invalid type detected" );
   static_assert( std::is_same< remove_const_t<Type4>, int volatile >::value, "Invalid type detected" );

   static_assert( std::is_same< remove_const_t<Type5>, int*          >::value, "Invalid type detected" );
   static_assert( std::is_same< remove_const_t<Type6>, int*          >::value, "Invalid type detected" );
   static_assert( std::is_same< remove_const_t<Type7>, int* volatile >::value, "Invalid type detected" );
   static_assert( std::is_same< remove_const_t<Type8>, int* volatile >::value, "Invalid type detected" );

   static_assert( std::is_same< remove_const_t<Type9 >, int const*          >::value, "Invalid type detected" );
   static_assert( std::is_same< remove_const_t<Type10>, int const*          >::value, "Invalid type detected" );
   static_assert( std::is_same< remove_const_t<Type11>, int const* volatile >::value, "Invalid type detected" );
   static_assert( std::is_same< remove_const_t<Type12>, int const* volatile >::value, "Invalid type detected" );

   static_assert( std::is_same< remove_const_t<Type13>, int&                >::value, "Invalid type detected" );
   static_assert( std::is_same< remove_const_t<Type14>, int const&          >::value, "Invalid type detected" );
   static_assert( std::is_same< remove_const_t<Type15>, int volatile&       >::value, "Invalid type detected" );
   static_assert( std::is_same< remove_const_t<Type16>, int const volatile& >::value, "Invalid type detected" );

   return EXIT_SUCCESS;
}
