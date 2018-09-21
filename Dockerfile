# Build environment for the application
FROM alpine:3.8 as builder

# Install build dependences
RUN apk add --update --no-cache git cmake make build-base gcc g++ linux-headers openssl openssl-dev openjdk8 gradle boost boost-dev

# Build all of our software
RUN git clone --depth 1 https://github.com/raveious/darksky-rtps.git /home/darksky-rtps
WORKDIR /home/darksky-rtps
RUN git submodule init && git submodule update
WORKDIR /home/darksky-rtps/build
RUN cmake .. && make

# Production container should only container the executable
FROM alpine:3.8
COPY --from=builder /home/darksky-rtps/build/forcaster /usr/bin/forcaster
CMD forcaster
