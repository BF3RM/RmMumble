FROM debian:stretch
ADD . /mumble
WORKDIR /mumble
RUN ./docker/install-dependencies.sh
CMD ['/mumble/docker/build.sh']
