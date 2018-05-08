#!/bin/sh
cp docker/Dockerfile .
docker build -t pr-mumble .
rm Dockerfile
