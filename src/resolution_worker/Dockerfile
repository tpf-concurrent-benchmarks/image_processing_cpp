FROM gcc:latest

RUN apt-get update; \
    apt-get install -y cmake

WORKDIR /app

COPY ./resolution_worker/CMakeLists.txt /app/resolution_worker/CMakeLists.txt
COPY ./shared /app/shared
COPY ./resolution_worker/src /app/resolution_worker/src

RUN cd resolution_worker; \
    mkdir -p cmake-build-debug; \
    cd cmake-build-debug; \
    cmake -DCMAKE_BUILD_TYPE=Release ..

RUN cd resolution_worker/cmake-build-debug; cmake --build .

EXPOSE 5557
EXPOSE 5558

CMD cd /app/resolution_worker/cmake-build-debug; ./resolution-worker