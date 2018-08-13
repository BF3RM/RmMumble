if [ ! -f mxe/dependencies.sh ]; then
    echo "Please run this script from the parent folder (./mxe/build.sh)."
    exit 1
fi

export MUMBLE_PROTOC=/usr/lib/mxe/usr/x86_64-unknown-linux-gnu/bin/protoc
export PATH=$PATH:/usr/lib/mxe/usr/bin

x86_64-w64-mingw32.static-qmake-qt5 -recursive CONFIG+="release no-g15 no-overlay no-bonjour no-elevation no-ice asio" INCLUDEDIR+="/usr/lib/mxe/usr/x86_64-w64-mingw32.static/qt5/include/"
make
cp prhk.bin release/ && zip -r pr-mumble-$GIT_COMMIT.zip release/ -i '*.exe' '*.dll' '*.bin'
