#!/bin/bash
export MUMBLE_PROTOC=/usr/lib/mxe/usr/x86_64-unknown-linux-gnu/bin/protoc
export PATH=$PATH:/usr/lib/mxe/usr/bin
if [ ! -f /app/prhk.bin ]; then
	echo 'Looks like there are no mumble sources available. Did you forget to mount the source directory to /app?'
	exit 1
fi

wget http://www.steinberg.net/sdk_downloads/asiosdk2.3.zip -P /tmp/
unzip /tmp/asiosdk2.3.zip -d /tmp/
mv /tmp/ASIOSDK2.3 3rdparty/asio

x86_64-w64-mingw32.static-qmake-qt5 -recursive CONFIG+="release no-g15 no-overlay no-bonjour no-elevation no-ice asio"
make
mkdir output > /dev/null
cp prhk.bin release/ && zip -r "output/pr-mumble-$(date '+%d-%m-%Y').zip" release/ -i '*.exe' '*.dll' '*.bin'

