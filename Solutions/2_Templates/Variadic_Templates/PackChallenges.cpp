/**************************************************************************************************
*
* \file PackChallenges.cpp
* \brief C++ Training - Programming challenges with variadic templates and parameter packs
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Provide a solution for the following challenges:
*
* Task 1: Sum up all the elements of a pack.
* Task 2: Sum up a pack of modified elements.
* Task 3: Check whether any element matches a given predicate 'pred()'.
* Task 4: Count the elements matching a given predicate 'pred()'.
* Task 5: Get the index of the first element matching a given predicate.
* Task 6: Get the nth element (where 'n' is a runtime value).
* Task 7: Get the first element of a parameter pack.
* Task 8: Get the last element of a parameter pack.
* Task 9: Get the minimum element of a parameter pack.
* Task 10: Get the maximum element of a parameter pack.
*
**************************************************************************************************/

#include <cassert>
#include <iostream>
#include <type_traits>


//=================================================================================================
// Task 1: Sum up all the elements of a pack.

template< typename... Ts >
constexpr auto sum_up_all_elements( Ts... values )
{
   // Pseudocode:
   // for( auto value : values ) {
   //    sum += value;
   // }
   // return sum;

   return ( ... + values );  // Unary left fold
   // return ( values + ... );  // Unary right fold
   // return ( 0 + ... + values );  // Binary left fold
   // return ( values + ... + 0 );  // Binary right fold
}


//=================================================================================================
// Task 2: Sum up a pack of modified elements.

template< typename Fn, typename... Ts >
constexpr auto sum_up_all_modified_elements( Fn fn, Ts... values )
{
   // Pseudocode:
   // for( auto value : values ) {
   //    sum += fn(value);
   // }
   // return sum;

   return ( ... + fn(values) );  // Unary left fold
   // return ( fn(values) + ... );  // Unary right fold
   // return ( 0 + ... + fn(values) );  // Binary left fold
   // return ( fn(values) + ... + 0 );  // Binary right fold
}


//=================================================================================================
// Task 3: Check whether any element matches a given predicate 'pred()'.

template< typename Pred, typename... Ts >
constexpr bool check_if_any_element_matches( Pred pred, Ts... values )
{
   // Pseudocode:
   // for( auto value : values )
   // if( pred( value ) )
   //    return true;
   // return false;

   return ( ... || pred(values) );
}


//=================================================================================================
// Task 4: Count the elements matching a given predicate 'pred()'.

template< typename Pred, typename... Ts >
constexpr size_t count_elements_matching_predicate( Pred pred, Ts... values )
{
   // Pseudocode:
   // size_t count{};
   // for( auto value : values )
   //    if( pred( value ) )
   //       ++count;
   // return count;

   return ( ... + ( pred(values) ? 1U : 0U ) );

   // Alternative based on the fact that 'bool' can be converted to 'size_t'
   //return ( ... + pred(values) );
}


//=================================================================================================
// Task 5: Get the index of the first element matching a given predicate.

template< typename Pred, typename... Ts >
constexpr auto get_index_of_first_matching_element( Pred pred, Ts... values )
{
   // Pseudocode:
   // for( size_t i=0U; i<size; ++i )
   // {
   //    if( pred( value ) )
   //       return i;
   //    return size;
   // }

   size_t index{};
   [[maybe_unused]] bool found = ( ( pred(values) ? false : ( ++index, true ) ) && ... );
   return index;

   // Solution by Henrik Thoma
   //size_t index{};
   //return ( ... || ( ++index, pred(values) ) ) ? --index : index;
}


//=================================================================================================
// Task 6: Get the nth element (where 'n' is a runtime value).

template< typename... Ts >
constexpr auto get_nth_element( size_t n, Ts... values )
{
   // Pseudocode:
   // values[n]

   assert( n < sizeof...(Ts) );
   std::common_type_t<Ts...> result{};
   size_t index{};
   [[maybe_unused]] bool found = ( ( index++ == n ? ( result = values, false ) : true ) && ... );
   return result;
}


//=================================================================================================
// Task 7: Get the first element of a parameter pack.

template< typename... Ts >
constexpr auto get_first_element( Ts... values )
{
   // Pseudocode:
   // values[0]

   std::common_type_t<Ts...> result{};
   [[maybe_unused]] bool found = ( ( result = values, true ) || ... );
   return result;
}


//=================================================================================================
// Task 8: Get the last element of a parameter pack.

constexpr auto const& id( auto const& value ) { return value; }

template< typename... Ts >
constexpr auto get_last_element( Ts... values )
{
   // Pseudocode:
   // values[size()-1]

   return ( id(values), ... );
}


//=================================================================================================
// Task 9: Get the minimum element of a parameter pack.

template< typename... Ts >
constexpr auto get_minimum_element( Ts... values )
{
   // Pseudocode:
   // auto min = values[values.size() - 1];
   // for( auto value : values )
   //    if( value < min )
   //       min = value;

   // Solution by Henrik Thoma
   std::common_type_t<Ts...> minimum = ( id(values), ... );
   ( ( values < minimum ? minimum = values : minimum ), ... );
   return minimum;
}


//=================================================================================================
// Task 10: Get the maximum element of a parameter pack.

template< typename... Ts >
constexpr auto get_maximum_element( Ts... values )
{
   // Pseudocode:
   // auto max = values[values.size() - 1];
   // for( auto value : values )
   //    if( max < value )
   //       max = value;

   // Henrik Thoma
   std::common_type_t<Ts...> maximum = ( id(values), ... );
   ( ( maximum < values ? maximum = values : maximum ), ... );
   return maximum;
}


//=================================================================================================

constexpr auto equal( int compare )
{
   return [compare]( int value ){ return value == compare; };
}

constexpr auto square()
{
   return []( auto const& value ){ return value*value; };
}

constexpr auto is_odd()
{
   return []( auto const& value ){ return value%2 == 1; };
}

constexpr auto is_even()
{
   return []( auto const& value ){ return value%2 == 0; };
}

int main()
{
   // Task 1: Sum up all the elements of a pack.
   static_assert( sum_up_all_elements( 1, 2, 3 ) == 6 );
   static_assert( sum_up_all_elements( 1, 2, 3, 4, 5 ) == 15 );

   // Task 2: Sum up a pack of modified elements.
   static_assert( sum_up_all_modified_elements( square(), 1, 2, 3 ) == 14 );
   static_assert( sum_up_all_modified_elements( square(), 1, 2, 3, 4, 5 ) == 55 );

   // Task 3: Check whether any element matches a given predicate 'pred()'.
   static_assert(  check_if_any_element_matches( equal(4), 1, 2, 3, 4, 5 ) );
   static_assert( !check_if_any_element_matches( equal(6), 1, 2, 3, 4, 5 ) );

   // Task 4: Count the elements matching a given predicate 'pred()'.
   static_assert( count_elements_matching_predicate( is_odd() , 1, 2, 3, 4, 5 ) == 3U );
   static_assert( count_elements_matching_predicate( is_even(), 1, 2, 3, 4, 5 ) == 2U );

   // Task 5: Get the index of the first element matching a given predicate.
   static_assert( get_index_of_first_matching_element( equal(4), 1, 2, 3, 4, 5 ) == 3U );
   static_assert( get_index_of_first_matching_element( equal(6), 1, 2, 3, 4, 5 ) == 5U );

   // Task 6: Get the nth element (where 'n' is a runtime value).
   static_assert( get_nth_element( 1, 1, 2, 3, 4, 5 ) == 2 );
   static_assert( get_nth_element( 3, 1, 2, 3, 4, 5 ) == 4 );

   // Task 7: Get the first element of a parameter pack.
   static_assert( get_first_element( 1, 2, 3, 4, 5 ) == 1 );
   static_assert( get_first_element( 5, 4, 3, 2, 1 ) == 5 );

   // Task 8: Get the last element of a parameter pack.
   static_assert( get_last_element( 1, 2, 3, 4, 5 ) == 5 );
   static_assert( get_last_element( 5, 4, 3, 2, 1 ) == 1 );

   // Task 9: Get the minimum element of a parameter pack.
   static_assert( get_minimum_element( 1, 2, 3, 4, 5 ) == 1 );
   static_assert( get_minimum_element( 5, 4, 3, 2, 1 ) == 1 );

   // Task 10: Get the maximum element of a parameter pack.
   static_assert( get_maximum_element( 1, 2, 3, 4, 5 ) == 5 );
   static_assert( get_maximum_element( 5, 4, 3, 2, 1 ) == 5 );

   return EXIT_SUCCESS;
}
