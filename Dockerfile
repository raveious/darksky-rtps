FROM alpine as builder

# Install build dependences
RUN apk add --update --no-cache git cmake make build-base gcc g++ linux-headers openssl openssl-dev openjdk8 gradle boost boost-dev

# Build all of out software
RUN git clone --depth 1 https://github.com/raveious/darksky-rtps.git /home/darksky-rtps
WORKDIR darksky-rtps/build
RUN cmake .. && make
