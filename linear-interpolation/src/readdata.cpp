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

vector<double> readHydrodynamicU() {
    netCDF::NcFile data("../../../../data/hydrodynamic_U.h5", netCDF::NcFile::read);

    multimap< string, NcVar > vars = data.getVars();

    return getVarVector<double>(vars.find("uo")->second);
}

vector<double> readHydrodynamicV() {
    netCDF::NcFile data("../../../../data/hydrodynamic_V.h5", netCDF::NcFile::read);

    multimap< string, NcVar > vars = data.getVars();

    return getVarVector<double>(vars.find("vo")->second);
}

tuple<vector<int>, vector<double>, vector<double>> readGrid() {
    netCDF::NcFile data("../../../../data/grid.h5", netCDF::NcFile::read);
    multimap< string, NcVar > vars = data.getVars();
    vector<int> time = getVarVector<int>(vars.find("times")->second);
    vector<double> longitude = getVarVector<double>(vars.find("longitude")->second);
    vector<double> latitude = getVarVector<double>(vars.find("latitude")->second);

    return {time, latitude, longitude};
}
