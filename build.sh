#!/bin/bash

if [ "$1" == "--clean-all" ]; then
  rm -rf ./build_stm
  rm -rf ./build_sim
  rm -rf ./build_tty
fi
if [ "$2" == "--clean-all" ]; then
  rm -rf ./build_stm
  rm -rf ./build_sim
  rm -rf ./build_tty
fi


build_stm() {
  if [ "$2" == "--clean" ]; then
    rm -rf ./build_stm
  fi

  mkdir -p build_stm
  cd ./build_stm

  run_cmake_configure() {
    cmake -DCMAKE_BUILD_TYPE=Release -S ../src/platform/stm -B .
  }
  run_cmake_build() {
    cmake --build . --config Release -- -j$(nproc)
  }


  run_cmake_configure || {
    run_cmake_configure; exit 1;
  }

  run_cmake_build > /dev/null 2>&1 || {
    run_cmake_build; exit 1;
  }

  cd ..

  echo "Done"
}


build_sim() {
  if [ "$2" == "--clean" ]; then
    rm -rf ./build_sim
  fi

  mkdir -p build_sim
  cd ./build_sim

  run_cmake_configure() {
    cmake -DCMAKE_BUILD_TYPE=Release -S ../src/platform/sim -B .
  }
  run_cmake_build() {
    cmake --build . --config Release -- -j$(nproc)
  }


  run_cmake_configure || {
    run_cmake_configure; exit 1;
  }

  run_cmake_build > /dev/null 2>&1 || {
    run_cmake_build; exit 1;
  }

  cd ..

  echo "Done"
}

build_tty() {
  if [ "$2" == "--clean" ]; then
    rm -rf ./build_tty
  fi

  mkdir -p build_tty
  cd ./build_tty

  run_cmake_configure() {
    cmake -DCMAKE_BUILD_TYPE=Debug -S ../src/platform/tty -B .
  }
  run_cmake_build() {
    cmake --build . --config Release -- -j$(nproc)
  }


  run_cmake_configure || {
    run_cmake_configure; exit 1;
  }

  run_cmake_build > /dev/null 2>&1 || {
    run_cmake_build; exit 1;
  }

  cd ..

  echo "Done"
}



build_and_flash_stm() {
	build_stm;
	./flash.sh > /dev/null 2>&1 || {
	./flash.sh || exit 1
	}
}

build_and_run_sim() {
	build_sim;
	./build_sim/ee-sim
}

build_and_run_tty() {
	build_tty;
	./build_tty/ee-tty
}



if [ "$1" == "sim" ]; then
  build_and_run_sim;
  exit 0;
fi

if [ "$1" == "stm" ]; then
  build_and_flash_stm;
  exit 0;
fi

if [ "$1" == "tty" ]; then
  build_and_run_tty;
  exit 0;
fi


# default:
build_and_run_sim;

