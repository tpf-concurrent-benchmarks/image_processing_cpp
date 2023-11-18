FROM gcc:latest

RUN apt-get update; \
    apt-get install -y cmake

WORKDIR /app

COPY ./size_worker/CMakeLists.txt /app/size_worker/CMakeLists.txt
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