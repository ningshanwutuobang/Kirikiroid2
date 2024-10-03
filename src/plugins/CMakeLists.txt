cmake_minimum_required(VERSION 3.6)
project(kr2plugin)


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -fPIC")

FILE(GLOB KR2PLUGIN_SRC_LIST

"${CMAKE_CURRENT_SOURCE_DIR}/*.c"
"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
LIST(APPEND
    KR2PLUGIN_SRC_LIST 
    ${CMAKE_CURRENT_SOURCE_DIR}/ncbind/ncbind.cpp)

add_library(kr2plugin
    STATIC
    ${KR2PLUGIN_SRC_LIST}
    )

target_compile_options(
kr2plugin
PUBLIC
-fexceptions -std=c++14 -fvisibility=hidden
)

target_compile_definitions(
kr2plugin
PUBLIC
-D__STDC_CONSTANT_MACROS -DTJS_TEXT_OUT_CRLF 
-DTJS_TEXT_OUT_CRLF
)

target_link_libraries(kr2plugin
    PUBLIC
    krkr
)
