/**************************************************************************************************
*
* \file IsPointer1.cpp
* \brief C++ Training - Easy Type Trait Example
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the 'is_pointer' type trait in the following example. The type trait should
*       determine if the given type is a pointer type. In case the given type is a pointer type,
*       the type trait should inherit from 'std::true_type', else it should derive from
*       'std::false_type'.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <memory>
#include <type_traits>
#include <utility>


// TODO: Implement the 'is_pointer' type trait to determine whether a given type is a pointer type.


int main()
{
   /*
   using Type1  = int;
   using Type2  = int const;
   using Type3  = int volatile;
   using Type4  = int const volatile;
   using Type5  = int&;
   using Type6  = int const&;
   using Type7  = std::unique_ptr<int>;
   using Type8  = std::unique_ptr<int> const;
   using Type9  = std::unique_ptr<int> volatile;
   using Type10 = std::unique_ptr<int> const volatile;

   using Type11 = int*;
   using Type12 = int* const;
   using Type13 = int* volatile;
   using Type14 = int* const volatile;
   using Type15 = int const*;
   using Type16 = int const* const;
   using Type17 = int const* volatile;
   using Type18 = int const* const volatile;

   static_assert( not is_pointer_v<Type1>  );
   static_assert( not is_pointer_v<Type2>  );
   static_assert( not is_pointer_v<Type3>  );
   static_assert( not is_pointer_v<Type4>  );
   static_assert( not is_pointer_v<Type5>  );
   static_assert( not is_pointer_v<Type6>  );
   static_assert( not is_pointer_v<Type7>  );
   static_assert( not is_pointer_v<Type8>  );
   static_assert( not is_pointer_v<Type9>  );
   static_assert( not is_pointer_v<Type10> );

   static_assert( is_pointer_v<Type11> );
   static_assert( is_pointer_v<Type12> );
   static_assert( is_pointer_v<Type13> );
   static_assert( is_pointer_v<Type14> );
   static_assert( is_pointer_v<Type15> );
   static_assert( is_pointer_v<Type16> );
   static_assert( is_pointer_v<Type17> );
   static_assert( is_pointer_v<Type18> );
   */

   return EXIT_SUCCESS;
}
