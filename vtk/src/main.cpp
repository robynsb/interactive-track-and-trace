#include <netcdf>
#include <vector>
#include <vtkActor2D.h>
#include <vtkNamedColors.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkProperty2D.h>
#include <vtkRenderer.h>
#include <vtkVertexGlyphFilter.h>

#include "helperClasses/BackgroundImage.h"
#include "helperClasses/EGlyphLayer.h"
#include "helperClasses/Program.h"

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


void renderCoordinates(vtkRenderer *ren, vtkNamedColors *colors) {

  vtkNew<vtkPoints> points;
  auto [times, lats, lons] = readGrid();

  double i = 0;
  for (double lat : lats) {
    for (double lon : lons) {
      cout << "lat: " << (lat*1000-46125)*661/16500 << "\t lon: " << (lon*1000+15875)*661/28750 << endl;
      points->InsertNextPoint((lat*1000-46125)*661/16500, (lon*1000+15875)*661/28750, 0);
    }
  }

  vtkNew<vtkPolyData> polydata;
  polydata->SetPoints(points);


  vtkNew<vtkVertexGlyphFilter> glyphFilter;
  glyphFilter->SetInputData(polydata);
  glyphFilter->Update();

  vtkNew<vtkPolyDataMapper2D> mapper;
  mapper->SetInputConnection(glyphFilter->GetOutputPort());
  mapper->Update();

  vtkNew<vtkActor2D> actor;
  actor->SetMapper(mapper);
  actor->GetProperty()->SetColor(colors->GetColor3d("Gold").GetData());
  actor->GetProperty()->SetPointSize(3);

  ren->AddActor(actor);
}


int main() {
  auto bg = new BackgroundImage("../../../../data/map_661-661.png");
  auto e = new EGlyphLayer();
  auto l = new EGlyphLayer();
  auto program = new Program(*bg, *e, *l);
  program->render();


  // vtkNew<vtkNamedColors> colors;
  // vtkNew<vtkRenderer> Euler, Background, Lagrange;
  // Euler->SetBackground(colors->GetColor3d("DarkSlateGray").GetData());


  // renderCoordinates(Euler, colors);

  return EXIT_SUCCESS;
}

