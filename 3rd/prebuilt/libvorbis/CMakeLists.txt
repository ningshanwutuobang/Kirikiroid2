 
# set(SOURCE CCModuleJPEG.cpp)
cmake_minimum_required(VERSION 3.6)
set(lib_name vorbis)
project(${lib_name})

add_library( # Sets the name of the library.
            ${lib_name}

             # Sets the library as ashared library.
             STATIC

             # Provides a relative pathto your source file(s).
             IMPORTED   GLOBAL)

set_target_properties(
            ${lib_name}
            PROPERTIES IMPORTED_LOCATION
           ${CMAKE_CURRENT_SOURCE_DIR}/${platform_spec_path_3rd}/lib/lib${lib_name}.a)
           
set_target_properties(
            ${lib_name}
            PROPERTIES INTERFACE_INCLUDE_DIRECTORIES
            ${CMAKE_CURRENT_SOURCE_DIR}/${platform_spec_path_3rd}/include
)


set(lib_name vorbisenc)

add_library( # Sets the name of the library.
            ${lib_name}

             # Sets the library as ashared library.
             STATIC

             # Provides a relative pathto your source file(s).
             IMPORTED   GLOBAL)

set_target_properties(
            ${lib_name}
            PROPERTIES IMPORTED_LOCATION
           ${CMAKE_CURRENT_SOURCE_DIR}/${platform_spec_path_3rd}/lib/lib${lib_name}.a)
           
set_target_properties(
            ${lib_name}
            PROPERTIES INTERFACE_INCLUDE_DIRECTORIES
            ${CMAKE_CURRENT_SOURCE_DIR}/${platform_spec_path_3rd}/include
)

target_link_libraries(${lib_name} INTERFACE vorbis)

set(lib_name vorbisfile)

add_library( # Sets the name of the library.
            ${lib_name}

             # Sets the library as ashared library.
             STATIC

             # Provides a relative pathto your source file(s).
             IMPORTED   GLOBAL)

set_target_properties(
            ${lib_name}
            PROPERTIES IMPORTED_LOCATION
           ${CMAKE_CURRENT_SOURCE_DIR}/${platform_spec_path_3rd}/lib/lib${lib_name}.a)
           
set_target_properties(
            ${lib_name}
            PROPERTIES INTERFACE_INCLUDE_DIRECTORIES
            ${CMAKE_CURRENT_SOURCE_DIR}/${platform_spec_path_3rd}/include
)

target_link_libraries(${lib_name} INTERFACE vorbis vorbisenc)
