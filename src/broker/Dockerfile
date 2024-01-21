FROM gcc:12.3.0 as builder
LABEL stage=builder

RUN apt-get update; \
    apt-get install -y cmake libzmq3-dev

WORKDIR /app

COPY ./broker/CMakeLists-docker.txt /app/broker/CMakeLists.txt
COPY ./shared /app/shared
COPY ./broker/src /app/broker/src

RUN cd broker; \
    mkdir -p cmake-build-debug; \
    cd cmake-build-debug; \
    cmake -DCPPZMQ_BUILD_TESTS=OFF -D BUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Release ..

RUN cd broker/cmake-build-debug; cmake --build .

FROM alpine:latest

WORKDIR /app

RUN apk update && apk add --no-cache gcompat libzmq

COPY --from=builder /app /app

EXPOSE 5557
EXPOSE 5558

CMD cd /app/broker/cmake-build-debug; ./broker