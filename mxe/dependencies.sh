#!/bin/bash

if [ ! -f mxe/dependencies.sh ]; then
    echo "Please run this script from the parent folder (./mxe/dependencies.sh)."
    exit 1
fi

if [[ $EUID -ne 0 ]]; then
   echo "This script must be run as root" 
   exit 1
fi

apt update

apt install -y gnupg
apt install -y dirmngr wget zip unzip

echo "deb https://mumble.info/snapshot/mirror/pkg.mxe.cc/repos/apt/debian jessie main" > /etc/apt/sources.list.d/mxeapt.list
#apt-key adv --keyserver keyserver.ubuntu.com --recv-keys D43A795B73B16ABE9643FE1AFD8FFF16DB45C6AB
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

wget http://www.steinberg.net/sdk_downloads/asiosdk2.3.zip -P /tmp/
unzip /tmp/asiosdk2.3.zip -d /tmp/
mv /tmp/ASIOSDK2.3 3rdparty/asio
