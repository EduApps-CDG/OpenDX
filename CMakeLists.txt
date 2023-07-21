# SPDX-FileCopyrightText: 2023 <copyright holder> <email>
# SPDX-License-Identifier: Apache-2.0

# - Try to find 
# Once done this will define
#  _FOUND - System has 
#  _INCLUDE_DIRS - The  include directories
#  _LIBRARIES - The libraries needed to use 
#  _DEFINITIONS - Compiler switches required for using 

cmake_minimum_required(VERSION 3.22)
project(OpenDX)
set(PROJECT_SOURCE_DIR "${CMAKE_SOURCE_DIR}")

find_package(PkgConfig)
pkg_check_modules(PC_ QUIET )
set(_DEFINITIONS ${PC__CFLAGS_OTHER})

find_path(_INCLUDE_DIR 
          HINTS ${PC__INCLUDEDIR} ${PC__INCLUDE_DIRS}
          PATH_SUFFIXES  )

find_library(_LIBRARY NAMES 
             HINTS ${PC__LIBDIR} ${PC__LIBRARY_DIRS} )

set(_LIBRARIES ${_LIBRARY} )
set(_INCLUDE_DIRS ${_INCLUDE_DIR} )
set(CMAKE_CXX_STANDARD 20)

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set _FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(  DEFAULT_MSG
                                  _LIBRARY _INCLUDE_DIR)
mark_as_advanced(_INCLUDE_DIR _LIBRARY )

#base include
include_directories(./include)
configure_file(include/config.hpp.in ../include/config.hpp)

#production include (for use with .so files)
include_directories(./prod_include)

find_package(PkgConfig REQUIRED)

#d3d9.so:
add_library(d3d9 SHARED libs/d3d9/d3d9.cpp)

#dxdiag:
pkg_check_modules(GTK4 REQUIRED gtk4)


include_directories(${GTK4_INCLUDE_DIRS})
link_directories(${GTK4_LIBRARY_DIRS})

add_executable(dxdiag tools/dxdiag/main.cpp)
target_link_libraries(dxdiag ${GTK4_LIBRARIES})
target_link_libraries(dxdiag d3d9)


#add ./tests/CMakeLists.txt
add_subdirectory(tests)
