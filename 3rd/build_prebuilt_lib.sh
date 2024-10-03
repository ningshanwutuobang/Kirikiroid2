#!/usr/bin/bash

ANDROID_ABI=${ANDROID_ABI:-arm64-v8a}

INSTALL_PATH=android/${ANDROID_ABI}
BUILD_DIR=build_and_${ANDROID_ABI}

case $ANDROID_ABI in
    arm64-v8a)
        ARCH=aarch64
        ;;
    armeabi-v7a)
        ARCH=armv7a
        ;;
    x86)
        ARCH=i686
        ;;
    *)
        echo "not supported $arch"
        exit
        ;;
esac


if [[ "$ARCH" == "armv7a" ]];
then
    ARCH2=arm
    PLATFORM=androideabi21
    HOST=$ARCH2-linux-androideabi
else
    ARCH2=$ARCH
    PLATFORM=android21
    HOST=$ARCH2-linux-android
fi

CC=$ARCH-linux-$PLATFORM-clang
CXX=$ARCH-linux-$PLATFORM-clang++

if [ "`which $CC`" = "" ];
then
    export PATH=$ANDROID_SDK_ROOT/ndk/21.0.6113669/toolchains/llvm/prebuilt/linux-x86_64/bin/:$PATH
    if [ "`which $CC`" = "" ];
    then
        echo "You should create android NDK toolchains first and add it into your PATH"
        exit
    fi
fi


# build opus
build_opus() {
    mkdir -p ${BUILD_DIR}/opus
    cd ${BUILD_DIR}/opus
    ../../opus-1.3.1/configure --host=$HOST CC=$CC  CXX=$CXX --prefix=`pwd`/../../prebuilt/opus/${INSTALL_PATH}
    make
    make install
    cd ../..
}

build_libogg() {
    mkdir -p ${BUILD_DIR}/libogg
    cd ${BUILD_DIR}/libogg
    ../../libogg-1.3.5/configure --host=$HOST CC=$CC  CXX=$CXX --prefix=`pwd`/../../prebuilt/libogg/${INSTALL_PATH} CFLAGS=-fPIC
    make
    make install
    cd ../..
}

# build libvorbis
build_libvorbis() {
    sed -i "s/-mno-ieee-fp//" libvorbis-1.3.7/configure
    mkdir -p ${BUILD_DIR}/libvorbis
    cd ${BUILD_DIR}/libvorbis
    ../../libvorbis-1.3.7/configure --host=$HOST CC=$CC  CXX=$CXX --prefix=`pwd`/../../prebuilt/libvorbis/${INSTALL_PATH} --with-ogg=`pwd`/../../prebuilt/libogg/${INSTALL_PATH}  CFLAGS="-Wno-error=unused-command-line-argument -fPIC" --disable-oggtest
    make
    make install
    cd ../..
}

build_opusfile() {
    mkdir -p ${BUILD_DIR}/opusfile
    cd ${BUILD_DIR}/opusfile
    ../../opusfile-0.12/configure --host=$HOST CC=$CC CXX=$CXX --prefix=`pwd`/../../prebuilt/opusfile/${INSTALL_PATH} DEPS_CFLAGS="-I../../prebuilt/libogg/${INSTALL_PATH}/include -I../../prebuilt/opus/${INSTALL_PATH}/include/opus" DEPS_LIBS="-L`pwd`/../../prebuilt/opus/${INSTALL_PATH}/lib -L`pwd`/../../prebuilt/libogg/${INSTALL_PATH}/lib -logg -lopus" --disable-http --disable-examples
    make
    make install
    cd ../..
}

build_unrar() {
    cd unrar
    make -f ../makefile.unrar CXX=$CXX STRIP=$HOST-strip AR=$HOST-ar DESTDIR=`pwd`/../prebuilt/unrar/${INSTALL_PATH} lib
    mkdir -p ../prebuilt/unrar/${INSTALL_PATH}
    mv *.a ../prebuilt/unrar/${INSTALL_PATH}
    cd ..
}

build_breakpad() {
    mkdir -p ${BUILD_DIR}/breakpad
    cd ${BUILD_DIR}/breakpad
    ../../breakpad/configure --host=$HOST CC=$CC CXX=$CXX --prefix=`pwd`/../../prebuilt/google_breakpad/${INSTALL_PATH}/ --disable-tools
    make 
    make install
    cd ../..
}

build_jpegturbo() {
    cd libjpeg-turbo
    autoreconf -fiv
    cd ..
    mkdir -p ${BUILD_DIR}/libjpeg-turbo
    cd ${BUILD_DIR}/libjpeg-turbo
    ../../libjpeg-turbo/configure --host=$HOST CC=$CC CXX=$CXX --prefix=`pwd`/../../prebuilt/libjpeg-turbo/${INSTALL_PATH} --with-pic=pic CFLAGS="-fPIC"
    make 
    make install
    cd ../..
}

build_ffmpeg() {
    mkdir -p ${BUILD_DIR}/ffmpeg
    cd ${BUILD_DIR}/ffmpeg
    ../../ffmpeg/configure --cross-prefix=$HOST- --cc=$CC --cxx=$CXX --arch=$ARCH --target-os=android --enable-pic --prefix=`pwd`/../../prebuilt/ffmpeg/${INSTALL_PATH} --disable-doc --disable-programs --disable-asm --extra-cflags=-DBIONIC_IOCTL_NO_SIGNEDNESS_OVERLOAD
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
