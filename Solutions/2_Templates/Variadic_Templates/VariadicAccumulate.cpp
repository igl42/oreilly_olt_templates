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

// Solution 1: Tail recursion with function overloading (since C++11)
/*
template< typename T >
auto accumulate( T value )
{
   return value;
}

template< typename T, typename... Ts >
auto accumulate( T value, Ts... values )
{
   return value + accumulate( values... );
}
*/

// Solution 2: Tail recursion with 'if constexpr' (since C++17)
/*
template< typename T, typename... Ts >
auto accumulate( T value, Ts... values )
{
   if constexpr( sizeof...(Ts) == 0U ) {
      return value;
   }
   else {
      return value + accumulate( values... );
   }
}
*/

// Solution 3: Fold expressions (possible since C++17)
template< typename... Ts >
auto accumulate( Ts... values )
{
   return ( ... + values );  // Unary left fold: evaluation from left to right
   // return ( values + ... );  // Unary right fold: evaluation from right to left
}


//=== Task 2 ======================================================================================

template< typename BinaryReductionOp, typename T1, typename T2, typename... Ts >
   requires std::invocable<BinaryReductionOp,T1,T2>
auto accumulate( BinaryReductionOp op, T1 value1, T2 value2, Ts... values )
{
   if constexpr( sizeof...(Ts) == 0U ) {
      return op( value1, value2 );
   }
   else {
      return op( value1, accumulate( op, value2, values... ) );
   }
}


//=== main() ======================================================================================

int main()
{
   // Task 1: Extend the given 'accumulate()' function by variadic templates to enable an
   //         arbitrary number of function arguments. 'accumulate()' should return the sum
   //         of all given arguments.
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

   // Task 2: Extend the 'accumulate()' function with a parameter that allows to inject the
   //         reduction operation into the algorithm. Test this by means of 'std::multiplies'.
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

   return EXIT_SUCCESS;
}
