/**************************************************************************************************
*
* \file Constraints2.cpp
* \brief C++ Training - Advanced C++20 concepts programming task
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task 1: Implement the concept 'IntCompatible' that requires the given type 'T' to be
*         convertible to 'int' and to have a size greater than or equal to the size of 'int'.
*
* Task 2: Implement the concept 'Arithmetic' that requires the given type 'T' to be either
*         an integral or floating point type, but does not accept 'bool'.
*
* Task 3: Implement the concept 'NonConstReference' that requires the given type 'T' to
*         be a reference to a non-const type.
*
* Task 4: Implement the concept 'IntegralAddable' that requires the given type 'T' to be
*         addable. The result of the addition should yield an integral value.
*
* Task 5: Implement the concept 'NoNarrowingConversion' that prevents narrowing conversions
*         between the given types 'From' and 'To'.
*
* Task 6: Implement the concept 'CompleteType' that requires the given type 'T' to be a
*         complete type.
*
**************************************************************************************************/

#include <cstdlib>
#include <concepts>
#include <string>
#include <utility>


//---- <Constraints.h> ----------------------------------------------------------------------------

// Task 1: Implement the concept 'IntCompatible' that requires the given type 'T' to be
//         convertible to 'int' and to have a size greater than or equal to the size of 'int'.
// TODO


// Task 2: Implement the concept 'Arithmetic' that requires the given type 'T' to be either
//         an integral or floating point type, but does not accept 'bool'.
// TODO


// Task 3: Implement the concept 'NonConstReference' that requires the given type 'T' to
//         be a reference to a non-const type.
// TODO


// Task 4: Implement the concept 'IntegralAddable' that requires the given type 'T' to be
//         addable. The result of the addition should yield an integral value.
// TODO


// Task 5: Implement the concept 'NoNarrowingConversion' that prevents narrowing conversions
//         between the given types 'From' and 'To'.
// TODO


// Task 6: Implement the concept 'CompleteType' that requires the given type 'T' to be a
//         complete type.
// TODO


//---- <Main.cpp> ---------------------------------------------------------------------------------

// Task 3
struct Widget
{
   Widget( int );
};
int operator+( Widget, Widget );

struct Gadget {};

struct Complete {};
struct Incomplete;


int main()
{
   // Task 1
   /*
   static_assert(     IntCompatible<int> );
   static_assert(     IntCompatible<unsigned int> );
   static_assert(     IntCompatible<long> );
   static_assert(     IntCompatible<size_t> );
   static_assert(     IntCompatible<float> );
   static_assert(     IntCompatible<double> );
   static_assert( not IntCompatible<char> );
   static_assert( not IntCompatible<unsigned short> );
   static_assert( not IntCompatible<std::string> );
   */

   // Task 2
   /*
   static_assert(     Arithmetic<char> );
   static_assert(     Arithmetic<short> );
   static_assert(     Arithmetic<int> );
   static_assert(     Arithmetic<long> );
   static_assert(     Arithmetic<float> );
   static_assert(     Arithmetic<double> );
   static_assert( not Arithmetic<bool> );
   static_assert( not Arithmetic<bool const> );
   static_assert( not Arithmetic<bool volatile> );
   static_assert( not Arithmetic<std::string> );
   */

   // Task 3
   /*
   static_assert(     NonConstReference<int&> );
   static_assert(     NonConstReference<int&&> );
   static_assert( not NonConstReference<int> );
   static_assert( not NonConstReference<int const> );
   static_assert( not NonConstReference<int const&> );
   static_assert( not NonConstReference<int const&&> );
   */

   // Task 4
   /*
   static_assert(     IntegralAddable<int> );
   static_assert(     IntegralAddable<long> );
   static_assert(     IntegralAddable<Widget> );
   static_assert( not IntegralAddable<float> );
   static_assert( not IntegralAddable<std::string> );
   static_assert( not IntegralAddable<Gadget> );
   */

   // Task 5
   /*
   static_assert(     NoNarrowingConversion<int,int> );
   static_assert(     NoNarrowingConversion<int,long> );
   static_assert(     NoNarrowingConversion<float,double> );
   static_assert(     NoNarrowingConversion<double,double> );
   static_assert(     NoNarrowingConversion<int,Widget> );
   static_assert( not NoNarrowingConversion<int,unsigned int> );
   static_assert( not NoNarrowingConversion<int,short> );
   static_assert( not NoNarrowingConversion<int,double> );
   static_assert( not NoNarrowingConversion<double,float> );
   static_assert( not NoNarrowingConversion<double,Widget> );
   */

   // Task 6
   /*
   static_assert(     CompleteType<int> );
   static_assert(     CompleteType<int*> );
   static_assert(     CompleteType<int&> );
   static_assert(     CompleteType<std::string> );
   static_assert(     CompleteType<Complete> );
   static_assert( not CompleteType<Incomplete> );
   */

   return EXIT_SUCCESS;
}

