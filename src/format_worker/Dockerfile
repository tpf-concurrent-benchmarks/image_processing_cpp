FROM gcc:latest

RUN apt-get update; \
    apt-get install -y cmake

WORKDIR /app

COPY ./format_worker/CMakeLists.txt /app/format_worker/CMakeLists.txt
COPY ./shared /app/shared
COPY ./format_worker/src /app/format_worker/src

RUN cd format_worker; \
    mkdir -p cmake-build-debug; \
    cd cmake-build-debug; \
    cmake -DCMAKE_BUILD_TYPE=Release ..

RUN cd format_worker/cmake-build-debug; cmake --build .

EXPOSE 5557
EXPOSE 5558

CMD cd /app/format_worker/cmake-build-debug; ./format-worker