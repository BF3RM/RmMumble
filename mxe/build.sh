#!/bin/bash

SHOULD_PACK=false
BUILD_TYPE=release

pack() {
    cp prhk.bin ${BUILD_TYPE}/ && zip -r rm-mumble-${BUILD_TYPE}.zip ${BUILD_TYPE}/ -i '*.exe' '*.dll' '*.bin'
}

while test $# -gt 0
do
    case "$1" in
        -pack) SHOULD_PACK=true
            ;;
        -debug) BUILD_TYPE=debug 
            ;;
    esac
    shift
done

if [ ! -f mxe/build.sh ]; then
    echo "Please run this script from the parent folder (./mxe/build.sh)."
    exit 1
fi

export MUMBLE_PROTOC=/usr/lib/mxe/usr/x86_64-unknown-linux-gnu/bin/protoc
export PATH=$PATH:/usr/lib/mxe/usr/bin

x86_64-w64-mingw32.static-qmake-qt5 -recursive CONFIG+="${BUILD_TYPE} no-g15 no-overlay no-bonjour no-elevation no-ice asio" INCLUDEDIR+="/usr/lib/mxe/usr/x86_64-w64-mingw32.static/qt5/include/"
make

EXIT_STATUS=$?

if [ $EXIT_STATUS -eq 0 ] && [ $SHOULD_PACK ]; then
    pack
fi
