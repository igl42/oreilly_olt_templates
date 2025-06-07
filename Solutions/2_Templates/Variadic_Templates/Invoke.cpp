/**************************************************************************************************
*
* \file Invoke.cpp
* \brief C++ Training - Variadic Template Programming Task
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Write a generic 'invoke()' function that invokes the given callable by passing the
*       given arguments.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>


//---- <functional> -------------------------------------------------------------------------------

template< typename Fn, typename... Args >
decltype(auto) invoke( Fn fn, Args&&... args )
{
   return std::forward<Fn>(fn)( std::forward<Args>(args)... );
}

// See https://en.cppreference.com/w/cpp/utility/functional/invoke for a complete implementation.


//---- <Main.cpp> ---------------------------------------------------------------------------------

int add( int a, int b )
{
   return a + b;
}

struct Subtract
{
   static long sub( long a, long b )
   {
      return a - b;
   }
};

[[maybe_unused]] auto mult = []( double a, double b )
{
   return a * b;
};


int main()
{
   int    const add_result  = invoke( add, 1, 2 );
   int    const sub_result  = invoke( Subtract::sub, 4L, 3L );
   double const mult_result = invoke( mult, 5.0, 6.0 );

   std::cout << "\n"
             << " add_result  = " << add_result << "\n"
             << " sub_result  = " << sub_result << "\n"
             << " mult_result = " << mult_result << "\n"
             << "\n";

   return EXIT_SUCCESS;
}
