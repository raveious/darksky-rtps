# Build environment for the application
FROM raveious/fastrtps as builder

# Install build dependences
RUN apk add --update --no-cache git cmake make build-base gcc g++ linux-headers openssl openssl-dev boost boost-dev

# Build cpprestsdk
RUN git clone --depth 1 https://github.com/Microsoft/cpprestsdk.git /home/cpprestsdk
WORKDIR /home/cpprestsdk/build
RUN cmake .. && make && make install

# Build forcaster
RUN git clone --depth 1 https://github.com/raveious/darksky-rtps.git /home/forcaster
WORKDIR /home/forcaster/build
RUN cmake .. && make

# Production container should only container the executable
FROM alpine

#COPY --from=builder /usr/local/include/pplx /usr/local/include/pplx
#COPY --from=builder /usr/local/include/cpprest /usr/local/include/cpprest
COPY --from=builder /usr/local/lib64/* /usr/local/lib64/
COPY --from=builder /usr/local/lib/cpprestsdk /usr/local/lib/cpprestsdk

COPY --from=builder /home/darksky-rtps/build/forcaster /usr/bin/forcaster

CMD forcaster
