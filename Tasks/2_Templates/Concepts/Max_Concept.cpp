/**************************************************************************************************
*
* \file Max_Concept.cpp
* \brief C++ Training - Moderate C++20 concepts programming task
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Step 1: Constrain the 'max()' function by means of C++20 concepts to comparable types (i.e.
*         types that support 'operator<()'). All types should be supported, but in case both
*         types are arithmetic, the comparison should be constraint according to the following
*         rules:
*
*          - at least one of the two types is a floating point type OR
*          - both types are either signed or unsigned.
*
* Step 2: Implement the 'is_string' type trait, which should detect if a given type is a string
*         like (i.e. 'std::string', 'std::string_view', or 'char const*').
*
* Step 3: Extend the 'max()' algorithm such that it is possible to add an overload for
*         'std::string_view', which performs a character comparison based on lowercase characters.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

using namespace std::literals::string_literals;


//---- <IsString.h> -------------------------------------------------------------------------------

// Step 2: Implement the 'is_string' type trait, which should detect if a given type is a string
//         like (i.e. 'std::string', 'std::string_view', or 'char const*').


//---- <Max.h> ------------------------------------------------------------------------------------

// Step 1: Constrain the 'max()' function by means of C++20 concepts to comparable types
//         (i.e. types that support 'operator<()').
template< typename T1, typename T2 >
inline auto max( T1 const& a, T2 const& b )
{
   return ( a < b ) ? b : a;
}


// Step 3: Extend the 'max()' algorithm such that it is possible to add an overload for
//         'std::string_view', which performs a character comparison based on lowercase
//         characters.
/*
auto lower_compare()
{
   return []( char a, char b ) { return std::tolower(a) < std::tolower(b); };
}

inline std::string_view max( std::string_view a, std::string_view b )
{
   if( std::lexicographical_compare( begin(a), end(a), begin(b), end(b), lower_compare() ) )
      return b;
   else
      return a;
}
*/


//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   // Numeric comparisons
   std::cout << "\n"
                " max( 1, 5L )     = " << ::max( 1, 5L ) << "\n"
                " max( 3UL, 2U )   = " << ::max( 3UL, 2U ) << "\n"
                " max( 1.2, -4 )   = " << ::max( 1.2, -4 ) << "\n"
                " max( -1.2F, 4U ) = " << ::max( -1.2F, 4U ) << "\n"
                " max( 1.0F, 2.8 ) = " << ::max( 1.0F, 2.8 ) << "\n"
                //" max( 1, 5U )     = " << ::max( 1, 5U ) << "\n"  // Compilation error
                //" max( 3L, 1UL )   = " << ::max( 3L, 1UL ) << "\n"  // Compilation error
                "\n";

   // String comparisons
   std::cout << " max( \"Hello\"s, \"World\"s ) = " << ::max( "Hello"s, "World"s ) << "\n"
                " max( \"bjarne\"s, \"Herb\" )  = " << ::max( "bjarne"s, "Herb" ) << "\n"
                "\n";

   return EXIT_SUCCESS;
}

