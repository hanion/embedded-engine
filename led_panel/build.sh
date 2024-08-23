if [ ! -d "build" ]; then
  mkdir build
fi
cd ./build
cmake -DCMAKE_TOOLCHAIN_FILE=./cubeide-gcc.cmake .. > /dev/null 2>&1 || { cmake -DCMAKE_TOOLCHAIN_FILE=./cubeide-gcc.cmake ..; exit 1; }
cmake --build . > /dev/null 2>&1 || { cmake --build .; exit 1; }
cd ..
./flash.sh > /dev/null 2>&1 || { ./flash.sh; exit 1; }

