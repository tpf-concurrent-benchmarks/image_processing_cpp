EXEC_MANAGER = manager
EXEC_SIZE_WORKER = size-worker
EXEC_RESOLUTION_WORKER = resolution-worker
EXEC_FORMAT_WORKER = format-worker
EXEC_BROKER = broker

init:
	docker swarm init

build:
	docker rmi image_processing_cpp_size_worker -f
	docker rmi image_processing_cpp_format_worker -f
	docker rmi image_processing_cpp_resolution_worker -f
	docker rmi image_processing_cpp_manager -f
	docker rmi image_processing_broker -f
	docker build -t image_processing_cpp_resolution_worker ./src/ -f ./src/resolution_worker/Dockerfile
	docker build -t image_processing_cpp_format_worker ./src/ -f ./src/format_worker/Dockerfile
	docker build -t image_processing_cpp_size_worker ./src/ -f ./src/size_worker/Dockerfile
	docker build -t image_processing_cpp_manager ./src/ -f ./src/manager/Dockerfile
	docker build -t image_processing_cpp_broker ./src/ -f ./src/broker/Dockerfile

setup: init build

deploy:
	mkdir -p graphite
	mkdir -p shared_vol
	mkdir -p shared_vol/input
	mkdir -p shared_vol/resized
	mkdir -p shared_vol/formatted
	mkdir -p shared_vol/cropped
	docker compose -f=docker-compose-deploy-local.yml up

deploy_remote:
	mkdir -p graphite
	mkdir -p shared_vol
	mkdir -p shared_vol/input
	mkdir -p shared_vol/resized
	mkdir -p shared_vol/formatted
	mkdir -p shared_vol/cropped
	N_WORKERS=${N_WORKERS} docker stack deploy -c docker-compose-deploy.yml image_processing_cpp

remove:
	docker stack rm image_processing_cpp

full_build_manager_local:
	cd src/manager/ && mkdir -p cmake-build-debug && cd cmake-build-debug && cmake -DCMAKE_BUILD_TYPE=Release ..  && cmake --build .

build_manager_local:
	cd src/manager/cmake-build-debug && cmake --build .

run_manager_local:
	cd src/manager/cmake-build-debug && ENV=LOCAL N_WORKERS=${N_WORKERS} ./${EXEC_MANAGER}

full_build_workers_local:
	cd src/format_worker/ && mkdir -p cmake-build-debug && cd cmake-build-debug && cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build .
	cd src/resolution_worker/ && mkdir -p cmake-build-debug && cd cmake-build-debug && cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build .
	cd src/size_worker/ && mkdir -p cmake-build-debug && cd cmake-build-debug && cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build .
	cd src/broker/ && mkdir -p cmake-build-debug && cd cmake-build-debug && cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build .

build_workers_local:
	cd src/format_worker/cmake-build-debug && cmake --build .
	cd src/resolution_worker/cmake-build-debug && cmake --build .
	cd src/size_worker/cmake-build-debug && cmake --build .

build_resolution_local:
	cd src/resolution_worker/cmake-build-debug && cmake --build .

build_format_local:
	cd src/format_worker/cmake-build-debug && cmake --build .

build_size_local:
	cd src/size_worker/cmake-build-debug && cmake --build .

build_broker_local:
	cd src/broker/cmake-build-debug && cmake --build .

run_format_worker_local:
	cd src/format_worker/cmake-build-debug && ENV=LOCAL ./$(EXEC_FORMAT_WORKER)

run_resolution_worker_local:
	cd src/resolution_worker/cmake-build-debug && ENV=LOCAL ./$(EXEC_RESOLUTION_WORKER)

run_size_worker_local:
	cd src/size_worker/cmake-build-debug && ENV=LOCAL ./$(EXEC_SIZE_WORKER)

run_broker_local:
	cd src/broker/cmake-build-debug && ENV=LOCAL ./$(EXEC_BROKER)


format:
	clang-format -i src/manager/src/**/*.cpp src/manager/src/**/*.h
	clang-format -i src/format_worker/src/**/*.cpp src/format_worker/src/**/*.h
	clang-format -i src/resolution_worker/src/**/*.cpp src/resolution_worker/src/**/*.h
	clang-format -i src/size_worker/src/**/*.cpp src/size_worker/src/**/*.h
	clang-format -i src/broker/src/**/*.cpp src/broker/src/**/*.h
	clang-format -i src/manager/src/main.cpp
	clang-format -i src/size_worker/src/main.cpp
	clang-format -i src/format_worker/src/main.cpp
	clang-format -i src/resolution_worker/src/main.cpp
	clang-format -i src/broker/src/main.cpp


down_graphite:
	if docker stack ls | grep -q graphite; then \
		docker stack rm graphite; \
		docker stack rm grafana; \
		docker stack rm cadvisor; \
	fi
.PHONY: down_graphite