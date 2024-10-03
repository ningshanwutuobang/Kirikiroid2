project(ffmpeg)
add_library( # Sets the name of the library.
            ffmpeg_avdevice
             # Sets the library as ashared library.
             STATIC
             # Provides a relative pathto your source file(s).
             IMPORTED  GLOBAL)

set_target_properties(
        ffmpeg_avdevice
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_CURRENT_SOURCE_DIR}/${platform_spec_path_3rd}/lib/libavdevice.a
)

add_library( # Sets the name of the library.
            ffmpeg_avfilter
             # Sets the library as ashared library.
             STATIC
             # Provides a relative pathto your source file(s).
             IMPORTED  GLOBAL)

set_target_properties(
        ffmpeg_avfilter
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_CURRENT_SOURCE_DIR}/${platform_spec_path_3rd}/lib/libavfilter.a
)

add_library( # Sets the name of the library.
            ffmpeg_avformat
             # Sets the library as ashared library.
             STATIC
             # Provides a relative pathto your source file(s).
             IMPORTED  GLOBAL)

set_target_properties(
        ffmpeg_avformat
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_CURRENT_SOURCE_DIR}/${platform_spec_path_3rd}/lib/libavformat.a
)


add_library( # Sets the name of the library.
            ffmpeg_avcodec
             # Sets the library as ashared library.
             STATIC
             # Provides a relative pathto your source file(s).
             IMPORTED  GLOBAL)

set_target_properties(
        ffmpeg_avcodec
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_CURRENT_SOURCE_DIR}/${platform_spec_path_3rd}/lib/libavcodec.a
)

add_library( # Sets the name of the library.
            ffmpeg_avutil
             # Sets the library as ashared library.
             STATIC
             # Provides a relative pathto your source file(s).
             IMPORTED  GLOBAL)

set_target_properties(
        ffmpeg_avutil
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_CURRENT_SOURCE_DIR}/${platform_spec_path_3rd}/lib/libavutil.a
)

add_library( # Sets the name of the library.
            ffmpeg_swresample
             # Sets the library as ashared library.
             STATIC
             # Provides a relative pathto your source file(s).
             IMPORTED  GLOBAL)

set_target_properties(
        ffmpeg_swresample
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_CURRENT_SOURCE_DIR}/${platform_spec_path_3rd}/lib/libswresample.a
)


add_library( # Sets the name of the library.
            ffmpeg_swscale
             # Sets the library as ashared library.
             STATIC
             # Provides a relative pathto your source file(s).
             IMPORTED  GLOBAL)

set_target_properties(
        ffmpeg_swscale
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_CURRENT_SOURCE_DIR}/${platform_spec_path_3rd}/lib/libswscale.a
)

add_library( # Sets the name of the library.
            ffmpeg
             # Sets the library as ashared library.
             STATIC
             # Provides a relative pathto your source file(s).
             empty.cpp)



target_include_directories(ffmpeg
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/${platform_spec_path_3rd}/include
)

target_link_libraries(ffmpeg
PUBLIC
ffmpeg_avdevice
ffmpeg_avfilter
ffmpeg_avformat
ffmpeg_avcodec
ffmpeg_avutil
ffmpeg_swresample
ffmpeg_swscale
)
