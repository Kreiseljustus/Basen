@echo off

cmake -S ../Vendor/Assimp -B ../Vendor/Assimp/build ^
  -G "Visual Studio 17 2022" -A x64 ^
  -DASSIMP_BUILD_SHARED_LIBS=OFF ^
  -DASSIMP_BUILD_TESTS=OFF ^
  -DASSIMP_BUILD_SAMPLES=OFF

cmake --build ../Vendor/Assimp/build --config Debug
cmake --build ../Vendor/Assimp/build --config Release
