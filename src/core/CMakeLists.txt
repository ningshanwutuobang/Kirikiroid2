project(krkr)
add_compile_options(-fPIC)
add_subdirectory(base/7zip/CPP/ANDROID/7za/jni)

FILE(GLOB KRKR_SRC_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/visual/*.cpp
#     ${CMAKE_CURRENT_SOURCE_DIR}/base/7zip/*.c
#     ${CMAKE_CURRENT_SOURCE_DIR}/base/7zip/C/*.c
#     ${CMAKE_CURRENT_SOURCE_DIR}/base/7zip/CPP/*/*.cpp
#     ${CMAKE_CURRENT_SOURCE_DIR}/base/7zip/CPP/*/*/*.cpp
#     ${CMAKE_CURRENT_SOURCE_DIR}/base/7zip/CPP/*/*/*/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/base/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/base/win32/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/environ/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/environ/ConfigManager/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/environ/cocos2d/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/environ/android/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/environ/linux/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/environ/ui/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/environ/ui/extension/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/environ/win32/SystemControl.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/extension/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/movie/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/movie/*/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/msg/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/msg/win32/MsgImpl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/msg/win32/OptionsDesc.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/sound/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sound/win32/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tjs2/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/encoding/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/minizip/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/minizip/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/win32/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/visual/gl/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/visual/ogl/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/visual/win32/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/visual/ARM/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/visual/ARM/*.c
    )

list(REMOVE_ITEM KRKR_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/visual/Resampler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/base/win32/FuncStubs.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/base/win32/SusieArchive.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/environ/MainFormUnit.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sound/xmmlib.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sound/WaveFormatConverter_SSE.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/visual/win32/GDIFontRasterizer.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/visual/win32/NativeFreeTypeFace.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/visual/win32/TVPSysFont.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/visual/win32/VSyncTimingThread.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/visual/LoadJXR.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/visual/LoadBPG.cpp
)


if (ANDROID_ABI STREQUAL "x86")
    list(REMOVE_ITEM KRKR_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/visual/ARM/tvpgl_arm.cpp)
endif()

# message("KRKR_SRC_FILES=${KRKR_SRC_FILES}")

add_library(krkr
    STATIC
    ${KRKR_SRC_FILES}
    
)


target_include_directories(
    krkr
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/base
    ${CMAKE_CURRENT_SOURCE_DIR}/base/win32 
    ${CMAKE_CURRENT_SOURCE_DIR}/environ 
    ${CMAKE_CURRENT_SOURCE_DIR}/environ/win32 
    ${CMAKE_CURRENT_SOURCE_DIR}/environ/android 
    ${CMAKE_CURRENT_SOURCE_DIR}/environ/sdl 
    ${CMAKE_CURRENT_SOURCE_DIR}/msg 
    ${CMAKE_CURRENT_SOURCE_DIR}/msg/win32 
    ${CMAKE_CURRENT_SOURCE_DIR}/extension
    ${CMAKE_CURRENT_SOURCE_DIR}/sound 
    ${CMAKE_CURRENT_SOURCE_DIR}/sound/win32 
    ${CMAKE_CURRENT_SOURCE_DIR}/tjs2
    ${CMAKE_CURRENT_SOURCE_DIR}/utils 
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/win32
    ${CMAKE_CURRENT_SOURCE_DIR}/visual
    ${CMAKE_CURRENT_SOURCE_DIR}/visual/ARM
    ${CMAKE_CURRENT_SOURCE_DIR}/visual/win32
    ${CMAKE_CURRENT_SOURCE_DIR}/visual/RenderScript/rs
    ${CMAKE_CURRENT_SOURCE_DIR}/../plugins
    ${CMAKE_CURRENT_SOURCE_DIR}/../../3rd/prebuilt/libjpeg-turbo/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../3rd/prebuilt/opencv/sdk/native/jni/include
    # ${CMAKE_CURRENT_SOURCE_DIR}/../../3rd/prebuilt/lz4/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../3rd/lz4/lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../../3rd/libarchive
    ${CMAKE_CURRENT_SOURCE_DIR}/../../3rd/oniguruma/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../3rd/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../3rd/oboe/include
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../3rd/libvorbis-1.3.7/include
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../3rd/opus-1.3.1/include
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../3rd/opusfile-0.12/include
    # ${CMAKE_CURRENT_SOURCE_DIR}/../../3rd/libogg-1.3.5/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../3rd/SDL2-2.0.14/include
#     PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}/base/7zip/CPP/myWindows
#     ${CMAKE_CURRENT_SOURCE_DIR}/base/7zip/CPP/
#     ${CMAKE_CURRENT_SOURCE_DIR}/base/7zip/CPP/include_windows
)
    
target_compile_definitions(krkr 
    PUBLIC
    -DTJS_TEXT_OUT_CRLF -D__STDC_CONSTANT_MACROS -DUSE_UNICODE_FSTRING
    -DTJS_TEXT_OUT_CRLF -D_7ZIP_ST
)

target_link_libraries(krkr 
    PUBLIC
    cocos2d ext_freetype  7za archive_static #  libbpg_static jxrlib_static
    turbojpep_static opencv_core opencv_imgproc ffmpeg OpenAL onig ogg opus vorbis vorbisfile vorbisenc opusfile  breakpad  breakpad_client unrar lz4_static SDL2-static #  oboe # ext_tremolo 
   
)

# target_compile_options(krkr -noWinconsistent-missing-override)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-inconsistent-missing-override")
    
#     $(LOCAL_PATH)/../../vendor/freetype/current/include \
#                  $(LOCAL_PATH)/../plugins \
# 				 $(LOCAL_PATH)/../../vendor/jxrlib/current/common/include \
# 				 $(LOCAL_PATH)/../../vendor/jxrlib/current/image/sys \
# 				 $(LOCAL_PATH)/../../vendor/jxrlib/current/jxrgluelib \
# 				 $(LOCAL_PATH)/../../vendor/libjpeg-turbo/current \
# 				 $(LOCAL_PATH)/../../vendor/onig/current \
# 				 $(LOCAL_PATH)/../../vendor/libiconv/current/include \
# 				 $(LOCAL_PATH)/../../vendor/fmod/include \
#                  $(LOCAL_PATH)/../../vendor/libgdiplus/src \
#                  $(LOCAL_PATH)/../../vendor/opus/current/include \
#                  $(LOCAL_PATH)/../../vendor/opus/opusfile/include \
#                  $(LOCAL_PATH)/../../vendor/opencv/current/build/include \
#                  $(LOCAL_PATH)/../../vendor/openal/current/include \
#                  $(LOCAL_PATH)/../../vendor/lz4 \
# 				 $(LOCAL_PATH)/../../libs/android/bpg/include \
# 				 $(LOCAL_PATH)/../../libs/android/ffmpeg/include \
# 				 $(LOCAL_PATH)/../../libs/android/libarchive/include \
#                  $(LOCAL_PATH)/visual/RenderScript/rs \
#     $(LOCAL_PATH)/../../vendor/cocos2d-x/current/cocos \
# 	$(LOCAL_PATH)/../../vendor/cocos2d-x/current/cocos/platform \
#     $(LOCAL_PATH)/../../vendor/cocos2d-x/current/external/webp/include/android \
#     $(LOCAL_PATH)/../../vendor/cocos2d-x/current/external/jpeg/include/android \
#     $(LOCAL_PATH)/../../vendor/cocos2d-x/current/external/png/include/android \
#     $(LOCAL_PATH)/../../vendor/cocos2d-x/current/external \

