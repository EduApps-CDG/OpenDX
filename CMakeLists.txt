# SPDX-FileCopyrightText: 2023 <copyright holder> <email>
# SPDX-License-Identifier: Apache-2.0

# - Try to find 
# Once done this will define
#  _FOUND - System has 
#  _INCLUDE_DIRS - The  include directories
#  _LIBRARIES - The libraries needed to use 
#  _DEFINITIONS - Compiler switches required for using 

set(CMAKE_BUILD_TYPE Debug)
set(PROJECT_SOURCE_DIR "${CMAKE_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/opendx/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/opendx/lib")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#Package
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/opendx)
set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME "opendx")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_DESCRIPTION "Open Source reimplementation of DirectX for Linux")
set(CPACK_PACKAGE_CONTACT "Eduardo P. Gomez <eduardoprocopiogomez@gmail.com>")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libgtk-4-1, libdrm2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=default -Wno-undef")

set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "${CPACK_PACKAGE_CONTACT}")
set(CPACK_DEBIAN_PACKAGE_SECTION "devel")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")

#base include
include_directories(./include)
configure_file(include/config.hpp.in ../include/config.hpp)

#production include (for use with .so files)
include_directories(./prod_include)

#Defaults
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)
cmake_minimum_required(VERSION 3.22)
project(OpenDX)

#Dependency
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)


#Packaging
include(CPack)
install(DIRECTORY ${CMAKE_BINARY_DIR}/opendx/bin DESTINATION /usr/ FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
install(DIRECTORY ${CMAKE_BINARY_DIR}/opendx/lib DESTINATION /usr/ FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ)
install(DIRECTORY ${CMAKE_BINARY_DIR}/opendx/usr DESTINATION / FILE_PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ)
set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA, ${CMAKE_SOURCE_DIR}/build/postinst)

find_package(PkgConfig)
pkg_check_modules(PC_ QUIET )
set(_DEFINITIONS ${PC__CFLAGS_OTHER})

find_path(_INCLUDE_DIR 
          HINTS ${PC__INCLUDEDIR} ${PC__INCLUDE_DIRS}
          PATH_SUFFIXES  )

find_library(_LIBRARY NAMES 
             HINTS ${PC__LIBDIR} ${PC__LIBRARY_DIRS} )
pkg_check_modules(GTK4 REQUIRED gtk4)
pkg_check_modules(LIBDRM REQUIRED libdrm)

set(_LIBRARIES ${_LIBRARY} )
set(_INCLUDE_DIRS ${_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set _FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(  DEFAULT_MSG
                                  _LIBRARY _INCLUDE_DIR)
mark_as_advanced(_INCLUDE_DIR _LIBRARY )

find_package(PkgConfig REQUIRED)

#dependency
include_directories(${GTK4_INCLUDE_DIRS})
link_directories(${GTK4_LIBRARY_DIRS})
include_directories(${LIBDRM_INCLUDE_DIRS})
link_directories(${LIBDRM_LIBRARY_DIRS})

#libopendx.so:
set(OPENDX_CPP libs/opendx/opendx.cpp)
#file(GLOB_RECURSE OPENDX_CPP libs/opendx/fun/*.cpp)
add_library(opendx SHARED ${OPENDX_CPP})
target_link_libraries(opendx ${GTK4_LIBRARIES})
target_link_libraries(opendx ${LIBDRM_LIBRARIES})

#libdsetup.so:
set(DSETUP_CPP libs/dsetup/dsetup.cpp)
file(GLOB_RECURSE DSETUP_CPP libs/dsetup/fun/*.cpp)

add_library(dsetup SHARED ${DSETUP_CPP})


#libd3d9.so:
file(GLOB D3D9_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "libs/d3d9/*.cpp")
add_library(d3d9 SHARED ${D3D9_SOURCES})
target_link_libraries(d3d9 ${LIBDRM_LIBRARIES})
target_include_directories(d3d9 PRIVATE ${GTK4_INCLUDE_DIRS})

# if(CMAKE_BUILD_TYPE STREQUAL "Debug")
#     target_link_libraries(d3d9 d3d9_i915)
# endif()

#libd3d9_i915.so:
file(GLOB_RECURSE D3D9_I915_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "libs/d3d9/i915/*.cpp")
add_library(d3d9_i915 SHARED ${D3D9_I915_SOURCES})
target_link_libraries(d3d9_i915 ${LIBDRM_LIBRARIES})
target_link_libraries(d3d9_i915 d3d9)
target_link_libraries(d3d9_i915 opendx)


#libd3d9_vmwgfx.so:
file(GLOB_RECURSE D3D9_VMWGFX_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "libs/d3d9/vmwgfx/*.cpp")
add_library(d3d9_vmwgfx SHARED ${D3D9_VMWGFX_SOURCES})
target_link_libraries(d3d9_vmwgfx ${LIBDRM_LIBRARIES})
target_link_libraries(d3d9_vmwgfx d3d9)
target_link_libraries(d3d9_vmwgfx opendx)

#libd3d9_bochs.so:
file(GLOB_RECURSE D3D9_BOCHS_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "libs/d3d9/bochs/*.cpp")
add_library(d3d9_bochs SHARED ${D3D9_BOCHS_SOURCES})
target_link_libraries(d3d9_bochs ${LIBDRM_LIBRARIES})
target_link_libraries(d3d9_bochs d3d9)
target_link_libraries(d3d9_bochs opendx)

#dxdiag:
add_executable(dxdiag tools/dxdiag/main.cpp)
target_link_libraries(dxdiag ${GTK4_LIBRARIES})
target_link_libraries(dxdiag dsetup)
target_link_libraries(dxdiag d3d9)

include(tests/CMakeLists.txt)
