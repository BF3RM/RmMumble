#!/bin/sh
cp docker/Dockerfile .
docker build -t mumblepr .
rm Dockerfile
