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

using namespace std;



EGlyphLayer::EGlyphLayer() {
  this->ren = vtkSmartPointer<vtkRenderer>::New();
  this->ren->SetLayer(1);
  this->ren->InteractiveOff();

  this->data = vtkSmartPointer<vtkPolyData>::New();
  this->direction = vtkSmartPointer<vtkDoubleArray>::New();
  this->direction->SetName("direction");
  readCoordinates();
}


void EGlyphLayer::readCoordinates() {
  vtkNew<vtkPoints> points;
  auto [times, lats, lons] = readGrid(); // FIXME: import Robin's readData function and use it
  this->numLats = lats.size();
  this->numLons = lons.size();

  this->direction->SetNumberOfComponents(3);
  this->direction->SetNumberOfTuples(numLats*numLons); 
  points->Allocate(numLats*numLons);

  auto camera = createNormalisedCamera();
  ren->SetActiveCamera(camera);

  int i = 0;
  for (double lat : lats) {
    for (double lon : lons) {
        cout << "lon: " << lon << " lat: " << lat << endl;
      direction->SetTuple3(i, 0.45, 0.90, 0); //FIXME: read this info from file
      points->InsertPoint(i++, lon, lat, 0);
      // see also https://vtk.org/doc/nightly/html/classvtkPolyDataMapper2D.html
    }
  }
  this->data->SetPoints(points);
  this->data->GetPointData()->AddArray(this->direction);
  this->data->GetPointData()->SetActiveVectors("direction");

  vtkSmartPointer<vtkTransformFilter> transformFilter = createCartographicTransformFilter();
  transformFilter->SetInputData(data);

  vtkNew<vtkGlyphSource2D> arrowSource;
  arrowSource->SetGlyphTypeToArrow();
  arrowSource->SetScale(0.2); //TODO: set this properly
  arrowSource->Update();

  vtkNew<vtkGlyph2D> glyph2D;
  glyph2D->SetSourceConnection(arrowSource->GetOutputPort());
  glyph2D->SetInputConnection(transformFilter->GetOutputPort());
  glyph2D->OrientOn();
  glyph2D->ClampingOn();
  glyph2D->SetScaleModeToScaleByVector(); 
  glyph2D->SetVectorModeToUseVector(); 
  glyph2D->Update();

//  vtkNew<vtkCoordinate> coordinate;
//  coordinate->SetCoordinateSystemToWorld();

  vtkNew<vtkPolyDataMapper>(mapper);
  // mapper->SetTransformCoordinate(coordinate);
  mapper->SetInputConnection(glyph2D->GetOutputPort());
  mapper->Update();

  vtkNew<vtkActor> actor;
  actor->SetMapper(mapper);

  actor->GetProperty()->SetColor(0,0,0);
  actor->GetProperty()->SetOpacity(0.2);

  this->ren->AddActor(actor)  ;
}


void EGlyphLayer::updateData(int t) {
  for (int i=0; i < numLats*numLons; i++) {
    this->direction->SetTuple3(i, std::cos(t), std::sin(t), 0); // FIXME: fetch data from file.
  }
  this->direction->Modified();
}
