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