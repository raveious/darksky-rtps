# Build environment for the application
FROM raveious/darksky-rtps:dev as builder

# Build forcaster
RUN git clone --depth 1 --recurse-submodules --single-branch https://github.com/raveious/darksky-rtps.git /darksky-rtps
WORKDIR /darksky-rtps/build
RUN cmake .. && make forcaster

# Production container should only container the executable
FROM raveious/fastrtps:alpine-latest

# Exposing known ports for this node
EXPOSE 44084/udp 17900/udp 17910/udp 17911/udp

# boost is loaded dynamically
RUN apk add --update --no-cache boost

#COPY --from=builder /usr/local/include/* /usr/local/include/
COPY --from=builder /usr/local/lib64/* /usr/local/lib64/
COPY --from=builder /usr/local/lib/* /usr/local/lib/

COPY --from=builder /darksky-rtps/build/forcaster/forcaster /usr/local/bin/forcaster

CMD forcaster
