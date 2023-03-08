# This target is "sample" and it is an executable.
# The executable is built from the source file "basic_window.cpp".

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)


include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_executable(sample basic_window.cpp)
target_link_libraries(sample ${GTK3_LIBRARIES})
target_link_libraries(sample d3d9)
