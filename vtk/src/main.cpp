#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkCamera.h>
#include <vtkDoubleArray.h>
#include <vtkMapper2D.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkProperty.h>
#include <vtkRectilinearGrid.h>
#include <vtkRectilinearGridGeometryFilter.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

#include <netcdf>

#define NLATS 67
#define NLONS 116

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

tuple<vector<int>, vector<double>, vector<double>> readGrid() {
    netCDF::NcFile data("../../../../data/grid.h5", netCDF::NcFile::read);
    multimap< string, NcVar > vars = data.getVars();
    vector<int> time = getVarVector<int>(vars.find("times")->second);
    vector<double> longitude = getVarVector<double>(vars.find("longitude")->second);
    vector<double> latitude = getVarVector<double>(vars.find("latitude")->second);

    return {time, latitude, longitude};
}

int main() {
  vtkNew<vtkNamedColors> colors;


  vtkNew<vtkDoubleArray> pCoords;
  pCoords->SetNumberOfComponents(3);
  pCoords->SetNumberOfTuples(NLATS*NLONS);
  auto [times, lats, lons] = readGrid();

  double i = 0;
  for (double lat : lats) {
    for (double lon : lons) {
      pCoords->InsertTuple3(i++, 0, lat, lon);
    }
  }


  vtkNew<vtkPoints> points;
  points->SetData(pCoords);

  vtkNew<vtkPolyData> polydata;
  polydata->SetPoints(points);


  vtkNew<vtkPolyDataMapper2D> mapper;
  mapper->SetInputData(polydata);
  mapper->SetScalarRange(0, 40);

  vtkNew<vtkActor2D> actor;
  actor->SetMapper(mapper);

  vtkNew<vtkRenderer> ren;
  ren->AddActor(actor);
  ren->SetBackground(colors->GetColor3d("DarkSlateGray").GetData());

  vtkNew<vtkRenderWindow> renWin;
  renWin->AddRenderer(ren);
  renWin->SetSize(900, 600);

  vtkNew<vtkRenderWindowInteractor> iren;
  iren->SetRenderWindow(renWin);
  iren->Start();

  return EXIT_SUCCESS;
}

