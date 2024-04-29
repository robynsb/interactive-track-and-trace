#include "EGlyphLayer.h"
#include <vtkRegularPolygonSource.h>
#include <vtkGlyph2D.h>
#include <vtkActor2D.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkProperty2D.h>
#include <vtkVertexGlyphFilter.h>
#include <netcdf>
#include <vtkArrowSource.h>

using namespace netCDF;
using namespace std;

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




EGlyphLayer::EGlyphLayer() {
  this->ren = vtkSmartPointer<vtkRenderer>::New();
  this->ren->SetLayer(1);
  this->ren->InteractiveOff();

  this->data = vtkSmartPointer<vtkPolyData>::New();
  readCoordinates();
}


void EGlyphLayer::readCoordinates() {
  vtkNew<vtkPoints> points;
  auto [times, lats, lons] = readGrid(); // FIXME: import Robin's readData function and use it

  double i = 0;
  for (double lat : lats) {
    for (double lon : lons) {
      //FIXME: hard-coded values; should update with window geometry.
      points->InsertNextPoint((lat*1000-46125)*661/16500, (lon*1000+15875)*661/28750, 0);
    }
  }
  this->data->SetPoints(points);

  // vtkNew<vtkArrowSource> arrowSource;
  vtkNew<vtkRegularPolygonSource> arrowSource;
  vtkNew<vtkGlyph2D> glyph2D;
  glyph2D->SetSourceConnection(arrowSource->GetOutputPort());
  glyph2D->SetInputData(this->data);
  glyph2D->Update();

  vtkNew<vtkPolyDataMapper>(mapper);
  mapper->SetInputConnection(glyph2D->GetOutputPort());
  mapper->Update();

  vtkNew<vtkActor> actor;
  actor->SetMapper(mapper);

  vtkNew<vtkNamedColors> colors;
  actor->GetProperty()->SetColor(colors->GetColor3d("Salmon").GetData());

  this->ren->AddActor(actor);
  
  // vtkNew<vtkVertexGlyphFilter> glyphFilter;
  // glyphFilter->SetInputData(this->data);
  // glyphFilter->Update();
  //
  // vtkNew<vtkPolyDataMapper2D> mapper;
  // mapper->SetInputConnection(glyphFilter->GetOutputPort());
  // mapper->Update();
  //
  // vtkNew<vtkNamedColors> colors;
  // vtkNew<vtkActor2D> actor;
  // actor->SetMapper(mapper);
  // actor->GetProperty()->SetColor(colors->GetColor3d("Gold").GetData());
  // actor->GetProperty()->SetPointSize(3);
  //
  // this->ren->AddActor(actor);
}


void EGlyphLayer::updateData(short t) {

}
