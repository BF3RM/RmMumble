#!/bin/bash

pack() {
    cp prhk.bin release/ && zip -r rm-mumble.zip release/ -i '*.exe' '*.dll' '*.bin'
}

if [ ! -f mxe/build.sh ]; then
    echo "Please run this script from the parent folder (./mxe/build.sh)."
    exit 1
fi

export MUMBLE_PROTOC=/usr/lib/mxe/usr/x86_64-unknown-linux-gnu/bin/protoc
export PATH=$PATH:/usr/lib/mxe/usr/bin

x86_64-w64-mingw32.static-qmake-qt5 -recursive CONFIG+="release no-g15 no-overlay no-bonjour no-elevation no-ice asio" INCLUDEDIR+="/usr/lib/mxe/usr/x86_64-w64-mingw32.static/qt5/include/"
make -j10

EXIT_STATUS=$?

if [ $EXIT_STATUS -eq 0 ]; then
    while test $# -gt 0
    do
        case "$1" in
            -pack) pack
                ;;
            #*) echo "argument $1"
            #    ;;
        esac
        shift
    done
fi
