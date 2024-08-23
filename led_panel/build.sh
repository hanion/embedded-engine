if [ "$1" == "--clean" ]; then
  rm -rf ./build
fi

if [ ! -d "build" ]; then
  mkdir build
fi
cd ./build

cmake -DCMAKE_TOOLCHAIN_FILE=./cubeide-gcc.cmake -DCMAKE_BUILD_TYPE=Release .. > /dev/null 2>&1 || { 
  cmake -DCMAKE_TOOLCHAIN_FILE=./cubeide-gcc.cmake -DCMAKE_BUILD_TYPE=Release ..; exit 1; 
}

cmake --build . --config Release -- -j$(nproc) > /dev/null 2>&1 || { 
  cmake --build . --config Release -- -j$(nproc); exit 1; 
}

cd ..
./flash.sh > /dev/null 2>&1 || { 
  ./flash.sh; exit 1; 
}

