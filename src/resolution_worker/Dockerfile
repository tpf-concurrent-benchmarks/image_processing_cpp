FROM gcc:12.3.0 as builder
LABEL stage=builder

RUN apt-get update; \
    apt-get install -y cmake libzmq3-dev

WORKDIR /app

COPY ./resolution_worker/CMakeLists-docker.txt /app/resolution_worker/CMakeLists.txt
COPY ./resolution_worker/resources /app/resolution_worker/resources
COPY ./shared /app/shared
COPY ./resolution_worker/src /app/resolution_worker/src

RUN cd resolution_worker; \
    mkdir -p cmake-build-debug; \
    cd cmake-build-debug; \
    cmake -DCPPZMQ_BUILD_TESTS=OFF -D BUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Release ..

RUN cd resolution_worker/cmake-build-debug; cmake --build .

FROM alpine:latest

WORKDIR /app

RUN apk update && apk add --no-cache gcompat libzmq

COPY --from=builder /app /app

EXPOSE 5557
EXPOSE 5558

CMD cd /app/resolution_worker/cmake-build-debug; ./resolution-worker