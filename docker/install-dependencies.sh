#!/bin/bash

apt update

apt install -y gnupg
apt install -y dirmngr wget unzip

echo "deb http://pkg.mxe.cc/repos/apt/debian jessie main" > /etc/apt/sources.list.d/mxeapt.list
apt-key adv --keyserver keyserver.ubuntu.com --recv-keys D43A795B73B16ABE9643FE1AFD8FFF16DB45C6AB
apt update

apt install -y \
git \
mxe-x86-64-w64-mingw32.static-qtbase \
mxe-x86-64-w64-mingw32.static-qtsvg \
mxe-x86-64-w64-mingw32.static-qttools \
mxe-x86-64-w64-mingw32.static-qttranslations \
mxe-x86-64-w64-mingw32.static-boost \
mxe-x86-64-w64-mingw32.static-protobuf \
mxe-x86-64-w64-mingw32.static-sqlite \
mxe-x86-64-w64-mingw32.static-flac \
mxe-x86-64-w64-mingw32.static-ogg \
mxe-x86-64-w64-mingw32.static-vorbis \
mxe-x86-64-w64-mingw32.static-libsndfile \
mxe-x86-64-w64-mingw32.static-dlfcn-win32
