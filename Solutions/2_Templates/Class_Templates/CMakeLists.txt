#==================================================================================================
#
#  CMakeLists for subchapter "Class Templates" of chapter "Templates"
#
#  Copyright (C) 2015-2025 Klaus Iglberger - All Rights Reserved
#
#  This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
#  context of the C++ training or with explicit agreement by Klaus Iglberger.
#
#==================================================================================================

cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)

add_executable(FixedVector1
   FixedVector1.cpp
   )

add_executable(IsConst1
   IsConst1.cpp
   )

add_executable(IsPointer1
   IsPointer1.cpp
   )

add_executable(RemoveConst1
   RemoveConst1.cpp
   )

add_executable(UniquePtr1
   UniquePtr1.cpp
   )

add_executable(Vector1
   Vector1.cpp
   )

add_executable(Vector2
   Vector2.cpp
   )

set_target_properties(
   FixedVector1
   IsConst1
   IsPointer1
   RemoveConst1
   UniquePtr1
   Vector1
   Vector2
   PROPERTIES
   FOLDER "2_Templates/Class_Templates"
   )
