 
# set(SOURCE CCModuleJPEG.cpp)
cmake_minimum_required(VERSION 3.6)
project(turbojpep_static)

add_library( # Sets the name of the library.
            turbojpep_static

             # Sets the library as ashared library.
             STATIC

             # Provides a relative pathto your source file(s).
             IMPORTED   GLOBAL)

set_target_properties(
            turbojpep_static
            PROPERTIES IMPORTED_LOCATION
           ${CMAKE_CURRENT_SOURCE_DIR}/${platform_spec_path_3rd}/lib/libturbojpeg.a)
           
set_target_properties(
            turbojpep_static
            PROPERTIES INTERFACE_INCLUDE_DIRECTORIES
            ${CMAKE_CURRENT_SOURCE_DIR}/${platform_spec_path_3rd}/include
)

# add_library(cocosjpeg STATIC ${SOURCE})
# 
# target_link_libraries(cocosjpeg jpeg cocos2d)
# 
# set_target_properties(cocosjpeg
#     PROPERTIES
#     ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
#     LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
# )
