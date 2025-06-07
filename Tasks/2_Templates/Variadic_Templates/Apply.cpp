/**************************************************************************************************
*
* \file Apply.cpp
* \brief C++ Training - Variadic Template Programming Task
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Write a generic 'apply()' function that invokes the given callable by passing the
*       values stored in the given tuple.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <functional>
#include <tuple>
#include <utility>


//---- <tuple> ------------------------------------------------------------------------------------

// TODO


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
   /*
   int    const add_result  = ::apply( add, std::make_tuple( 1, 2 ) );
   int    const sub_result  = ::apply( Subtract::sub, std::make_tuple( 4L, 3L ) );
   double const mult_result = ::apply( mult, std::make_tuple( 5.0, 6.0 ) );

   std::cout << "\n"
             << " add_result  = " << add_result << "\n"
             << " sub_result  = " << sub_result << "\n"
             << " mult_result = " << mult_result << "\n"
             << "\n";
   */

   return EXIT_SUCCESS;
}
