#!/bin/bash

if [ "$1" == "--clean-all" ]; then
  rm -rf ./build_stm
  rm -rf ./build_sim
fi
if [ "$2" == "--clean-all" ]; then
  rm -rf ./build_stm
  rm -rf ./build_sim
fi


build_stm() {
  if [ "$2" == "--clean" ]; then
    rm -rf ./build_stm
  fi

  mkdir -p build_stm
  cd ./build_stm

  run_cmake_configure() {
    cmake -DTARGET_PLATFORM=stm -DCMAKE_TOOLCHAIN_FILE=../src/platform/stm/cubeide-gcc.cmake -DCMAKE_BUILD_TYPE=Release -S ../src/platform/stm -B .
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

  #TODO: build for sim

  cd ..
}



if [ "$1" == "sim" ]; then
  build_sim;
  exit 0;
fi

if [ "$1" == "stm" ]; then
  build_stm;
  ./flash.sh > /dev/null 2>&1 || {
    ./flash.sh || exit 1
  }
  exit 0;
fi


# default: build and flash stm
build_stm;
./flash.sh > /dev/null 2>&1 || {
 ./flash.sh || exit 1
}

