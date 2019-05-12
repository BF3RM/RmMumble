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


apt update
apt install -y autoconf automake autopoint bash bison bzip2 flex g++ g++-multilib gettext git gperf intltool libc6-dev-i386 libgdk-pixbuf2.0-dev libltdl-dev libssl-dev libtool-bin libxml-parser-perl lzip make openssl p7zip-full patch perl pkg-config python ruby sed unzip wget xz-utils
git clone https://github.com/snaiperskaya96/mxe.git && cd mxe
make qtbase qtsvg qttools qttranslations boost protobuf sqlite flac ogg vorbis libsndfile dlfcn-win32 opus cc MXE_PLUGIN_DIRS=plugins/examples/qt5-freeze MXE_TARGETS=x86_64-w64-mingw32.shared --jobs=3 JOBS=2

PATH=$PATH:/mxe/usr/bin/ make -j6
PATH=$PATH:/mxe/usr/bin/ make -j6


bash /mxe/tools/copydlldeps.sh --infile bin/RmMumbleApp.dll --destdir bin/ --recursivesrcdir /mxe/usr/x86_64-w64-mingw32.shared/ --copy --enforcedir /mxe/usr/x86_64-w64-mingw32.shared/qt5/plugins/platforms/ --enforcedir /mxe/usr/x86_64-w64-mingw32.shared/qt5/plugins/sqldrivers/ --objdump /mxe/usr/bin/x86_64-w64-mingw32.shared-objdump