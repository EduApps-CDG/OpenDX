# This target is "sample" and it is an executable.
# The executable is built from the source file "basic_window.cpp".

pkg_check_modules(GTK4 REQUIRED gtk4)


include_directories(${GTK4_INCLUDE_DIRS})
link_directories(${GTK4_LIBRARY_DIRS})

add_executable(sample basic_window.cpp)
target_link_libraries(sample ${GTK4_LIBRARIES})
target_link_libraries(sample d3d9)
