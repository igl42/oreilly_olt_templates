/**************************************************************************************************
*
* \file VariadicAccumulate.cpp
* \brief C++ Training - Variadic Template Programming Task
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task 1: Extend the given 'accumulate()' function by variadic templates to enable an arbitrary
*         number of function arguments. 'accumulate()' should return the sum of all given
*         arguments.
*
* Task 2: Extend the 'accumulate()' function with a parameter that allows to inject the reduction
*         operation into the algorithm. Test this by means of 'std::multiplies'.
*
**************************************************************************************************/

#include <concepts>
#include <cstdlib>
#include <iostream>


//=== Task 1 ======================================================================================

// TODO: Extend the given 'accumulate()' function by variadic templates to enable an arbitrary
//       number of function arguments. 'accumulate()' should return the sum of all given
//       arguments.
template< typename T >
auto accumulate( T value )
{
   return value;
}


//=== Task 2 ======================================================================================

// TODO


//=== main() ======================================================================================

int main()
{
   // Task 1: Extend the given 'accumulate()' function by variadic templates to enable an
   //         arbitrary number of function arguments. 'accumulate()' should return the sum
   //         of all given arguments.
   /*
   {
      auto const result1 = ::accumulate( 1 );
      auto const result2 = ::accumulate( 1, 2 );
      auto const result3 = ::accumulate( 1, 2, 3 );
      auto const result4 = ::accumulate( 1, 2, 3, 4 );

      std::cout << "\n"
                << " result1 = " << result1 << "\n"
                << " result2 = " << result2 << "\n"
                << " result3 = " << result3 << "\n"
                << " result4 = " << result4 << "\n"
                << "\n";
   }
   */

   // Task 2: Extend the 'accumulate()' function with a parameter that allows to inject the
   //         reduction operation into the algorithm. Test this by means of 'std::multiplies'.
   /*
   {
      auto const result2 = ::accumulate( std::multiplies{}, 1, 2 );
      auto const result3 = ::accumulate( std::multiplies{}, 1, 2, 3 );
      auto const result4 = ::accumulate( std::multiplies{}, 1, 2, 3, 4 );

      std::cout << "\n"
                << " result2 = " << result2 << "\n"
                << " result3 = " << result3 << "\n"
                << " result4 = " << result4 << "\n"
                << "\n";
   }
   */

   return EXIT_SUCCESS;
}
