## Location of data
The data path is hardcoded such that the following tree structure is assumed:
```
data/
  grid.h5
  hydrodynamic_U.h5
  hydrodynamic_V.h5
interactive-track-and-trace/
  opening-hdf5/
     ...
```

## Compiling
Let the current directory be the `src` directory. Run:
```shell
mkdir build
cd build
cmake ..
make
```

### Building with Linux
Makes use of `mdspan` which is not supported by glibc++ at time of writing. See [compiler support](https://en.cppreference.com/w/cpp/compiler_support/23) for `mdspan`. The solution to this is to use Clang and libc++; this is configured in our CMake setup, however the default installation of the `netcdf-cxx` package on at least Arch linux (and suspectedly Debian derivatives as well) specifically builds for the glibc implementation. To get the netcdf C++ bindings functional with the libc++ implementation, one needs to build from source. On Linux, this requires a few changes to the CMake file included with the netcdf-cxx source code, which are detailed below.

Step-by-step to build the program using clang++ and libc++ on linux:
 1. Download the source code of netcdf-cxx, found at 'https://github.com/Unidata/netcdf-cxx4/releases/tag/v4.3.1' (make sure to download the release source code, as the master branch contains non-compilable code).
 2. Edit the CMakeLists.txt file, by appending '-stdlib=libc++' to the `CMAKE_CXX_FLAGS` variable in line 430. This means line 430 should read: 
    ```cmake 
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wno-unused-variable -Wno-unused-parameter -stdlib=libc++")
    ```
 2. Build the source code with the following: 
  ```sh 
    mkdir build && cd build
    cmake .. -DCMAKE_CXX_COMPILER=/usr/bin/clang++
    make
    ctest
    sudo make install
  ```
 3. Now the code should compile through the standard steps described in the Compiling section.
