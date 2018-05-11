#!/bin/bash
source /docker/setup-env.sh
x86_64-w64-mingw32.static-qmake-qt5 -recursive CONFIG+="release no-g15 no-overlay no-bonjour no-elevation no-ice asio"
make
cp prhk.bin release/ && zip -r /output/pr-mumble-$GIT_COMMIT.zip release/ -i '*.exe' '*.dll' '*.bin'
