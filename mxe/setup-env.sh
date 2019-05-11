#!/bin/bash
## Careful! This is debian stretch only and could just die at some point because it relays on mumble's mirror

apt update
apt install -y gnupg curl apt-transport-https apt-utils
curl -sL "http://keyserver.ubuntu.com/pks/lookup?op=get&search=0x86B72ED9" | apt-key add
echo 'deb http://dl.mumble.info/mirror/mirror.mxe.cc/repos/apt/ stretch main' >> /etc/apt/sources.list
apt update
apt install -y mxe-i686-w64-mingw32.static-qt5 mxe-i686-w64-mingw32.static-protobuf mxe-i686-w64-mingw32.static-boost


git clone https://phab.skayahack.uk/source/pr-mumble.git
cd pr-mumble && git submodule update --init
mkdir cmake-build && cd cmake-build
/usr/lib/mxe/usr/bin/i686-w64-mingw32.static-cmake ..
