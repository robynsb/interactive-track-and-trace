## What is new?
There is one new added component: `AdvectionKernel`s which is an "interface" (i.e an abstract class).
There are two implementations simple Euler integration called `EulerIntegrationKernel` and 
Runge Kutta integration called `RK4AdvectionKernel`.

Main function gives a good example of how to use the library. Especially the following function which prints the
position of the particle at every time step.
```Cpp
template <typename AdvectionKernelImpl>
void advectForSomeTime(const UVGrid &uvGrid, const AdvectionKernelImpl &kernel, double latstart, double lonstart) {

    // Require at compile time that kernel derives from the abstract class AdvectionKernel
    static_assert(std::is_base_of<AdvectionKernel, AdvectionKernelImpl>::value, NotAKernelError);

    double lat1 = latstart, lon1 = lonstart;
    for(int time = 100; time <= 10000; time += AdvectionKernel::DT) {
        cout << "lat = " << lat1 << " lon = " << lon1 << endl;
        auto [templat, templon] = kernel.advect(time, lat1, lon1);
        lat1 = templat;
        lon1 = templon;
    }
}
```


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