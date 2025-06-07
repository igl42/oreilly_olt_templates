/**************************************************************************************************
*
* \file HigherOrder.cpp
* \brief C++ Training - Variadic Template Programming Task
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the given 'count_if()' call in terms of reusable higher order functions
*       called 'youngerThan()', 'hasName()' and 'when_all()'. 'youngerThan()' should
*       provide a reusable predicate to check for a given age, 'hasName()' should provide
*       a reusable predicate to check for a given name, and 'when_all()' should provide
*       a generic way to combine an arbitrary number of predicates.
*
**************************************************************************************************/

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>


struct Person
{
   std::string firstname;
   std::string lastname;
   int age;
};


auto youngerThan( int age )
{
   return [age]( Person const& person )
   {
      return person.age < age;
   };
}


auto hasName( std::string_view name )
{
   return [name]( Person const& person )
   {
      return person.lastname == name;
   };
}


template< typename... Fs >
auto when_all( Fs... fs )
{
   return [fs...]( Person const& person )
   {
      return ( fs(person) && ... );
   };
}


int main()
{
   std::vector<Person> table =
      { Person{ "Homer",      "Simpson",    38 }
      , Person{ "Marge",      "Simpson",    34 }
      , Person{ "Bart",       "Simpson",    10 }
      , Person{ "Lisa",       "Simpson",     8 }
      , Person{ "Maggie",     "Simpson",     1 }
      , Person{ "Hans",       "Moleman",    33 }
      , Person{ "Ralph",      "Wiggum",      8 }
      , Person{ "Milhouse",   "Van Houten", 10 }
      , Person{ "Ned",        "Flanders",   60 }
      , Person{ "Jeff",       "Albertson",  45 }
      , Person{ "Montgomery", "Burns",     104 } };

   /*
   size_t const count =
      std::count_if( begin(table), end(table), []( Person const& person )
      {
         return person.age < 18 && person.lastname == "Simpson";
      } );
   */

   size_t const count =
      std::count_if( begin(table), end(table),
         when_all( youngerThan(18), hasName("Simpson") ) );

   std::cout << "The table contains " << count << " children named \"Simpson\"\n";

   return EXIT_SUCCESS;
}

