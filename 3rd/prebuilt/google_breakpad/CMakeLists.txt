 
# set(SOURCE CCModuleJPEG.cpp)
cmake_minimum_required(VERSION 3.6)
set(lib_name breakpad)
project(${lib_name})

add_library( # Sets the name of the library.
            ${lib_name}

             # Sets the library as ashared library.
             STATIC

             # Provides a relative pathto your source file(s).
             IMPORTED   GLOBAL)

set_target_properties(${lib_name}
            PROPERTIES IMPORTED_LOCATION
            ${CMAKE_CURRENT_SOURCE_DIR}/${platform_spec_path_3rd}/lib/lib${lib_name}.a
)
set_target_properties(${lib_name}
            PROPERTIES INTERFACE_INCLUDE_DIRECTORIES
            ${CMAKE_CURRENT_SOURCE_DIR}/${platform_spec_path_3rd}/include
)

add_library( # Sets the name of the library.
            ${lib_name}_client

             # Sets the library as ashared library.
             STATIC

             # Provides a relative pathto your source file(s).
             IMPORTED   GLOBAL)

set_target_properties(${lib_name}_client
            PROPERTIES IMPORTED_LOCATION
            ${CMAKE_CURRENT_SOURCE_DIR}/${platform_spec_path_3rd}/lib/lib${lib_name}_client.a
)
set_target_properties(${lib_name}_client
            PROPERTIES INTERFACE_INCLUDE_DIRECTORIES
            ${CMAKE_CURRENT_SOURCE_DIR}/${platform_spec_path_3rd}/include
)
