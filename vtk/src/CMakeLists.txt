cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(VtkBase)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(VTK COMPONENTS 
  CommonColor
  CommonColor
  CommonCore
  CommonDataModel
  FiltersGeneral
  FiltersGeometry
  FiltersProgrammable
  FiltersSources
  ImagingSources
  InteractionStyle
  IOImage
  RenderingContextOpenGL2
  RenderingCore
  RenderingCore
  RenderingFreeType
  RenderingGL2PSOpenGL2
  RenderingOpenGL2)


if (NOT VTK_FOUND)
  message(FATAL_ERROR "VtkBase: Unable to find the VTK build folder.")
endif()

# netcdf setup
find_package(netCDF REQUIRED)

add_executable(VtkBase MACOSX_BUNDLE main.cpp 
  helperClasses/BackgroundImage.cpp 
  helperClasses/BackgroundImage.h
  helperClasses/EGlyphLayer.cpp
  helperClasses/EGlyphLayer.h
  helperClasses/Layer.cpp
  helperClasses/Layer.h
  helperClasses/LGlyphLayer.cpp
  helperClasses/LGlyphLayer.h
  helperClasses/Program.cpp
  helperClasses/Program.h
  commands/TimerCallbackCommand.h
  commands/TimerCallbackCommand.cpp
        helperClasses/SpawnPointCallback.h
        helperClasses/SpawnPointCallback.cpp
)

execute_process(
    COMMAND nc-config --includedir
    OUTPUT_VARIABLE NETCDF_INCLUDE_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
    COMMAND ncxx4-config --libdir
    OUTPUT_VARIABLE NETCDFCXX_LIB_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

target_include_directories(VtkBase PUBLIC ${netCDF_INCLUDE_DIR})

find_library(NETCDF_LIB NAMES netcdf-cxx4 netcdf_c++4 PATHS ${NETCDFCXX_LIB_DIR} NO_DEFAULT_PATH)

# Prevent a "command line is too long" failure in Windows.
set(CMAKE_NINJA_FORCE_RESPONSE_FILE "ON" CACHE BOOL "Force Ninja to use response files.")
target_link_libraries(VtkBase ${NETCDF_LIB} ${VTK_LIBRARIES})

# vtk_module_autoinit is needed
vtk_module_autoinit(
  TARGETS VtkBase
  MODULES ${VTK_LIBRARIES}
)
