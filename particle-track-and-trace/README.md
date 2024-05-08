## Vtk
This folder contains the Vtk program which actually displays the simulated data. The code is driven by the `Program` class, which contains the upper level of the vtk pipeline: the class has attributes for a vtkRenderWindow and vtkRenderWindowInteractor. vtkRenderers are managed through an abstract `Layer` class, which the program keeps track of trough a vector attribute.

Each layer implementation contains and manages one vtkRenderer, this includes managing which layer of the vtkrenderwindow ths layer renders to. Currently implemented are three such layers:
 * the `BackgroundImage` class reads in image data and displays this to the screen on the 0th layer - the background.
 * the `EGlyphLayer` class renders a visualization of the Eulerian flow-velocities as a grid of arrow-glyphs (in which the direction and length of the glyph represents the direction and strength of the velocity at that point).
 * the `LGlyphLayer` class renders a given set of particles as circular glyphs. These particles are advected according to an advection function, determined by an `AdvectionKernel`.

The `LGlyphLayer` deserves some more explanation, as it depends on the `SpawnpointCallback` class to place particles in its dataset. The `SpawnpointCallback` makes use of the vtkCallbackCommand class and the vtk observer pattern to create new particles on mouseclick. It does so through a shared reference to the LGlyphLayer's `data` and `points` attributes, which the SpawnpointCallback then edits directly. 

The program also adds a second observer to the vtk pattern through the `TimerCallbackCommand`. This class subscribes to a vtkTimerEvent to manage the simulation of the program. To this end the TimerCallbackCommand has attributes for a timestep (dt) and current time (time). On every callback, the current time is updated according to the dt attribute, and this change is propagated to the layers containing the data by use of the program and layers' `updateData()` functions.


## Location of data
The data path is hardcoded such that the following tree structure is assumed:
```
data/
  grid.h5
  hydrodynamic_U.h5
  hydrodynamic_V.h5
interactive-track-and-trace/
  particle-track-and-trace/
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

