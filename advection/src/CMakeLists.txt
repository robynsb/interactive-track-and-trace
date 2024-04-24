cmake_minimum_required (VERSION 3.28)
project (Advection)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(netCDF REQUIRED)

add_executable(Advection main.cpp
        readdata.cpp
        readdata.h
        interpolate.cpp
        interpolate.h
        UVGrid.cpp
        UVGrid.h
        Vel.h
        Vel.cpp
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

target_include_directories(Advection PUBLIC ${netCDF_INCLUDE_DIR})

find_library(NETCDF_LIB NAMES netcdf-cxx4 netcdf_c++4 PATHS ${NETCDFCXX_LIB_DIR} NO_DEFAULT_PATH)
target_link_libraries(Advection ${NETCDF_LIB})
