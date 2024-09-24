#!/usr/bin/bash

ARCH=aarch64


if [ "`which $ARCH-linux-android21-clang`" = "" ];
then
    export PATH=$ANDROID_SDK_ROOT/ndk/21.0.6113669/toolchains/llvm/prebuilt/linux-x86_64/bin/:$PATH
    if [ "`which $ARCH-linux-android21-clang`" = "" ];
    then
        echo "You should create android NDK toolchains first and add it into your PATH"
        exit
    fi
fi


# build opus
build_opus() {
    mkdir -p build_and/opus
    cd build_and/opus
    ../../opus-1.3.1/configure --host=$ARCH-linux-android CC=$ARCH-linux-android21-clang  CXX=$ARCH-linux-android21-clang++ --prefix=`pwd`/../../prebuilt/opus
    make
    make install
    cd ../..
}

build_libogg() {
    mkdir -p build_and/libogg
    cd build_and/libogg
    ../../libogg-1.3.5/configure --host=$ARCH-linux-android CC=$ARCH-linux-android21-clang  CXX=$ARCH-linux-android21-clang++ --prefix=`pwd`/../../prebuilt/libogg
    make
    make install
    cd ../..
}

# build libvorbis
build_libvorbis() {
    mkdir -p build_and/libvorbis
    cd build_and/libvorbis
    ../../libvorbis-1.3.7/configure --host=$ARCH-linux-android CC=$ARCH-linux-android21-clang  CXX=$ARCH-linux-android21-clang++ --prefix=`pwd`/../../prebuilt/libvorbis --with-ogg=`pwd`/../../prebuilt/libogg
    make
    make install
    cd ../..
}

build_opusfile() {
    mkdir -p build_and/opusfile
    cd build_and/opusfile
    ../../opusfile-0.12/configure --host=$ARCH-linux-android CC=$ARCH-linux-android21-clang  CXX=$ARCH-linux-android21-clang++ --prefix=`pwd`/../../prebuilt/opusfile DEPS_CFLAGS="-I../../prebuilt/libogg/include -I../../prebuilt/opus/include/opus" DEPS_LIBS="-L`pwd`/../../prebuilt/opus/lib -L`pwd`/../../prebuilt/libogg/lib -logg -lopus" --disable-http --disable-examples
    make
    make install
    cd ../..
}

build_unrar() {
    cd unrar
    make -f ../makefile.unrar CXX=$ARCH-linux-android21-clang++ STRIP=$ARCH-linux-android-strip AR=$ARCH-linux-android-ar DESTDIR=`pwd`/../prebuilt/unrar lib
    mv *.a ../prebuilt/unrar
    cd ..
}

build_breakpad() {
    mkdir -p build_and/breakpad
    cd build_and/breakpad
    ../../breakpad/configure --host=$ARCH-linux-android CC=$ARCH-linux-android21-clang  CXX=$ARCH-linux-android21-clang++ --prefix=`pwd`/../../prebuilt/google_breakpad --disable-tools
    make 
    make install
    cd ../..
}

build_jpegturbo() {
    cd libjpeg-turbo
    autoreconf -fiv
    cd ..
    mkdir -p build_and/libjpeg-turbo
    cd build_and/libjpeg-turbo
    ../../libjpeg-turbo/configure --host=$ARCH-linux-android CC=$ARCH-linux-android21-clang  CXX=$ARCH-linux-android21-clang++ --prefix=`pwd`/../../prebuilt/libjpeg-turbo
    make 
    make install
    cd ../..
}

build_ffmpeg() {
    mkdir -p build_and/ffmpeg
    cd build_and/ffmpeg
    ../../ffmpeg/configure --cross-prefix=$ARCH-linux-android- --cc=$ARCH-linux-android21-clang --cxx=$ARCH-linux-android21-clang++ --arch=$ARCH --target-os=android --enable-pic --prefix=`pwd`/../../prebuilt/ffmpeg --disable-doc --disable-programs
    make
    make install -i # ignore set permisson error
    cd ../..
}




build_opus
build_libogg
build_libvorbis
build_opusfile
build_unrar
build_breakpad
build_jpegturbo
build_ffmpeg
