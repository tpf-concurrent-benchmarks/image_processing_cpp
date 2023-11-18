FROM gcc:latest

RUN apt-get update; \
    apt-get install -y cmake

WORKDIR /app

COPY ./manager/CMakeLists.txt /app/manager/CMakeLists.txt
COPY ./shared /app/shared
COPY ./manager/src /app/manager/src

RUN cd manager; \
    mkdir -p cmake-build-debug; \
    cd cmake-build-debug; \
    cmake -DCMAKE_BUILD_TYPE=Release ..

RUN cd manager/cmake-build-debug; cmake --build .

EXPOSE 5557
EXPOSE 5558

CMD cd /app/manager/cmake-build-debug; ./manager