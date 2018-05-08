FROM debian:stretch
ADD . /mumble
WORKDIR /mumble

RUN ./docker/install-dependencies.sh
CMD ./docker/build.sh
