#!/usr/bin/bash

# update submodule 
git submodule init
git submodule update --init
git submodule sync
cd ffmpeg 
git apply ../ffmpeg.diff
cd ..
cp android_lf.h libarchive/libarchive/
cp linux-syscall-support/lss breakpad/src/third_party/ -r

# download other files

wget https://downloads.xiph.org/releases/vorbis/libvorbis-1.3.7.tar.xz
wget https://downloads.xiph.org/releases/ogg/libogg-1.3.5.tar.xz
wget https://archive.mozilla.org/pub/opus/opus-1.3.1.tar.gz
wget https://downloads.xiph.org/releases/opus/opusfile-0.12.tar.gz
wget https://www.rarlab.com/rar/unrarsrc-6.0.7.tar.gz
wget http://www.libsdl.org/release/SDL2-2.0.14.tar.gz


tar xvf libvorbis-1.3.7.tar.xz
tar xvf libogg-1.3.5.tar.xz
tar xvf opus-1.3.1.tar.gz
tar xvf opusfile-0.12.tar.gz
tar xvf unrarsrc-6.0.7.tar.gz
tar xvf SDL2-2.0.14.tar.gz

cp SDL_android.c SDL2-2.0.14/src/core/android/


