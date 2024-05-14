#include "EGlyphLayer.h"
#include <vtkPointData.h>
#include <vtkDoubleArray.h>
#include <vtkGlyphSource2D.h>
#include <vtkRegularPolygonSource.h>
#include <vtkGlyph2D.h>
#include <vtkActor2D.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkProperty2D.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkArrowSource.h>

#include "../CartographicTransformation.h"
#include "../advection/readdata.h"
#include "../advection/interpolate.h"

#include "vtkTransform.h"

using namespace std;

EGlyphLayer::EGlyphLayer(std::shared_ptr<UVGrid> uvGrid) {
  this->ren = vtkSmartPointer<vtkRenderer>::New();
  this->ren->SetLayer(1);
  this->ren->InteractiveOff();

  this->uvGrid = uvGrid;

  this->data = vtkSmartPointer<vtkPolyData>::New();
  this->direction = vtkSmartPointer<vtkDoubleArray>::New();
  this->direction->SetName("direction");
  readCoordinates();
}


void EGlyphLayer::readCoordinates() {
  vtkNew<vtkPoints> points;
  this->numLats = uvGrid->lats.size();
  this->numLons = uvGrid->lons.size();

  this->direction->SetNumberOfComponents(3);
  this->direction->SetNumberOfTuples(numLats * numLons);
  points->Allocate(numLats * numLons);

  vtkSmartPointer<vtkTransformFilter> filter = createCartographicTransformFilter(uvGrid);
  auto transform = filter->GetTransform();

  int i = 0;
  int latIndex = 0;
  for (double lat: uvGrid->lats) {
    int lonIndex = 0;
    for (double lon: uvGrid->lons) {
      auto [u, v] = (*uvGrid)[0, latIndex, lonIndex];
      direction->SetTuple3(i, u/2, v/2, 0);
      // pre-transform the points, so we don't have to include the cartographic transform while running the program.
      double out[3] = {lon, lat, 0};
      transform->TransformPoint(out, out);
      points->InsertPoint(i++, out[0], out[1], 0);
      lonIndex++;
    }
    latIndex++;
  }

  this->data->SetPoints(points);
  this->data->GetPointData()->AddArray(this->direction);
  this->data->GetPointData()->SetActiveVectors("direction");

  vtkNew<vtkGlyphSource2D> arrowSource;
  arrowSource->SetGlyphTypeToArrow();
  arrowSource->SetScale(0.2); //TODO: set this properly
  arrowSource->Update();

  vtkNew<vtkGlyph2D> glyph2D;
  glyph2D->SetSourceConnection(arrowSource->GetOutputPort());
  glyph2D->SetInputData(data);
  glyph2D->OrientOn();
  glyph2D->ClampingOn();
  glyph2D->SetScaleModeToScaleByVector();
  glyph2D->SetVectorModeToUseVector();
  glyph2D->Update();

  vtkNew<vtkPolyDataMapper>mapper;
  mapper->SetInputConnection(glyph2D->GetOutputPort());
  mapper->Update();

  vtkNew<vtkActor> actor;
  actor->SetMapper(mapper);

  actor->GetProperty()->SetColor(0, 0, 0);
  actor->GetProperty()->SetOpacity(0.2);

  this->ren->AddActor(actor);
}


void EGlyphLayer::updateData(int t) {
  int i = 0;
  for (int lat = 0; lat < uvGrid->latSize; lat++) {
    for (int lon = 0; lon < uvGrid->lonSize; lon++) {
      auto [u, v] = (*uvGrid)[t/3600, lat, lon];
      // TODO: 5*v scaling stuff should really be a filter transform
      this->direction->SetTuple3(i, u/2, v/2, 0);
      i++;
    }
  }
  this->direction->Modified();
}
