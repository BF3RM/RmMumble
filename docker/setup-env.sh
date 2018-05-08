#!/bin/bash
export MUMBLE_PROTOC=/usr/lib/mxe/usr/x86_64-unknown-linux-gnu/bin/protoc
export PATH=$PATH:/usr/lib/mxe/usr/bin

git clone https://$GIT_USER@phab.skayahack.uk/source/pr-mumble.git && cd pr-mumble
git submodule update --init
git checkout $GIT_COMMIT

wget http://www.steinberg.net/sdk_downloads/asiosdk2.3.zip -P /tmp/
unzip /tmp/asiosdk2.3.zip -d /tmp/
mv /tmp/ASIOSDK2.3 3rdparty/asio

