#include <print>
#include <stdexcept>

#include <netcdf>

#include "readdata.h"

using namespace std;
using namespace netCDF;

template <typename T>
vector<T> getVarVector(const NcVar &var) {
    int length = 1;
    for (NcDim dim : var.getDims()) {
        length *= dim.getSize();
    }

    vector<T> vec(length);

    var.getVar(vec.data());

    return vec;
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
pair<vector<T>, std::dextents<std::size_t, 3>> get3DMat(const NcVar &var) {
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

pair<vector<double>, std::dextents<std::size_t, 3>> readHydrodynamicU() {
    netCDF::NcFile data("../../../../data/hydrodynamic_U.h5", netCDF::NcFile::read);

    multimap< string, NcVar > vars = data.getVars();

    return get3DMat<double>(vars.find("uo")->second);
}

pair<vector<double>, std::dextents<std::size_t, 3>> readHydrodynamicV() {
    netCDF::NcFile data("../../../../data/hydrodynamic_V.h5", netCDF::NcFile::read);

    multimap< string, NcVar > vars = data.getVars();

    return get3DMat<double>(vars.find("vo")->second);
}

tuple<vector<int>, vector<double>, vector<double>> readGrid() {
    netCDF::NcFile data("../../../../data/grid.h5", netCDF::NcFile::read);
    multimap< string, NcVar > vars = data.getVars();
    vector<int> time = getVarVector<int>(vars.find("times")->second);
    vector<double> longitude = getVarVector<double>(vars.find("longitude")->second);
    vector<double> latitude = getVarVector<double>(vars.find("latitude")->second);

    return {time, latitude, longitude};
}