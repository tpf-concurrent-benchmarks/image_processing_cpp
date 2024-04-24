# Image Processing - C++

## Objective

This is a C++ implementation of an image processing pipeline under [common specifications](https://github.com/tpf-concurrent-benchmarks/docs/tree/main/image_processing) defined for multiple languages.

The objective of this project is to benchmark the language on a real-world distributed system.

## Deployment

### Requirements

- [Docker >3](https://www.docker.com/) (needs docker swarm)
- [CMake 3.25](https://cmake.org/) (for local development)
- [g++ 12.3.0](https://gcc.gnu.org/) (for local development)

### Configuration

- **Number of replicas:** `N_WORKERS` constant is defined in the `Makefile` file, and determines the number of worker replicas per
stage.

### Commands

#### Startup

- `make setup` will make required initializations, equivalent to:
  - `make init`: starts docker swarm
  - `make build`: builds manager and worker images
- `make template_data`: downloads test image into the input folder

#### Run

- `make deploy`: deploys the manager and worker services locally, alongside with Graphite, Grafana and cAdvisor.
- `make remove`: removes all services (stops the swarm)
- `make full_build_master_local:`  builds the manager locally (it downloads and builds all dependencies, so it may take a while). Same for `make full_build_worker_local`.
- `make build_master_local:` builds the manager locally, useful when doing local development and you already run `make full_build_master_local:`. Same goes for the workers.
- `make run_master_local:` runs the master locally. It asumes that the master project has been built. Same goes for the workers.

#### Local development

The project can be built with the following commands once you are in the root directory of the desired project:

```bash
mkdir cmake-build-debug
cd cmake-build-debug
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

If you have already built the project (with its dependencies) and only want to build the executable, run the following command:

```bash
cmake --build .
```

This is particularly useful when you are local developing and want to build the project faster, as you don't need to build the dependencies every time.

##### About ports on worker and manager

The default ZMQ ports for the manager are 5557 (PUSH) and 5558 (PULL). The ports in the worker must be the same as the ones in the mananager but interchanged.
For instance, if the manager is using 5557 (PUSH) and 5558 (PULL), the worker must use 5558 (PUSH) and 5557 (PULL).

## Used libraries

- [json](https://github.com/nlohmann/json): JSON for Modern C++
- [libzmq](https://github.com/zeromq/libzmq): ZeroMQ core engine in C++
- [cpp-statsd-client](https://github.com/vthiery/cpp-statsd-client): Statsd client implementation for C++
- [stb](https://github.com/nothings/stb): Single-file public domain (or MIT licensed) libraries for C/C++
