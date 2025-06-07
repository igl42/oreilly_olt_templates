/**************************************************************************************************
*
* \file Span.h
* \brief C++ Training - Simplified implementation of the C++20 std::span
*
* Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
**************************************************************************************************/

#include <array>
#include <cassert>
#include <climits>
#include <cstddef>
#include <limits>
#include <type_traits>
#include <utility>
#include <version>

#pragma once

#ifdef __cpp_lib_span
#  include <span>
#else

namespace std {

//*************************************************************************************************
// Namespace functions (for pre-C++17)
//*************************************************************************************************

/*
template< typename Container >
constexpr auto data( Container& cont ) -> decltype( cont.data() )
{
   return cont.data();
}

template< typename Container >
constexpr auto data( const Container& cont ) -> decltype( cont.data() )
{
   return cont.data();
}

template< typename T, size_t N >
constexpr T* data( T (&arr)[N] ) noexcept
{
   return arr;
}

template< typename Container >
constexpr auto size( const Container& cont ) noexcept -> decltype( cont.size() )
{
   return cont.size();
}

template< typename T, size_t N >
constexpr size_t size( T (&)[N] ) noexcept
{
   return N;
}
*/


//*************************************************************************************************
// Implementation details
//*************************************************************************************************

template< class, size_t > class span;

namespace detail {

template< typename T, size_t Extent >
true_type eval_is_span( const span<T,Extent>& );

false_type eval_is_span( ... );

template< typename T >
using is_span = decltype( detail::eval_is_span( declval<T>() ) );

template< typename T >
constexpr bool is_span_v = is_span<T>::value;

} // namespace detail


//*************************************************************************************************
// Class definition
//*************************************************************************************************

/*inline*/ constexpr size_t dynamic_extent = numeric_limits<size_t>::max();


template< typename T, size_t Extent = dynamic_extent >
class span
{
 public:
   using element_type    = T;
   using value_type      = remove_cv_t<T>;
   using index_type      = size_t;
   using difference_type = ptrdiff_t;

   using pointer       = T*;
   using const_pointer = const T*;

   using reference       = T&;
   using const_reference = const T&;

   using iterator       = T*;
   using const_iterator = const T*;

   using reverse_iterator       = T*;
   using const_reverse_iterator = const T*;

   static constexpr size_t extent = Extent;

 private:
   template< typename Container >
   using enable_if_is_neither_array_nor_span =
      enable_if_t< !is_array<Container>::value && !detail::is_span_v<Container> >;

   template< typename From, typename To, size_t N >
   using enable_if_is_convertible_to_span =
      enable_if_t< N == Extent && is_convertible<From(*)[],To(*)[]>::value >;

   template< size_t Offset, size_t Count >
   static constexpr size_t extent_v =
      ( Count != dynamic_extent ? Count : Extent - Offset );

 public:
   template< bool B = ( Extent == 0UL ), enable_if_t<B>* = nullptr >
   constexpr span() noexcept;

   constexpr span( pointer ptr, index_type count );
   constexpr span( pointer first, pointer last );

   template< size_t N >
   constexpr span( element_type (&arr)[N] ) noexcept;

   template< size_t N >
   constexpr span( array<value_type,N>& arr, enable_if_is_convertible_to_span<value_type,element_type,N>* = nullptr ) noexcept;

   template< size_t N >
   constexpr span( const array<value_type,N>& arr, enable_if_is_convertible_to_span<value_type,element_type,N>* = nullptr ) noexcept;

   template< typename Container >
   constexpr span( Container& cont, enable_if_is_neither_array_nor_span<Container>* = nullptr );

   template< typename Container >
   constexpr span( const Container& cont, enable_if_is_neither_array_nor_span<Container>* = nullptr );

   template< typename U, size_t N >
   constexpr span( const span<U,N>& s, enable_if_is_convertible_to_span<U,element_type,N>* = nullptr ) noexcept;

   constexpr span( const span& other ) noexcept = default;
   constexpr span& operator=( const span& other ) noexcept = default;

   constexpr auto begin () const noexcept -> iterator;
   constexpr auto cbegin() const noexcept -> const_iterator;

   constexpr auto end () const noexcept -> iterator;
   constexpr auto cend() const noexcept -> const_iterator;

   constexpr auto rbegin () const noexcept -> reverse_iterator;
   constexpr auto crbegin() const noexcept -> const_reverse_iterator;

   constexpr auto rend () const noexcept -> reverse_iterator;
   constexpr auto crend() const noexcept -> const_reverse_iterator;

   constexpr auto front() const -> reference;
   constexpr auto back () const -> reference;

   constexpr auto operator[]( index_type idx ) const -> reference;

   constexpr auto data() const noexcept -> pointer;

   static constexpr auto size() noexcept -> index_type;
   static /*[[nodiscard]]*/ constexpr bool empty() noexcept;

   template< size_t Count >
   constexpr auto first() const -> span<T,Count>;
   constexpr auto first( size_t count ) const -> span<T>;

   template< size_t Count >
   constexpr auto last() const -> span<T,Count>;
   constexpr auto last( size_t count ) const -> span<T>;

   template< size_t Offset, size_t Count >
   constexpr auto subspan() const -> span<T,extent_v<Offset,Count>>;
   constexpr auto subspan( size_t offset, size_t count ) const -> span<T>;

 private:
   T* ptr_{ nullptr };
};


template< typename T, size_t Extent >
template< bool B, enable_if_t<B>* >
constexpr span<T,Extent>::span() noexcept
{}

template< typename T, size_t Extent >
constexpr span<T,Extent>::span( pointer ptr, index_type count )
   : ptr_{ ptr }
{
   assert( Extent == count );
}

template< typename T, size_t Extent >
constexpr span<T,Extent>::span( pointer first, pointer last )
   : span( first, last - first )
{}

template< typename T, size_t Extent >
template< size_t N >
constexpr span<T,Extent>::span( element_type (&arr)[N] ) noexcept
   : ptr_{ arr }
{}

template< typename T, size_t Extent >
template< size_t N >
constexpr span<T,Extent>::span( array<value_type,N>& arr, enable_if_is_convertible_to_span<value_type,element_type,N>* ) noexcept
   : ptr_{ arr.data() }
{}

template< typename T, size_t Extent >
template< size_t N >
constexpr span<T,Extent>::span( const array<value_type,N>& arr, enable_if_is_convertible_to_span<value_type,element_type,N>* ) noexcept
   : ptr_{ arr.data() }
{}

template< typename T, size_t Extent >
template< typename Container >
constexpr span<T,Extent>::span( Container& cont, enable_if_is_neither_array_nor_span<Container>* )
   : ptr_{ data(cont) }
{}

template< typename T, size_t Extent >
template< typename Container >
constexpr span<T,Extent>::span( const Container& cont, enable_if_is_neither_array_nor_span<Container>* )
   : ptr_{ data(cont) }
{}

template< typename T, size_t Extent >
template< typename U, size_t N >
constexpr span<T,Extent>::span( const span<U,N>& s, enable_if_is_convertible_to_span<U,element_type,N>* ) noexcept
   : ptr_{ s.data() }
{}

template< typename T, size_t Extent >
constexpr auto span<T,Extent>::begin() const noexcept -> iterator
{
   return ptr_;
}

template< typename T, size_t Extent >
constexpr auto span<T,Extent>::cbegin() const noexcept -> const_iterator
{
   return ptr_;
}

template< typename T, size_t Extent >
constexpr auto span<T,Extent>::end() const noexcept -> iterator
{
   return ptr_ + Extent;
}

template< typename T, size_t Extent >
constexpr auto span<T,Extent>::cend() const noexcept -> const_iterator
{
   return ptr_ + Extent;
}

template< typename T, size_t Extent >
constexpr auto span<T,Extent>::rbegin() const noexcept -> reverse_iterator
{
   return end() - 1UL;
}

template< typename T, size_t Extent >
constexpr auto span<T,Extent>::crbegin() const noexcept -> const_reverse_iterator
{
   return end() - 1UL;
}

template< typename T, size_t Extent >
constexpr auto span<T,Extent>::rend() const noexcept -> reverse_iterator
{
   return begin() - 1UL;
}

template< typename T, size_t Extent >
constexpr auto span<T,Extent>::crend() const noexcept -> const_reverse_iterator
{
   return begin() - 1UL;
}

template< typename T, size_t Extent >
constexpr auto span<T,Extent>::front() const -> reference
{
   static_assert( Extent > 0UL, "Invalid extent detected" );
   return *begin();
}

template< typename T, size_t Extent >
constexpr auto span<T,Extent>::back() const -> reference
{
   static_assert( Extent > 0UL, "Invalid extent detected" );
   return *(end()-1UL);
}

template< typename T, size_t Extent >
constexpr auto span<T,Extent>::operator[]( index_type idx ) const -> reference
{
   assert( idx < Extent );
   return ptr_[idx];
}

template< typename T, size_t Extent >
constexpr auto span<T,Extent>::data() const noexcept -> pointer
{
   return ptr_;
}

template< typename T, size_t Extent >
constexpr auto span<T,Extent>::size() noexcept -> index_type
{
   return Extent;
}

template< typename T, size_t Extent >
/*[[nodiscard]]*/ constexpr bool span<T,Extent>::empty() noexcept
{
   return Extent == 0UL;
}

template< typename T, size_t Extent >
template< size_t Count >
constexpr auto span<T,Extent>::first() const -> span<T,Count>
{
   static_assert( Count <= Extent, "Invalid count detected" );
   return span<T,Count>( ptr_, Count );
}

template< typename T, size_t Extent >
constexpr auto span<T,Extent>::first( size_t count ) const -> span<T>
{
   assert( count <= Extent );
   return span<T>( ptr_, count );
}

template< typename T, size_t Extent >
template< size_t Count >
constexpr auto span<T,Extent>::last() const -> span<T,Count>
{
   static_assert( Count <= Extent, "Invalid count detected" );
   return span<T,Count>( ptr_+Extent-Count, Count );
}

template< typename T, size_t Extent >
constexpr auto span<T,Extent>::last( size_t count ) const -> span<T>
{
   assert( count <= Extent );
   return span<T>( ptr_+Extent-count, count );
}

template< typename T, size_t Extent >
template< size_t Offset, size_t Count >
constexpr auto span<T,Extent>::subspan() const -> span<T,extent_v<Offset,Count>>
{
   static_assert( Offset < Extent, "Invalid offset detected" );
   static_assert( Offset + Count < Extent, "Invalid count detected" );
   constexpr size_t newExtent = extent_v<Offset,Count>;
   return span<T,newExtent>( ptr_+Offset, newExtent );
}

template< typename T, size_t Extent >
constexpr auto span<T,Extent>::subspan( size_t offset, size_t count ) const -> span<T>
{
   assert( offset < Extent );
   assert( offset + count < Extent );
   return span<T>( ptr_+offset, count );
}


//*************************************************************************************************
// Class specialization for Extent = dynamic_extent
//*************************************************************************************************

template< typename T >
class span<T,dynamic_extent>
{
 public:
   using element_type    = T;
   using value_type      = remove_cv_t<T>;
   using index_type      = size_t;
   using difference_type = ptrdiff_t;

   using pointer       = T*;
   using const_pointer = const T*;

   using reference       = T&;
   using const_reference = const T&;

   using iterator       = T*;
   using const_iterator = const T*;

   using reverse_iterator       = T*;
   using const_reverse_iterator = const T*;

   static constexpr size_t extent = dynamic_extent;

 private:
   template< typename Container >
   using enable_if_is_neither_array_nor_span =
      enable_if_t< !is_array<Container>::value && !detail::is_span_v<Container> >;

   template< typename From, typename To >
   using enable_if_is_convertible_to_span =
      enable_if_t< is_convertible<From(*)[],To(*)[]>::value >;

   template< size_t Offset, size_t Count >
   static constexpr size_t extent_v =
      ( Count != dynamic_extent ? Count : dynamic_extent );

 public:
   constexpr span() noexcept = default;
   constexpr span( pointer ptr, index_type count );
   constexpr span( pointer first, pointer last );

   template< size_t N >
   constexpr span( element_type (&arr)[N] ) noexcept;

   template< size_t N >
   constexpr span( array<value_type,N>& arr ) noexcept;

   template< size_t N >
   constexpr span( const array<value_type,N>& arr ) noexcept;

   template< typename Container >
   constexpr span( Container& cont, enable_if_is_neither_array_nor_span<Container>* = nullptr );

   template< typename Container >
   constexpr span( const Container& cont, enable_if_is_neither_array_nor_span<Container>* = nullptr );

   template< typename U >
   constexpr span( const span<U>& s, enable_if_is_convertible_to_span<U,element_type>* = nullptr ) noexcept;

   constexpr span( const span& other ) noexcept = default;
   constexpr span& operator=( const span& other ) noexcept = default;

   constexpr auto begin () const noexcept -> iterator;
   constexpr auto cbegin() const noexcept -> const_iterator;

   constexpr auto end () const noexcept -> iterator;
   constexpr auto cend() const noexcept -> const_iterator;

   constexpr auto rbegin () const noexcept -> reverse_iterator;
   constexpr auto crbegin() const noexcept -> const_reverse_iterator;

   constexpr auto rend () const noexcept -> reverse_iterator;
   constexpr auto crend() const noexcept -> const_reverse_iterator;

   constexpr auto front() const -> reference;
   constexpr auto back () const -> reference;

   constexpr auto operator[]( index_type idx ) const -> reference;

   constexpr auto data() const noexcept -> pointer;

   constexpr auto size() const noexcept -> index_type;
   /*[[nodiscard]]*/ constexpr bool empty() const noexcept;

   template< size_t Count >
   constexpr auto first() const -> span<T,Count>;
   constexpr auto first( size_t count ) const -> span<T>;

   template< size_t Count >
   constexpr auto last() const -> span<T,Count>;
   constexpr auto last( size_t count ) const -> span<T>;

   template< size_t Offset, size_t Count >
   constexpr auto subspan() const -> span<T,extent_v<Offset,Count>>;
   constexpr auto subspan( size_t offset, size_t count ) const -> span<T>;

 private:
   T*     ptr_ { nullptr };
   size_t size_{ 0UL };
};


template< typename T >
constexpr span<T,dynamic_extent>::span( pointer ptr, index_type count )
   : ptr_ { ptr }
   , size_{ count }
{}

template< typename T >
constexpr span<T,dynamic_extent>::span( pointer first, pointer last )
   : span( first, last - first )
{}

template< typename T >
template< size_t N >
constexpr span<T,dynamic_extent>::span( element_type (&arr)[N] ) noexcept
   : ptr_ { arr }
   , size_{ N }
{}

template< typename T >
template< size_t N >
constexpr span<T,dynamic_extent>::span( array<value_type,N>& arr ) noexcept
   : ptr_ { arr.data() }
   , size_{ N }
{}

template< typename T >
template< size_t N >
constexpr span<T,dynamic_extent>::span( const array<value_type,N>& arr ) noexcept
   : ptr_ { arr.data() }
   , size_{ N }
{}

template< typename T >
template< typename Container >
constexpr span<T,dynamic_extent>::span( Container& cont, enable_if_is_neither_array_nor_span<Container>* )
   : ptr_ { data(cont) }
   , size_{ size(cont) }
{}

template< typename T >
template< typename Container >
constexpr span<T,dynamic_extent>::span( const Container& cont, enable_if_is_neither_array_nor_span<Container>* )
   : ptr_ { data(cont) }
   , size_{ size(cont) }
{}

template< typename T >
template< typename U >
constexpr span<T,dynamic_extent>::span( const span<U>& s, enable_if_is_convertible_to_span<U,element_type>* ) noexcept
   : ptr_ { s.data() }
   , size_{ s.size() }
{}

template< typename T >
constexpr auto span<T,dynamic_extent>::begin() const noexcept -> iterator
{
   return ptr_;
}

template< typename T >
constexpr auto span<T,dynamic_extent>::cbegin() const noexcept -> const_iterator
{
   return ptr_;
}

template< typename T >
constexpr auto span<T,dynamic_extent>::end() const noexcept -> iterator
{
   return ptr_ + size_;
}

template< typename T >
constexpr auto span<T,dynamic_extent>::cend() const noexcept -> const_iterator
{
   return ptr_ + size_;
}

template< typename T >
constexpr auto span<T,dynamic_extent>::rbegin() const noexcept -> reverse_iterator
{
   return end() - 1UL;
}

template< typename T >
constexpr auto span<T,dynamic_extent>::crbegin() const noexcept -> const_reverse_iterator
{
   return end() - 1UL;
}

template< typename T >
constexpr auto span<T,dynamic_extent>::rend() const noexcept -> reverse_iterator
{
   return begin() - 1UL;
}

template< typename T >
constexpr auto span<T,dynamic_extent>::crend() const noexcept -> const_reverse_iterator
{
   return begin() - 1UL;
}

template< typename T >
constexpr auto span<T,dynamic_extent>::front() const -> reference
{
   assert( size_ > 0UL );
   return *begin();
}

template< typename T >
constexpr auto span<T,dynamic_extent>::back() const -> reference
{
   assert( size_ > 0UL );
   return *(end()-1UL);
}

template< typename T >
constexpr auto span<T,dynamic_extent>::operator[]( index_type idx ) const -> reference
{
   assert( idx < size_ );
   return ptr_[idx];
}

template< typename T >
constexpr auto span<T,dynamic_extent>::data() const noexcept -> pointer
{
   return ptr_;
}

template< typename T >
constexpr auto span<T,dynamic_extent>::size() const noexcept -> index_type
{
   return size_;
}

template< typename T >
/*[[nodiscard]]*/ constexpr bool span<T,dynamic_extent>::empty() const noexcept
{
   return size_ == 0UL;
}

template< typename T >
template< size_t Count >
constexpr auto span<T,dynamic_extent>::first() const -> span<T,Count>
{
   assert( Count <= size() );
   return span<T,Count>( ptr_, Count );
}

template< typename T >
constexpr auto span<T,dynamic_extent>::first( size_t count ) const -> span<T>
{
   assert( count <= size() );
   return span<T>( ptr_, count );
}

template< typename T >
template< size_t Count >
constexpr auto span<T,dynamic_extent>::last() const -> span<T,Count>
{
   assert( Count <= size() );
   return span<T,Count>( ptr_+size_-Count, Count );
}

template< typename T >
constexpr auto span<T,dynamic_extent>::last( size_t count ) const -> span<T>
{
   assert( count <= size() );
   return span<T>( ptr_+size_-count, count );
}

template< typename T >
template< size_t Offset, size_t Count >
constexpr auto span<T,dynamic_extent>::subspan() const -> span<T,extent_v<Offset,Count>>
{
   assert( Offset < size() );
   assert( Offset + Count < size() );
   constexpr size_t newExtent = extent_v<Offset,Count>;
   return span<T,newExtent>( ptr_+Offset, newExtent );
}

template< typename T >
constexpr auto span<T,dynamic_extent>::subspan( size_t offset, size_t count ) const -> span<T>
{
   assert( offset < size() );
   assert( offset + count < size() );
   return span<T>( ptr_+offset, count );
}


//*************************************************************************************************
// Deduction Guides (for C++17)
//*************************************************************************************************

template< typename T, size_t N >
span( T(&)[N] ) -> span<T,N>;

template< typename T, size_t N >
span( array<T,N>& ) -> span<T,N>;

template< typename T, size_t N >
span( const array<T,N>& ) -> span<const T,N>;

template< typename Container >
span( Container& ) -> span< typename Container::value_type >;

template< typename Container >
span( const Container& ) -> span< const typename Container::value_type >;



//*************************************************************************************************
// Namespace functions
//*************************************************************************************************

template< typename T, size_t Extent >
constexpr auto begin( span<T,Extent> s ) noexcept
{
   return s.begin();
}

template< typename T, size_t Extent >
constexpr auto end( span<T,Extent> s ) noexcept
{
   return s.end();
}

template< size_t I, class T, size_t Extent >
constexpr T& get( span<T,Extent> s ) noexcept
{
   return s[I];
}

} // namespace std

#endif

