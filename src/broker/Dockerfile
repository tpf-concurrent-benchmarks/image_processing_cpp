FROM gcc:latest

RUN apt-get update; \
    apt-get install -y cmake; \
    apt-get install -y libzmq3-dev

WORKDIR /app

COPY ./broker/CMakeLists-docker.txt /app/broker/CMakeLists.txt
COPY ./shared /app/shared
COPY ./broker/src /app/broker/src

RUN cd broker; \
    mkdir -p cmake-build-debug; \
    cd cmake-build-debug; \
    cmake -DCMAKE_BUILD_TYPE=Release ..

RUN cd broker/cmake-build-debug; cmake --build .

EXPOSE 5557
EXPOSE 5558

CMD cd /app/broker/cmake-build-debug; ./broker