#!/bin/bash
source /docker/setup-env.sh
x86_64-w64-mingw32.static-qmake-qt5 -recursive CONFIG+="release g15-emulator no-overlay no-bonjour no-elevation no-ice asio"
make
zip -r /output/pr-mumble-$GIT_COMMIT.zip release/ -i '*.exe' '*.dll' '*.bin'
