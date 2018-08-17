FROM debian:stretch
WORKDIR /
COPY docker /docker

RUN /docker/install-dependencies.sh
CMD /docker/build.sh
