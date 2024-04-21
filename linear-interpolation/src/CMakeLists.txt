cmake_minimum_required (VERSION 3.28)
project (LinearInterpolate)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Force use of libc++ for mdspan support
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ ")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(netCDF REQUIRED)

add_executable(LinearInterpolate main.cpp
        readdata.cpp
        readdata.h
        vecutils.cpp
        vecutils.h)

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

target_include_directories(LinearInterpolate PUBLIC ${netCDF_INCLUDE_DIR})

find_library(NETCDF_LIB NAMES netcdf-cxx4 netcdf_c++4 PATHS ${NETCDFCXX_LIB_DIR} NO_DEFAULT_PATH)
target_link_libraries(LinearInterpolate ${NETCDF_LIB})
