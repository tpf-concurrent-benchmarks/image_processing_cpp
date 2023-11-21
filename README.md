# Image Processing in C++

## How to build with CMake

It can be built with the following commands once you are in the root directory of the desired project:

```bash
mkdir cmake-build-debug
cd cmake-build-debug
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

## Building only the project

If you have already built the project (with its dependencies) and only want to build the executable, run the following command:

```bash
cmake --build .
```

This is particularly useful when you are local developing and want to build the project faster, as you don't need to build the dependencies every time.

## Running all services with Docker

```bash
docker compose -f=docker-compose-deploy-local.yml up
```

## Running only Graphite, Grafana and cAdvisor with Docker

```bash
docker compose -f=docker-compose-graphite.yaml up
```

## About ports on worker and manager

The default ZMQ ports for the manager are 5557 (PUSH) and 5558 (PULL). The ports in the worker must be the same as the ones in the mananager but interchanged.
For instance, if the manager is using 5557 (PUSH) and 5558 (PULL), the worker must use 5558 (PUSH) and 5557 (PULL).

## Number of replicas

If you wish to change the number of replicas, you can do so by changing the `N_WORKERS` constant in the `Makefile` file.

## Makefile

There is a Makefile in the root directory of the project that can be used to build and run the project

- `make build`: builds manager and worker images
- `make deploy`: deploys the manager and worker services locally, alongside with Graphite, Grafana and cAdvisor.
- `make deploy_remote`: deploys (with Docker Swarm) the manager and worker services, alongside with Graphite, Grafana and cAdvisor.
- `make remove`: removes all services (stops the swarm)
- `make full_build_master_local:`  builds the manager locally (it downloads and builds all dependencies, so it may take a while). Same for `make full_build_worker_local`.
- `make build_master_local:` builds the manager locally, useful when doing local development and you already run `make full_build_master_local:`. Same goes for the workers.
- `make run_master_local:` runs the worker locally. It asumes that the master project has been built. Same goes for the workers.

## Running the project

Once one of the projects is built, you can run the executable with the following command once you are in the `cmake-build-debug `directory.
For example, if you want to run the manager, you can do:

```bash
./manager
```

## Used libraries

- [json](https://github.com/nlohmann/json): JSON for Modern C++
- [libzmq](https://github.com/zeromq/libzmq): ZeroMQ core engine in C++
- [cpp-statsd-client](https://github.com/vthiery/cpp-statsd-client): Statsd client implementation for C++
- [stb](https://github.com/nothings/stb): Single-file public domain (or MIT licensed) libraries for C/C++
