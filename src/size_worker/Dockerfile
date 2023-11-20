FROM gcc:latest

RUN apt-get update; \
    apt-get install -y cmake; \
    apt-get install -y libzmq3-dev

WORKDIR /app

COPY ./size_worker/resources /app/size_worker/resources
COPY ./size_worker/CMakeLists-docker.txt /app/size_worker/CMakeLists.txt
COPY ./shared /app/shared
COPY ./size_worker/src /app/size_worker/src

RUN cd size_worker; \
    mkdir -p cmake-build-debug; \
    cd cmake-build-debug; \
    cmake -DCMAKE_BUILD_TYPE=Release ..

RUN cd size_worker/cmake-build-debug; cmake --build .

EXPOSE 5557
EXPOSE 5558

CMD cd /app/size_worker/cmake-build-debug; ./size-worker