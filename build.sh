mkdir -p ./build/Release
mkdir -p ./build/Debug

cd build/Release
cmake ../.. -D CMAKE_C_COMPILER=gcc -D CMAKE_CXX_COMPILER=g++ -DSQLITECPP_INTERNAL_SQLITE=ON
make