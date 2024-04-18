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
Makes use of `mdspan` which is not supported by GCC libstdc++ at time of writing. See [compiler support](https://en.cppreference.com/w/cpp/compiler_support/23) for `mdspan`. Probably you will need to install Clang libc++.

