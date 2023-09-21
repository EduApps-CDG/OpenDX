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

#Package
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/opendx)
set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME "opendx")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_DESCRIPTION "Open Source reimplementation of DirectX for Linux")
set(CPACK_PACKAGE_CONTACT "Eduardo P. Gomez <eduardoprocopiogomez@gmail.com>")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libgtk-4-1")

include(CPack)
install(DIRECTORY ${CMAKE_BINARY_DIR}/opendx/bin DESTINATION /usr/ FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
install(DIRECTORY ${CMAKE_BINARY_DIR}/opendx/lib DESTINATION /usr/ FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/opendx/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/opendx/lib")

#C/C++ flags
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

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

#dependency
include_directories(${GTK4_INCLUDE_DIRS})
link_directories(${GTK4_LIBRARY_DIRS})

#libopendx.so:
set(OPENDX_CPP libs/opendx/opendx.cpp)
#file(GLOB_RECURSE OPENDX_CPP libs/opendx/fun/*.cpp)
add_library(opendx SHARED ${OPENDX_CPP})
target_link_libraries(opendx ${GTK4_LIBRARIES})

#libdsetup.so:
set(DSETUP_CPP libs/dsetup/dsetup.cpp)
file(GLOB_RECURSE DSETUP_CPP libs/dsetup/fun/*.cpp)

add_library(dsetup SHARED ${DSETUP_CPP})

#libd3d9.so:
add_library(d3d9 SHARED libs/d3d9/d3d9.cpp)

#dxdiag:
pkg_check_modules(GTK4 REQUIRED gtk4)

add_executable(dxdiag tools/dxdiag/main.cpp)
target_link_libraries(dxdiag ${GTK4_LIBRARIES})
target_link_libraries(dxdiag dsetup)
target_link_libraries(dxdiag d3d9)


#add ./tests/CMakeLists.txt
add_subdirectory(tests)
