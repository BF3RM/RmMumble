FROM debian:jessie
RUN mkdir /app
WORKDIR /app

COPY build.sh /app/build.sh
RUN apt update && apt install -y apt-transport-https
RUN echo "deb https://mumble.info/snapshot/mirror/pkg.mxe.cc/repos/apt/debian jessie main" > /etc/apt/sources.list.d/mxeapt.list
RUN apt update
RUN apt-key adv --keyserver keyserver.ubuntu.com --recv-keys D43A795B73B16ABE9643FE1AFD8FFF16DB45C6AB

RUN apt install -y --force-yes mxe-x86-64-w64-mingw32.static-qtbase \
	mxe-x86-64-w64-mingw32.static-qtsvg \
	mxe-x86-64-w64-mingw32.static-qttools \
	mxe-x86-64-w64-mingw32.static-qttranslations \
	mxe-x86-64-w64-mingw32.static-boost \
	mxe-x86-64-w64-mingw32.static-protobuf \
	mxe-x86-64-w64-mingw32.static-sqlite \
	mxe-x86-64-w64-mingw32.static-flac \
 	mxe-x86-64-w64-mingw32.static-ogg \
	mxe-x86-64-w64-mingw32.static-vorbis \
	mxe-x86-64-w64-mingw32.static-libsndfile

RUN apt install -y zip
HEALTHCHECK CMD pidof -x "build.sh" >/dev/null || exit 1
CMD ./docker/build.sh

