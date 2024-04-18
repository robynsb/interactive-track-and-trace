#include <iostream>
#include <mdspan>
#include <print>
#include <stdexcept>

#include <netcdf>

using namespace std;
using namespace netCDF;

template <typename T>
void printContentsOfVec(const std::vector<T>& vec) {
  for (const auto& element : vec) {
    cout << element << " ";
  }
  cout << std::endl;
}

template <typename T>
vector<T> getVarVector(NcVar var) {
  int length = 1;
  for (NcDim dim : var.getDims()) {
    length *= dim.getSize();
  }

  vector<T> vec(length);

  var.getVar(vec.data());

  return vec;
}

template <typename T>
using arr3d = std::mdspan<
                 T,
                 std::dextents<
                     std::size_t,
                     3
                 >
               >;


template <typename T>
void print3DMatrixSlice(arr3d<T> arr, int t) {
  for (int x = 0; x < arr.extent(1); x++) {
    for (int y = 0; y < arr.extent(2); y++) {
      print("{} ", arr[t,x,y]);
    }
    println("");
  }
}

void print3DMatrixSlice(arr3d<double> arr, int t) {
  for (int x = 0; x < arr.extent(1); x++) {
    for (int y = 0; y < arr.extent(2); y++) {
      print("{:>10.4f} ", arr[t,x,y]);
    }
    println("");
  }
}

/**
 * Read a 3D matrix from a NetCDF variable.
 * Reads data into a contiguous 1D data vector.
 * Returns a pair of the size of the matrix (in the form of an extent) with the data vector.
 *
 * Inteded usage of this function involves using the two returned values
 * to create an mdspan:
 *
 * auto arr = mdspan(vec.data(), size);
 */
template <typename T>
pair<vector<T>, std::dextents<std::size_t, 3>> get3DMat(NcVar var) {
  if(var.getDimCount() != 3) {
    throw invalid_argument("Variable is not 3D");
  }
  int timeLength = var.getDim(0).getSize();
  int latLength = var.getDim(1).getSize();
  int longLength = var.getDim(2).getSize();
  vector<T> vec(timeLength*latLength*longLength);
  var.getVar(vec.data());
  auto arr = std::mdspan(vec.data(), timeLength, latLength, longLength);

  return {vec, arr.extents()};
}

int main () {
  netCDF::NcFile data("../../../../data/hydrodynamic_U.h5", netCDF::NcFile::read);

  multimap< string, NcVar > vars = data.getVars();

  auto [vec, size] = get3DMat<double>(vars.find("uo")->second);

  auto arr = std::mdspan(vec.data(), size);

  print3DMatrixSlice(arr, 100);

  return 0;
}
